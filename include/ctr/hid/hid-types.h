/**
 * @file ctr/hid/hid-types.h
 * @brief Input types.
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

#ifndef __LIBCTR_HID_TYPES_H__
#define __LIBCTR_HID_TYPES_H__

#include <stdint.h>

#if 0

/**
 * @brief Minimum sound volume level.
 */
#define HID_VOLUME_MIN (0x00)

/**
 * @brief Maximum sound volume level.
 */
#define HID_VOLUME_MAX (0x3F)

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @ingroup hid
 * @typedef struct HIDContext HIDContext
 * @brief Handle to a HID session.
 * @details An HIDContext represents a thread-safe handle to a session with
 * the HID service.
 */
typedef struct struct HIDContext;

/**
 * @ingroup hid
 * @enum HIDKeyStatus
 * @brief Keypad status.
 */
typedef enum {
	HID_KEYPAD_PRESSED 		= 0x00000001, /**< Key is currently pressed. */
	HID_KEYPAD_HELD 		= 0x00000002, /**< Key has been pressed for several keyframes. */
	HID_KEYPAD_RELEASED 	= 0x00000003, /**< Key is not currently being presses. */
} HIDKeyStatus;

/**
 * @ingroup hid
 * @enum HIDKeyCode
 * @brief Key codes.
 * @note The following keys are only available on the New 3DS: 
 *     ::HID_KEY_ZL
 *     ::HID_KEY_ZR
 *     ::HID_KEY_CSTICK_RIGHT
 *     ::HID_KEY_CSTICK_LEFT
 *     ::HID_KEY_CSTICK_UP
 *     ::HID_KEY_CSTICK_DOWN
 */
typedef enum {
	HID_KEY_A 				= (1 <<  0), /**< 'A' */
	HID_KEY_B 				= (1 <<  1), /**< 'B' */
	HID_KEY_SELECT 			= (1 <<  2), /**< Select */
	HID_KEY_START 			= (1 <<  3), /**< Start */
	HID_KEY_DPAD_RIGHT 		= (1 <<  4), /**< Right (DPad) */
	HID_KEY_DPAD_LEFT 		= (1 <<  5), /**< Left (DPad) */
	HID_KEY_DPAD_UP 		= (1 <<  6), /**< Up (DPad) */
	HID_KEY_DPAD_DOWN 		= (1 <<  7), /**< Down (DPad) */
	HID_KEY_R 				= (1 <<  8), /**< 'R' */
	HID_KEY_L 				= (1 <<  9), /**< 'L' */
	HID_KEY_X 				= (1 << 10), /**< 'X' */
	HID_KEY_Y 				= (1 << 11), /**< 'Y' */
	HID_KEY_ZL 				= (1 << 14), /**< 'ZL' */
	HID_KEY_ZR 				= (1 << 15), /**< 'ZR' */
	HID_KEY_TOUCH 			= (1 << 20), /**< Touchpad */
	HID_KEY_CSTICK_RIGHT 	= (1 << 24), /**< Right (C-Stick) */
	HID_KEY_CSTICK_LEFT 	= (1 << 25), /**< Left (C-Stick) */
	HID_KEY_CSTICK_UP 		= (1 << 26), /**< Up (C-Stick) */
	HID_KEY_CSTICK_DOWN 	= (1 << 27), /**< Down (C-Stick) */
	HID_KEY_CPAD_RIGHT 		= (1 << 28), /**< Right (Circle Pad) */
	HID_KEY_CPAD_LEFT 		= (1 << 29), /**< Left (Circle Pad) */
	HID_KEY_CPAD_UP 		= (1 << 30), /**< Up (Circle Pad) */
	HID_KEY_CPAD_DOWN 		= (1 << 31), /**< Down (Circle Pad) */
} HIDKeyCode;

#ifdef __cplusplus
}
#endif

#endif

#endif
