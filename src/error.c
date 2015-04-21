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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libctr.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdint.h>

#include "ctr/error/error.h"
#include "ctr/svc/svc.h"

/*
 * Yes, this isn't thread-safe **YET**.
 *
 * I will make it so later, but right now I just want to
 * focus on my interface APIs.
 */
static int cerrorno = 0;

int cerror(void) {
	return cerrorno;
}

int* cerrorptr(void) {
	return &cerrorno;
}

