/*
 * Copyright 2020, 2022-2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "rpmsg_lite.h"
#include "fsl_component_generic_list.h"
#include "fsl_adapter_rpmsg.h"
#include "mcmgr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Weak function. */
#if defined(__GNUC__)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__ICCARM__)
#define __WEAK_FUNC __weak
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__DSC__) || defined(__CW__)
#define __WEAK_FUNC __attribute__((weak))
#endif

typedef struct _hal_rpmsg_rx_state
{
    rpmsg_rx_callback_t callback;
    void *param;
} hal_rpmsg_rx_state_t;

/*! @brief rpmsg state structure. */
typedef struct _hal_rpmsg_state
{
    uint8_t local_addr;
    uint8_t remote_addr;
    volatile uint8_t rpmsg_lite_peer_ept_is_ready;
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
    struct rpmsg_lite_ept_static_context endpoint;
#endif
    struct rpmsg_lite_endpoint *pEndpoint;
    hal_rpmsg_rx_state_t rx;
} hal_rpmsg_state_t;

typedef struct _hal_rpmsg_peer_ept_state
{
    list_element_t link;
    hal_rpmsg_state_t *rpmsgHandle;
} hal_rpmsg_peer_ept_state;

#ifndef RPMSG_GLOBAL_VARIABLE_ALLOC
#if (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 0U))
#define SH_MEM_TOTAL_SIZE (6144U)
#if defined(__ICCARM__) /* IAR Workbench */
#pragma location = "rpmsg_sh_mem_section"
static char rpmsg_lite_base[SH_MEM_TOTAL_SIZE];
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION) /* Keil MDK */
static char rpmsg_lite_base[SH_MEM_TOTAL_SIZE] __attribute__((section("rpmsg_sh_mem_section")));
#elif defined(__GNUC__)
static char rpmsg_lite_base[SH_MEM_TOTAL_SIZE] __attribute__((section(".noinit.$rpmsg_sh_mem")));
#else
#error "RPMsg: Please provide your definition of rpmsg_lite_base[]!"
#endif
#endif /* HAL_RPMSG_SELECT_ROLE */

extern uint32_t rpmsg_sh_mem_start[];
extern uint32_t rpmsg_sh_mem_end[];
#else

#if (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 0U))
#define SH_MEM_TOTAL_SIZE (6144U)
extern char *rpmsg_lite_base;
#endif /* HAL_RPMSG_SELECT_ROLE */

extern uint32_t rpmsg_sh_mem_start[];
extern uint32_t rpmsg_sh_mem_end[];
#endif /* RPMSG_GLOBAL_VARIABLE_ALLOC */

#define RPMSG_LITE_LINK_ID (0U)

#define APP_RPMSG_COREUP_EVENT_DATA   (0U)
#define APP_RPMSG_READY_EVENT_DATA    (1U)
#define APP_RPMSG_EP_READY_EVENT_DATA (2U)

#ifndef RPMSG_REMOTE_READY_RETRY_COUNT
#define RPMSG_REMOTE_READY_RETRY_COUNT 10000000U
#endif

static int32_t s_rpmsgEptCount                    = -1;
static uint8_t s_peerRpmsgEptCount                = 0U;
static struct rpmsg_lite_instance *s_rpmsgContext = NULL;
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
static struct rpmsg_lite_instance s_context = {0};
#endif
static uint8_t s_rpmsg_init_golbal                               = 0U;
static list_label_t s_rpmsgEpList                                = {0};
static volatile uint8_t s_rpmsgPeerEptData[MAX_EP_COUNT]         = {0};
static hal_rpmsg_peer_ept_state s_rpmsgPeerEptStat[MAX_EP_COUNT] = {0};
/*******************************************************************************
 * Code
 ******************************************************************************/
/*
 * This function is used for periodic check if the rpmsg endpoint is ready, and will be called in rpmsg send..
 * RPMsg_EpReadyTimeDelay is a weak function, so it could be re-implemented by
 * upper layer.
 */
__WEAK_FUNC void RPMsg_EpReadyTimeDelay(uint32_t ms);
__WEAK_FUNC void RPMsg_EpReadyTimeDelay(uint32_t ms)
{
    /* Reserved*/
}
#if 0  /* Reserved API */
static uint16_t rpmsg_lite_recv_ack_flag;

