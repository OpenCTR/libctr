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

#ifndef __LIBCTR_HID_ENUM_H__
#define __LIBCTR_HID_ENUM_H__

/**
 * @file ctr/hid/hid_enum.h
 * @brief HID enums.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Key codes.
 * @note The following keys are only available on the New 3DS: 
 * ::CTR_HID_KEY_ZL, ::CTR_HID_KEY_ZR, 
 * ::CTR_HID_KEY_CSTICK_RIGHT, ::CTR_HID_KEY_CSTICK_LEFT, 
 * ::CTR_HID_KEY_CSTICK_UP, ::CTR_HID_KEY_CSTICK_DOWN.
 */
typedef enum {
	CTR_HID_KEY_A 				= (1 <<  0), /**< 'A' */
	CTR_HID_KEY_B 				= (1 <<  1), /**< 'B' */
	CTR_HID_KEY_SELECT 			= (1 <<  2), /**< Select */
	CTR_HID_KEY_START 			= (1 <<  3), /**< Start */
	CTR_HID_KEY_DPAD_RIGHT 		= (1 <<  4), /**< Right (DPad) */
	CTR_HID_KEY_DPAD_LEFT 		= (1 <<  5), /**< Left (DPad) */
	CTR_HID_KEY_DPAD_UP 		= (1 <<  6), /**< Up (DPad) */
	CTR_HID_KEY_DPAD_DOWN 		= (1 <<  7), /**< Down (DPad) */
	CTR_HID_KEY_R 				= (1 <<  8), /**< 'R' */
	CTR_HID_KEY_L 				= (1 <<  9), /**< 'L' */
	CTR_HID_KEY_X 				= (1 << 10), /**< 'X' */
	CTR_HID_KEY_Y 				= (1 << 11), /**< 'Y' */
	CTR_HID_KEY_ZL 				= (1 << 14), /**< 'ZL' */
	CTR_HID_KEY_ZR 				= (1 << 15), /**< 'ZR' */
	CTR_HID_KEY_TOUCH 			= (1 << 20), /**< Touchpad */
	CTR_HID_KEY_CSTICK_RIGHT 	= (1 << 24), /**< Right (C-Stick) */
	CTR_HID_KEY_CSTICK_LEFT 	= (1 << 25), /**< Left (C-Stick) */
	CTR_HID_KEY_CSTICK_UP 		= (1 << 26), /**< Up (C-Stick) */
	CTR_HID_KEY_CSTICK_DOWN 	= (1 << 27), /**< Down (C-Stick) */
	CTR_HID_KEY_CPAD_RIGHT 		= (1 << 28), /**< Right (Circle Pad) */
	CTR_HID_KEY_CPAD_LEFT 		= (1 << 29), /**< Left (Circle Pad) */
	CTR_HID_KEY_CPAD_UP 		= (1 << 30), /**< Up (Circle Pad) */
	CTR_HID_KEY_CPAD_DOWN 		= (1 << 31), /**< Down (Circle Pad) */
} CtrHidKey;

CTR_API_END

#endif
