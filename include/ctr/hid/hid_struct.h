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

#ifndef __LIBCTR_HID_STRUCT_H__
#define __LIBCTR_HID_STRUCT_H__

/**
 * @file ctr/hid/hid_struct.h
 * @brief HID data structures.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @private
 * @brief Opaque data type for CtrHidContextData
 */
struct CtrHidContextDataPrivate;

/**
 * @brief Thread-safe container for HID data.
 * @details The contents of this container are private, and should 
 * <em>ABSOLUTELY never be modified by the user</em>.
 */
typedef struct CtrHidContextDataPrivate CtrHidContextData;

/**
 * @private
 * @brief The default HID context data.
 */
extern CtrHidContextData * gCtrHID;

CTR_API_END

#endif
