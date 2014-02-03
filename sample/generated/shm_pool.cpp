
#include "shm_pool.hpp"
#include "buffer.hpp"

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

static const wl_interface* wl_shm_pool_request_create_buffer_types[] = { &buffer::interface, nullptr, nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_shm_pool_request_destroy_types[] = { };
static const wl_interface* wl_shm_pool_request_resize_types[] = { nullptr };

static const wl_message wl_shm_pool_requests[] = {
    { "create_buffer", "niiiiu", wl_shm_pool_request_create_buffer_types },
    { "destroy", "", wl_shm_pool_request_destroy_types },
    { "resize", "i", wl_shm_pool_request_resize_types },
};

const wl_interface shm_pool::interface = {
    "wl_shm_pool", 1,
    3, wl_shm_pool_requests,
    0, nullptr
};

shm_pool::shm_pool(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
}

shm_pool::shm_pool(proxy& factory)
    : proxy(factory, interface) {
}

shm_pool::~shm_pool(){
    destroy();
}

buffer shm_pool::create_buffer(int32_t offset_, int32_t width_, int32_t height_, int32_t stride_, uint32_t format_) {
    buffer id_(*this);
    marshal(0, id_.wl_obj(), offset_, width_, height_, stride_, format_);
    return id_;
}

void shm_pool::resize(int32_t size_) {
    marshal(2, size_);
}

void shm_pool::destroy() {
    if(valid() && managed()) {
        marshal(1);
    }
    proxy::destroy();
}

