/*
** ###################################################################
**     Processors:          MIMX9594AVZXN_ca55
**                          MIMX9594AVZXN_cm33
**                          MIMX9594AVZXN_cm7
**                          MIMX9596AVTXN_ca55
**                          MIMX9596AVTXN_cm33
**                          MIMX9596AVTXN_cm7
**                          MIMX9596AVYXN_ca55
**                          MIMX9596AVYXN_cm33
**                          MIMX9596AVYXN_cm7
**                          MIMX9596AVZXN_ca55
**                          MIMX9596AVZXN_cm33
**                          MIMX9596AVZXN_cm7
**                          MIMX9596CVTXN_ca55
**                          MIMX9596CVTXN_cm33
**                          MIMX9596CVTXN_cm7
**                          MIMX9596CVYXN_ca55
**                          MIMX9596CVYXN_cm33
**                          MIMX9596CVYXN_cm7
**                          MIMX9596CVZXN_ca55
**                          MIMX9596CVZXN_cm33
**                          MIMX9596CVZXN_cm7
**                          MIMX9596DVTXN_ca55
**                          MIMX9596DVTXN_cm33
**                          MIMX9596DVTXN_cm7
**                          MIMX9596DVYXN_ca55
**                          MIMX9596DVYXN_cm33
**                          MIMX9596DVYXN_cm7
**                          MIMX9596DVYXQ_ca55
**                          MIMX9596DVYXQ_cm33
**                          MIMX9596DVYXQ_cm7
**                          MIMX9596DVZXN_ca55
**                          MIMX9596DVZXN_cm33
**                          MIMX9596DVZXN_cm7
**                          MIMX9596XVTXN_ca55
**                          MIMX9596XVTXN_cm33
**                          MIMX9596XVTXN_cm7
**                          MIMX9596XVYXN_ca55
**                          MIMX9596XVYXN_cm33
**                          MIMX9596XVYXN_cm7
**                          MIMX9596XVZXN_ca55
**                          MIMX9596XVZXN_cm33
**                          MIMX9596XVZXN_cm7
**
**     Version:             rev. 1.0, 2023-01-10
**     Build:               b240728
**
**     Abstract:
**         CMSIS Peripheral Access Layer for IR_COMPRESS
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2023-01-10)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file IR_COMPRESS.h
 * @version 1.0
 * @date 2023-01-10
 * @brief CMSIS Peripheral Access Layer for IR_COMPRESS
 *
 * CMSIS Peripheral Access Layer for IR_COMPRESS
 */

