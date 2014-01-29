/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 *
 * @defgroup ble_sdk_srv_bas LED Button Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief LED Button Service module.
 *
 * @details This module implements the LED Button Service with the Battery Level characteristic.
 *          During initialization it adds the LED Button Service and Battery Level characteristic
 *          to the BLE stack database. Optionally it can also add a Report Reference descriptor
 *          to the Battery Level characteristic (used when including the LED Button Service in
 *          the HID service).
 *
 *          If specified, the module will support notification of the Battery Level characteristic
 *          through the ble_lbs_battery_level_update() function.
 *          If an event handler is supplied by the application, the LED Button Service will
 *          generate LED Button Service events to the application.
 *
 * @note The application must propagate BLE stack events to the LED Button Service module by calling
 *       ble_lbs_on_ble_evt() from the from the @ref ble_stack_handler callback.
 *
 * @note Attention! 
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile 
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_LBS_H__
#define BLE_LBS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"


// Forward declaration of the ble_lbs_t type. 
typedef struct ble_lbs_s ble_lbs_t;

typedef void (*ble_lbs_led_write_handler_t) (ble_lbs_t * p_lbs, uint8_t new_state);

typedef struct
{
    ble_lbs_led_write_handler_t led_write_handler;                    /**< Event handler to be called when LED characteristic is written. */
} ble_lbs_init_t;

/**@brief LED Button Service structure. This contains various status information for the service. */
typedef struct ble_lbs_s
{
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    led_char_handles;
    ble_gatts_char_handles_t    button_char_handles;
    uint8_t                     uuid_type;
    uint16_t                    conn_handle;
    ble_lbs_led_write_handler_t led_write_handler;
} ble_lbs_t;

/**@brief Function for initializing the LED Button Service.
 *
 * @param[out]  p_lbs       LED Button Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_lbs_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_lbs_init(ble_lbs_t * p_lbs, const ble_lbs_init_t * p_lbs_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the LED Button Service.
 *
 *
 * @param[in]   p_lbs      LED Button Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_lbs_on_ble_evt(ble_lbs_t * p_lbs, ble_evt_t * p_ble_evt);

/**@brief Function for sending a button state notification.
 */
uint32_t ble_lbs_on_button_change(ble_lbs_t * p_lbs, uint8_t button_state);

#endif // BLE_LBS_H__

/** @} */
