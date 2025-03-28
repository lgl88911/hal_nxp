/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_PWT_H_
#define FSL_PWT_H_

#include "fsl_common.h"

/*!
 * @addtogroup pwt_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FSL_PWT_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1 */

/*! @brief PWT clock source selection */
typedef enum _pwt_clock_source
{
    kPWT_TimerClock = 0U, /*!< The Timer clock is used as the clock source of PWT counter */
    kPWT_AlternativeClock /*!< Alternative clock is used as the clock source of PWT counter */
} pwt_clock_source_t;

/*! @brief PWT prescaler factor selection for clock source */
typedef enum _pwt_clock_prescale
{
    kPWT_Prescale_Divide_1 = 0U, /*!< PWT clock divided by 1 */
    kPWT_Prescale_Divide_2,      /*!< PWT clock divided by 2 */
    kPWT_Prescale_Divide_4,      /*!< PWT clock divided by 4 */
    kPWT_Prescale_Divide_8,      /*!< PWT clock divided by 8 */
    kPWT_Prescale_Divide_16,     /*!< PWT clock divided by 16 */
    kPWT_Prescale_Divide_32,     /*!< PWT clock divided by 32 */
    kPWT_Prescale_Divide_64,     /*!< PWT clock divided by 64 */
    kPWT_Prescale_Divide_128     /*!< PWT clock divided by 128 */
} pwt_clock_prescale_t;

/*! @brief PWT Input Edge */
typedef enum _pwt_input_edge
{
    kPWT_StartFall_CaptureFall_Edge = 0U, /*!< The first falling-edge starts the pulse width measurement, and on all the
                                             subsequent falling edges, the pulse width is captured. */
    kPWT_StartRise_CaptureRiseAndFall_Edge, /*!< The first rising edge starts the pulse width measurement, and on all
                                               the subsequent rising and falling edges, the pulse width is captured. */
    kPWT_StartFall_CaptureRiseAndFall_Edge, /*!< The first falling edge starts the pulse width measurement, and on all
                                               the subsequent rising and falling edges, the pulse width is captured.*/
    kPWT_StartRise_CaptureRise_Edge /*!< The first-rising edge starts the pulse width measurement, and on all the
                                       subsequent rising edges, the pulse width is captured. */
} pwt_input_edge_t;

/*! @brief PWT input port selection */
typedef enum _pwt_input_select
{
    kPWT_InputPort_0 = 0U, /*!< PWT input comes from PWTIN[0] */
    kPWT_InputPort_1,      /*!< PWT input comes from PWTIN[1] */
    kPWT_InputPort_2,      /*!< PWT input comes from PWTIN[2] */
    kPWT_InputPort_3       /*!< PWT input comes from PWTIN[3] */
} pwt_input_select_t;

/*!
 * @brief List of PWT interrupts
 */
typedef enum _pwt_interrupt_enable
{
    kPWT_ModuleInterruptEnable          = PWT_R1_PWTIE_MASK,  /*!< Module Interrupt */
    kPWT_PulseWidthReadyInterruptEnable = PWT_R1_PRDYIE_MASK, /*!< Pulse width data ready interrupt */
    kPWT_CounterOverflowInterruptEnable = PWT_R1_POVIE_MASK   /*!< Counter overflow interrupt */
} pwt_interrupt_enable_t;

/*!
 * @brief List of PWT flags
 */
typedef enum _pwt_status_flags
{
    kPWT_CounterOverflowFlag = PWT_R1_PWTOV_MASK,  /*!< Counter overflow flag */
    kPWT_PulseWidthValidFlag = PWT_R1_PWTRDY_MASK, /*!< Pulse width valid flag */
} pwt_status_flags_t;

/*!
 * @brief PWT configuration structure
 *
 * This structure holds the configuration settings for the PWT peripheral. To initialize this
 * structure to reasonable defaults, call the PWT_GetDefaultConfig() function and pass a
 * pointer to the configuration structure instance.
 *
 * The configuration structure can be made constant so as to reside in flash.
 */
typedef struct _pwt_config
{
    pwt_clock_source_t clockSource; /*!< Clock source for the counter */
    pwt_clock_prescale_t prescale;  /*!< Pre-scaler to divide down the clock */
    pwt_input_select_t inputSelect; /*!< PWT Pulse input port selection */
    pwt_input_edge_t edge;          /*!< PWT Input Edge */
} pwt_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the PWT clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the PWT driver.
 *
 * @param base   PWT peripheral base address
 * @param config Pointer to the user configuration structure.
 */
