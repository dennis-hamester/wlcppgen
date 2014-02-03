
#include "subcompositor.hpp"
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

static const wl_interface* wl_subcompositor_request_destroy_types[] = { };
static const wl_interface* wl_subcompositor_request_get_subsurface_types[] = { &subsurface::interface, &surface::interface, &surface::interface };

static const wl_message wl_subcompositor_requests[] = {
    { "destroy", "", wl_subcompositor_request_destroy_types },
    { "get_subsurface", "noo", wl_subcompositor_request_get_subsurface_types },
};

const wl_interface subcompositor::interface = {
    "wl_subcompositor", 1,
    2, wl_subcompositor_requests,
    0, nullptr
};

subcompositor::subcompositor(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
}

subcompositor::subcompositor(proxy& factory)
    : proxy(factory, interface) {
}

subcompositor::~subcompositor(){
    destroy();
}

subsurface subcompositor::get_subsurface(surface& surface_, surface& parent_) {
    subsurface id_(*this);
    marshal(1, id_.wl_obj(), surface_.wl_obj(), parent_.wl_obj());
    return id_;
}

void subcompositor::destroy() {
    if(valid() && managed()) {
        marshal(0);
    }
    proxy::destroy();
}

