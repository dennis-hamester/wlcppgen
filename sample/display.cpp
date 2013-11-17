
#include "display.hpp"

using namespace std;
using namespace wlcpp;

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

display::display(wl_proxy* obj)
    : proxy(obj) {
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
    callback callback(*this);
    marshal(0, callback.wl_obj());
    return callback;
}

registry display::get_registry() {
    registry callback(*this);
    marshal(1, callback.wl_obj());
    return callback;
}

void display::destroy() {
    if(valid()) {
        wl_display_disconnect(wl_obj());
        invalidate();
    }
}

