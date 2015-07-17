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

#ifndef __LIBCTR_ATOMIC_H__
#define __LIBCTR_ATOMIC_H__

/**
 * @file ctr/atomic/atomic.h
 * @brief Atomic API.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Atomically add a value to a variable.
 * @param[in,out] ea Address of the value to atomically update.
 * @param[in] value Value to add to the variable.
 */
void ctrAtomicAdd(uint32_t* ea, const uint32_t value);

/**
 * @brief Atomically subtract a value from a variable.
 * @param[in,out] ea Address of the value to atomically update.
 * @param[in] value Value to subtract from the variable.
 */
void ctrAtomicSub(uint32_t* ea, const uint32_t value);

/**
 * @brief Atomically perform an AND operation on a variable.
 * @param[in,out] ea Address of the value to atomically update.
 * @param[in] value Value to AND with the variable.
 */
void ctrAtomicAnd(uint32_t* ea, const uint32_t value);

/**
 * @brief Atomically perform an OR operation on a variable.
 * @param[in,out] ea Address of the value to atomically update.
 * @param[in] value Value to OR with the variable.
 */
void ctrAtomicOr(uint32_t* ea, const uint32_t value);

/**
 * @brief Atomically set the value of a variable.
 * @param[in,out] ea Address of the value to atomically update.
 * @param[in] value Value to OR with the variable.
 */
void ctrAtomicStore(uint32_t* ea, const uint32_t value);

/**
 * @brief Atomically increment a variable.
 * @param[in,out] ea Address of the value to atomically update.
 */
void ctrAtomicIncrement(uint32_t* ea);

/**
 * @brief Atomically decrement a variable.
 * @param[in,out] ea Address of the value to atomically update.
 */
void ctrAtomicDecrement(uint32_t* ea);

/**
 * @brief Atomically replace the value of a variable, if it matches a certain
 * value.
 * @param[in,out] ea Address of the value to atomically update.
 * @param[in] compare Value to compare against.
 * @param[in] value Replacement value, if the variable is a match.
 */
void ctrAtomicCompareAndSwap(uint32_t* ea, uint32_t compare, uint32_t value);

/**
 * @brief Atomically read an integer value.
 * @param[in] ea Address of the variable to atomically read.
 * @return Current value of the atomic variable.
 */
uint32_t ctrAtomicRead(uint32_t* ea);

CTR_API_END

#endif
