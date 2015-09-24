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

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")
set(CMAKE_BUILD_TYPE_INIT "Debug")

include(CMakePackageConfigHelpers)

project(libctr LANGUAGES NONE VERSION 0.1.2)

option(ENABLE_DOC "Enable Doxygen Documentation" OFF)

if(ENABLE_DOC)
    add_subdirectory(doc)
endif()

find_package(CTR CONFIG QUIET REQUIRED artool)

enable_language(ASM)

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
)

target_include_directories(ctr PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_property(TARGET ctr PROPERTY INTERFACE_INCLUDE_DIRECTORIES "include")
set_property(TARGET ctr PROPERTY EXPORT_NAME "CTR")

configure_package_config_file(libctr-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/libctr-config.cmake
    INSTALL_DESTINATION lib/cmake/libctr
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/libctr-config-version.cmake
    COMPATIBILITY AnyNewerVersion 
    VERSION ${LIBCTR_VERSION}
)

install(TARGETS ctr DESTINATION lib EXPORT libctr)

install(DIRECTORY include/
    DESTINATION include
    PATTERN ".*" EXCLUDE
)

install(EXPORT libctr
    DESTINATION lib/cmake/libctr
    FILE libctr-targets.cmake
    NAMESPACE CTR::
)

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/libctr-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/libctr-config-version.cmake
    DESTINATION lib/cmake/libctr
)