void rpmsg_ack_init(void)
{
    rpmsg_lite_recv_ack_flag = 0U;
    (void)MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, RPMsgPeerReadyEventHandler,
                              (void *)&rpmsg_lite_recv_ack_flag);
}

void rpmsg_recv_ack(void)
{
    (void)MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, 1U);
}

void rpmsg_wait_ack(void)
{
    while (1U != rpmsg_lite_recv_ack_flag)
        ;
}
#endif /* Reserved API */

static int32_t rpmsg_ept_read_cb(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    hal_rpmsg_state_t *rpmsgHandle;

    rpmsgHandle = (hal_rpmsg_state_t *)priv;
    assert(NULL != rpmsgHandle->rx.callback);

    return rpmsgHandle->rx.callback(rpmsgHandle->rx.param, payload, payload_len);
}

static void RPMsgPeerReadyEventHandler(uint16_t eventData, void *context)
{
    uint16_t *data = (uint16_t *)context;
    list_element_handle_t list_element;
    hal_rpmsg_peer_ept_state *rpmsgPeerEptState;
    uint8_t address = 0U;

    if ((eventData & 0xff00U) == APP_RPMSG_EP_READY_EVENT_DATA << 0x8U)
    {
        address                                   = eventData & 0xffU;
        s_rpmsgPeerEptData[s_peerRpmsgEptCount++] = address;
    }

    list_element = LIST_GetHead(&s_rpmsgEpList);
    while (NULL != list_element)
    {
        rpmsgPeerEptState = (hal_rpmsg_peer_ept_state *)(void *)list_element;

        if (rpmsgPeerEptState->rpmsgHandle->remote_addr == address)
        {
            rpmsgPeerEptState->rpmsgHandle->rpmsg_lite_peer_ept_is_ready = 1U;
        }
        list_element = LIST_GetNext(list_element);
    }

    *data = eventData;
}

#if (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 0U))
static hal_rpmsg_status_t HAL_RpmsgMcmgrMasterInit(void)
{
    static volatile uint16_t RPMsgRemoteReadyEventData = 0;
    volatile uint32_t timeout                          = RPMSG_REMOTE_READY_RETRY_COUNT;

    if (0 > s_rpmsgEptCount)
    {
        if (0U == s_rpmsg_init_golbal)
        {
            s_rpmsg_init_golbal = 1U;
            LIST_Init((&s_rpmsgEpList), 0);
            (void)MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, RPMsgPeerReadyEventHandler,
                                      (void *)&RPMsgRemoteReadyEventData);
            (void)MCMGR_Init();
            if (MCMGR_StartCore(kMCMGR_Core1, (void *)(char *)REMOTE_CORE_BOOT_ADDRESS, 2, kMCMGR_Start_Asynchronous) !=
                kStatus_MCMGR_Success)
            {
                return kStatus_HAL_RpmsgError;
            }
        }

        while ((APP_RPMSG_READY_EVENT_DATA != RPMsgRemoteReadyEventData) && (--timeout != 0u))
        {
        };
        RPMsgRemoteReadyEventData = 0;
        if (timeout == 0u)
        {
            return kStatus_HAL_RpmsgTimeout;
        }

        /* Master init */
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
        s_rpmsgContext = rpmsg_lite_master_init((void *)rpmsg_lite_base, SH_MEM_TOTAL_SIZE, RPMSG_LITE_LINK_ID,
                                                RL_NO_FLAGS, &s_context);
#else
        s_rpmsgContext =
            rpmsg_lite_master_init((void *)rpmsg_lite_base, SH_MEM_TOTAL_SIZE, RPMSG_LITE_LINK_ID, RL_NO_FLAGS);
#endif
        if (RL_NULL == s_rpmsgContext)
        {
            return kStatus_HAL_RpmsgError;
        }

        s_rpmsgEptCount = 0;
    }

    return kStatus_HAL_RpmsgSuccess;
}
static hal_rpmsg_status_t HAL_RpmsgMasterInit(hal_rpmsg_handle_t handle, hal_rpmsg_config_t *config)
{
    hal_rpmsg_state_t *rpmsgHandle;
    rpmsgHandle = (hal_rpmsg_state_t *)handle;

    rpmsgHandle->local_addr  = config->local_addr;
    rpmsgHandle->remote_addr = config->remote_addr;

    rpmsgHandle->rx.callback = NULL;
    rpmsgHandle->rx.param    = NULL;
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
    rpmsgHandle->pEndpoint = rpmsg_lite_create_ept(s_rpmsgContext, rpmsgHandle->local_addr, rpmsg_ept_read_cb,
                                                   rpmsgHandle, &rpmsgHandle->endpoint);
#else
    rpmsgHandle->pEndpoint =
        rpmsg_lite_create_ept(s_rpmsgContext, rpmsgHandle->local_addr, rpmsg_ept_read_cb, rpmsgHandle);
#endif
    if (RL_NULL == rpmsgHandle->pEndpoint)
    {
        return kStatus_HAL_RpmsgError;
    }

    return kStatus_HAL_RpmsgSuccess;
}
#endif /* HAL_RPMSG_SELECT_ROLE */

