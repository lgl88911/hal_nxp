/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_SPI_H_
#define FSL_SPI_H_

#include "fsl_common.h"

/*!
 * @addtogroup spi_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SPI driver version. */
#define FSL_SPI_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*! @} */

/*! @brief Global variable for dummy data value setting. */
extern volatile uint8_t s_dummyData[];

#ifndef SPI_DUMMYDATA
/*! @brief SPI dummy transfer data, the data is sent while txBuff is NULL. */
#define SPI_DUMMYDATA (0x00U)
#endif

/*! @brief Retry times for waiting flag. */
#ifndef SPI_RETRY_TIMES
#define SPI_RETRY_TIMES 0U /* Define to zero means keep waiting until the flag is assert/deassert. */
#endif

#define SPI_DATA(n)  (((uint32_t)(n)) & 0xFFFFUL)
#define SPI_CTRLMASK (0xFFFF0000U)

#define SPI_ASSERTNUM_SSEL(n)   ((~(1UL << ((n) + 16UL))) & 0xF0000UL)
#define SPI_DEASSERTNUM_SSEL(n) (1UL << ((n) + 16UL))
#define SPI_DEASSERT_ALL        (0xF0000UL)

#define SPI_FIFOWR_FLAGS_MASK (~(SPI_DEASSERT_ALL | SPI_FIFOWR_TXDATA_MASK | SPI_FIFOWR_LEN_MASK))

#define SPI_FIFOTRIG_TXLVL_GET(base) (((base)->FIFOTRIG & SPI_FIFOTRIG_TXLVL_MASK) >> SPI_FIFOTRIG_TXLVL_SHIFT)
#define SPI_FIFOTRIG_RXLVL_GET(base) (((base)->FIFOTRIG & SPI_FIFOTRIG_RXLVL_MASK) >> SPI_FIFOTRIG_RXLVL_SHIFT)

/*
 * INTEN interrupts shift, to include both INTEN interrupts and FIFOINTEN interrupts
 * in to one enumeration _spi_interrupt_enable.
 */
#define SPI_INTEN_IRQ_SHIFT 16U
/* All interrupt control bits in FIFOINTEN */
#define SPI_FIFOINTEN_ALL_MASK                                                                 \
    (SPI_FIFOINTENSET_RXERR_MASK | SPI_FIFOINTENSET_TXERR_MASK | SPI_FIFOINTENSET_RXLVL_MASK | \
     SPI_FIFOINTENSET_TXLVL_MASK)
/* All interrupt control bits in INTEN */
#define SPI_INTEN_ALL_MASK                                                                                         \
    (SPI_INTENSET_RXRDYEN_MASK | SPI_INTENSET_TXRDYEN_MASK | SPI_INTENSET_RXOVEN_MASK | SPI_INTENSET_TXUREN_MASK | \
     SPI_INTENSET_SSAEN_MASK | SPI_INTENSET_SSDEN_MASK | SPI_INTENSET_MSTIDLEEN_MASK)

/*! @brief SPI transfer option.*/
typedef enum _spi_xfer_option
{
    kSPI_FrameDelay  = (SPI_FIFOWR_EOF_MASK), /*!< A delay may be inserted, defined in the DLY register.*/
    kSPI_FrameAssert = (SPI_FIFOWR_EOT_MASK), /*!< SSEL will be deasserted at the end of a transfer */
} spi_xfer_option_t;

/*! @brief SPI data shifter direction options.*/
typedef enum _spi_shift_direction
{
    kSPI_MsbFirst = 0U, /*!< Data transfers start with most significant bit. */
    kSPI_LsbFirst = 1U  /*!< Data transfers start with least significant bit. */
} spi_shift_direction_t;

/*! @brief SPI clock polarity configuration.*/
typedef enum _spi_clock_polarity
{
    kSPI_ClockPolarityActiveHigh = 0x0U, /*!< Active-high SPI clock (idles low). */
    kSPI_ClockPolarityActiveLow          /*!< Active-low SPI clock (idles high). */
} spi_clock_polarity_t;

/*! @brief SPI clock phase configuration.*/
typedef enum _spi_clock_phase
{
    kSPI_ClockPhaseFirstEdge = 0x0U, /*!< First edge on SCK occurs at the middle of the first
                                      *   cycle of a data transfer. */
    kSPI_ClockPhaseSecondEdge        /*!< First edge on SCK occurs at the start of the
                                      *   first cycle of a data transfer. */
} spi_clock_phase_t;

