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
#ifndef CAPI
#define CAPI __attribute__((pcs("aapcs"), optimize(3), visibility("default")))
#endif

/**
 * @def CTR_ARG_NONNULL
 * @brief Declare that a function parameter cannot be <code>NULL</code>
 */
#ifndef CTR_ARG_NONNULL
#define CTR_ARG_NONNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#endif

/**
 * @def CTR_UNUSED
 * @brief Declare that a function or a parameter will not be used.
 */
#ifndef CTR_UNUSED
#define CTR_UNUSED __attribute__((__unused__))
#endif

/**
 * @def CTR_WARN_UNUSED_RESULT
 * @brief Declare that the function return parameter should be used.
 */
#ifndef CTR_WARN_UNUSED_RESULT
#define CTR_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#endif

/**
 * @def CTR_DEPRECATED
 * @brief Declare that a function is depreciated.
 */
#ifndef CTR_DEPRECATED
#define CTR_DEPRECATED __attribute__((__deprecated__))
#endif

/**
 * @def CTR_RETURNS_NONNULL
 * @brief Declare that a function will not return <code>NULL</code>.
 */
#ifndef CTR_RETURNS_NONNULL
#define CTR_RETURNS_NONNULL __attribute__((returns_nonnull))
#endif

/**
 * @def CTR_ALLOCATE
 * @brief Declare that a function will allocate memory, like
 * <code>malloc()</code>.
 */
#ifndef CTR_ALLOCATE
#define CTR_ALLOCATE __attribute__((malloc))
#endif

/**
 * @def CTR_NORETURN
 * @brief Declare that a function will never return.
 */
#ifndef CTR_NORETURN
#define CTR_NORETURN __attribute__((noreturn))
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
 * @brief Declare the end of the public API.
 */
#ifndef CTR_API_END
#ifdef __cplusplus
#define CTR_API_END }
#else
#define CTR_API_END
#endif
#endif

/**
 * @def CTR_CONTEXT_DECLARE(module,type,global)
 * @brief Create a new opaque data structure to hold context data.
 *
 * @param[in] module Namespace the context belongs in. A (extern) global
 * variable named <code>g&lt;MODULE_NAME&gt;</code> is declared.
 * Developers are encouraged to define a macro that refers to this global
 * variable, instead of having users refer to it directly (e.x
 * <code>#define CTR_GSP_THIS gGSP</code>. This will allow existing
 * applications to still compile even if the naming scheme is changed.
 *
 * @param[in] type Name of the opaque data type. First, an empty
 * <code>struct</code> is created, named <code>&lt;TYPE&gt;Private</code>.
 * Then, <code>&lt;TYPE&gt;</code> is defined as a type of the private type.
 * This creates an opaque data type. In your implementation, you must define a
 * <code>struct</code> name <code>&lt;TYPE&gt;Private</code>.
 */
#ifndef CTR_CONTEXT_DECLARE
#define CTR_CONTEXT_DECLARE(module, type) \
    struct type##Private;                 \
    typedef struct type##Private type;    \
    extern type *g##module;
#endif

#endif
