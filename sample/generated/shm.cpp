
#include "shm.hpp"
#include "shm_pool.hpp"

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

static const wl_interface* wl_shm_request_create_pool_types[] = { &shm_pool::interface, nullptr, nullptr };

static const wl_message wl_shm_requests[] = {
    { "create_pool", "nhi", wl_shm_request_create_pool_types },
};

static const wl_interface* wl_shm_event_format_types[] = { nullptr };

static const wl_message wl_shm_events[] = {
    { "format", "u", wl_shm_event_format_types },
};

const wl_interface shm::interface = {
    "wl_shm", 1,
    1, wl_shm_requests,
    1, wl_shm_events
};

const shm::listener_t shm::listener = {
    &format_handler,
};

shm::shm(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

shm::shm(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

shm_pool shm::create_pool(int32_t fd_, int32_t size_) {
    shm_pool id_(*this);
    marshal(0, id_.wl_obj(), fd_, size_);
    return id_;
}

void shm::format_handler(void* data, wl_proxy* wl_obj, uint32_t format_) {
    auto& handler = proxy::user_data_to_wrapper_cast<shm>(data)->_format_handler;
    if(handler) {
        handler(format_);
    }
}

