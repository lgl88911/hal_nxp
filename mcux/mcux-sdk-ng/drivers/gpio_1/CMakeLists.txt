# Copyright 2024 NXP
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_MCUX_COMPONENT_driver.gpio_1)
    mcux_component_version(2.1.1)

    mcux_add_source(SOURCES fsl_gpio.h fsl_gpio.c)

    mcux_add_include(INCLUDES .)

endif()
