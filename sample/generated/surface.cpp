
#include "surface.hpp"
#include "buffer.hpp"
#include "callback.hpp"
#include "output.hpp"
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

static const wl_interface* wl_surface_request_destroy_types[] = { };
static const wl_interface* wl_surface_request_attach_types[] = { &buffer::interface, nullptr, nullptr };
static const wl_interface* wl_surface_request_damage_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_surface_request_frame_types[] = { &callback::interface };
static const wl_interface* wl_surface_request_set_opaque_region_types[] = { &region::interface };
static const wl_interface* wl_surface_request_set_input_region_types[] = { &region::interface };
static const wl_interface* wl_surface_request_commit_types[] = { };
static const wl_interface* wl_surface_request_set_buffer_transform_types[] = { nullptr };
static const wl_interface* wl_surface_request_set_buffer_scale_types[] = { nullptr };

static const wl_message wl_surface_requests[] = {
    { "destroy", "", wl_surface_request_destroy_types },
    { "attach", "?oii", wl_surface_request_attach_types },
    { "damage", "iiii", wl_surface_request_damage_types },
    { "frame", "n", wl_surface_request_frame_types },
    { "set_opaque_region", "?o", wl_surface_request_set_opaque_region_types },
    { "set_input_region", "?o", wl_surface_request_set_input_region_types },
    { "commit", "", wl_surface_request_commit_types },
    { "set_buffer_transform", "2i", wl_surface_request_set_buffer_transform_types },
    { "set_buffer_scale", "3i", wl_surface_request_set_buffer_scale_types },
};

static const wl_interface* wl_surface_event_enter_types[] = { &output::interface };
static const wl_interface* wl_surface_event_leave_types[] = { &output::interface };

static const wl_message wl_surface_events[] = {
    { "enter", "o", wl_surface_event_enter_types },
    { "leave", "o", wl_surface_event_leave_types },
};

const wl_interface surface::interface = {
    "wl_surface", 3,
    9, wl_surface_requests,
    2, wl_surface_events
};

const surface::listener_t surface::listener = {
    &enter_handler,
    &leave_handler,
};

surface::surface(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

surface::surface(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

surface::~surface(){
    destroy();
}

void surface::attach(buffer* buffer_, int32_t x_, int32_t y_) {
    marshal(1, buffer_ ? buffer_->wl_obj() : nullptr, x_, y_);
}

void surface::damage(int32_t x_, int32_t y_, int32_t width_, int32_t height_) {
    marshal(2, x_, y_, width_, height_);
}

callback surface::frame() {
    callback callback_(*this);
    marshal(3, callback_.wl_obj());
    return callback_;
}

void surface::set_opaque_region(region* region_) {
    marshal(4, region_ ? region_->wl_obj() : nullptr);
}

void surface::set_input_region(region* region_) {
    marshal(5, region_ ? region_->wl_obj() : nullptr);
}

void surface::commit() {
    marshal(6);
}

void surface::set_buffer_transform(int32_t transform_) {
    marshal(7, transform_);
}

void surface::set_buffer_scale(int32_t scale_) {
    marshal(8, scale_);
}

void surface::destroy() {
    if(valid()) {
        marshal(0);
    }
    proxy::destroy();
}

void surface::enter_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_) {
    auto& handler = proxy::user_data_to_wrapper_cast<surface>(data)->_enter_handler;
    if(handler) {
        handler(*proxy::wrapper_cast<output>(output_));
    }
}

void surface::leave_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_) {
    auto& handler = proxy::user_data_to_wrapper_cast<surface>(data)->_leave_handler;
    if(handler) {
        handler(*proxy::wrapper_cast<output>(output_));
    }
}

