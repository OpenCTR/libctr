/**
 * @file ctr/error/error-types.h
 * @brief Error types.
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

#ifndef __LIBCTR_ERROR_TYPES_H__
#define __LIBCTR_ERROR_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Error type.
 * @details All errors in libctr are a 32-bit signed
 * integer.
 */
typedef int32_t CError;

#ifdef __cplusplus
}
#endif

#endif
