
#include "output.hpp"

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

static const wl_interface* wl_output_event_geometry_types[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_output_event_mode_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_output_event_done_types[] = { };
static const wl_interface* wl_output_event_scale_types[] = { nullptr };

static const wl_message wl_output_events[] = {
    { "geometry", "iiiiissi", wl_output_event_geometry_types },
    { "mode", "uiii", wl_output_event_mode_types },
    { "done", "2", wl_output_event_done_types },
    { "scale", "2i", wl_output_event_scale_types },
};

const wl_interface output::interface = {
    "wl_output", 2,
    0, nullptr,
    4, wl_output_events
};

const output::listener_t output::listener = {
    &geometry_handler,
    &mode_handler,
    &done_handler,
    &scale_handler,
};

output::output(wl_proxy* obj)
    : proxy(obj) {
    add_listener(listener);
}

output::output(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void output::geometry_handler(void* data, wl_proxy* wl_obj, int32_t x_, int32_t y_, int32_t physical_width_, int32_t physical_height_, int32_t subpixel_, const char* make_, const char* model_, int32_t transform_) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_geometry_handler;
    if(handler) {
        handler(x_, y_, physical_width_, physical_height_, subpixel_, make_, model_, transform_);
    }
}

void output::mode_handler(void* data, wl_proxy* wl_obj, uint32_t flags_, int32_t width_, int32_t height_, int32_t refresh_) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_mode_handler;
    if(handler) {
        handler(flags_, width_, height_, refresh_);
    }
}

void output::done_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_done_handler;
    if(handler) {
        handler();
    }
}

void output::scale_handler(void* data, wl_proxy* wl_obj, int32_t factor_) {
    auto& handler = proxy::user_data_to_wrapper_cast<output>(data)->_scale_handler;
    if(handler) {
        handler(factor_);
    }
}

