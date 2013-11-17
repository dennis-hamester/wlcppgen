
#ifndef _WLCPP_DISPLAY_
#define _WLCPP_DISPLAY_

#include "wlcpp.hpp"
#include "event_queue.hpp"

namespace wlcpp {

class display;

#define WLCPP_DISPLAY_VERSION 1

/** global error values
 *
 *  These errors are global and can be emitted in response to any server
 *  request.
 */
enum display_error {
    DISPLAY_ERROR_INVALID_OBJECT = 0, /**< server couldn't find object */
    DISPLAY_ERROR_INVALID_METHOD = 1, /**< method doesn't exist on the specified interface */
    DISPLAY_ERROR_NO_MEMORY = 2, /**< server is out of memory */
};

/** core global object
 *
 *  The core global object. This is a special singleton object. It is used for
 *  internal Wayland protocol features.
 */
class display final
    : public proxy {
public:
    /** wl_interface for display */
    static const wl_interface interface;

    /** display version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_display object
     *  @param obj Object to wrap
     */
    display(wl_proxy* obj = nullptr);

    explicit display(const std::string& name);

    explicit display(int fd);

    /** Default move constructor */
    display(display&& rhs) = default;

    /** Destructor */
    virtual ~display();

    /** Default move assignment operator */
    display& operator=(display&& rhs) = default;

    wl_display* wl_obj() const;
    int get_fd() const;
    int dispatch();
    int dispatch_queue(event_queue& queue);
    int dispatch_queue_pending(event_queue& queue);
    int dispatch_pending();
    int get_error();
    int flush();
    int roundtrip();
    event_queue create_queue();
    int prepare_read_queue(event_queue& queue);
    int prepare_read();
    void cancel_read();
    int read_events();

    /** asynchronous roundtrip
     *
     *  The sync request asks the server to emit the 'done' event on the returned
     *  wl_callback object. Since requests are handled in-order and events are
     *  delivered in-order, this can used as a barrier to ensure all previous
     *  requests and the resulting events have been handled.
     *  
     *  The object returned by this request will be destroyed by the compositor
     *  after the callback is fired and as such the client must not attempt to use
     *  it after that point.
     *
     *  @return
     */
    callback sync();

    /** get global registry object
     *
     *  This request creates a registry object that allows the client to list and
     *  bind the global objects available from the compositor.
     *
     *  @return
     */
    registry get_registry();

protected:
    void destroy() override;
};

} // namespace wlcpp

#endif // _WLCPP_DISPLAY_