void PWT_Init(PWT_Type *base, const pwt_config_t *config);

/*!
 * @brief Gates the PWT clock.
 *
 * @param base PWT peripheral base address
 */
void PWT_Deinit(PWT_Type *base);

/*!
 * @brief  Fills in the PWT configuration structure with the default settings.
 *
 * The default values are:
 * @code
 *   config->clockSource = kPWT_TimerClock;
 *   config->prescale = kPWT_Prescale_Divide_1;
 *   config->inputSelect = kPWT_InputPort_0;
 *   config->edge = kPWT_StartRise_CaptureRiseAndFall_Edge;
 * @endcode
 * @param config Pointer to the user configuration structure.
 */
void PWT_GetDefaultConfig(pwt_config_t *config);

/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected PWT interrupts.
 *
 * @param base PWT peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::pwt_interrupt_enable_t
 */
static inline void PWT_EnableInterrupts(PWT_Type *base, uint32_t mask)
{
    base->R1 |= mask;
}

/*!
 * @brief Disables the selected PWT interrupts.
 *
 * @param base PWT peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::pwt_interrupt_enable_t
 */
static inline void PWT_DisableInterrupts(PWT_Type *base, uint32_t mask)
{
    base->R1 &= ~mask;
}

/*!
 * @brief Gets the enabled PWT interrupts.
 *
 * @param base PWT peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::pwt_interrupt_enable_t
 */
static inline uint32_t PWT_GetEnabledInterrupts(PWT_Type *base)
{
    return (base->R1 & (PWT_R1_PWTIE_MASK | PWT_R1_PRDYIE_MASK | PWT_R1_POVIE_MASK));
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the PWT status flags.
 *
 * @param base PWT peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::pwt_status_flags_t
 */
static inline uint32_t PWT_GetStatusFlags(PWT_Type *base)
{
    return (base->R1 & (PWT_R1_PWTRDY_MASK | PWT_R1_PWTOV_MASK));
}

/*!
 * @brief Clears the PWT status flags.
 *
 * @param base PWT peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::pwt_status_flags_t
 */
static inline void PWT_ClearStatusFlags(PWT_Type *base, uint32_t mask)
{
    base->R1 &= ~mask;
}

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the PWT counter.
 *
 * @param base PWT peripheral base address
 */
static inline void PWT_StartTimer(PWT_Type *base)
{
    base->R1 |= PWT_R1_PWTEN_MASK;
}

/*!
 * @brief Stops the PWT counter.
 *
 * @param base PWT peripheral base address
 */
static inline void PWT_StopTimer(PWT_Type *base)
{
    base->R1 &= ~PWT_R1_PWTEN_MASK;
}

/*! @}*/

/*!
 * @brief Reads the current counter value.
 *
 * This function returns the timer counting value
 *
 * @param base    PWT peripheral base address
 *
 * @return Current 16-bit timer counter value
 */
static inline uint16_t PWT_GetCurrentTimerCount(PWT_Type *base)
{
    return (uint16_t)((base->R2 & PWT_R2_PWTC_MASK) >> PWT_R2_PWTC_SHIFT);
}
/*!
 * @brief Reads the positive pulse width.
 *
 * This function reads the low and high registers and returns the 16-bit positive pulse width
 *
 * @param base PWT peripheral base address.
 *
 * @return The 16-bit positive pulse width.
 */
static inline uint16_t PWT_ReadPositivePulseWidth(PWT_Type *base)
{
    return (uint16_t)((base->R1 & PWT_R1_PPW_MASK) >> PWT_R1_PPW_SHIFT);
}

/*!
 * @brief Reads the negative pulse width.
 *
 * This function reads the low and high registers and returns the 16-bit negative pulse width
 *
 * @param base PWT peripheral base address.
 *
 * @return The 16-bit negative pulse width.
 */
static inline uint16_t PWT_ReadNegativePulseWidth(PWT_Type *base)
{
    return (uint16_t)((base->R2 & PWT_R2_NPW_MASK) >> PWT_R2_NPW_SHIFT);
}

/*!
 * @brief Performs a software reset on the PWT module.
 *
 * @param base PWT peripheral base address
 */
static inline void PWT_Reset(PWT_Type *base)
{
    base->R1 |= PWT_R1_PWTSR_MASK;
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_PWT_H_*/
