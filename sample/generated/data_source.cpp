
#include "data_source.hpp"

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

static const wl_interface* wl_data_source_request_offer_types[] = { nullptr };
static const wl_interface* wl_data_source_request_destroy_types[] = { };

static const wl_message wl_data_source_requests[] = {
    { "offer", "s", wl_data_source_request_offer_types },
    { "destroy", "", wl_data_source_request_destroy_types },
};

static const wl_interface* wl_data_source_event_target_types[] = { nullptr };
static const wl_interface* wl_data_source_event_send_types[] = { nullptr, nullptr };
static const wl_interface* wl_data_source_event_cancelled_types[] = { };

static const wl_message wl_data_source_events[] = {
    { "target", "?s", wl_data_source_event_target_types },
    { "send", "sh", wl_data_source_event_send_types },
    { "cancelled", "", wl_data_source_event_cancelled_types },
};

const wl_interface data_source::interface = {
    "wl_data_source", 1,
    2, wl_data_source_requests,
    3, wl_data_source_events
};

const data_source::listener_t data_source::listener = {
    &target_handler,
    &send_handler,
    &cancelled_handler,
};

data_source::data_source(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

data_source::data_source(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

data_source::~data_source(){
    destroy();
}

void data_source::offer(const string& mime_type_) {
    marshal(0, mime_type_.c_str());
}

void data_source::destroy() {
    if(valid() && managed()) {
        marshal(1);
    }
    proxy::destroy();
}

void data_source::target_handler(void* data, wl_proxy* wl_obj, const char* mime_type_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_source>(data)->_target_handler;
    if(handler) {
        string mime_type_str = mime_type_ ? mime_type_ : string();
        handler(mime_type_ ? &mime_type_str : nullptr);
    }
}

void data_source::send_handler(void* data, wl_proxy* wl_obj, const char* mime_type_, int32_t fd_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_source>(data)->_send_handler;
    if(handler) {
        handler(mime_type_, fd_);
    }
}

void data_source::cancelled_handler(void* data, wl_proxy* wl_obj) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_source>(data)->_cancelled_handler;
    if(handler) {
        handler();
    }
}

