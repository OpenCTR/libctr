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

#ifndef __LIBCTR_ERROR_PRIVATE_H__
#define __LIBCTR_ERROR_PRIVATE_H__

/**
 * @file ctr/error_private.h
 * @brief Error API (Private).
 */

#include "ctr/base_private.h"
#include "ctr/error.h"

CTR_API_BEGIN

/**
 * @brief Obtain a pointer to the libctr errno.
 * Returns a thread-safe pointer for libctr
 * functions to set.
 */
int *cerrorptr(void);

/**
 * @brief Set the libctr errno.
 * @details Uses atomic operations to set the value of cerrno.
 * Only downside is that while cerrno is <i>thread-safe</i>, it
 * is <em>not</em> <i>thread-local</i>.
 * @param[in] error Error number to set cerrno as.
 */
void cerror_set(int error);

CTR_API_END

#endif
