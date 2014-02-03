
#include "buffer.hpp"

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

static const wl_interface* wl_buffer_request_destroy_types[] = { };

static const wl_message wl_buffer_requests[] = {
    { "destroy", "", wl_buffer_request_destroy_types },
};

static const wl_interface* wl_buffer_event_release_types[] = { };

static const wl_message wl_buffer_events[] = {
    { "release", "", wl_buffer_event_release_types },
};

const wl_interface buffer::interface = {
    "wl_buffer", 1,
    1, wl_buffer_requests,
    1, wl_buffer_events
};

const buffer::listener_t buffer::listener = {
    &release_handler,
};

buffer::buffer(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

buffer::buffer(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

buffer::~buffer(){
    destroy();
}

void buffer::destroy() {
    if(valid() && managed()) {
        marshal(0);
    }
    proxy::destroy();
}

void buffer::release_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<buffer>(data)->_release_handler;
    if(handler) {
        handler();
    }
}

