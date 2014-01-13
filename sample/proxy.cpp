
#include "proxy.hpp"

using namespace std;
using namespace wlcpp;

proxy::proxy(wl_proxy* proxy, bool managed)
    : _proxy(proxy),
      _managed(managed) {
    set_user_data();
}

proxy::proxy(proxy& factory, const wl_interface& interface)
    : _proxy(wl_proxy_create(factory.wl_obj(), &interface)),
      _managed(true) {
    set_user_data();
}

proxy::proxy(proxy&& rhs)
    : _proxy(rhs.wl_obj()),
      _managed(rhs._managed) {
    set_user_data();
    rhs.invalidate();
}

proxy::~proxy() {
    destroy();
}

bool proxy::valid() const {
    return _proxy != nullptr;
}

bool proxy::managed() const {
    return _managed;
}

void proxy::invalidate() {
    _proxy = nullptr;
}

wl_proxy* proxy::wl_obj() const {
    return _proxy;
}

uint32_t proxy::get_id() const {
    return wl_proxy_get_id(_proxy);
}

string proxy::get_class() const {
    return wl_proxy_get_class(_proxy);
}

void proxy::set_queue(event_queue& queue) {
    wl_proxy_set_queue(_proxy, queue.wl_obj());
}

void proxy::reset_queue() {
    wl_proxy_set_queue(_proxy, nullptr);
}

proxy& proxy::operator=(proxy&& rhs) {
    destroy();
    _proxy = rhs.wl_obj();
    _managed = rhs._managed;
    set_user_data();
    rhs.invalidate();
    return *this;
}

proxy::operator bool() const {
    return valid();
}

bool proxy::operator==(const proxy& rhs) const {
    return get_id() == rhs.get_id();
}

bool proxy::operator!=(const proxy& rhs) const {
    return get_id() != rhs.get_id();
}

void proxy::destroy() {
    if(valid() && _managed) {
        wl_proxy_destroy(_proxy);
        invalidate();
    }
}

void proxy::set_user_data() {
    if(valid() && _managed) {
        wl_proxy_set_user_data(_proxy, this);
    }
}

