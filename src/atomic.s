################################################################################
# libctr - Library for Nintendo 3DS homebrew.
#
# Copyright (C) 2015, OpenCTR Contributors.
#
# This file is part of libctr.
#
# libctr is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3 as published by
# the Free Software Foundation.
#
# libctr is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License
# along with libctr. If not, see <http://www.gnu.org/licenses/>.
################################################################################

.arm
.align 4

.global ctrAtomicAdd
.global ctrAtomicSub
.global ctrAtomicAnd
.global ctrAtomicOr
.global ctrAtomicStore
.global ctrAtomicIncrement
.global ctrAtomicDecrement
.global ctrAtomicCompareAndSwap
.global ctrAtomicRead

.type ctrAtomicAdd, %function
.type ctrAtomicSub, %function
.type ctrAtomicAnd, %function
.type ctrAtomicOr, %function
.type ctrAtomicStore, %function
.type ctrAtomicIncrement, %function
.type ctrAtomicDecrement, %function
.type ctrAtomicCompareAndSwap, %function
.type ctrAtomicRead, %function

ctrAtomicAdd:
    pld [r0]
ctrAtomicAddLoop:
    ldrex r3, [r0]
    add r3, r3, r1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicAddLoop
    bx lr

ctrAtomicSub:
    pld [r0]
ctrAtomicSubLoop:
    ldrex r3, [r0]
    sub r3, r3, r1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicSubLoop
    bx lr

ctrAtomicAnd:
    pld [r0]
ctrAtomicAndLoop:
    ldrex r3, [r0]
    and r3, r3, r1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicAndLoop
    bx lr

ctrAtomicOr:
    pld [r0]
ctrAtomicOrLoop:
    ldrex r3, [r0]
    orr r3, r3, r1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicOrLoop
    bx lr

ctrAtomicStore:
    pld [r0]
ctrAtomicStoreLoop:
    ldrex r3, [r0]
    mov r3, r1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicStoreLoop
    bx lr

ctrAtomicIncrement:
    pld [r0]
ctrAtomicIncrementLoop:
    ldrex r3, [r0]
    add r3, r3, #1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicIncrementLoop
    bx lr

ctrAtomicDecrement:
    pld [r0]
ctrAtomicDecrementLoop:
    ldrex r3, [r0]
    sub r3, r3, #1
    strex r2, r3, [r0]
    cmp r2, #0
    bne ctrAtomicDecrementLoop
    bx lr

ctrAtomicCompareAndSwap:
    pld [r0]
ctrAtomicCompareAndSwapLoop:
    ldrex ip, [r0]
    cmp ip, r1
    bne ctrAtomicCompareAndSwapReturn
    strex r3, r2, [r0]
    cmp r3, #0
    bne ctrAtomicCompareAndSwapLoop
    bx lr
ctrAtomicCompareAndSwapReturn:
    bx lr

ctrAtomicRead:
    pld [r0]
    mov r3, r0
ctrAtomicReadLoop:
    ldrex r0, [r3]
    add r2, r0, #0
    strex r1, r2, [r3]
    cmp r1, #0
    bne ctrAtomicReadLoop
    bx lr