#if (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 1U))
static hal_rpmsg_status_t HAL_RpmsgMcmgrRemoteInit()
{
    uint32_t startupData;
    mcmgr_status_t status;
    volatile static uint16_t RPMsgRemoteReadyEventData = 0;

    if (0 > s_rpmsgEptCount)
    {
        if (0U == s_rpmsg_init_golbal)
        {
            LIST_Init((&s_rpmsgEpList), 0);
            s_rpmsg_init_golbal = 1U;
            (void)MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, RPMsgPeerReadyEventHandler,
                                      (void *)&RPMsgRemoteReadyEventData);
            (void)MCMGR_Init();
            do
            {
                status = MCMGR_GetStartupData(&startupData);
            } while (status != kStatus_MCMGR_Success);
        }
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
        s_rpmsgContext =
            rpmsg_lite_remote_init((void *)(char *)rpmsg_sh_mem_start, RPMSG_LITE_LINK_ID, RL_NO_FLAGS, &s_context);
#else
        s_rpmsgContext = rpmsg_lite_remote_init((void *)(char *)rpmsg_sh_mem_start, RPMSG_LITE_LINK_ID, RL_NO_FLAGS);

#endif
        if (RL_NULL == s_rpmsgContext)
        {
            return kStatus_HAL_RpmsgError;
        }

        /* Trigger event notify master */
        (void)MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, APP_RPMSG_READY_EVENT_DATA);
        do
        {
        } while (RL_TRUE != rpmsg_lite_is_link_up(s_rpmsgContext));

        /* rpmsg initialized */
        s_rpmsgEptCount = 0;
    }
    return kStatus_HAL_RpmsgSuccess;
}
static hal_rpmsg_status_t HAL_RpmsgRemoteInit(hal_rpmsg_handle_t handle, hal_rpmsg_config_t *config)
{
    hal_rpmsg_state_t *rpmsgHandle;

    rpmsgHandle = (hal_rpmsg_state_t *)handle;

    /* Set local/remote addr */
    rpmsgHandle->local_addr  = config->local_addr;
    rpmsgHandle->remote_addr = config->remote_addr;

    rpmsgHandle->rx.callback = NULL;
    rpmsgHandle->rx.param    = NULL;
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
    rpmsgHandle->pEndpoint = rpmsg_lite_create_ept(s_rpmsgContext, rpmsgHandle->local_addr, rpmsg_ept_read_cb,
                                                   rpmsgHandle, &rpmsgHandle->endpoint);
#else
    rpmsgHandle->pEndpoint =
        rpmsg_lite_create_ept(s_rpmsgContext, rpmsgHandle->local_addr, rpmsg_ept_read_cb, rpmsgHandle);
#endif

    if (RL_NULL == rpmsgHandle->pEndpoint)
    {
        return kStatus_HAL_RpmsgError;
    }

    return kStatus_HAL_RpmsgSuccess;
}
#endif /* HAL_RPMSG_SELECT_ROLE */