/*! @brief txFIFO watermark values */
typedef enum _spi_txfifo_watermark
{
    kSPI_TxFifo0 = 0, /*!< SPI tx watermark is empty */
    kSPI_TxFifo1 = 1, /*!< SPI tx watermark at 1 item */
    kSPI_TxFifo2 = 2, /*!< SPI tx watermark at 2 items */
    kSPI_TxFifo3 = 3, /*!< SPI tx watermark at 3 items */
    kSPI_TxFifo4 = 4, /*!< SPI tx watermark at 4 items */
    kSPI_TxFifo5 = 5, /*!< SPI tx watermark at 5 items */
    kSPI_TxFifo6 = 6, /*!< SPI tx watermark at 6 items */
    kSPI_TxFifo7 = 7, /*!< SPI tx watermark at 7 items */
} spi_txfifo_watermark_t;

/*! @brief rxFIFO watermark values */
typedef enum _spi_rxfifo_watermark
{
    kSPI_RxFifo1 = 0, /*!< SPI rx watermark at 1 item */
    kSPI_RxFifo2 = 1, /*!< SPI rx watermark at 2 items */
    kSPI_RxFifo3 = 2, /*!< SPI rx watermark at 3 items */
    kSPI_RxFifo4 = 3, /*!< SPI rx watermark at 4 items */
    kSPI_RxFifo5 = 4, /*!< SPI rx watermark at 5 items */
    kSPI_RxFifo6 = 5, /*!< SPI rx watermark at 6 items */
    kSPI_RxFifo7 = 6, /*!< SPI rx watermark at 7 items */
    kSPI_RxFifo8 = 7, /*!< SPI rx watermark at 8 items */
} spi_rxfifo_watermark_t;

/*! @brief Transfer data width */
typedef enum _spi_data_width
{

    kSPI_Data8Bits  = 7,  /*!< 8 bits data width (7)*/
    kSPI_Data16Bits = 15, /*!< 16 bits data width (15)*/

} spi_data_width_t;

/*! @brief Slave select */
typedef enum _spi_ssel
{
    kSPI_Ssel0 = 0, /*!< Slave select 0 */
} spi_ssel_t;

/*! @brief ssel polarity */
typedef enum _spi_spol
{
    kSPI_SpolActiveAllLow = 0,
} spi_spol_t;

/*!
 * @brief SPI delay time configure structure.
 * Note:
 *   The DLY register controls several programmable delays related to SPI signalling,
 *   it stands for how many SPI clock time will be inserted.
 *   The maxinun value of these delay time is 15.
 */
typedef struct _spi_delay_config
{
    uint8_t preDelay;      /*!< Delay between SSEL assertion and the beginning of transfer. */
    uint8_t postDelay;     /*!< Delay between the end of transfer and SSEL deassertion. */
    uint8_t frameDelay;    /*!< Delay between frame to frame. */
    uint8_t transferDelay; /*!< Delay between transfer to transfer. */
} spi_delay_config_t;

/*! @brief SPI master user configure structure.*/
typedef struct _spi_master_config
{
    bool enableLoopback;             /*!< Enable loopback for test purpose */
    bool enableMaster;               /*!< Enable SPI at initialization time */
    spi_clock_polarity_t polarity;   /*!< Clock polarity */
    spi_clock_phase_t phase;         /*!< Clock phase */
    spi_shift_direction_t direction; /*!< MSB or LSB */
    uint32_t baudRate_Bps;           /*!< Baud Rate for SPI in Hz */
    spi_data_width_t dataWidth;      /*!< Width of the data */
    spi_ssel_t sselNum;              /*!< Slave select number */
    spi_spol_t sselPol;              /*!< Configure active CS polarity */
    uint8_t txWatermark;             /*!< txFIFO watermark */
    uint8_t rxWatermark;             /*!< rxFIFO watermark */
    spi_delay_config_t delayConfig;  /*!< Delay configuration. */
} spi_master_config_t;

/*! @brief SPI transfer status.*/
enum
{
    kStatus_SPI_Busy  = MAKE_STATUS(kStatusGroup_LPC_SPI, 0), /*!< SPI bus is busy */
    kStatus_SPI_Idle  = MAKE_STATUS(kStatusGroup_LPC_SPI, 1), /*!< SPI is idle */
    kStatus_SPI_Error = MAKE_STATUS(kStatusGroup_LPC_SPI, 2), /*!< SPI  error */
    kStatus_SPI_BaudrateNotSupport =
        MAKE_STATUS(kStatusGroup_LPC_SPI, 3),                  /*!< Baudrate is not support in current clock source */
    kStatus_SPI_Timeout = MAKE_STATUS(kStatusGroup_LPC_SPI, 4) /*!< SPI timeout polling status flags. */
};

