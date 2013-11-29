
#ifndef _WLCPP_DISPLAY_
#define _WLCPP_DISPLAY_

#include <functional>
#include <string>
#include <utility>
#include "proxy.hpp"

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

namespace wlcpp {

class callback;
class registry;

#define WLCPP_DISPLAY_VERSION 1

/** \brief global error values
 *
 *  These errors are global and can be emitted in response to any server
 *  request.
 */
enum display_error {
    DISPLAY_ERROR_INVALID_OBJECT = 0, /**< server couldn't find object */
    DISPLAY_ERROR_INVALID_METHOD = 1, /**< method doesn't exist on the specified interface */
    DISPLAY_ERROR_NO_MEMORY = 2, /**< server is out of memory */
};

/** \brief core global object
 *
 *  The core global object. This is a special singleton object. It is used for
 *  internal Wayland protocol features.
 */
class display final
    : public proxy {
public:
    /** \brief wl_interface for @ref display */
    static const wl_interface interface;

    /** \brief @ref display version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_display object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    display(wl_proxy* obj = nullptr);

    explicit display(const std::string& name);

    explicit display(int fd);

    /** \brief Default move constructor */
    display(display&& rhs) = default;

    /** \brief Destructor */
    virtual ~display();

    /** \brief Default move assignment operator */
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

    /** \brief asynchronous roundtrip
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

    /** \brief get global registry object
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

