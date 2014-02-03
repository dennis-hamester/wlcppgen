
#include "seat.hpp"
#include "keyboard.hpp"
#include "pointer.hpp"
#include "touch.hpp"

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

static const wl_interface* wl_seat_request_get_pointer_types[] = { &pointer::interface };
static const wl_interface* wl_seat_request_get_keyboard_types[] = { &keyboard::interface };
static const wl_interface* wl_seat_request_get_touch_types[] = { &touch::interface };

static const wl_message wl_seat_requests[] = {
    { "get_pointer", "n", wl_seat_request_get_pointer_types },
    { "get_keyboard", "n", wl_seat_request_get_keyboard_types },
    { "get_touch", "n", wl_seat_request_get_touch_types },
};

static const wl_interface* wl_seat_event_capabilities_types[] = { nullptr };
static const wl_interface* wl_seat_event_name_types[] = { nullptr };

static const wl_message wl_seat_events[] = {
    { "capabilities", "u", wl_seat_event_capabilities_types },
    { "name", "2s", wl_seat_event_name_types },
};

const wl_interface seat::interface = {
    "wl_seat", 3,
    3, wl_seat_requests,
    2, wl_seat_events
};

const seat::listener_t seat::listener = {
    &capabilities_handler,
    &name_handler,
};

seat::seat(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

seat::seat(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

pointer seat::get_pointer() {
    pointer id_(*this);
    marshal(0, id_.wl_obj());
    return id_;
}

keyboard seat::get_keyboard() {
    keyboard id_(*this);
    marshal(1, id_.wl_obj());
    return id_;
}

touch seat::get_touch() {
    touch id_(*this);
    marshal(2, id_.wl_obj());
    return id_;
}

void seat::capabilities_handler(void* data, wl_proxy* wl_obj, uint32_t capabilities_) {
    auto& handler = proxy::user_data_to_wrapper_cast<seat>(data)->_capabilities_handler;
    if(handler) {
        handler(capabilities_);
    }
}

void seat::name_handler(void* data, wl_proxy* wl_obj, const char* name_) {
    auto& handler = proxy::user_data_to_wrapper_cast<seat>(data)->_name_handler;
    if(handler) {
        handler(name_);
    }
}

