
#ifndef _WLCPP_EVENT_QUEUE_HPP_
#define _WLCPP_EVENT_QUEUE_HPP_

#include <wayland-client.h>

namespace wlcpp {

class event_queue {
public:
    event_queue(wl_event_queue* queue = nullptr);
    event_queue(const event_queue&) = delete;
    event_queue(event_queue&&) = default;
    ~event_queue();

    bool valid() const;
    wl_event_queue* wl_obj() const;

    event_queue& operator=(const event_queue&) = delete;
    event_queue& operator=(event_queue&&) = default;
    operator bool() const;
    bool operator==(const event_queue& rhs) const;
    bool operator!=(const event_queue& rhs) const;

private:
    wl_event_queue* _queue;
};

} // namespace wlcpp

#endif // _WLCPP_EVENT_QUEUE_HPP_

