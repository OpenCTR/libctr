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

#ifndef __LIBCTR_GSP_STRUCT_H__
#define __LIBCTR_GSP_STRUCT_H__

/**
 * @file ctr/gsp/gsp_struct.h
 * @brief GSP data structures.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Display target to draw onto a screen.
 * @details Display targets are the usual way for displaying a framebuffer.
 */
typedef struct {
	uint8_t*          colorAddress[2]; /**< Primary and secondary framebuffers. */
	CtrGspColorFormat colorFormat[2];  /**< Framebuffer color formats. */
	uint16_t          x;               /**< Screen offset on the x-axis. */
	uint16_t          y;               /**< Screen offset on the y-axis. */
	uint16_t          width;           /**< Width of the render buffer. */
	uint16_t          height;          /**< Height of the render buffer. */
} CtrGspTarget;

/**
 * @private
 * @brief Opaque data type for CtrGspContextData
 */
struct CtrGspContextDataPrivate;

/**
 * @brief Thread-safe container for GSP data.
 * @details The contents of this container are private, and should 
 * <em>ABSOLUTELY never be modified by the user</em>.
 */
typedef struct CtrGspContextDataPrivate CtrGspContextData;

/**
 * @private
 * @brief The default GSP context data.
 */
extern CtrGspContextData * gCtrGspCurrentContext;

CTR_API_END

#endif
