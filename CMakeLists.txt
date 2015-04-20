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

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Values: Debug, Release, RelWithDebInfo, MinSizeRel")
endif()

if(NOT DEFINED CTR_ROOT)
	message(SEND_ERROR "CTR_ROOT undefined")
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/OpenCTR-Toolchain.cmake")
set(CMAKE_INSTALL_PREFIX "${CTR_ROOT}" CACHE INTERNAL "CMAKE_INSTALL_ROOT")

project(libctr)

include(CMakePackageConfigHelpers)
include(CMakeProjectSettings)
include(CMakeProjectVersion)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(ctr
	src/sys.c
)

set_property(TARGET ctr PROPERTY EXPORT_NAME "libctr")

if(WIN32)
	# Win32 CMake find_package() searches <prefix>/CMake/
	set(CONFIG_PREFIX "CMake")
else()
	# UNIX CMake find_package() searches <prefix>/share/cmake
	set(CONFIG_PREFIX "share/cmake")
endif()

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/libctr-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/libctr-config.cmake
	INSTALL_DESTINATION ${CONFIG_PREFIX}
	PATH_VARS CONFIG_PREFIX
)

install(TARGETS ctr 
	EXPORT libctr
	ARCHIVE DESTINATION lib
	INCLUDES DESTINATION include
)

install(EXPORT libctr
	DESTINATION ${CONFIG_PREFIX}
	FILE libctr-targets.cmake
	NAMESPACE CTR::
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libctr-config.cmake
	DESTINATION ${CONFIG_PREFIX}
)

install(DIRECTORY include/
	DESTINATION include
	USE_SOURCE_PERMISSIONS
	#REGEX "^\\..*$" EXCLUDE
	PATTERN .* EXCLUDE
)