/*! @brief SPI interrupt sources.*/
enum _spi_interrupt_enable
{
    kSPI_RxErrIrq               = SPI_FIFOINTENSET_RXERR_MASK,                        /*!< Rx error interrupt */
    kSPI_TxErrIrq               = SPI_FIFOINTENSET_TXERR_MASK,                        /*!< Tx error interrupt */
    kSPI_RxLvlIrq               = SPI_FIFOINTENSET_RXLVL_MASK,                        /*!< Rx level interrupt */
    kSPI_TxLvlIrq               = SPI_FIFOINTENSET_TXLVL_MASK,                        /*!< Tx level interrupt */
    kSPI_SlaveSelectAssertIrq   = SPI_INTENSET_SSAEN_MASK << SPI_INTEN_IRQ_SHIFT,     /*!< Slave select assert */
    kSPI_SlaveSelectDeassertIrq = SPI_INTENSET_SSDEN_MASK << SPI_INTEN_IRQ_SHIFT,     /*!< Slave select deassert */
    kSPI_MasterIdleIrq          = SPI_INTENSET_MSTIDLEEN_MASK << SPI_INTEN_IRQ_SHIFT, /*!< Master idle */
};

/*! @brief SPI status flags.*/
enum _spi_statusflags
{
    kSPI_TxEmptyFlag    = SPI_FIFOSTAT_TXEMPTY_MASK,    /*!< txFifo is empty */
    kSPI_TxNotFullFlag  = SPI_FIFOSTAT_TXNOFULL_MASK,   /*!< txFifo is not full */
    kSPI_RxNotEmptyFlag = SPI_FIFOSTAT_RXNOTEMPTY_MASK, /*!< rxFIFO is not empty */
    kSPI_RxFullFlag     = SPI_FIFOSTAT_RXFULL_MASK,     /*!< rxFIFO is full */
};

/*! @brief SPI transfer structure */
typedef struct _spi_transfer
{
    uint8_t *txData;      /*!< Send buffer */
    uint8_t *rxData;      /*!< Receive buffer */
    uint32_t configFlags; /*!< Additional option to control transfer, @ref spi_xfer_option_t. */
    size_t dataSize;      /*!< Transfer bytes */
} spi_transfer_t;

/*! @brief Internal configuration structure used in 'spi' and 'spi_dma' driver */
typedef struct _spi_config
{
    spi_data_width_t dataWidth;
    spi_ssel_t sselNum;
} spi_config_t;

/*! @brief  Master handle type */
typedef struct _spi_master_handle spi_master_handle_t;

/*! @brief SPI master callback for finished transmit */
typedef void (*spi_master_callback_t)(SPI_Type *base, spi_master_handle_t *handle, status_t status, void *userData);

/*! @brief SPI transfer handle structure */
struct _spi_master_handle
{
    uint8_t *volatile txData;         /*!< Transfer buffer */
    uint8_t *volatile rxData;         /*!< Receive buffer */
    volatile size_t txRemainingBytes; /*!< Number of data to be transmitted [in bytes] */
    volatile size_t rxRemainingBytes; /*!< Number of data to be received [in bytes] */
    volatile int8_t toReceiveCount; /*!< The number of data expected to receive in data width. Since the received count
                                       and sent count should be the same to complete the transfer, if the sent count is
                                       x and the received count is y, toReceiveCount is x-y. */
    size_t totalByteCount;          /*!< A number of transfer bytes */
    volatile uint32_t state;        /*!< SPI internal state */
    spi_master_callback_t callback; /*!< SPI callback */
    void *userData;                 /*!< Callback parameter */
    uint8_t dataWidth;              /*!< Width of the data [Valid values: 1 to 16] */
    uint8_t sselNum;      /*!< Slave select number to be asserted when transferring data [Valid values: 0 to 3] */
    uint32_t configFlags; /*!< Additional option to control transfer */
    uint8_t txWatermark;  /*!< txFIFO watermark */
    uint8_t rxWatermark;  /*!< rxFIFO watermark */
};

