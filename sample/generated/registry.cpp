
#include "registry.hpp"

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

static const wl_interface* wl_registry_request_bind_types[] = { nullptr, nullptr, nullptr, nullptr };

static const wl_message wl_registry_requests[] = {
    { "bind", "usun", wl_registry_request_bind_types },
};

static const wl_interface* wl_registry_event_global_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_registry_event_global_remove_types[] = { nullptr };

static const wl_message wl_registry_events[] = {
    { "global", "usu", wl_registry_event_global_types },
    { "global_remove", "u", wl_registry_event_global_remove_types },
};

const wl_interface registry::interface = {
    "wl_registry", 1,
    1, wl_registry_requests,
    2, wl_registry_events
};

const registry::listener_t registry::listener = {
    &global_handler,
    &global_remove_handler,
};

registry::registry(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

registry::registry(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

void registry::global_handler(void* data, wl_proxy* wl_obj, uint32_t name_, const char* interface_, uint32_t version_) {
    auto& handler = proxy::user_data_to_wrapper_cast<registry>(data)->_global_handler;
    if(handler) {
        handler(name_, interface_, version_);
    }
}

void registry::global_remove_handler(void* data, wl_proxy* wl_obj, uint32_t name_) {
    auto& handler = proxy::user_data_to_wrapper_cast<registry>(data)->_global_remove_handler;
    if(handler) {
        handler(name_);
    }
}