hal_rpmsg_status_t HAL_RpmsgMcmgrInit(void)
{
    hal_rpmsg_status_t state;
    if (0U == s_rpmsg_init_golbal)
    {
        (void)MCMGR_EarlyInit();
    }

#if (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 0U))
    state = HAL_RpmsgMcmgrMasterInit();
#elif (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 1U))
    state = HAL_RpmsgMcmgrRemoteInit();
#endif /* HAL_RPMSG_SELECT_ROLE */

    return state;
}
hal_rpmsg_status_t HAL_RpmsgInit(hal_rpmsg_handle_t handle, hal_rpmsg_config_t *config)
{
    hal_rpmsg_status_t state;
    hal_rpmsg_state_t *rpmsgHandle;
    uint8_t count = 0;

    assert(HAL_RPMSG_HANDLE_SIZE >= sizeof(hal_rpmsg_state_t));
    assert(NULL != handle);
    rpmsgHandle = (hal_rpmsg_state_t *)handle;

#if (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 0U))
    state = HAL_RpmsgMasterInit(handle, config);
#elif (defined(HAL_RPMSG_SELECT_ROLE) && (HAL_RPMSG_SELECT_ROLE == 1U))
    state = HAL_RpmsgRemoteInit(handle, config);
#endif /* HAL_RPMSG_SELECT_ROLE */
    rpmsgHandle->rx.callback = config->callback;
    rpmsgHandle->rx.param    = config->param;

    /* Send peer Edpt ready to peer device */
    (void)MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, APP_RPMSG_EP_READY_EVENT_DATA << 0x8U | config->local_addr);
    s_rpmsgPeerEptStat[s_rpmsgEptCount].rpmsgHandle = rpmsgHandle;
    (void)LIST_AddTail(&s_rpmsgEpList, (list_element_handle_t)&s_rpmsgPeerEptStat[s_rpmsgEptCount]);
    s_rpmsgEptCount++;

    while (count < s_peerRpmsgEptCount)
    {
        if (rpmsgHandle->remote_addr == s_rpmsgPeerEptData[count++])
        {
            rpmsgHandle->rpmsg_lite_peer_ept_is_ready = 1U;
        }
    }

    return state;
}

hal_rpmsg_status_t HAL_RpmsgDeinit(hal_rpmsg_handle_t handle)
{
    hal_rpmsg_state_t *rpmsgHandle;

    rpmsgHandle = (hal_rpmsg_state_t *)handle;

    if (s_rpmsgEptCount > 0)
    {
        (void)rpmsg_lite_destroy_ept(s_rpmsgContext, rpmsgHandle->pEndpoint);
        s_rpmsgEptCount--;
    }

    if (0 == s_rpmsgEptCount)
    {
        s_rpmsgEptCount = -1;
        (void)rpmsg_lite_deinit(s_rpmsgContext);
        for (int i = 0; i < MAX_EP_COUNT; i++)
        {
            s_rpmsgPeerEptData[i] = 0U;
        }
    }

    return kStatus_HAL_RpmsgSuccess;
}

hal_rpmsg_status_t HAL_RpmsgSendTimeout(hal_rpmsg_handle_t handle, uint8_t *data, uint32_t length, uint32_t timeout)
{
    hal_rpmsg_state_t *rpmsgHandle;
    hal_rpmsg_status_t status = kStatus_HAL_RpmsgSuccess;

#if defined(HDI_MODE) && (HDI_MODE == 1)
    uint32_t primask;
#endif

    int32_t rpmsgStatus;
    volatile uint32_t epTimeout = RPMSG_REMOTE_READY_RETRY_COUNT;
    assert(NULL != data);

    rpmsgHandle = (hal_rpmsg_state_t *)handle;
    /* loop check peer device rpmsg endpoint is ready */
    while ((0 == rpmsgHandle->rpmsg_lite_peer_ept_is_ready) && (--epTimeout != 0u))
    {
    }
    if (epTimeout == 0u)
    {
        return kStatus_HAL_RpmsgTimeout;
    }

#if defined(HDI_MODE) && (HDI_MODE == 1)
    /* In HDI mode this function can be called from ISR therefore,
     * we need to disable interrupt when this configuration is enabled */
    primask = DisableGlobalIRQ();
#endif

    do
    {
        if (RL_TRUE != rpmsg_lite_is_link_up(s_rpmsgContext))
        {
            status = kStatus_HAL_RpmsgError;
            break;
        }
        rpmsgStatus = rpmsg_lite_send(s_rpmsgContext, rpmsgHandle->pEndpoint, rpmsgHandle->remote_addr, (char *)data,
                                      length, timeout);
        if (RL_SUCCESS != rpmsgStatus)
        {
            if (RL_ERR_NO_MEM == rpmsgStatus)
            {
                status = kStatus_HAL_RpmsgTimeout;
            }
            else
            {
                status = kStatus_HAL_RpmsgError;
            }
            break;
        }
    } while (false);

#if defined(HDI_MODE) && (HDI_MODE == 1)
    EnableGlobalIRQ(primask);
#endif

    return status;
}
hal_rpmsg_status_t HAL_RpmsgSend(hal_rpmsg_handle_t handle, uint8_t *data, uint32_t length)
{
    return HAL_RpmsgSendTimeout(handle, data, length, RPMSG_WAITFOREVER);
}

