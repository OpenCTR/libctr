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
find_package(Sphinx QUIET REQUIRED)
find_package(Breathe QUIET REQUIRED)

option(ENABLE_UPLOAD "Enable 'upload' target to upload documentation" OFF)

# Libctr headers directory.
get_filename_component(LIBCTR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include ABSOLUTE)

# Sphinx settings
set(CONFIG_PATH "${CMAKE_CURRENT_BINARY_DIR}")
set(HTML_PATH "${CMAKE_CURRENT_BINARY_DIR}/html")
set(XML_PATH "${CMAKE_CURRENT_BINARY_DIR}/xml")
set(RST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/rst")
set(UPLOAD_PATH "${CMAKE_CURRENT_BINARY_DIR}/upload")
set(THEME_PATH "${CMAKE_CURRENT_SOURCE_DIR}/_themes")
set(STATIC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/_static")

# Doxygen settings
set(PROJECT_NAME libctr)
set(PROJECT_VERSION ${LIBCTR_VERSION})
set(PROJECT_BRIEF "\"Software library for Nintendo 3DS homebrew\"")
set(PROJECT_LOGO ${STATIC_PATH}/logo.svg)

# Generate a list of libctr headers.
file(GLOB_RECURSE H_FILES "${LIBCTR_INCLUDE_DIR}/*.h")
# Generate a list of rst file dependencies.
file(GLOB_RECURSE RST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/rst/*.rst)

# Convert from a CMake list into a string
string(REPLACE ";" " " LIBCTR_HEADERS "${H_FILES}")

# Configure Doxyfile.in
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	@ONLY
)

# Configure conf.py.in
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
	${CMAKE_CURRENT_BINARY_DIR}/conf.py
	@ONLY
)

# Generate HTML documentation
add_custom_command(OUTPUT ${HTML_PATH} 
	DEPENDS "${RST_FILES};${H_FILES}"
	COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	COMMAND ${SPHINX_EXECUTABLE} -b html -c . -q ${RST_PATH} ${HTML_PATH}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating HTML"
)

# Documentation target to generate all documentation formats
add_custom_target(doc ALL DEPENDS ${HTML_PATH})

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
		COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_CURRENT_BINARY_DIR}/upload push --quiet origin gh-pages
	)

	# Cleanup
	set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "upload")
endif()

# Install documentation
install(DIRECTORY ${HTML_PATH}/
	DESTINATION share/doc/libctr
	PATTERN ".*" EXCLUDE
)

# Cleanup
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "html")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "xml")
