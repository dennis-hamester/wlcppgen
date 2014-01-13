
#include "region.hpp"

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

static const wl_interface* wl_region_request_destroy_types[] = { };
static const wl_interface* wl_region_request_add_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_region_request_subtract_types[] = { nullptr, nullptr, nullptr, nullptr };

static const wl_message wl_region_requests[] = {
    { "destroy", "", wl_region_request_destroy_types },
    { "add", "iiii", wl_region_request_add_types },
    { "subtract", "iiii", wl_region_request_subtract_types },
};

const wl_interface region::interface = {
    "wl_region", 1,
    3, wl_region_requests,
    0, nullptr
};

region::region(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
}

region::region(proxy& factory)
    : proxy(factory, interface) {
}

region::~region(){
    destroy();
}

void region::add(int32_t x_, int32_t y_, int32_t width_, int32_t height_) {
    marshal(1, x_, y_, width_, height_);
}

void region::subtract(int32_t x_, int32_t y_, int32_t width_, int32_t height_) {
    marshal(2, x_, y_, width_, height_);
}

void region::destroy() {
    if(valid() && managed()) {
        marshal(0);
    }
    proxy::destroy();
}

