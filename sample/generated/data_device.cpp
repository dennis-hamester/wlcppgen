
#include "data_device.hpp"
#include "data_offer.hpp"
#include "data_source.hpp"
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

static const wl_interface* wl_data_device_request_start_drag_types[] = { &data_source::interface, &surface::interface, &surface::interface, nullptr };
static const wl_interface* wl_data_device_request_set_selection_types[] = { &data_source::interface, nullptr };

static const wl_message wl_data_device_requests[] = {
    { "start_drag", "?oo?ou", wl_data_device_request_start_drag_types },
    { "set_selection", "?ou", wl_data_device_request_set_selection_types },
};

static const wl_interface* wl_data_device_event_data_offer_types[] = { &data_offer::interface };
static const wl_interface* wl_data_device_event_enter_types[] = { nullptr, &surface::interface, nullptr, nullptr, &data_offer::interface };
static const wl_interface* wl_data_device_event_leave_types[] = { };
static const wl_interface* wl_data_device_event_motion_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_data_device_event_drop_types[] = { };
static const wl_interface* wl_data_device_event_selection_types[] = { &data_offer::interface };

static const wl_message wl_data_device_events[] = {
    { "data_offer", "n", wl_data_device_event_data_offer_types },
    { "enter", "uoff?o", wl_data_device_event_enter_types },
    { "leave", "", wl_data_device_event_leave_types },
    { "motion", "uff", wl_data_device_event_motion_types },
    { "drop", "", wl_data_device_event_drop_types },
    { "selection", "?o", wl_data_device_event_selection_types },
};

const wl_interface data_device::interface = {
    "wl_data_device", 1,
    2, wl_data_device_requests,
    6, wl_data_device_events
};

const data_device::listener_t data_device::listener = {
    &data_offer_handler,
    &enter_handler,
    &leave_handler,
    &motion_handler,
    &drop_handler,
    &selection_handler,
};

data_device::data_device(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

data_device::data_device(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void data_device::start_drag(data_source* source_, surface& origin_, surface* icon_, uint32_t serial_) {
    marshal(0, source_ ? source_->wl_obj() : nullptr, origin_.wl_obj(), icon_ ? icon_->wl_obj() : nullptr, serial_);
}

void data_device::set_selection(data_source* source_, uint32_t serial_) {
    marshal(1, source_ ? source_->wl_obj() : nullptr, serial_);
}

void data_device::data_offer_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_data_offer_handler;
    if(handler) {
        handler(data_offer(id_));
    }
}

void data_device::enter_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_, wl_fixed_t x_, wl_fixed_t y_, wl_proxy* id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_enter_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_), x_, y_, proxy::wrapper_cast<data_offer>(id_));
    }
}

void data_device::leave_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_leave_handler;
    if(handler) {
        handler();
    }
}

void data_device::motion_handler(void* data, wl_proxy* wl_obj, uint32_t time_, wl_fixed_t x_, wl_fixed_t y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_motion_handler;
    if(handler) {
        handler(time_, x_, y_);
    }
}

void data_device::drop_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_drop_handler;
    if(handler) {
        handler();
    }
}

void data_device::selection_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_device>(data)->_selection_handler;
    if(handler) {
        handler(proxy::wrapper_cast<data_offer>(id_));
    }
}

