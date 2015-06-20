######################################################################
# This file is part of libctr.
# 
# libctr is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# libctr is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with libctr. If not, see <http://www.gnu.org/licenses/>.
######################################################################

.arm
.align 4

.global svc_thread_create
.global svc_output_debug_string
.global svc_exit_process
.global svc_control_memory
.global svc_connect_to_port
.global svc_send_sync_request
.global svc_close_handle
.global svc_thread_sleep

.type svc_thread_create, %function
.type svc_output_debug_string, %function
.type svc_exit_process, %function
.type svc_control_memory, %function
.type svc_connect_to_port, %function
.type svc_send_sync_request, %function
.type svc_close_handle, %function
.type svc_thread_sleep, %function

svc_thread_create:
	stmfd sp!, {r0, r4}
	ldr r0, [sp, #0x8]
	ldr r4, [sp, #0x8+0x4]
	svc 0x08
	ldr r2, [sp], #4
	str r1, [r2]
	ldr r4, [sp], #4
	bx lr

svc_output_debug_string:
	str r0, [sp,#-0x4]!
	svc 0x3D
	ldr r2, [sp], #4
	str r1, [r2]
	bx lr

svc_exit_process:
	svc 0x03
	bx lr

svc_control_memory:
	push {r0, r4}
	ldr r0, [sp, #0x8]
	ldr r4, [sp, #0x8+0x4]
	svc 0x01
	ldr r2, [sp], #4
	str r1, [r2]
	ldr r4, [sp], #4
	bx lr

svc_connect_to_port:
	str r0, [sp, #-0x4]!
	svc 0x2D
	ldr r3, [sp], #4
	str r1, [r3]
	bx lr

svc_send_sync_request:
	svc 0x32
	bx lr

svc_close_handle:
	svc 0x23
	bx lr

svc_thread_sleep:
	svc 0x0A
	bx lr
