
#ifndef _WLCPP_EVENT_QUEUE_HPP_
#define _WLCPP_EVENT_QUEUE_HPP_

#include <wayland-client.h>

namespace wlcpp {

class event_queue {
public:
    event_queue(wl_event_queue* queue = nullptr, bool managed = true);
    event_queue(const event_queue&) = delete;
    event_queue(event_queue&& rhs);
    ~event_queue();

    bool valid() const;
    bool managed() const;
    void invalidate();
    wl_event_queue* wl_obj() const;

    event_queue& operator=(const event_queue&) = delete;
    event_queue& operator=(event_queue&& rhs);
    operator bool() const;
    bool operator==(const event_queue& rhs) const;
    bool operator!=(const event_queue& rhs) const;

private:
    void destroy();

    wl_event_queue* _queue;
    bool _managed;
};

} // namespace wlcpp

#endif // _WLCPP_EVENT_QUEUE_HPP_

