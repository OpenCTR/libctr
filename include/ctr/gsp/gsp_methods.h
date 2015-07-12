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

#ifndef __LIBCTR_GSP_METHODS_H__
#define __LIBCTR_GSP_METHODS_H__

/**
 * @file ctr/gsp/gsp_methods.h
 * @brief GSP functions.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Initialize a GSP context.
 * @param[out] context Newly created GSP context.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrGspContextDataInitialize(CtrGspContextData* context) CTR_ARG_NONNULL(1);

/**
 * @brief Release a GSP context.
 * @param[in] context Unused GSP context.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrGspContextDataFinalize(CtrGspContextData* context) CTR_ARG_NONNULL(1);

/**
 * @brief Allocate & align local memory.
 * @param[in] alignment Page size.
 * @param[in] size Size to allocate.
 * @return Address to allocated buffer in local memory.
 */
CAPI void* ctrGspLocalAlign(const uint32_t alignment, const uint32_t size);

/**
 * @brief Deallocate a buffer in local memory.
 * @param[in,out] addr Address allocated with ctrGspLocalFree().
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrGspLocalFree(void* addr);

/**
 * @brief Sync the displays and the GPU.
 * @param[in] context GSP context data.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrGspFlush(CtrGspContextData* context) CTR_ARG_NONNULL(1);

/**
 * @brief Wait for a vsync to occur on a screen.
 * @param[in] screen Screen to wait for.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrGspWaitForVSync(CtrGspContextData* context, CtrGspScreen screen) CTR_ARG_NONNULL(1);

/**
 * @brief Register a display target.
 * @param[in] context GSP context data.
 * @param[in] tgt Display target.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrGspSetTarget(CtrGspContextData* context, const CtrGspTarget* tgt) CTR_ARG_NONNULL(1);

/**
 * @brief Return the pixel size for a color format.
 * @param[in] format Color format.
 * @return Size (in bytes) of 1 pixel.
 */
CAPI uint8_t ctrGspPixelSize(CtrGspColorFormat format);

CTR_API_END

#endif