#if !defined(IR_COMPRESS_H_)
#define IR_COMPRESS_H_                           /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMX9594AVZXN_ca55))
#include "MIMX9594_ca55_COMMON.h"
#elif (defined(CPU_MIMX9594AVZXN_cm33))
#include "MIMX9594_cm33_COMMON.h"
#elif (defined(CPU_MIMX9594AVZXN_cm7))
#include "MIMX9594_cm7_COMMON.h"
#elif (defined(CPU_MIMX9596AVTXN_ca55) || defined(CPU_MIMX9596AVYXN_ca55) || defined(CPU_MIMX9596AVZXN_ca55) || defined(CPU_MIMX9596CVTXN_ca55) || defined(CPU_MIMX9596CVYXN_ca55) || defined(CPU_MIMX9596CVZXN_ca55) || defined(CPU_MIMX9596DVTXN_ca55) || defined(CPU_MIMX9596DVYXN_ca55) || defined(CPU_MIMX9596DVYXQ_ca55) || defined(CPU_MIMX9596DVZXN_ca55) || defined(CPU_MIMX9596XVTXN_ca55) || defined(CPU_MIMX9596XVYXN_ca55) || defined(CPU_MIMX9596XVZXN_ca55))
#include "MIMX9596_ca55_COMMON.h"
#elif (defined(CPU_MIMX9596AVTXN_cm33) || defined(CPU_MIMX9596AVYXN_cm33) || defined(CPU_MIMX9596AVZXN_cm33) || defined(CPU_MIMX9596CVTXN_cm33) || defined(CPU_MIMX9596CVYXN_cm33) || defined(CPU_MIMX9596CVZXN_cm33) || defined(CPU_MIMX9596DVTXN_cm33) || defined(CPU_MIMX9596DVYXN_cm33) || defined(CPU_MIMX9596DVYXQ_cm33) || defined(CPU_MIMX9596DVZXN_cm33) || defined(CPU_MIMX9596XVTXN_cm33) || defined(CPU_MIMX9596XVYXN_cm33) || defined(CPU_MIMX9596XVZXN_cm33))
#include "MIMX9596_cm33_COMMON.h"
#elif (defined(CPU_MIMX9596AVTXN_cm7) || defined(CPU_MIMX9596AVYXN_cm7) || defined(CPU_MIMX9596AVZXN_cm7) || defined(CPU_MIMX9596CVTXN_cm7) || defined(CPU_MIMX9596CVYXN_cm7) || defined(CPU_MIMX9596CVZXN_cm7) || defined(CPU_MIMX9596DVTXN_cm7) || defined(CPU_MIMX9596DVYXN_cm7) || defined(CPU_MIMX9596DVYXQ_cm7) || defined(CPU_MIMX9596DVZXN_cm7) || defined(CPU_MIMX9596XVTXN_cm7) || defined(CPU_MIMX9596XVYXN_cm7) || defined(CPU_MIMX9596XVZXN_cm7))
#include "MIMX9596_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- IR_COMPRESS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IR_COMPRESS_Peripheral_Access_Layer IR_COMPRESS Peripheral Access Layer
 * @{
 */

/** IR_COMPRESS - Size of Registers Arrays */
#define IR_COMPRESS_NEO_PIPE1_IR_COMP_CONF_COUNT  1u

/** IR_COMPRESS - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x48 */
    __IO uint32_t CTRL_CAM;                          /**< Camera 0 IR Compress Control Register, array offset: 0x0, array step: 0x48 */
    __IO uint32_t KNEE_POINT1_CAM;                   /**< Camera 0 IR Compress KneePoint 1 Register, array offset: 0x4, array step: 0x48 */
    __IO uint32_t KNEE_POINT2_CAM;                   /**< Camera 0 IR Compress KneePoint 2 Register, array offset: 0x8, array step: 0x48 */
    __IO uint32_t KNEE_POINT3_CAM;                   /**< Camera 0 IR Compress KneePoint 3 Register, array offset: 0xC, array step: 0x48 */
    __IO uint32_t KNEE_POINT4_CAM;                   /**< Camera 0 IR Compress KneePoint 4 Register, array offset: 0x10, array step: 0x48 */
    __IO uint32_t KNEE_OFFSET0_CAM;                  /**< Camera 0 IR Compress Knee Offset 0 Register, array offset: 0x14, array step: 0x48 */
    __IO uint32_t KNEE_OFFSET1_CAM;                  /**< Camera 0 IR Compress Knee Offset 1 Register, array offset: 0x18, array step: 0x48 */
    __IO uint32_t KNEE_OFFSET2_CAM;                  /**< Camera 0 IR Compress Knee Offset 2 Register, array offset: 0x1C, array step: 0x48 */
    __IO uint32_t KNEE_OFFSET3_CAM;                  /**< Camera 0 IR Compress Knee Offset 3 Register, array offset: 0x20, array step: 0x48 */
    __IO uint32_t KNEE_OFFSET4_CAM;                  /**< Camera 0 IR Compress Knee Offset 4 Register, array offset: 0x24, array step: 0x48 */
    __IO uint32_t KNEE_RATIO01_CAM;                  /**< Camera 0 IR Compress Knee Ratio 01 Register, array offset: 0x28, array step: 0x48 */
    __IO uint32_t KNEE_RATIO23_CAM;                  /**< Camera 0 IR Compress Knee Ratio 23 Register, array offset: 0x2C, array step: 0x48 */
    __IO uint32_t KNEE_RATIO4_CAM;                   /**< Camera 0 IR Compress Knee Ratio 4 Register, array offset: 0x30, array step: 0x48 */
    __IO uint32_t KNEE_NPOINT0_CAM;                  /**< Camera 0 IR Compress New KneePoint 0 Register, array offset: 0x34, array step: 0x48 */
    __IO uint32_t KNEE_NPOINT1_CAM;                  /**< Camera 0 IR Compress New KneePoint 1 Register, array offset: 0x38, array step: 0x48 */
    __IO uint32_t KNEE_NPOINT2_CAM;                  /**< Camera 0 IR Compress New KneePoint 2 Register, array offset: 0x3C, array step: 0x48 */
    __IO uint32_t KNEE_NPOINT3_CAM;                  /**< Camera 0 IR Compress New KneePoint 3 Register, array offset: 0x40, array step: 0x48 */
    __IO uint32_t KNEE_NPOINT4_CAM;                  /**< Camera 0 IR Compress New KneePoint 4 Register, array offset: 0x44, array step: 0x48 */
  } NEO_PIPE1_IR_COMP_CONF[IR_COMPRESS_NEO_PIPE1_IR_COMP_CONF_COUNT];
} IR_COMPRESS_Type;

