
#include "shell_surface.hpp"
#include "output.hpp"
#include "seat.hpp"
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

static const wl_interface* wl_shell_surface_request_pong_types[] = { nullptr };
static const wl_interface* wl_shell_surface_request_move_types[] = { &seat::interface, nullptr };
static const wl_interface* wl_shell_surface_request_resize_types[] = { &seat::interface, nullptr, nullptr };
static const wl_interface* wl_shell_surface_request_set_toplevel_types[] = { };
static const wl_interface* wl_shell_surface_request_set_transient_types[] = { &surface::interface, nullptr, nullptr, nullptr };
static const wl_interface* wl_shell_surface_request_set_fullscreen_types[] = { nullptr, nullptr, &output::interface };
static const wl_interface* wl_shell_surface_request_set_popup_types[] = { &seat::interface, nullptr, &surface::interface, nullptr, nullptr, nullptr };
static const wl_interface* wl_shell_surface_request_set_maximized_types[] = { &output::interface };
static const wl_interface* wl_shell_surface_request_set_title_types[] = { nullptr };
static const wl_interface* wl_shell_surface_request_set_class_types[] = { nullptr };

static const wl_message wl_shell_surface_requests[] = {
    { "pong", "u", wl_shell_surface_request_pong_types },
    { "move", "ou", wl_shell_surface_request_move_types },
    { "resize", "ouu", wl_shell_surface_request_resize_types },
    { "set_toplevel", "", wl_shell_surface_request_set_toplevel_types },
    { "set_transient", "oiiu", wl_shell_surface_request_set_transient_types },
    { "set_fullscreen", "uu?o", wl_shell_surface_request_set_fullscreen_types },
    { "set_popup", "ouoiiu", wl_shell_surface_request_set_popup_types },
    { "set_maximized", "?o", wl_shell_surface_request_set_maximized_types },
    { "set_title", "s", wl_shell_surface_request_set_title_types },
    { "set_class", "s", wl_shell_surface_request_set_class_types },
};

static const wl_interface* wl_shell_surface_event_ping_types[] = { nullptr };
static const wl_interface* wl_shell_surface_event_configure_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_shell_surface_event_popup_done_types[] = { };

static const wl_message wl_shell_surface_events[] = {
    { "ping", "u", wl_shell_surface_event_ping_types },
    { "configure", "uii", wl_shell_surface_event_configure_types },
    { "popup_done", "", wl_shell_surface_event_popup_done_types },
};

const wl_interface shell_surface::interface = {
    "wl_shell_surface", 1,
    10, wl_shell_surface_requests,
    3, wl_shell_surface_events
};

const shell_surface::listener_t shell_surface::listener = {
    &ping_handler,
    &configure_handler,
    &popup_done_handler,
};

shell_surface::shell_surface(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

shell_surface::shell_surface(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void shell_surface::pong(uint32_t serial_) {
    marshal(0, serial_);
}

void shell_surface::move(seat& seat_, uint32_t serial_) {
    marshal(1, seat_.wl_obj(), serial_);
}

void shell_surface::resize(seat& seat_, uint32_t serial_, uint32_t edges_) {
    marshal(2, seat_.wl_obj(), serial_, edges_);
}

void shell_surface::set_toplevel() {
    marshal(3);
}

void shell_surface::set_transient(surface& parent_, int32_t x_, int32_t y_, uint32_t flags_) {
    marshal(4, parent_.wl_obj(), x_, y_, flags_);
}

void shell_surface::set_fullscreen(uint32_t method_, uint32_t framerate_, output* output_) {
    marshal(5, method_, framerate_, output_ ? output_->wl_obj() : nullptr);
}

void shell_surface::set_popup(seat& seat_, uint32_t serial_, surface& parent_, int32_t x_, int32_t y_, uint32_t flags_) {
    marshal(6, seat_.wl_obj(), serial_, parent_.wl_obj(), x_, y_, flags_);
}

void shell_surface::set_maximized(output* output_) {
    marshal(7, output_ ? output_->wl_obj() : nullptr);
}

void shell_surface::set_title(const string& title_) {
    marshal(8, title_.c_str());
}

void shell_surface::set_class(const string& class__) {
    marshal(9, class__.c_str());
}

void shell_surface::ping_handler(void* data, wl_proxy* wl_obj, uint32_t serial_) {
    auto& handler = proxy::user_data_to_wrapper_cast<shell_surface>(data)->_ping_handler;
    if(handler) {
        handler(serial_);
    }
}

void shell_surface::configure_handler(void* data, wl_proxy* wl_obj, uint32_t edges_, int32_t width_, int32_t height_) {
    auto& handler = proxy::user_data_to_wrapper_cast<shell_surface>(data)->_configure_handler;
    if(handler) {
        handler(edges_, width_, height_);
    }
}

void shell_surface::popup_done_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<shell_surface>(data)->_popup_done_handler;
    if(handler) {
        handler();
    }
}

