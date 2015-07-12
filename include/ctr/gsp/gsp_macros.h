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

#ifndef __LIBCTR_GSP_MACROS_H__
#define __LIBCTR_GSP_MACROS_H__

/**
 * @file ctr/gsp/gsp_macros.h
 * @brief GSP macros.
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
#define CTR_GSP_THIS gCtrGspCurrentContext

#endif
