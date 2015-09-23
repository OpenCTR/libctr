/*
 *******************************************************************************
 * libctr - Library for Nintendo 3DS homebrew.
 *
 * Copyright (C) 2015, OpenCTR Contributors.
 *
 * This file is part of libctr.
 *
 * libctr is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * libctr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libctr. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
*/

#ifndef __LIBCTR_ERROR_H__
#define __LIBCTR_ERROR_H__

/**
 * @file ctr/error.h
 * @brief Error API.
 */

/**
 * @todo Fill ctr/error.h using 3DBrew errors page.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @enum CtrErrors
 * @brief Basic libctr errors.
 * @todo Add more errors.
 */
enum CtrErrors {
    /** Request timed out. */
    CTR_ERROR_TIMEOUT = (0x09401BFE),
    /** Invalid handle. */
    CTR_ERROR_INVALID_HANDLE = (0xD8E007F7),
    /** Argument was outside of valid range. */
    CTR_ERROR_ARG_INVALID_RANGE = (0xE0E01BFD),
    /** Argument is an invalid pointer. */
    CTR_ERROR_ARG_INVALID_POINTER = (0xD8E007F6),
    /** Request could not be found. */
    CTR_ERROR_NOT_FOUND = (0xD88007FA),
    /** Port name was too long. */
    CTR_ERROR_PORT_NAME_TOO_LONG = (0xE0E0181E),
};

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
CAPI const char *cstrerror(int err);

CTR_API_END

#endif
