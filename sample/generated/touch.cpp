
#include "touch.hpp"
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

static const wl_interface* wl_touch_request_release_types[] = { };

static const wl_message wl_touch_requests[] = {
    { "release", "3", wl_touch_request_release_types },
};

static const wl_interface* wl_touch_event_down_types[] = { nullptr, nullptr, &surface::interface, nullptr, nullptr, nullptr };
static const wl_interface* wl_touch_event_up_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_touch_event_motion_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_touch_event_frame_types[] = { };
static const wl_interface* wl_touch_event_cancel_types[] = { };

static const wl_message wl_touch_events[] = {
    { "down", "uuoiff", wl_touch_event_down_types },
    { "up", "uui", wl_touch_event_up_types },
    { "motion", "uiff", wl_touch_event_motion_types },
    { "frame", "", wl_touch_event_frame_types },
    { "cancel", "", wl_touch_event_cancel_types },
};

const wl_interface touch::interface = {
    "wl_touch", 3,
    1, wl_touch_requests,
    5, wl_touch_events
};

const touch::listener_t touch::listener = {
    &down_handler,
    &up_handler,
    &motion_handler,
    &frame_handler,
    &cancel_handler,
};

touch::touch(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

touch::touch(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

touch::~touch(){
    destroy();
}

void touch::destroy() {
    if(valid() && managed()) {
        marshal(0);
    }
    proxy::destroy();
}

void touch::down_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, wl_proxy* surface_, int32_t id_, wl_fixed_t x_, wl_fixed_t y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_down_handler;
    if(handler) {
        handler(serial_, time_, *proxy::wrapper_cast<surface>(surface_), id_, x_, y_);
    }
}

void touch::up_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, int32_t id_) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_up_handler;
    if(handler) {
        handler(serial_, time_, id_);
    }
}

void touch::motion_handler(void* data, wl_proxy* wl_obj, uint32_t time_, int32_t id_, wl_fixed_t x_, wl_fixed_t y_) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_motion_handler;
    if(handler) {
        handler(time_, id_, x_, y_);
    }
}

void touch::frame_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_frame_handler;
    if(handler) {
        handler();
    }
}

void touch::cancel_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<touch>(data)->_cancel_handler;
    if(handler) {
        handler();
    }
}

