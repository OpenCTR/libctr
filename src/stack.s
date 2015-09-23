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
.align 2

.global initSystem
.global __ctru_exit

.type initSystem, %function
.type __ctru_exit, %function

initSystem:
    ldr r2, =saved_stack
    str sp, [r2]
    str lr, [r2,#4]

    bl ctr_init

    ldr r2, =fake_heap_start
    ldr sp, [r2]

    ldr r3, =__stacksize__
    ldr r3, [r3]
    add sp, sp, r3

    bl __libc_init_array

    ldr r2, =saved_stack
    ldr lr, [r2,#4]
    bx lr

__ctru_exit:
    bl __libc_fini_array

    ldr r2, =saved_stack
    ldr sp, [r2]
    b ctr_exit

.data
.align 2

__stacksize__:
    .word 32 * 1024
    .weak __stacksize__

.bss
.align 2

saved_stack:
    .space 8

