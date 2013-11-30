
#include "pointer.hpp"
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

static const wl_interface* wl_pointer_request_set_cursor_types[] = { nullptr, &surface::interface, nullptr, nullptr };
static const wl_interface* wl_pointer_request_release_types[] = { };

static const wl_message wl_pointer_requests[] = {
    { "set_cursor", "u?oii", wl_pointer_request_set_cursor_types },
    { "release", "3", wl_pointer_request_release_types },
};

static const wl_interface* wl_pointer_event_enter_types[] = { nullptr, &surface::interface, nullptr, nullptr };
static const wl_interface* wl_pointer_event_leave_types[] = { nullptr, &surface::interface };
static const wl_interface* wl_pointer_event_motion_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_pointer_event_button_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_pointer_event_axis_types[] = { nullptr, nullptr, nullptr };

static const wl_message wl_pointer_events[] = {
    { "enter", "uoff", wl_pointer_event_enter_types },
    { "leave", "uo", wl_pointer_event_leave_types },
    { "motion", "uff", wl_pointer_event_motion_types },
    { "button", "uuuu", wl_pointer_event_button_types },
    { "axis", "uuf", wl_pointer_event_axis_types },
};

const wl_interface pointer::interface = {
    "wl_pointer", 3,
    2, wl_pointer_requests,
    5, wl_pointer_events
};

const pointer::listener_t pointer::listener = {
    &enter_handler,
    &leave_handler,
    &motion_handler,
    &button_handler,
    &axis_handler,
};

pointer::pointer(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

pointer::pointer(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

pointer::~pointer(){
    destroy();
}

void pointer::set_cursor(uint32_t serial_, surface* surface_, int32_t hotspot_x_, int32_t hotspot_y_) {
    marshal(0, serial_, surface_ ? surface_->wl_obj() : nullptr, hotspot_x_, hotspot_y_);
}

void pointer::destroy() {
    if(valid()) {
        marshal(1);
    }
    proxy::destroy();
}

void pointer::enter_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_, wl_fixed_t surface_x_, wl_fixed_t surface_y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_enter_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_), surface_x_, surface_y_);
    }
}

void pointer::leave_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_leave_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_));
    }
}

void pointer::motion_handler(void* data, wl_proxy* wl_obj, uint32_t time_, wl_fixed_t surface_x_, wl_fixed_t surface_y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_motion_handler;
    if(handler) {
        handler(time_, surface_x_, surface_y_);
    }
}

void pointer::button_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, uint32_t button_, uint32_t state_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_button_handler;
    if(handler) {
        handler(serial_, time_, button_, state_);
    }
}

void pointer::axis_handler(void* data, wl_proxy* wl_obj, uint32_t time_, uint32_t axis_, wl_fixed_t value_) {
    auto& handler = proxy::user_data_to_wrapper_cast<pointer>(data)->_axis_handler;
    if(handler) {
        handler(time_, axis_, value_);
    }
}

