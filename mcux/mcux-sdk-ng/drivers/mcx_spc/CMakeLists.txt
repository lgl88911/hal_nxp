# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.mcx_spc)
    mcux_component_version(2.7.0)

    mcux_add_source(SOURCES fsl_spc.h fsl_spc.c)

    mcux_add_include(INCLUDES .)

endif()
