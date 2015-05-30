/**
 * @file ctr/hid/hid-types.h
 */

/*
 * libctr - Library for Nintendo 3DS homebrew.
 * 
 * Copyright (C) 2015 The OpenCTR Project. 
 * 
 * This file is part of libctr. 
 * 
 * libctr is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License version 3 as 
 * published by the Free Software Foundation.
 * 
 * libctr is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with libctr. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBCTR_HID_H__
#define __LIBCTR_HID_H__

#include "hid-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup hid
 * @brief Create a new HID context.
 * @param[out] hid New HID context.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_context_new(HIDContext* hid);

/**
 * @ingroup hid
 * @brief Release a HID context.
 * @param[in] hid HID context to release
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_context_free(HIDContext* hid);

/**
 * @ingroup hid
 * @brief Update the HID context state.
 * @details hid_context_update() <b>MUST</b> be called once-per-frame. If 
 * hid_context_update() is not called, then the internal HID state will not be
 * updated, and hid_read_touchpad(), hid_read_circlepad(), hid_read_accel(),
 * and hid_read_gyro() will return the exact same values as when they were 
 * last called.
 * @param[in] hid HID context to update.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_context_update(HIDContext* hid);

/**
 * @ingroup hid
 * @brief Get the current status of one HID key/button.
 * @param[in] hid HID Context.
 * @param[out] status Current status of @a key.
 * @param[in] key Key/Button to query.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_get_key_status(HIDContext* hid, HIDKeyStatus* status, HIDKeyCode key);

/**
 * @ingroup hid
 * @brief Read the current touchpad values.
 * @param[in] hid HID Context.
 * @param[out] px Current touchpad pixel (X).
 * @param[out] py Current touchpad pixel (Y).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_touchpad(HIDContext* hid, uint16_t* px, uint16_t* py);

/**
 * @ingroup hid
 * @brief Read the current circlepad values.
 * @param[in] hid HID Context.
 * @param[out] dx Current circlepad offset (X).
 * @param[out] dy Current circlepad offset (Y).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_circlepad(HIDContext* hid, int16_t* dx, int16_t dy);

/**
 * @ingroup hid
 * @brief Read the current accelerometer values.
 * @param[in] hid HID Context.
 * @param[out] x Current position (X-axis).
 * @param[out] y Current position (Y-axis).
 * @param[out] z Current position (Z-axis).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_accel(HIDContext* hid, int16_t* x, int16_t* y, int16_t* z);

/**
 * @ingroup hid
 * @brief Read the current gyroscope values.
 * @param[in] hid HID Context.
 * @param[out] roll Current roll rotation.
 * @param[out] yaw Current yaw rotation.
 * @param[out] pitch Current pitch rotation.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_gyro(HIDContext* hid, int16_t* roll, int16_t* yaw, int16_t* pitch);

/**
 * @ingroup hid
 * @brief Get the current volume level (using the volume slider).
 * @param[in] hid HID Context.
 * @param[out] volume Current volume level (#HID_VOLUME_MIN to #HID_VOLUME_MAX).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_get_volume(HIDContext* hid, uint8_t* volume);

#ifdef __cplusplus
}
#endif

#endif
