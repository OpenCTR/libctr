#.rst:
# CMakeProjectSettings
# --------------------
# 
# Project settings.
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
	message(SEND_ERROR "CTR_ROOT is not set")
	return()
endif()

find_program(CMAKE_ASM_COMPILER_EXE 
	NAMES
		arm-none-eabi-as
	PATHS
		${CTR_ROOT}
	PATH_SUFFIXES
		bin
	DOC
		"Find the arm-none-eabi-as assembler"
	NO_DEFAULT_PATH
)

if(NOT CMAKE_ASM_COMPILER_EXE)
	message(SEND_ERROR "Could not find arm-none-eabi-as")
	return()
endif()

set(CMAKE_ASM_COMPILER "${CMAKE_ASM_COMPILER_EXE}")
set(CMAKE_ASM_COMPILER_ID "GNU")
set(CMAKE_ASM_COMPILER_ID_RUN TRUE)
set(CMAKE_ASM_COMPILER_FORCED TRUE)

# Enable assembly (for SVC functions)
enable_language(ASM)
