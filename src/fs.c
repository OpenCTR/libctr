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
#include <errno.h>
#include <sys/iosupport.h>

#include "ctr/svc/svc.h"

#include "ctr/service/service.h"

#include "ctr/sys/sys.h"
#include "ctr/sys/sys-private.h"

#include "ctr/error/error.h"
#include "ctr/error/error-private.h"

#include "ctr/fs/fs.h"
#include "ctr/fs/fs-private.h"

#define CTR_FS_SDMC (0x00000009)

static SVCHandle ctr_fs_handle = 0;
static uint64_t* ctr_fs_offset_table = NULL;
static uint64_t ctr_fs_offset_table_size = 0;
static uint64_t ctr_fs_offset_table_index = 0;

static void ctrFsInit(void) __attribute__((constructor (107)));
static void ctrFsExit(void) __attribute__((destructor (107)));

static void ctrFsInit(void) {
	uint32_t* cmdbuf = NULL;
	int ret;

	ret = ctrServiceGetHandle(&ctr_fs_handle, "fs:USER");
	if(ret != 0) {
		sys_debug_printf("Error getting fs:USER handle: 0x%08x\n", ret);
		svc_exit_process();
	}

	cmdbuf = svc_get_commandbuffer();

	cmdbuf[0] = 0x08010002;
	cmdbuf[1] = 0x00000020;

	ret = svc_send_sync_request(ctr_fs_handle);
	if(ret != 0) {
		sys_debug_printf("Error init request for filesystem: 0x%08x\n", ret);
		svc_exit_process();
	}

	ret = cmdbuf[1];
	if(ret != 0) {
		sys_debug_printf("Error initializing filesystem: 0x%08x\n", ret);
		svc_exit_process();
	}

	ctr_fs_offset_table = (uint64_t*)malloc(sizeof(uint64_t));
	ctr_fs_offset_table_size = 1;
	ctr_fs_offset_table_index = 0;
}

static void ctrFsExit(void) {
	svc_close_handle(ctr_fs_handle);
}

int ctrFsOpen(int* fd, const char* path, int flags) {
	int ret;
	uint32_t* cmdbuf = NULL;

	if(fd == NULL) {
		(*cerrorptr()) = EFAULT;
		return -1;
	}

	if(path == NULL) {
		(*cerrorptr()) = EFAULT;
		return -1;
	}

	const int len = strlen(path) + 1;
	if(len <= 1) {
		(*cerrorptr()) = EFAULT;
		return -1;
	}

	/**
	 * @todo Check if NAND mode. If true, replace cmdbuf[2].
	 * Current behavior: Use SDMC for all files.
	 * Future: Use SDMC by default, allow switching between SDMC/NAND.
	 */

	cmdbuf = svc_get_commandbuffer();

	cmdbuf[0] = 0x08030204;
	cmdbuf[1] = 0x00000000;
	cmdbuf[2] = 0x00000009;
	cmdbuf[3] = 0x00000001;
	cmdbuf[4] = 0x00000000;
	cmdbuf[5] = 0x00000003;
	cmdbuf[6] = len;
	cmdbuf[7] = flags;
	cmdbuf[8] = 0x00000000; // attributes
	cmdbuf[9] = ((0x00000000 << 0x0E) | 0x00000802);
	cmdbuf[10] = (uint32_t)((uint8_t*)"");
	cmdbuf[11] = ((len << 0x0E) | 0x02);
	cmdbuf[12] = (uint32_t)path;

	ret = svc_send_sync_request(ctr_fs_handle);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	ret = cmdbuf[1];
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	if(fd != NULL) {
		*fd = cmdbuf[3];
	}

	return 0;
}

int ctrFsRead(int fd, void* buffer, uint64_t size, uint64_t* osize) {
	uint32_t* cmdbuf = NULL;
	int ret;

	// TODO: Get offset.
	const uint64_t offset = 0;

	cmdbuf = svc_get_commandbuffer();

	cmdbuf[0] = 0x080200C2;
	cmdbuf[1] = (uint32_t)(offset);
	cmdbuf[2] = (uint32_t)(offset >> 32);
	cmdbuf[3] = (uint32_t)(size);
	cmdbuf[4] = ((size << 0x04) | 0x0C);
	cmdbuf[5] = ((uint32_t)buffer);

	ret = svc_send_sync_request(fd);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	ret = cmdbuf[1];
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	if(osize != NULL) {
		*osize = cmdbuf[2];
	}

	return 0;
}

int ctrFsWrite(int fd, const void* buffer, uint64_t size, uint64_t* osize) {
	uint32_t* cmdbuf = NULL;
	int ret;

	const uint64_t offset = 0;

	cmdbuf = svc_get_commandbuffer();

	cmdbuf[0] = 0x08030102;
	cmdbuf[1] = (uint32_t)(offset);
	cmdbuf[2] = (uint32_t)(offset >> 32);
	cmdbuf[3] = (uint32_t)(size);
	cmdbuf[4] = (0x00000000);
	cmdbuf[5] = ((size << 0x04) | 0x0A);
	cmdbuf[6] = (uint32_t)buffer;

	ret = svc_send_sync_request(fd);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	ret = cmdbuf[1];
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	if(osize != NULL) {
		*osize = cmdbuf[2];
	}

	return 0;
}

int ctrFsClose(int fd) {
	uint32_t* cmdbuf = NULL;
	int ret;

	cmdbuf[0] = 0x08080000;

	ret = svc_send_sync_request(fd);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	ret = cmdbuf[1];
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	svc_close_handle(fd);

	return 0;
}


/* Stubs */
int ctrFsOpendir(int* fd, const char* path) { return -1; }
int ctrFsReaddir(int fd, CtrFsDirent* dir) { return -1; }
int ctrFsClosedir(int fd) { return -1; }
int ctrFsStat(const char* path, CtrFsStat* st) { return -1; }
int ctrFsFstat(int fd, CtrFsStat* st) { return -1; }
int ctrFsMkdir(const char* path, CtrFsMode mode) { return -1; }
int ctrFsRename(const char* source, const char* dest) { return -1; }
int ctrFsRmdir(const char* path) { return -1; }
int ctrFsUnlink(const char* path) { return -1; }
int ctrFsLseek(int fd, int64_t offset, ctrFsOrigin origin, uint64_t* pos) { return -1; }
int ctrFsFsync(int fd) { return -1; }
int ctrFsSdmcStatus(CtrFsStatus* status) { return -1; }
int ctrFsTruncate(const char* path, uint64_t size) { return -1; }
int ctrFsFtruncate(int fd, uint64_t size) { return -1; }
int ctrFsGetAvailableSize(uint64_t* sdmc_size, uint64_t* nand_size) { return -1; }

