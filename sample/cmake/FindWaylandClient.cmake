# Copyright (c) 2013, Dennis Hamester <dennis.hamester@gmail.com>
# 
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

# - Find the Wayland Client library
# This module defines the following variables:
#  WaylandClient_INCLUDE_DIRS   - include directories for Wayland Client
#  WaylandClient_LIBRARIES      - libraries to link against Wayland Client
#  WaylandClient_VERSION        - version of the Wayland Client library
#  WaylandClient_FOUND          - true if Wayland Client has been found
#  WaylandClient_PROTOCOL       - path to wayland.xml protocol specification
#  WaylandClient_PROTOCOL_FOUND - true if wayland.xml was found

find_path(WaylandClient_INCLUDE_DIR wayland-client.h)
find_library(WaylandClient_LIBRARY NAMES wayland-client)

set(WaylandClient_INCLUDE_DIRS ${WaylandClient_INCLUDE_DIR})
set(WaylandClient_LIBRARIES ${WaylandClient_LIBRARY})

if(WaylandClient_INCLUDE_DIR)
    file(READ ${WaylandClient_INCLUDE_DIR}/wayland-version.h _wayland_client_version_header)

    string(REGEX MATCH "define WAYLAND_VERSION_MAJOR ([0-9]+)" _wayland_client_version_major ${_wayland_client_version_header})
    set(WaylandClient_VERSION_MAJOR ${CMAKE_MATCH_1})

    string(REGEX MATCH "define WAYLAND_VERSION_MINOR ([0-9]+)" _wayland_client_version_minor ${_wayland_client_version_header})
    set(WaylandClient_VERSION_MINOR ${CMAKE_MATCH_1})

    string(REGEX MATCH "define WAYLAND_VERSION_MICRO ([0-9]+)" _wayland_client_version_micro ${_wayland_client_version_header})
    set(WaylandClient_VERSION_MICRO ${CMAKE_MATCH_1})

    set(WaylandClient_VERSION ${WaylandClient_VERSION_MAJOR}.${WaylandClient_VERSION_MINOR}.${WaylandClient_VERSION_MICRO})
endif()

find_path(WaylandClient_PROTOCOL_PATH wayland.xml /usr/share/wayland)
if(WaylandClient_PROTOCOL_PATH)
    set(WaylandClient_PROTOCOL ${WaylandClient_PROTOCOL_PATH}/wayland.xml)
    set(WaylandClient_PROTOCOL_FOUND TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WaylandClient
    FOUND_VAR WaylandClient_FOUND
    REQUIRED_VARS WaylandClient_INCLUDE_DIR WaylandClient_LIBRARY
    VERSION_VAR WaylandClient_VERSION
)

mark_as_advanced(WaylandClient_INCLUDE_DIR WaylandClient_LIBRARY)

