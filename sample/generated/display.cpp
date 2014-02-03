
#include "display.hpp"
#include "callback.hpp"
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

static const wl_interface* wl_display_request_sync_types[] = { &callback::interface };
static const wl_interface* wl_display_request_get_registry_types[] = { &registry::interface };

static const wl_message wl_display_requests[] = {
    { "sync", "n", wl_display_request_sync_types },
    { "get_registry", "n", wl_display_request_get_registry_types },
};

static const wl_interface* wl_display_event_error_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_display_event_delete_id_types[] = { nullptr };

static const wl_message wl_display_events[] = {
    { "error", "ous", wl_display_event_error_types },
    { "delete_id", "u", wl_display_event_delete_id_types },
};

const wl_interface display::interface = {
    "wl_display", 1,
    2, wl_display_requests,
    2, wl_display_events
};

display::display(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
}

display::display(const string& name)
    : proxy(reinterpret_cast<wl_proxy*>(name.empty() ? wl_display_connect(nullptr) : wl_display_connect(name.c_str()))) {
}

display::display(int fd)
    : proxy(reinterpret_cast<wl_proxy*>(wl_display_connect_to_fd(fd))) {
}

display::~display() {
    destroy();
}

wl_display* display::wl_obj() const {
    return reinterpret_cast<wl_display*>(proxy::wl_obj());
}

int display::get_fd() const {
    return wl_display_get_fd(wl_obj());
}

int display::dispatch() {
    return wl_display_dispatch(wl_obj());
}

int display::dispatch_queue(event_queue& queue) {
    return wl_display_dispatch_queue(wl_obj(), queue.wl_obj());
}

int display::dispatch_queue_pending(event_queue& queue) {
    return wl_display_dispatch_queue_pending(wl_obj(), queue.wl_obj());
}

int display::dispatch_pending() {
    return wl_display_dispatch_pending(wl_obj());
}

int display::get_error() {
    return wl_display_get_error(wl_obj());
}

int display::flush() {
    return wl_display_flush(wl_obj());
}

int display::roundtrip() {
    return wl_display_roundtrip(wl_obj());
}

event_queue display::create_queue() {
    return event_queue(wl_display_create_queue(wl_obj()));
}

int display::prepare_read_queue(event_queue& queue) {
    return wl_display_prepare_read_queue(wl_obj(), queue.wl_obj());
}

int display::prepare_read() {
    return wl_display_prepare_read(wl_obj());
}

void display::cancel_read() {
    wl_display_cancel_read(wl_obj());
}

int display::read_events() {
    return wl_display_read_events(wl_obj());
}

callback display::sync() {
    callback callback_(*this);
    marshal(0, callback_.wl_obj());
    return callback_;
}

registry display::get_registry() {
    registry callback_(*this);
    marshal(1, callback_.wl_obj());
    return callback_;
}

void display::destroy() {
    if(valid() && managed()) {
        wl_display_disconnect(wl_obj());
        invalidate();
    }
}

