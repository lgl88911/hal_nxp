# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.lpspi_edma)
    mcux_component_version(2.4.5)

    mcux_add_source(SOURCES fsl_lpspi_edma.h fsl_lpspi_edma.c)

    mcux_add_include(INCLUDES .)

endif()

if(CONFIG_MCUX_COMPONENT_driver.lpspi)
    mcux_component_version(2.6.9)

    mcux_add_source(SOURCES fsl_lpspi.c fsl_lpspi.h)

    mcux_add_include(INCLUDES .)

endif()