void *HAL_RpmsgAllocTxBuffer(hal_rpmsg_handle_t handle, uint32_t size)
{
    return HAL_RpmsgAllocTxBufferTimeout(handle, size, RPMSG_WAITFOREVER);
}

void *HAL_RpmsgAllocTxBufferTimeout(hal_rpmsg_handle_t handle, uint32_t size, uint32_t timeout)
{
    void *buf = NULL;
#if defined(HDI_MODE) && (HDI_MODE == 1)
    /* In HDI mode this function can be called from ISR therefore, 
     * we need to disable interrupt when this configuration is enabled */
    uint32_t primask;
    primask = DisableGlobalIRQ();
#endif
    buf     = rpmsg_lite_alloc_tx_buffer(s_rpmsgContext, &size, timeout);
#if defined(HDI_MODE) && (HDI_MODE == 1)
    EnableGlobalIRQ(primask);
#endif
    return buf;
}

hal_rpmsg_status_t HAL_RpmsgFreeRxBuffer(hal_rpmsg_handle_t handle, uint8_t *data)
{
    hal_rpmsg_status_t status = kStatus_HAL_RpmsgSuccess;
#if defined(HDI_MODE) && (HDI_MODE == 1)
    /* In HDI mode this function can be called from ISR therefore, 
     * we need to disable interrupt when this configuration is enabled */
    uint32_t primask;
    primask = DisableGlobalIRQ();
#endif
    if (RL_SUCCESS != rpmsg_lite_release_rx_buffer(s_rpmsgContext, data))
    {
        status = kStatus_HAL_RpmsgError;
    }
#if defined(HDI_MODE) && (HDI_MODE == 1)
    EnableGlobalIRQ(primask);
#endif
    return status;
}

hal_rpmsg_status_t HAL_RpmsgNoCopySend(hal_rpmsg_handle_t handle, uint8_t *data, uint32_t length)
{
    hal_rpmsg_state_t *rpmsgHandle;
    hal_rpmsg_status_t status = kStatus_HAL_RpmsgSuccess;
#if defined(HDI_MODE) && (HDI_MODE == 1)
    uint32_t primask;
#endif
    rpmsgHandle                 = (hal_rpmsg_state_t *)handle;
    volatile uint32_t epTimeout = RPMSG_REMOTE_READY_RETRY_COUNT;

    /* loop check peer device rpmsg endpoint is ready */
    while ((0 == rpmsgHandle->rpmsg_lite_peer_ept_is_ready) && (--epTimeout != 0u))
    {
    }

    if (epTimeout == 0u)
    {
        return kStatus_HAL_RpmsgTimeout;
    }

#if defined(HDI_MODE) && (HDI_MODE == 1)
    /* In HDI mode this function can be called from ISR therefore, 
     * we need to disable interrupt when this configuration is enabled */
    primask = DisableGlobalIRQ();
#endif
    assert(NULL != data);

    do
    {
        if (RL_TRUE != rpmsg_lite_is_link_up(s_rpmsgContext))
        {
            status = kStatus_HAL_RpmsgError;
            break;
        }

        if (RL_SUCCESS != rpmsg_lite_send_nocopy(s_rpmsgContext, rpmsgHandle->pEndpoint, rpmsgHandle->remote_addr,
                                                 (char *)data, length))
        {
            status = kStatus_HAL_RpmsgError;
            break;
        }
    } while (false);

#if defined(HDI_MODE) && (HDI_MODE == 1)
    EnableGlobalIRQ(primask);
#endif

    return status;
}
hal_rpmsg_status_t HAL_RpmsgInstallRxCallback(hal_rpmsg_handle_t handle, rpmsg_rx_callback_t callback, void *param)
{
    hal_rpmsg_state_t *rpmsgHandle;

    rpmsgHandle = (hal_rpmsg_state_t *)handle;

    rpmsgHandle->rx.callback = callback;
    rpmsgHandle->rx.param    = param;

    return kStatus_HAL_RpmsgSuccess;
}

hal_rpmsg_status_t HAL_RpmsgEnterLowpower(hal_rpmsg_handle_t handle)
{
    return kStatus_HAL_RpmsgError;
}

hal_rpmsg_status_t HAL_RpmsgExitLowpower(hal_rpmsg_handle_t handle)
{
    return kStatus_HAL_RpmsgError;
}
