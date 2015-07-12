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

#ifndef __LIBCTR_GSP_ENUM_H__
#define __LIBCTR_GSP_ENUM_H__

/**
 * @file ctr/gsp/gsp_enum.h
 * @brief GSP enums.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Available screens.
 * @details These names were chosen for technical accuracy. For easier to
 * remember names, use CTR_GSP_TOP_SCREEN, CTR_GSP_BOTTOM_SCREEN, and
 * CTR_GSP_STEREO_SCREEN instead.
 */
typedef enum {
	CTR_GSP_SCREEN0 	= 0x00, /**< Top screen. */
	CTR_GSP_SCREEN0_ALT = 0x01, /**< Top screen (alternate). */
	CTR_GSP_SCREEN1 	= 0x02, /**< Bottom screen. */
	CTR_GSP_SCREEN_ALL  = 0x03, /**< Top and bottom screen. */
} CtrGspScreen;

/**
 * @brief Color formats.
 */
typedef enum {
	/**
	 * 32-bit color format that uses 8-bit red, 8-bit green, 8-bit blue, and
	 * 8-bit alpha.
	 */
	CTR_GSP_COLOR_FORMAT_RGBA8  = 0x00,
	/**
	 * 24-bit color format that uses 8-bit blue, 8-bit green, and 8-bit red.
	 */
	CTR_GSP_COLOR_FORMAT_BGR8   = 0x01,
	/**
	 * A 16-bit color format that uses 5-bit red, 5-bit green, 5-bit blue, and
	 * 1-bit alpha.
	 */
	CTR_GSP_COLOR_FORMAT_RGB5A1 = 0x02,
	/**
	 * A 16-bit color format that uses 5-bit red, 6-bit green, and 5-bit blue.
	 */
	CTR_GSP_COLOR_FORMAT_RGB565 = 0x03,
	/**
	 * 16-bit color format that uses 4-bit red, 4-bit green, 4-bit blue, and
	 * 4-bit alpha.
	 */
	CTR_GSP_COLOR_FORMAT_RGBA4  = 0x04,
} CtrGspColorFormat;

CTR_API_END

#endif
