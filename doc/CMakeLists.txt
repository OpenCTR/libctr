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

find_package(Doxygen QUIET REQUIRED)

get_filename_component(LIBCTR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include ABSOLUTE)
get_filename_component(LIBCTR_DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)

set(PROJECT_NAME libctr)
set(PROJECT_VERSION ${LIBCTR_VERSION})
set(PROJECT_BRIEF "\"Software library for Nintendo 3DS homebrew\"")
set(PROJECT_LOGO ${CMAKE_CURRENT_SOURCE_DIR}/logo.svg)
set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(LAYOUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/layout.xml)
set(EXAMPLE_PATH)
set(IMAGE_PATH)
set(HTML_OUTPUT html)
set(HTML_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/header.html)
set(HTML_FOOTER ${CMAKE_CURRENT_SOURCE_DIR}/footer.html)
set(HTML_EXTRA_STYLESHEET ${CMAKE_CURRENT_SOURCE_DIR}/style.css)
set(HTML_EXTRA_FILES)
set(STRIP_FROM_PATH "${LIBCTR_INCLUDE_DIR}/ ${LIBCTR_DOC_DIR}/")
set(STRIP_FROM_INC_PATH)
set(EXCLUDE "${LIBCTR_INCLUDE_DIR}/ctr/ctr.h")

file(GLOB_RECURSE H_FILES "${LIBCTR_INCLUDE_DIR}/*.h")
file(GLOB_RECURSE MD_FILES "${LIBCTR_DOC_DIR}/*.md")
file(GLOB_RECURSE DOX_FILES "${LIBCTR_DOC_DIR}/*.dox")

set(INPUT "${H_FILES};${MD_FILES};${DOX_FILES}")
string(REPLACE ";" " " INPUT "${INPUT}")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	@ONLY
)

# Generate HTML documentation
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html
	COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating HTML"
)

# Documentation target to generate all documentation formats
add_custom_target(doc ALL 
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html
)

if(ENABLE_UPLOAD)
	# Git is required for pushing to GitHub Pages.
	find_package(Git QUIET REQUIRED)

	# Create custom 'upload' target
	add_custom_target(upload 
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html
		# Remove the existing upload directory.
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/upload
		# Clone the GitHub Pages repo
		COMMAND ${GIT_EXECUTABLE} clone -q -b gh-pages https://github.com/OpenCTR/libctr ${CMAKE_CURRENT_BINARY_DIR}/upload
		# Remove all existing files
		COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_CURRENT_BINARY_DIR}/upload rm -rf --quiet .
		# Copy the HTML files into the git repository
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_BINARY_DIR}/html ${CMAKE_CURRENT_BINARY_DIR}/upload/
		# Create the .nojekyll to allow subdirectories
		COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/upload/.nojekyll
		# Add the newly copied files into Git
		COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_CURRENT_BINARY_DIR}/upload add .
		# Commit the new files
		COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_CURRENT_BINARY_DIR}/upload commit --quiet -m "Updated HTML documentation"
		# Push the new files into GitHub
		COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_CURRENT_BINARY_DIR}/upload push --quiet origin master
	)

	# Cleanup
	set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "upload")
endif()

# Cleanup
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "html")
