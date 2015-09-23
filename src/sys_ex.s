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

.global sys_get_tls
.global sys_get_commandbuffer
.global sys_control_memory_ex
.global sys_query_memory_ex
.global sys_process_exit
.global sys_thread_create_ex
.global sys_thread_exit
.global sys_thread_sleep_ex
.global sys_mutex_new_ex
.global sys_mutex_unlock_ex
.global sys_close_handle
.global sys_wait_sync
.global sys_connect_to_port
.global sys_send_sync_request
.global sys_debug_printf_ex
.global sys_event_create
.global sys_event_signal
.global sys_event_clear
.global sys_map_memoryblock
.global sys_wait_sync2

.type sys_get_tls, %function
.type sys_get_commandbuffer, %function
.type sys_control_memory_ex, %function
.type sys_query_memory_ex, %function
.type sys_process_exit, %function
.type sys_thread_create_ex, %function
.type sys_thread_exit, %function
.type sys_thread_sleep_ex, %function
.type sys_mutex_new_ex, %function
.type sys_mutex_unlock_ex, %function
.type sys_close_handle, %function
.type sys_wait_sync, %function
.type sys_connect_to_port, %function
.type sys_send_sync_request, %function
.type sys_debug_printf_ex, %function
.type sys_event_create, %function
.type sys_event_signal, %function
.type sys_event_clear, %function
.type sys_map_memoryblock, %function
.type sys_wait_sync2, %function

sys_get_tls:
    mrc p15, 0, r0, c13, c0, 3
    bx lr

sys_get_commandbuffer:
    mrc p15, 0, r0, c13, c0, 3
    add r0, #0x80
    bx lr

sys_control_memory_ex:
    push {r0, r4}
    ldr r0, [sp, #0x8]
    ldr r4, [sp, #0x8+0x4]
    svc 0x01
    ldr r2, [sp], #4
    str r1, [r2]
    ldr r4, [sp], #4
    bx lr

sys_query_memory_ex:
    push {r0, r1, r4-r6}
    svc 0x02
    ldr r6, [sp]
    str r1, [r6]
    str r2, [r6, #4]
    str r3, [r6, #8]
    str r4, [r6, #0xc]
    ldr r6, [sp, #4]
    str r5, [r6]
    add sp, sp, #8
    pop {r4-r6}
    bx lr

sys_process_exit:
    svc 0x03
    bx lr

sys_thread_create_ex:
    stmfd sp!, {r0, r4}
    ldr r0, [sp, #0x8]
    ldr r4, [sp, #0x8+0x4]
    svc 0x08
    ldr r2, [sp], #4
    str r1, [r2]
    ldr r4, [sp], #4
    bx lr

sys_thread_exit:
    svc 0x09
    bx lr

sys_thread_sleep_ex:
    svc 0x0A
    bx lr

sys_mutex_new_ex:
    str r0, [sp, #-4]!
    svc 0x13
    ldr r3, [sp], #4
    str r1, [r3]
    bx lr

sys_mutex_unlock_ex:
    svc 0x14
    bx lr

sys_close_handle:
    svc 0x23
    bx lr

sys_wait_sync:
    svc 0x24
    bx lr

sys_connect_to_port:
    str r0, [sp, #-0x4]!
    svc 0x2D
    ldr r3, [sp], #4
    str r1, [r3]
    bx lr

sys_send_sync_request:
    svc 0x32
    bx lr

sys_debug_printf_ex:
    str r0, [sp,#-0x4]!
    svc 0x3D
    ldr r2, [sp], #4
    str r1, [r2]
    bx lr

sys_event_create:
    str r0, [sp, #-4]!
    svc 0x17
    ldr r2, [sp], #4
    str r1, [r2]
    bx lr

sys_event_signal:
    svc 0x18
    bx lr

sys_event_clear:
    svc 0x19
    bx lr

sys_map_memoryblock:
    svc 0x1F
    bx lr

sys_wait_sync2:
    str r5, [sp, #-4]!
    str r4, [sp, #-4]!
    mov r5, r0
    ldr r0, [sp, #0x8]
    ldr r4, [sp, #0x8+0x4]
    svc 0x25
    str r1, [r5]
    ldr r4, [sp], #4
    ldr r5, [sp], #4
    bx lr

