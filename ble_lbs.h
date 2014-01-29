/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the license.txt file.
 */

#ifndef BLE_LBS_H__
#define BLE_LBS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#define LBS_UUID_BASE {0x23, 0xD1, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}
#define LBS_UUID_SERVICE 0x1523
#define LBS_UUID_LED_CHAR 0x1525
#define LBS_UUID_BUTTON_CHAR 0x1524

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