/* ----------------------------------------------------------------------------
   -- IR_COMPRESS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IR_COMPRESS_Register_Masks IR_COMPRESS Register Masks
 * @{
 */

/*! @name CTRL_CAM - Camera 0 IR Compress Control Register */
/*! @{ */

#define IR_COMPRESS_CTRL_CAM_OBPP_MASK           (0x1U)
#define IR_COMPRESS_CTRL_CAM_OBPP_SHIFT          (0U)
/*! OBPP
 *  0b0..8bpp output
 *  0b1..16bpp output
 */
#define IR_COMPRESS_CTRL_CAM_OBPP(x)             (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_CTRL_CAM_OBPP_SHIFT)) & IR_COMPRESS_CTRL_CAM_OBPP_MASK)

#define IR_COMPRESS_CTRL_CAM_ENABLE_MASK         (0x80000000U)
#define IR_COMPRESS_CTRL_CAM_ENABLE_SHIFT        (31U)
/*! ENABLE
 *  0b0..IR compression operation is disabled, and the corresponding pipeline 1 output is not written to memory.
 *  0b1..IR compression operation is enabled.
 */
#define IR_COMPRESS_CTRL_CAM_ENABLE(x)           (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_CTRL_CAM_ENABLE_SHIFT)) & IR_COMPRESS_CTRL_CAM_ENABLE_MASK)
/*! @} */

/* The count of IR_COMPRESS_CTRL_CAM */
#define IR_COMPRESS_CTRL_CAM_COUNT               (1U)

/*! @name KNEE_POINT1_CAM - Camera 0 IR Compress KneePoint 1 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_POINT1_CAM_KNEEPOINT_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_POINT1_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_POINT1_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_POINT1_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_POINT1_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_POINT1_CAM */
#define IR_COMPRESS_KNEE_POINT1_CAM_COUNT        (1U)

/*! @name KNEE_POINT2_CAM - Camera 0 IR Compress KneePoint 2 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_POINT2_CAM_KNEEPOINT_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_POINT2_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_POINT2_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_POINT2_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_POINT2_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_POINT2_CAM */
#define IR_COMPRESS_KNEE_POINT2_CAM_COUNT        (1U)

/*! @name KNEE_POINT3_CAM - Camera 0 IR Compress KneePoint 3 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_POINT3_CAM_KNEEPOINT_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_POINT3_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_POINT3_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_POINT3_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_POINT3_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_POINT3_CAM */
#define IR_COMPRESS_KNEE_POINT3_CAM_COUNT        (1U)

/*! @name KNEE_POINT4_CAM - Camera 0 IR Compress KneePoint 4 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_POINT4_CAM_KNEEPOINT_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_POINT4_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_POINT4_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_POINT4_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_POINT4_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_POINT4_CAM */
#define IR_COMPRESS_KNEE_POINT4_CAM_COUNT        (1U)

