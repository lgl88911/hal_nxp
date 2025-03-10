include_guard(GLOBAL)


if (CONFIG_USE_BOARD_Project_Template_lpcxpresso51u68)
# Add set(CONFIG_USE_BOARD_Project_Template_lpcxpresso51u68 true) in config.cmake to use this component

message("BOARD_Project_Template_lpcxpresso51u68 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_usart_adapter AND (CONFIG_DEVICE_ID STREQUAL LPC51U68) AND CONFIG_USE_device_LPC51U68_startup AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_flexcomm_usart AND CONFIG_USE_driver_lpc_gpio AND CONFIG_USE_driver_lpc_iocon AND CONFIG_USE_driver_power AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)) AND (CONFIG_BOARD STREQUAL lpcxpresso51u68))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.h "" BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/board.c "" BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/clock_config.c "" BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/pin_mux.c "" BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.h ${CMAKE_CURRENT_LIST_DIR}/project_template/. BOARD_Project_Template_lpcxpresso51u68)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/project_template/peripherals.c "" BOARD_Project_Template_lpcxpresso51u68)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/project_template/.
)

else()

message(SEND_ERROR "BOARD_Project_Template_lpcxpresso51u68 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

