
#ifndef _WLCPP_PROXY_HPP_
#define _WLCPP_PROXY_HPP_

#include <string>
#include <utility>
#include <wayland-client.h>
#include "event_queue.hpp"

namespace wlcpp {

class proxy {
public:
    proxy(wl_proxy* proxy = nullptr);
    proxy(proxy& factory, const wl_interface& interface);
    proxy(const proxy&) = delete;
    proxy(proxy&& rhs);
    virtual ~proxy();

    bool valid() const;
    void invalidate();
    wl_proxy* wl_obj() const;
    std::uint32_t get_id() const;
    std::string get_class() const;
    void set_queue(event_queue& queue);
    void reset_queue();

    proxy& operator=(const proxy&) = delete;
    proxy& operator=(proxy&& rhs);
    operator bool() const;
    bool operator==(const proxy& rhs) const;
    bool operator!=(const proxy& rhs) const;

protected:
    virtual void destroy();

    template <typename T>
    static T* user_data_to_wrapper_cast(void* data) {
        if(data == nullptr) {
            return nullptr;
        }

        return static_cast<T*>(reinterpret_cast<proxy*>(data));
    }

    template <typename T>
    static T* wrapper_cast(wl_proxy* obj) {
        if(obj == nullptr) {
            return nullptr;
        }

        return user_data_to_wrapper_cast<T>(wl_proxy_get_user_data(obj));
    }

    template <typename T>
    void add_listener(const T& listener) {
        if(valid() && !wl_proxy_get_listener(_proxy)) {
            wl_proxy_add_listener(_proxy, reinterpret_cast<void (**)()>(&const_cast<T&>(listener)), this);
        }

        set_user_data();
    }

    template <typename... T>
    void marshal(std::uint32_t opcode, T&&... args) {
        wl_proxy_marshal(_proxy, opcode, std::forward<T>(args)...);
    }

private:
    void set_user_data();

    wl_proxy* _proxy;
};

} // namespace wlcpp

#endif // _WLCPP_PROXY_HPP_

