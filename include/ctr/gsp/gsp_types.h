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

/** Top screen. */
#define CTR_GSP_TOP_SCREEN (CTR_GSP_SCREEN0)
/** Bottom screen. */
#define CTR_GSP_BOTTOM_SCREEN (CTR_GSP_SCREEN1)
/** Stereoscopic 3D screen. */
#define CTR_GSP_STEREO_SCREEN (CTR_GSP_SCREEN0_ALT)
/** Top and bottom screens. */
#define CTR_GSP_BOTH_SCREENS (CTR_GSP_SCREEN_ALL)
/** Width of the top screen. */
#define CTR_GSP_SCREEN0_WIDTH (240)
/** Height of the top screen. */
#define CTR_GSP_SCREEN0_HEIGHT (400)
/** Width of the bottom screen. */
#define CTR_GSP_SCREEN1_WIDTH (240)
/** Height of the bottom screen. */
#define CTR_GSP_SCREEN1_HEIGHT (320)
/** Alignment size for GSP framebuffers. */
#define CTR_GSP_DISPLAY_ALIGN_SIZE (0x10)
/** Current GSP context. */
#define CTR_GSP_THIS gGSP

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

/**
 * @brief Display target to draw onto a screen.
 * @details Display targets are the usual way for rendering a framebuffer.
 * 
 * The top screen has two framebuffers - one for the left eye, the other for
 * the right eye. The second framebuffer will not be used when rendering to
 * the bottom screen.
 */
typedef struct {
	/** Address of primary and secondary framebuffers. */
	uint8_t* address[2];
	/** Framebuffer color format. */
	CtrGspColorFormat format;
	/** Screen offset on the x-axis. */
	uint16_t x;
	/** Screen offset on the y-axis. */
	uint16_t y;
	/** Width of the render buffer. */
	uint16_t width;
	/** Height of the render buffer. */
	uint16_t height;
	/** Target screen - CTR_GSP_TOP_SCREEN or CTR_GSP_BOTTOM_SCREEN. */
	uint8_t screen;
} CtrGspTarget;

/**
 * @brief GSP Context Data (Private).
 * @warning The contents of this data structure should
 * <em>never</em> be modified by the user.
 */
struct CtrGspContextDataPrivate;

/**
 * @brief GSP Context Data.
 */
typedef struct CtrGspContextDataPrivate CtrGspContextData;

/**
 * @var gGSP
 * @brief Global GSP Context Data.
 * @details <code>gGSP</code> refers to the global GSP context data.
 * It is created during the GSP startup sequence, and should be thread-safe.
 * 
 * Developers should not refer to <code>gGSP</code> directly, and should
 * use CTR_GSP_THIS instead.
 */
extern CtrGspContextData * gGSP;

CTR_API_END

#endif
