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

#ifndef __LIBCTR_BASE_H__
#define __LIBCTR_BASE_H__

/**
 * @file ctr/base.h
 * @brief Base API.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * @def CAPI
 * @brief Declare an exported, public function.
 */
#define CAPI __attribute__((pcs("aapcs"), optimize(3), visibility("default")))

/**
 * @def CTR_ARG_NONNULL
 * @brief Declare that a function parameter cannot be <code>NULL</code>
 */
#define CTR_ARG_NONNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))

/**
 * @def CTR_UNUSED
 * @brief Declare that a function or a parameter will not be used.
 */
#define CTR_UNUSED __attribute__((__unused__))

/**
 * @def CTR_WARN_UNUSED_RESULT
 * @brief Declare that the function return parameter should be used.
 */
#define CTR_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))

/**
 * @def CTR_DEPRECATED
 * @brief Declare that a function is depreciated.
 */
#define CTR_DEPRECATED __attribute__((__deprecated__))

/**
 * @def CTR_RETURNS_NONNULL
 * @brief Declare that a function will not return <code>NULL</code>.
 */
#define CTR_RETURNS_NONNULL __attribute__((returns_nonnull))

/**
 * @def CTR_ALLOCATE
 * @brief Declare that a function will allocate memory, like
 * <code>malloc()</code>.
 */
#define CTR_ALLOCATE __attribute__((malloc))

/**
 * @def CTR_NORETURN
 * @brief Declare that a function will never return.
 */
#define CTR_NORETURN __attribute__((noreturn))

/**
 * @def CTR_API_BEGIN
 * @brief Declare the start of the public API.
 */
#ifdef __cplusplus
#define CTR_API_BEGIN extern "C" {
#else
#define CTR_API_BEGIN
#endif

/**
 * @def CTR_API_END
 * @brief Declare the end of the public API.
 */
#ifdef __cplusplus
#define CTR_API_END }
#else
#define CTR_API_END
#endif

#endif
