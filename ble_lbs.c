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

/* Attention! 
*  To maintain compliance with Nordic Semiconductor ASA’s Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/

#include "ble_lbs.h"
#include <string.h>
#include "nordic_common.h"
#include "ble_srv_common.h"
#include "app_util.h"


#define INVALID_BATTERY_LEVEL  255

#if 0

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_lbs       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_lbs_t * p_lbs, ble_evt_t * p_ble_evt)
{
    p_lbs->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_lbs       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_lbs_t * p_lbs, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_lbs->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_lbs       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_lbs_t * p_lbs, ble_evt_t * p_ble_evt)
{
    if (p_lbs->is_notification_supported)
    {
        ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
        
        if (
            (p_evt_write->handle == p_lbs->battery_level_handles.cccd_handle)
            &&
            (p_evt_write->len == 2)
        )
        {
            // CCCD written, call application event handler
            if (p_lbs->evt_handler != NULL)
            {
                ble_lbs_evt_t evt;
                
                if (ble_srv_is_notification_enabled(p_evt_write->data))
                {
                    evt.evt_type = BLE_LBS_EVT_NOTIFICATION_ENABLED;
                }
                else
                {
                    evt.evt_type = BLE_LBS_EVT_NOTIFICATION_DISABLED;
                }

                p_lbs->evt_handler(p_lbs, &evt);
            }
        }
    }
}


void ble_lbs_on_ble_evt(ble_lbs_t * p_lbs, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_lbs, p_ble_evt);
            break;
            
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_lbs, p_ble_evt);
            break;
            
        case BLE_GATTS_EVT_WRITE:
            on_write(p_lbs, p_ble_evt);
            break;
            
        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for adding the Battery Level characteristic.
 *
 * @param[in]   p_lbs        Battery Service structure.
 * @param[in]   p_lbs_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t button_char_add(ble_lbs_t * p_lbs, const ble_lbs_init_t * p_lbs_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t             initial_battery_level;
    uint8_t             encoded_report_ref[BLE_SRV_ENCODED_REPORT_REF_LEN];
    uint8_t             init_len;
    

    memset(&cccd_md, 0, sizeof(cccd_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;
    
    memset(&char_md, 0, sizeof(char_md));
    
    char_md.char_props.read   = 1;
    char_md.char_props.notify = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md;
    char_md.p_sccd_md         = NULL;
    
    ble_uuid.type = p_lbs->uuid_type;
    ble_uuid.uuid = LBS_UUID_BUTTON_CHAR;
    
    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    
    initial_battery_level = p_lbs_init->initial_batt_level;
    
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(uint8_t);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(uint8_t);
    attr_char_value.p_value      = &initial_battery_level;
    
    err_code = sd_ble_gatts_characteristic_add(p_lbs->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_lbs->battery_level_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    if (p_lbs_init->p_report_ref != NULL)
    {
        // Add Report Reference descriptor
        BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_REPORT_REF_DESCR);
        
        memset(&attr_md, 0, sizeof(attr_md));

        attr_md.read_perm = p_lbs_init->battery_level_report_read_perm;
        BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);

        attr_md.vloc       = BLE_GATTS_VLOC_STACK;
        attr_md.rd_auth    = 0;
        attr_md.wr_auth    = 0;
        attr_md.vlen       = 0;
        
        init_len = ble_srv_report_ref_encode(encoded_report_ref, p_lbs_init->p_report_ref);
        
        memset(&attr_char_value, 0, sizeof(attr_char_value));

        attr_char_value.p_uuid       = &ble_uuid;
        attr_char_value.p_attr_md    = &attr_md;
        attr_char_value.init_len     = init_len;
        attr_char_value.init_offs    = 0;
        attr_char_value.max_len      = attr_char_value.init_len;
        attr_char_value.p_value      = encoded_report_ref;
        
        err_code = sd_ble_gatts_descriptor_add(p_lbs->battery_level_handles.value_handle,
                                               &attr_char_value,
                                               &p_lbs->report_ref_handle);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    else
    {
        p_lbs->report_ref_handle = BLE_GATT_HANDLE_INVALID;
    }
    
    return NRF_SUCCESS;
}
#endif

uint32_t ble_lbs_init(ble_lbs_t * p_lbs, const ble_lbs_init_t * p_lbs_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_lbs->conn_handle       = BLE_CONN_HANDLE_INVALID;
    p_lbs->led_write_handler = p_lbs_init->led_write_handler;
    
    // Add service
    ble_uuid128_t base_uuid = LBS_UUID_BASE;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_lbs->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    ble_uuid.type = p_lbs->uuid_type;
    ble_uuid.uuid = LBS_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_lbs->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    return NRF_SUCCESS;
}

uint32_t ble_lbs_on_button_change(ble_lbs_t * p_lbs, uint8_t button_state)
{
    return NRF_SUCCESS;
}
