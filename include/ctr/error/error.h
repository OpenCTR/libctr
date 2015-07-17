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

#ifndef __LIBCTR_ERROR_H__
#define __LIBCTR_ERROR_H__

/**
 * @file ctr/error/error.h
 * @brief libctr Error API.
 */

#include "ctr/base.h"
#include "ctr/error/error_types.h"

CTR_API_BEGIN

/**
 * @brief Return the latest error number.
 * @details The libctr equivalent of errno. libctr functions 
 * return 0 if they were successful, or -1 if they encountered an 
 * error. In the later case, <code>cerror()</code> may be called
 * to obtain an error number code corresponding to the error 
 * encountered inside the libctr function.
 */
CAPI int cerror(void);

/**
 * @brief Return a brief description of an error number.
 * @param err Error number (usually obtained through <code>cerror()</code>).
 * @return Brief description of the error.
 */
CAPI const char* cstrerror(int err);

CTR_API_END

#endif
