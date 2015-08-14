####################################################################
# libctr - Library for Nintendo 3DS homebrew.
# 
# Copyright (C) 2015 The OpenCTR Project. 
# 
# This file is part of libctr. 
# 
# libctr is free software: you can redistribute it and/or modify 
# it under the terms of the GNU General Public License version 3 as 
# published by the Free Software Foundation.
# 
# libctr is distributed in the hope that it will be useful, 
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License 
# along with libctr. If not, see <http://www.gnu.org/licenses/>.
####################################################################

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_BUILD_TYPE_INIT "Debug")

include(CMakePackageConfigHelpers)
include(OpenCTR)

project(libctr VERSION 0.1.1)

option(ENABLE_DOC "Enable Doxygen Documentation" OFF)

if(ENABLE_DOC)
	add_subdirectory(doc)
endif()

find_package(OpenCTR CONFIG QUIET REQUIRED artool)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Enable Assembly
enable_language(ASM)

# Convert default_font.ttf to an ARM Object file.
ctr_add_resources(DEFAULT_FONT data/default_font.ttf
	HEADER default_font.h
)

add_library(ctr STATIC 
	src/sys.c
	src/sys_ex.s
	src/init.c
	src/stack.s
	src/service.c
	src/error.c
	src/atomic.s
	src/fs.c
	src/font.c
	src/gsp.c
	src/sdmc.c
	${DEFAULT_FONT}
)

# Export CTR::CTR instead of CTR::ctr
set_property(TARGET ctr PROPERTY EXPORT_NAME "CTR")

# Add ``<prefix>/include`` to the list of included directories in libctr.
set_property(TARGET ctr PROPERTY 
	INTERFACE_INCLUDE_DIRECTORIES "$<INSTALL_PREFIX>/include"
)

# Configure libctr-config.cmake
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/libctr-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/libctr-config.cmake
	INSTALL_DESTINATION lib/cmake/libctr
)

# Create libctr-config-version.cmake
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/libctr-config-version.cmake 
	COMPATIBILITY AnyNewerVersion 
	VERSION ${LIBCTR_VERSION}
)

# Install libctr headers
install(DIRECTORY include/
	DESTINATION include
	PATTERN ".*" EXCLUDE
)

# Install libctru.a
install(TARGETS ctr DESTINATION lib EXPORT libctr)

# Install libctr-targets.cmake
install(EXPORT libctr
	DESTINATION lib/cmake/libctr
	FILE libctr-targets.cmake
	NAMESPACE CTR::
)

# Install libctr-config.cmake and libctr-config-version.cmake
install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/libctr-config.cmake
	${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/libctr-config-version.cmake
	DESTINATION lib/cmake/libctr
)
