/*
 * This file is part of libctr.
 * 
 * libctr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libctr is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libctr. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ctr/svc/svc.h"

#include "ctr/sys/sys.h"

#include "ctr/service/service.h"

#include "ctr/error/error.h"
#include "ctr/error/error-private.h"

static SVCHandle ctr_service_handle = 0;

static void ctrServiceInit(void) __attribute__((constructor (105)));
static void ctrServiceExit(void) __attribute__((destructor (105)));


static void ctrServiceInit(void) {
	char buffer[200];
	uint32_t* cmdbuf = NULL;
	int ret;

	if(ctr_service_handle != 0) {
		return;
	}

	ret = svc_connect_to_port(&ctr_service_handle, "srv:");
	if(ret != 0) {
		snprintf(buffer, 200, "svc_connect_to_port() error: 0x%08x\n", ret);
		svc_output_debug_string(buffer, strlen(buffer));
		svc_exit_process();
	}

	cmdbuf = svc_get_commandbuffer();
	assert(cmdbuf != NULL);

	cmdbuf[0] = 0x00010002;
	cmdbuf[1] = 0x00000020;

	ret = svc_send_sync_request(ctr_service_handle);
	if(ret != 0) {
		snprintf(buffer, 200, "svc_send_sync_request() error: 0x%08x\n", ret);
		svc_output_debug_string(buffer, strlen(buffer));
		svc_exit_process();
	}

	if(cmdbuf[1] != 0) {
		snprintf(buffer, 200, "ctrServiceInit() error: 0x%08x\n", ret);
		svc_output_debug_string(buffer, strlen(buffer));
		svc_exit_process();
	}
}

static void ctrServiceExit(void) {
	// svc_close_handle()
}

int ctrServiceGetHandle(SVCHandle* handle, const char* name) {
	uint32_t* cmdbuf = NULL;
	int ret;

/*
	Handle h = __get_handle_from_list(name);
	if(h != 0) {
		return svcDuplicateHandle(out, h);
	}
*/

	const int len = strlen(name);

	cmdbuf = svc_get_commandbuffer();
	assert(cmdbuf != NULL);

	cmdbuf[0] = 0x00050100;

	// cmdbuf[1] = name;
	strcpy((char*) &cmdbuf[1], name);

	cmdbuf[3] = len;
	cmdbuf[4] = 0x00;

	ret = svc_send_sync_request(ctr_service_handle);
	if(ret != 0) {
		sys_debug_printf("svc_send_sync_request: %d\n", ret);

		(*cerrorptr()) = ret;
		return -1;
	}

	ret = cmdbuf[1];
	if(ret != 0) {
		sys_debug_printf("cmdbuf[0] = %d\n", ret);

		(*cerrorptr()) = ret;
		return -1;
	}

	if(handle != NULL) {
		*handle = cmdbuf[3];
	}

	return 0;
}

