
#include "compositor.hpp"
#include "region.hpp"
#include "surface.hpp"

using namespace std;
using namespace wlcpp;

/* The following code was generated from the "wayland" protocol specification.
 *
 * Copyright © 2008-2011 Kristian Høgsberg
 * Copyright © 2010-2011 Intel Corporation
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

static const wl_interface* wl_compositor_request_create_surface_types[] = { &surface::interface };
static const wl_interface* wl_compositor_request_create_region_types[] = { &region::interface };

static const wl_message wl_compositor_requests[] = {
    { "create_surface", "n", wl_compositor_request_create_surface_types },
    { "create_region", "n", wl_compositor_request_create_region_types },
};

const wl_interface compositor::interface = {
    "wl_compositor", 3,
    2, wl_compositor_requests,
    0, nullptr
};

compositor::compositor(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
}

compositor::compositor(proxy& factory)
    : proxy(factory, interface) {
}

surface compositor::create_surface() {
    surface id_(*this);
    marshal(0, id_.wl_obj());
    return id_;
}

region compositor::create_region() {
    region id_(*this);
    marshal(1, id_.wl_obj());
    return id_;
}

