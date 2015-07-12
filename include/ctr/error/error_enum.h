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

#ifndef __LIBCTR_ERROR_ENUM_H__
#define __LIBCTR_ERROR_ENUM_H__

/**
 * @file ctr/error/error_enum.h
 * @brief Error enums.
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

CTR_API_END

#endif
