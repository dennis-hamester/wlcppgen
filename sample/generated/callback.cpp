
#include "callback.hpp"

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

static const wl_interface* wl_callback_event_done_types[] = { nullptr };

static const wl_message wl_callback_events[] = {
    { "done", "u", wl_callback_event_done_types },
};

const wl_interface callback::interface = {
    "wl_callback", 1,
    0, nullptr,
    1, wl_callback_events
};

const callback::listener_t callback::listener = {
    &done_handler,
};

callback::callback(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

callback::callback(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void callback::done_handler(void* data, wl_proxy* wl_obj, uint32_t serial_) {
    auto& handler = proxy::user_data_to_wrapper_cast<callback>(data)->_done_handler;
    if(handler) {
        handler(serial_);
    }
}