/*! @brief Typedef for master interrupt handler. */
typedef void (*spi_master_irq_handler_t)(SPI_Type *base, spi_master_handle_t *handle);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @brief Returns instance number for SPI peripheral base address. */
uint32_t SPI_GetInstance(SPI_Type *base);

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief  Sets the SPI master configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in SPI_MasterInit().
 * User may use the initialized structure unchanged in SPI_MasterInit(), or modify
 * some fields of the structure before calling SPI_MasterInit(). After calling this API,
 * the master is ready to transfer.
 * Example:
   @code
   spi_master_config_t config;
   SPI_MasterGetDefaultConfig(&config);
   @endcode
 *
 * @param config pointer to master config structure
 */
void SPI_MasterGetDefaultConfig(spi_master_config_t *config);

/*!
 * @brief Initializes the SPI with master configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by SPI_MasterGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   @code
   spi_master_config_t config = {
   .baudRate_Bps = 400000,
   ...
   };
   SPI_MasterInit(SPI0, &config);
   @endcode
 *
 * @param base SPI base pointer
 * @param config pointer to master configuration structure
 * @param srcClock_Hz Source clock frequency.
 */
status_t SPI_MasterInit(SPI_Type *base, const spi_master_config_t *config, uint32_t srcClock_Hz);

/*!
 * @brief De-initializes the SPI.
 *
 * Calling this API resets the SPI module, gates the SPI clock.
 * The SPI module can't work unless calling the SPI_MasterInit/SPI_SlaveInit to initialize module.
 *
 * @param base SPI base pointer
 */
void SPI_Deinit(SPI_Type *base);

/*!
 * @brief Enable or disable the SPI Master or Slave
 * @param base SPI base pointer
 * @param enable or disable ( true = enable, false = disable)
 */
static inline void SPI_Enable(SPI_Type *base, bool enable)
{
    if (enable)
    {
        base->CFG |= SPI_CFG_ENABLE_MASK;
    }
    else
    {
        base->CFG &= ~SPI_CFG_ENABLE_MASK;
    }
}

/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the status flag.
 *
 * @param base SPI base pointer
 * @return SPI Status, use status flag to AND @ref _spi_statusflags could get the related status.
 */