/*! @name KNEE_OFFSET0_CAM - Camera 0 IR Compress Knee Offset 0 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_OFFSET0_CAM_OFFSET_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_OFFSET0_CAM_OFFSET_SHIFT (0U)
#define IR_COMPRESS_KNEE_OFFSET0_CAM_OFFSET(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_OFFSET0_CAM_OFFSET_SHIFT)) & IR_COMPRESS_KNEE_OFFSET0_CAM_OFFSET_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_OFFSET0_CAM */
#define IR_COMPRESS_KNEE_OFFSET0_CAM_COUNT       (1U)

/*! @name KNEE_OFFSET1_CAM - Camera 0 IR Compress Knee Offset 1 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_OFFSET1_CAM_OFFSET_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_OFFSET1_CAM_OFFSET_SHIFT (0U)
#define IR_COMPRESS_KNEE_OFFSET1_CAM_OFFSET(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_OFFSET1_CAM_OFFSET_SHIFT)) & IR_COMPRESS_KNEE_OFFSET1_CAM_OFFSET_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_OFFSET1_CAM */
#define IR_COMPRESS_KNEE_OFFSET1_CAM_COUNT       (1U)

/*! @name KNEE_OFFSET2_CAM - Camera 0 IR Compress Knee Offset 2 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_OFFSET2_CAM_OFFSET_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_OFFSET2_CAM_OFFSET_SHIFT (0U)
#define IR_COMPRESS_KNEE_OFFSET2_CAM_OFFSET(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_OFFSET2_CAM_OFFSET_SHIFT)) & IR_COMPRESS_KNEE_OFFSET2_CAM_OFFSET_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_OFFSET2_CAM */
#define IR_COMPRESS_KNEE_OFFSET2_CAM_COUNT       (1U)

/*! @name KNEE_OFFSET3_CAM - Camera 0 IR Compress Knee Offset 3 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_OFFSET3_CAM_OFFSET_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_OFFSET3_CAM_OFFSET_SHIFT (0U)
#define IR_COMPRESS_KNEE_OFFSET3_CAM_OFFSET(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_OFFSET3_CAM_OFFSET_SHIFT)) & IR_COMPRESS_KNEE_OFFSET3_CAM_OFFSET_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_OFFSET3_CAM */
#define IR_COMPRESS_KNEE_OFFSET3_CAM_COUNT       (1U)

/*! @name KNEE_OFFSET4_CAM - Camera 0 IR Compress Knee Offset 4 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_OFFSET4_CAM_OFFSET_MASK (0xFFFFFU)
#define IR_COMPRESS_KNEE_OFFSET4_CAM_OFFSET_SHIFT (0U)
#define IR_COMPRESS_KNEE_OFFSET4_CAM_OFFSET(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_OFFSET4_CAM_OFFSET_SHIFT)) & IR_COMPRESS_KNEE_OFFSET4_CAM_OFFSET_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_OFFSET4_CAM */
#define IR_COMPRESS_KNEE_OFFSET4_CAM_COUNT       (1U)

/*! @name KNEE_RATIO01_CAM - Camera 0 IR Compress Knee Ratio 01 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_RATIO01_CAM_RATIO0_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_RATIO01_CAM_RATIO0_SHIFT (0U)
#define IR_COMPRESS_KNEE_RATIO01_CAM_RATIO0(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_RATIO01_CAM_RATIO0_SHIFT)) & IR_COMPRESS_KNEE_RATIO01_CAM_RATIO0_MASK)

#define IR_COMPRESS_KNEE_RATIO01_CAM_RATIO1_MASK (0xFFFF0000U)
#define IR_COMPRESS_KNEE_RATIO01_CAM_RATIO1_SHIFT (16U)
#define IR_COMPRESS_KNEE_RATIO01_CAM_RATIO1(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_RATIO01_CAM_RATIO1_SHIFT)) & IR_COMPRESS_KNEE_RATIO01_CAM_RATIO1_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_RATIO01_CAM */
#define IR_COMPRESS_KNEE_RATIO01_CAM_COUNT       (1U)

