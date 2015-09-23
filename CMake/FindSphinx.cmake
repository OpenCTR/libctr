#.rst:
# FindSphinx
# ----------
#
# Locate Sphinx - The official python documentation generator
#
# Result Variables
# ~~~~~~~~~~~~~~~~
#
# ``SPHINX_FOUND``
#  Set to ``TRUE`` if Sphinx was found on the users system.
# ``SPHINX_EXECUTABLE``
#  Path to the ``sphinx-build`` python executable.
# ``SPHINX_VERSION``
#  Version of Sphinx detected.

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

if(APPLE)
    # Fink
    list(APPEND SPHINX_PATH_DIRS "/sw")
    # DarwinPorts
    list(APPEND SPHINX_PATH_DIRS "/opt/local")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "(Solaris|SunOS)")
    # BlastWave
    list(APPEND SPHINX_PATH_DIRS "/opt/csw")
endif()

if(UNIX)
    list(APPEND SPHINX_PATH_DIRS "/usr")
    list(APPEND SPHINX_PATH_DIRS "/usr/local")
endif()

find_program(SPHINX_EXECUTABLE
    NAMES
        sphinx-build 
        sphinx-build.exe 
        sphinx-build.py 
    PATHS 
        ${SPHINX_PATH_DIRS} 
    PATH_SUFFIXES 
        bin
    DOC 
        "Path to sphinx-build"
)

if(NOT SPHINX_VERSION)
    set(_SPHINX_VERSION "0.0.0")

    if(SPHINX_EXECUTABLE)
        execute_process(
            COMMAND ${SPHINX_EXECUTABLE} --version
            RESULT_VARIABLE result 
            OUTPUT_VARIABLE output 
            ERROR_VARIABLE error 
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        set(SPHINX_REGEX
            "^Sphinx \\(sphinx-build\\) ([0-9]+\\.[0-9]+\\.[0-9]+)$")

        if(${result} EQUAL 0)
            if("${output}" MATCHES ${SPHINX_REGEX})
                string(REGEX REPLACE ${SPHINX_REGEX} "\\1" _VERSION "${output}")
            endif()
        endif()
    endif()

    set(SPHINX_VERSION "${_VERSION}" CACHE STRING "Sphinx version")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sphinx
    REQUIRED_VARS SPHINX_EXECUTABLE
    VERSION_VAR SPHINX_VERSION
)