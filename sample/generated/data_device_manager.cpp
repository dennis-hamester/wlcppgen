
#include "data_device_manager.hpp"
#include "data_device.hpp"
#include "data_source.hpp"
#include "seat.hpp"

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

static const wl_interface* wl_data_device_manager_request_create_data_source_types[] = { &data_source::interface };
static const wl_interface* wl_data_device_manager_request_get_data_device_types[] = { &data_device::interface, &seat::interface };

static const wl_message wl_data_device_manager_requests[] = {
    { "create_data_source", "n", wl_data_device_manager_request_create_data_source_types },
    { "get_data_device", "no", wl_data_device_manager_request_get_data_device_types },
};

const wl_interface data_device_manager::interface = {
    "wl_data_device_manager", 1,
    2, wl_data_device_manager_requests,
    0, nullptr
};

data_device_manager::data_device_manager(wl_proxy* obj)
    : proxy(obj) {
}

data_device_manager::data_device_manager(proxy& factory)
    : proxy(factory, interface) {
}

data_source data_device_manager::create_data_source() {
    data_source id_(*this);
    marshal(0, id_.wl_obj());
    return id_;
}

data_device data_device_manager::get_data_device(seat& seat_) {
    data_device id_(*this);
    marshal(1, id_.wl_obj(), seat_.wl_obj());
    return id_;
}

