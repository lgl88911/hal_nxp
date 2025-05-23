/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019 , NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_FRO_CALIB_H_
#define __FSL_FRO_CALIB_H_

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.fro_calib"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief FRO_CALIB driver version 2.0.0. */
#define FSL_FRO_CALIB_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the version of the FRO Calibration library */
unsigned int fro_calib_Get_Lib_Ver(void);

/* timer instance */
/* timer clock frquency in KHz */
ErrorCode_t Chip_TIMER_Instance_Freq(CTIMER_Type *base, unsigned int timerFreq);

/* USB_SOF_Event */
ErrorCode_t USB_SOF_Event(USBD_HANDLE_T hUsb);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __FSL_FRO_CALIB_H_ */