/*! @name KNEE_RATIO23_CAM - Camera 0 IR Compress Knee Ratio 23 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_RATIO23_CAM_RATIO2_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_RATIO23_CAM_RATIO2_SHIFT (0U)
#define IR_COMPRESS_KNEE_RATIO23_CAM_RATIO2(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_RATIO23_CAM_RATIO2_SHIFT)) & IR_COMPRESS_KNEE_RATIO23_CAM_RATIO2_MASK)

#define IR_COMPRESS_KNEE_RATIO23_CAM_RATIO3_MASK (0xFFFF0000U)
#define IR_COMPRESS_KNEE_RATIO23_CAM_RATIO3_SHIFT (16U)
#define IR_COMPRESS_KNEE_RATIO23_CAM_RATIO3(x)   (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_RATIO23_CAM_RATIO3_SHIFT)) & IR_COMPRESS_KNEE_RATIO23_CAM_RATIO3_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_RATIO23_CAM */
#define IR_COMPRESS_KNEE_RATIO23_CAM_COUNT       (1U)

/*! @name KNEE_RATIO4_CAM - Camera 0 IR Compress Knee Ratio 4 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_RATIO4_CAM_RATIO4_MASK  (0xFFFFU)
#define IR_COMPRESS_KNEE_RATIO4_CAM_RATIO4_SHIFT (0U)
#define IR_COMPRESS_KNEE_RATIO4_CAM_RATIO4(x)    (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_RATIO4_CAM_RATIO4_SHIFT)) & IR_COMPRESS_KNEE_RATIO4_CAM_RATIO4_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_RATIO4_CAM */
#define IR_COMPRESS_KNEE_RATIO4_CAM_COUNT        (1U)

/*! @name KNEE_NPOINT0_CAM - Camera 0 IR Compress New KneePoint 0 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_NPOINT0_CAM_KNEEPOINT_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_NPOINT0_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_NPOINT0_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_NPOINT0_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_NPOINT0_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_NPOINT0_CAM */
#define IR_COMPRESS_KNEE_NPOINT0_CAM_COUNT       (1U)

/*! @name KNEE_NPOINT1_CAM - Camera 0 IR Compress New KneePoint 1 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_NPOINT1_CAM_KNEEPOINT_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_NPOINT1_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_NPOINT1_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_NPOINT1_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_NPOINT1_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_NPOINT1_CAM */
#define IR_COMPRESS_KNEE_NPOINT1_CAM_COUNT       (1U)

/*! @name KNEE_NPOINT2_CAM - Camera 0 IR Compress New KneePoint 2 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_NPOINT2_CAM_KNEEPOINT_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_NPOINT2_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_NPOINT2_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_NPOINT2_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_NPOINT2_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_NPOINT2_CAM */
#define IR_COMPRESS_KNEE_NPOINT2_CAM_COUNT       (1U)

/*! @name KNEE_NPOINT3_CAM - Camera 0 IR Compress New KneePoint 3 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_NPOINT3_CAM_KNEEPOINT_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_NPOINT3_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_NPOINT3_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_NPOINT3_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_NPOINT3_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_NPOINT3_CAM */
#define IR_COMPRESS_KNEE_NPOINT3_CAM_COUNT       (1U)

/*! @name KNEE_NPOINT4_CAM - Camera 0 IR Compress New KneePoint 4 Register */
/*! @{ */

#define IR_COMPRESS_KNEE_NPOINT4_CAM_KNEEPOINT_MASK (0xFFFFU)
#define IR_COMPRESS_KNEE_NPOINT4_CAM_KNEEPOINT_SHIFT (0U)
#define IR_COMPRESS_KNEE_NPOINT4_CAM_KNEEPOINT(x) (((uint32_t)(((uint32_t)(x)) << IR_COMPRESS_KNEE_NPOINT4_CAM_KNEEPOINT_SHIFT)) & IR_COMPRESS_KNEE_NPOINT4_CAM_KNEEPOINT_MASK)
/*! @} */

/* The count of IR_COMPRESS_KNEE_NPOINT4_CAM */
#define IR_COMPRESS_KNEE_NPOINT4_CAM_COUNT       (1U)


/*!
 * @}
 */ /* end of group IR_COMPRESS_Register_Masks */


/*!
 * @}
 */ /* end of group IR_COMPRESS_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* IR_COMPRESS_H_ */

