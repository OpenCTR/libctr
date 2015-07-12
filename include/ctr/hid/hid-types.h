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

#include "ctr/base/base.h"




#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif


#if 0

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



#endif

#endif
