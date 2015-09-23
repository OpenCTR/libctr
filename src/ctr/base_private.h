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

#ifndef __LIBCTR_BASE_PRIVATE_H__
#define __LIBCTR_BASE_PRIVATE_H__

/**
 * @private
 * @file ctr/base_private.h
 * @brief Base API (Private).
 */

#include <sys/iosupport.h>
#include <malloc.h>
#include <errno.h>

#include "ctr/base.h"

#define CTR_INIT __attribute__((constructor(107)))
#define CTR_FINI __attribute__((destructor(107)))

#endif