static inline uint32_t SPI_GetStatusFlags(SPI_Type *base)
{
    assert(NULL != base);
    return base->FIFOSTAT;
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the interrupt for the SPI.
 *
 * @param base SPI base pointer
 * @param irqs SPI interrupt source. The parameter can be any combination of the following values:
 *        @arg kSPI_RxErrIrq
 *        @arg kSPI_TxErrIrq
 *        @arg kSPI_RxLvlIrq
 *        @arg kSPI_TxLvlIrq
 *        @arg kSPI_SlaveSelectAssertIrq
 *        @arg kSPI_SlaveSelectDeassertIrq
 *        @arg kSPI_MasterIdleIrq
 */
static inline void SPI_EnableInterrupts(SPI_Type *base, uint32_t irqs)
{
    assert(NULL != base);

    base->FIFOINTENSET = (irqs & SPI_FIFOINTEN_ALL_MASK);
    base->INTENSET     = ((irqs >> SPI_INTEN_IRQ_SHIFT) & SPI_INTEN_ALL_MASK);
}

/*!
 * @brief Disables the interrupt for the SPI.
 *
 * @param base SPI base pointer
 * @param irqs SPI interrupt source. The parameter can be any combination of the following values:
 *        @arg kSPI_RxErrIrq
 *        @arg kSPI_TxErrIrq
 *        @arg kSPI_RxLvlIrq
 *        @arg kSPI_TxLvlIrq
 *        @arg kSPI_SlaveSelectAssertIrq
 *        @arg kSPI_SlaveSelectDeassertIrq
 *        @arg kSPI_MasterIdleIrq
 */
static inline void SPI_DisableInterrupts(SPI_Type *base, uint32_t irqs)
{
    assert(NULL != base);

    base->FIFOINTENCLR = (irqs & SPI_FIFOINTEN_ALL_MASK);
    base->INTENCLR     = ((irqs >> SPI_INTEN_IRQ_SHIFT) & SPI_INTEN_ALL_MASK);
}

/*! @} */

/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Enables the DMA request from SPI txFIFO.
 *
 * @param base SPI base pointer
 * @param enable True means enable DMA, false means disable DMA
 */
void SPI_EnableTxDMA(SPI_Type *base, bool enable);

/*!
 * @brief Enables the DMA request from SPI rxFIFO.
 *
 * @param base SPI base pointer
 * @param enable True means enable DMA, false means disable DMA
 */
void SPI_EnableRxDMA(SPI_Type *base, bool enable);

/*! @} */

/*!
 * @name Bus Operations
 * @{
 */
/*!
 * @brief Returns the configurations.
 *
 * @param base SPI peripheral address.
 * @return return configurations which contain datawidth and SSEL numbers.
 *         return data type is a pointer of spi_config_t.
 */
void *SPI_GetConfig(SPI_Type *base);

/*!
 * @brief Sets the baud rate for SPI transfer. This is only used in master.
 *
 * @param base SPI base pointer
 * @param baudrate_Bps baud rate needed in Hz.
 * @param srcClock_Hz SPI source clock frequency in Hz.
 */
status_t SPI_MasterSetBaud(SPI_Type *base, uint32_t baudrate_Bps, uint32_t srcClock_Hz);

/*!
 * @brief Writes a data into the SPI data register.
 *
 * @param base SPI base pointer
 * @param data needs to be write.
 * @param configFlags transfer configuration options @ref spi_xfer_option_t
 */
void SPI_WriteData(SPI_Type *base, uint16_t data, uint32_t configFlags);

/*!
 * @brief Gets a data from the SPI data register.
 *
 * @param base SPI base pointer
 * @return Data in the register.
 */
static inline uint32_t SPI_ReadData(SPI_Type *base)
{
    assert(NULL != base);
    return base->FIFORD;
}

/*!
 * @brief Set delay time for transfer.
 *        the delay uint is SPI clock time, maximum value is 0xF.
 * @param base SPI base pointer
 * @param config configuration for delay option @ref spi_delay_config_t.
 */
static inline void SPI_SetTransferDelay(SPI_Type *base, const spi_delay_config_t *config)
{
    assert(NULL != base);
    assert(NULL != config);
    base->DLY = (SPI_DLY_PRE_DELAY(config->preDelay) | SPI_DLY_POST_DELAY(config->postDelay) |
                 SPI_DLY_FRAME_DELAY(config->frameDelay) | SPI_DLY_TRANSFER_DELAY(config->transferDelay));
}

/*!
 * @brief Set up the dummy data.
 *
 * @param base SPI peripheral address.
 * @param dummyData Data to be transferred when tx buffer is NULL.
 */
void SPI_SetDummyData(SPI_Type *base, uint8_t dummyData);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the SPI master handle.
 *
 * This function initializes the SPI master handle which can be used for other SPI master transactional APIs. Usually,
 * for a specified SPI instance, call this API once to get the initialized handle.
 *
 * @param base SPI peripheral base address.
 * @param handle SPI handle pointer.
 * @param callback Callback function.
 * @param userData User data.
 */
status_t SPI_MasterTransferCreateHandle(SPI_Type *base,
                                        spi_master_handle_t *handle,
                                        spi_master_callback_t callback,
                                        void *userData);

/*!
 * @brief Transfers a block of data using a polling method.
 *
 * @param base SPI base pointer
 * @param xfer pointer to spi_xfer_config_t structure
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_SPI_Timeout The transfer timed out and was aborted.
 */
status_t SPI_MasterTransferBlocking(SPI_Type *base, spi_transfer_t *xfer);

/*!
 * @brief Performs a non-blocking SPI interrupt transfer.
 *
 * @param base SPI peripheral base address.
 * @param handle pointer to spi_master_handle_t structure which stores the transfer state
 * @param xfer pointer to spi_xfer_config_t structure
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_MasterTransferNonBlocking(SPI_Type *base, spi_master_handle_t *handle, spi_transfer_t *xfer);

/*!
 * @brief Gets the master transfer count.
 *
 * This function gets the master transfer count.
 *
 * @param base SPI peripheral base address.
 * @param handle Pointer to the spi_master_handle_t structure which stores the transfer state.
 * @param count The number of bytes transferred by using the non-blocking transaction.
 * @return status of status_t.
 */
status_t SPI_MasterTransferGetCount(SPI_Type *base, spi_master_handle_t *handle, size_t *count);

/*!
 * @brief SPI master aborts a transfer using an interrupt.
 *
 * This function aborts a transfer using an interrupt.
 *
 * @param base SPI peripheral base address.
 * @param handle Pointer to the spi_master_handle_t structure which stores the transfer state.
 */
void SPI_MasterTransferAbort(SPI_Type *base, spi_master_handle_t *handle);

/*!
 * @brief Interrupts the handler for the SPI.
 *
 * @param base SPI peripheral base address.
 * @param handle pointer to spi_master_handle_t structure which stores the transfer state.
 */
void SPI_MasterTransferHandleIRQ(SPI_Type *base, spi_master_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_SPI_H_*/
