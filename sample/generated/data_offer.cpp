
#include "data_offer.hpp"

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

static const wl_interface* wl_data_offer_request_accept_types[] = { nullptr, nullptr };
static const wl_interface* wl_data_offer_request_receive_types[] = { nullptr, nullptr };
static const wl_interface* wl_data_offer_request_destroy_types[] = { };

static const wl_message wl_data_offer_requests[] = {
    { "accept", "u?s", wl_data_offer_request_accept_types },
    { "receive", "sh", wl_data_offer_request_receive_types },
    { "destroy", "", wl_data_offer_request_destroy_types },
};

static const wl_interface* wl_data_offer_event_offer_types[] = { nullptr };

static const wl_message wl_data_offer_events[] = {
    { "offer", "s", wl_data_offer_event_offer_types },
};

const wl_interface data_offer::interface = {
    "wl_data_offer", 1,
    3, wl_data_offer_requests,
    1, wl_data_offer_events
};

const data_offer::listener_t data_offer::listener = {
    &offer_handler,
};

data_offer::data_offer(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

data_offer::data_offer(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

data_offer::~data_offer(){
    destroy();
}

void data_offer::accept(uint32_t serial_, const string* mime_type_) {
    marshal(0, serial_, mime_type_ ? mime_type_->c_str() : nullptr);
}

void data_offer::receive(const string& mime_type_, int32_t fd_) {
    marshal(1, mime_type_.c_str(), fd_);
}

void data_offer::destroy() {
    if(valid() && managed()) {
        marshal(2);
    }
    proxy::destroy();
}

void data_offer::offer_handler(void* data, wl_proxy* wl_obj, const char* mime_type_) {
    auto& handler = proxy::user_data_to_wrapper_cast<data_offer>(data)->_offer_handler;
    if(handler) {
        handler(mime_type_);
    }
}

