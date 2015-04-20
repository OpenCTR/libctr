#.rst:
# OpenCTR-Toolchain
# -----------------
# 
# CMake toolchain (``CMAKE_TOOLCHAIN_FILE``) for enabling OpenCTR 
# support.
# 

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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with libctr.  If not, see <http://www.gnu.org/licenses/>.
######################################################################

if(NOT DEFINED CTR_ROOT)
	#message(SEND_ERROR "CTR_ROOT is not set")
	#return()
endif()

function(setcache var val)
	set(${var} ${val} CACHE INTERNAL "${var}")
endfunction()

setcache(CMAKE_SYSTEM_NAME "Generic")
setcache(CMAKE_SYSTEM_VERSION 1)
setcache(CMAKE_SYSTEM_PROCESSOR "ARM")

setcache(CMAKE_C_COMPILER "arm-none-eabi-gcc")
setcache(CMAKE_C_COMPILER_ID "GNU")
setcache(CMAKE_C_COMPILER_ID_RUN TRUE)
setcache(CMAKE_C_COMPILER_FORCED TRUE)
setcache(CMAKE_COMPILER_IS_GNUCC TRUE)

setcache(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
setcache(CMAKE_CXX_COMPILER_ID "GNU")
setcache(CMAKE_CXX_COMPILER_ID_RUN TRUE)
setcache(CMAKE_CXX_COMPILER_FORCED TRUE)
setcache(CMAKE_COMPILER_IS_GNUCXX TRUE)

setcache(CMAKE_FIND_ROOT_PATH "${CTR_ROOT}")
setcache(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
setcache(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
setcache(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

setcache(UNIX TRUE)
setcache(APPLE FALSE)
setcache(WIN32 FALSE)
setcache(CYGWIN FALSE)
setcache(MSVC FALSE)

setcache(CMAKE_CROSSCOMPILING TRUE)
setcache(CMAKE_EXECUTABLE_SUFFIX ".elf")
setcache(CMAKE_SKIP_RPATH TRUE)
setcache(BUILD_SHARED_LIBS FALSE)
setcache(CMAKE_STATIC_LIBRARY_PREFIX "lib")
setcache(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
setcache(CMAKE_SIZEOF_VOID_P "4")
setcache(CMAKE_AR "arm-none-eabi-ar")
setcache(CMAKE_RANLIB "arm-none-eabi-ranlib")
setcache(CMAKE_STANDARD_LIBRARIES "-lc -lm")
