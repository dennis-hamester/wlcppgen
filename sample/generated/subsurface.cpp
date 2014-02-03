
#include "subsurface.hpp"
#include "surface.hpp"

using namespace std;
using namespace wlcpp;

/* The following code was generated from the "wayland" protocol specification.
 *
 * Copyright © 2008-2011 Kristian Høgsberg
 * Copyright © 2010-2011 Intel Corporation
 * Copyright © 2012-2013 Collabora, Ltd.
 *
 * Permission to use, copy, modify, distribute, and sell this
 * software and its documentation for any purpose is hereby granted
 * without fee, provided that the above copyright notice appear in
 * all copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * the copyright holders not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 */

static const wl_interface* wl_subsurface_request_destroy_types[] = { };
static const wl_interface* wl_subsurface_request_set_position_types[] = { nullptr, nullptr };
static const wl_interface* wl_subsurface_request_place_above_types[] = { &surface::interface };
static const wl_interface* wl_subsurface_request_place_below_types[] = { &surface::interface };
static const wl_interface* wl_subsurface_request_set_sync_types[] = { };
static const wl_interface* wl_subsurface_request_set_desync_types[] = { };

static const wl_message wl_subsurface_requests[] = {
    { "destroy", "", wl_subsurface_request_destroy_types },
    { "set_position", "ii", wl_subsurface_request_set_position_types },
    { "place_above", "o", wl_subsurface_request_place_above_types },
    { "place_below", "o", wl_subsurface_request_place_below_types },
    { "set_sync", "", wl_subsurface_request_set_sync_types },
    { "set_desync", "", wl_subsurface_request_set_desync_types },
};

const wl_interface subsurface::interface = {
    "wl_subsurface", 1,
    6, wl_subsurface_requests,
    0, nullptr
};

subsurface::subsurface(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
}

subsurface::subsurface(proxy& factory)
    : proxy(factory, interface) {
}

subsurface::~subsurface(){
    destroy();
}

void subsurface::set_position(int32_t x_, int32_t y_) {
    marshal(1, x_, y_);
}

void subsurface::place_above(surface& sibling_) {
    marshal(2, sibling_.wl_obj());
}

void subsurface::place_below(surface& sibling_) {
    marshal(3, sibling_.wl_obj());
}

void subsurface::set_sync() {
    marshal(4);
}

void subsurface::set_desync() {
    marshal(5);
}

void subsurface::destroy() {
    if(valid() && managed()) {
        marshal(0);
    }
    proxy::destroy();
}

