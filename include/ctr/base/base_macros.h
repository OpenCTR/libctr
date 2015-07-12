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

/**
 * @file ctr/base/base_macros.h
 * @brief libctr base macros.
 */

/**
 * @def CAPI
 * @brief Declare an exported, public function.
 */
#ifndef CAPI
#define CAPI __attribute__ ((pcs("aapcs"), optimize(3), visibility("default")))
#endif

/**
 * @def CTR_ARG_NONNULL
 * @brief Declare that a function parameter cannot be <code>NULL</code>
 */
#ifndef CTR_ARG_NONNULL
#define CTR_ARG_NONNULL(...) __attribute__ ((__nonnull__(__VA_ARGS__)))
#endif

/**
 * @def CTR_UNUSED
 * @brief Declare that a function or a parameter will not be used.
 */
#ifndef CTR_UNUSED
#define CTR_UNUSED __attribute__ ((__unused__))
#endif

/**
 * @def CTR_WARN_UNUSED_RESULT
 * @brief Declare that the function return parameter should be used.
 */
#ifndef CTR_WARN_UNUSED_RESULT
#define CTR_WARN_UNUSED_RESULT __attribute__ ((__warn_unused_result__))
#endif

/**
 * @def CTR_DEPRECATED
 * @brief Declare that a function is depreciated.
 */
#ifndef CTR_DEPRECATED
#define CTR_DEPRECATED __attribute__ ((__deprecated__))
#endif

/**
 * @def CTR_RETURNS_NONNULL
 * @brief Declare that a function will not return <code>NULL</code>.
 */
#ifndef CTR_RETURNS_NONNULL
#define CTR_RETURNS_NONNULL __attribute__ ((returns_nonnull))
#endif

/**
 * @def CTR_ALLOCATE
 * @brief Declare that a function will allocate memory, like <code>malloc()</code>.
 */
#ifndef CTR_ALLOCATE
#define CTR_ALLOCATE __attribute__ ((malloc))
#endif

/**
 * @def CTR_NORETURN
 * @brief Declare that a function will never return.
 */
#ifndef CTR_NORETURN
#define CTR_NORETURN __attribute__ ((noreturn))
#endif

/**
 * @def CTR_API_BEGIN
 * @brief Declare the start of the public API.
 */
#ifndef CTR_API_BEGIN
#ifdef __cplusplus
#define CTR_API_BEGIN extern "C" {
#else
#define CTR_API_BEGIN
#endif
#endif

/**
 * @def CTR_API_END
 * @brief Declare the start of the public API.
 */
#ifndef CTR_API_END
#ifdef __cplusplus
#define CTR_API_END }
#else
#define CTR_API_END
#endif
#endif
