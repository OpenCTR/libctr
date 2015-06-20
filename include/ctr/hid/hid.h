/**
 * @file ctr/hid/hid.h
 * @brief Interface to the HID service.
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

#if 0
/**
 * @ingroup hid
 * @brief Create a new session with the HID service.
 * @param[out] ctx New HID context.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_session_new(HIDContext* ctx);

/**
 * @ingroup hid
 * @brief Close an HID session.
 * @param[in] ctx HID context representing a session.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_session_close(HIDContext* ctx);

/**
 * @ingroup hid
 * @brief Update the HID context state.
 * @details hid_context_update() <b>MUST</b> be called once-per-frame. If 
 * hid_context_update() is not called, then the internal HID state will not be
 * updated, and hid_read_touchpad(), hid_read_circlepad(), hid_read_accel(),
 * and hid_read_gyro() will return the exact same values as when they were 
 * last called.
 * @param[in] ctx HID context to update.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_context_update(HIDContext* ctx);

#if 0

// Ideas for future API:

typedef void(*HIDEventCB)(HIDKey key, HIDStatus status);

int hid_add_callback(HIDContext* hid, HIDEventCB callback, HIDEventType);
	+ Adds a callback to hid.
	+ hid->callbacks[HID_SLOT_Y] = callback;

uint8_t* hid_get_state(HIDContext* hid);
	+ uint8_t* keystate = malloc(HID_KEYS_MAX);
	+ memset(state, 0x00, HID_KEYS_MAX);
	+ if(isKeyPressedA()) state[HID_KEY_A] = 0x01;
	+ return state;

#endif



/**
 * @ingroup hid
 * @brief Get the current status of one HID key/button.
 * @param[in] ctx HID Context.
 * @param[out] status Current status of @a key.
 * @param[in] key Key/Button to query.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_get_key_status(HIDContext* ctx, HIDKeyStatus* status, HIDKeyCode key);




/**
 * @ingroup hid
 * @brief Read the current touchpad values.
 * @param[in] ctx HID Context.
 * @param[out] px Current touchpad pixel (X).
 * @param[out] py Current touchpad pixel (Y).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_touchpad(HIDContext* ctx, uint16_t* px, uint16_t* py);

/**
 * @ingroup hid
 * @brief Read the current circlepad values.
 * @param[in] ctx HID Context.
 * @param[out] dx Current circlepad offset (X).
 * @param[out] dy Current circlepad offset (Y).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_circlepad(HIDContext* ctx, int16_t* dx, int16_t dy);

/**
 * @ingroup hid
 * @brief Read the current accelerometer values.
 * @param[in] ctx HID Context.
 * @param[out] x Current position (X-axis).
 * @param[out] y Current position (Y-axis).
 * @param[out] z Current position (Z-axis).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_accel(HIDContext* ctx, int16_t* x, int16_t* y, int16_t* z);

/**
 * @ingroup hid
 * @brief Read the current gyroscope values.
 * @param[in] ctx HID Context.
 * @param[out] roll Current roll rotation.
 * @param[out] yaw Current yaw rotation.
 * @param[out] pitch Current pitch rotation.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_read_gyro(HIDContext* ctx, int16_t* roll, int16_t* yaw, int16_t* pitch);

/**
 * @ingroup hid
 * @brief Get the current volume level (using the volume slider).
 * @param[in] ctx HID Context.
 * @param[out] volume Current volume level (#HID_VOLUME_MIN to #HID_VOLUME_MAX).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int hid_get_volume(HIDContext* ctx, uint8_t* volume);

#endif

#ifdef __cplusplus
}
#endif

#endif
