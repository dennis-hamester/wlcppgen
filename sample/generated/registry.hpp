
#ifndef _REGISTRY_HPP_
#define _REGISTRY_HPP_

#include <functional>
#include <string>
#include <utility>
#include "../proxy.hpp"

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


#define WLCPP_REGISTRY_VERSION 1

/** \brief global registry object
 *
 *  The global registry object. The server has a number of global objects that
 *  are available to all clients. These objects typically represent an actual
 *  object in the server (for example, an input device) or they are singleton
 *  objects that provide extension functionality.
 *
 *  When a client creates a registry object, the registry object will emit a
 *  global event for each global currently in the registry. Globals come and go
 *  as a result of device or monitor hotplugs, reconfiguration or other events,
 *  and the registry will send out global and global_remove events to keep the
 *  client up to date with the changes. To mark the end of the initial burst of
 *  events, the client can use the wl_display.sync request immediately after
 *  calling wl_display.get_registry.
 *
 *  A client can bind to a global object by using the bind request. This creates
 *  a client-side handle that lets the object emit events to the client and lets
 *  the client invoke requests on the object.
 */
class registry final
    : public proxy {
public:
    /** \brief wl_interface for @ref registry */
    static const wl_interface interface;

    /** \brief @ref registry version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_registry object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    registry(wl_proxy* obj = nullptr);

    /** \brief Create new @ref registry from factory
     *  @param factory Object which acts as the factory
     */
    explicit registry(proxy& factory);

    /** \brief Default move constructor */
    registry(registry&& rhs) = default;

    /** \brief Default destructor */
    virtual ~registry() = default;

    /** \brief Default move assignment operator */
    registry& operator=(registry&& rhs) = default;

    /** \brief bind an object to the display
     *
     *  Binds a new, client-created object to the server using the specified name as
     *  the identifier.
     *
     *  @param name_ unique name for the object
     *  @param version_
     *  @return
     */
    template <typename T>
    T bind(std::uint32_t name_, std::uint32_t version_) {
        T id_(*this);
        marshal(0, name_, T::interface.name, version_, id_.wl_obj());
        return id_;
    }

    /** \brief announce global object
     *
     *  Notify the client of global objects.
     *
     *  The event notifies the client that a global object with the given name is
     *  now available, and it implements the given version of the given interface.
     *
     *  @param name_
     *  @param interface_
     *  @param version_
     */
    using global_handler_sig = void (std::uint32_t name_, const std::string& interface_, std::uint32_t version_);

    /** \brief Set a handler for the global event
     *  @param handler Callable of signature @ref global_handler_sig
     */
    template <typename T>
    void set_global_handler(T&& handler) {
        _global_handler = std::function<global_handler_sig>(std::forward<T>(handler));
    }

    /** \brief announce removal of global object
     *
     *  Notify the client of removed global objects.
     *
     *  This event notifies the client that the global identified by name is no
     *  longer available. If the client bound to the global using the bind request,
     *  the client should now destroy that object.
     *
     *  The object remains valid and requests to the object will be ignored until
     *  the client destroys it, to avoid races between the global going away and a
     *  client sending a request to it.
     *
     *  @param name_
     */
    using global_remove_handler_sig = void (std::uint32_t name_);

    /** \brief Set a handler for the global_remove event
     *  @param handler Callable of signature @ref global_remove_handler_sig
     */
    template <typename T>
    void set_global_remove_handler(T&& handler) {
        _global_remove_handler = std::function<global_remove_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*global_handler) (void*, wl_proxy*, std::uint32_t, const char*, std::uint32_t);
        void (*global_remove_handler) (void*, wl_proxy*, std::uint32_t);
    };

    static void global_handler(void* data, wl_proxy* wl_obj, std::uint32_t name_, const char* interface_, std::uint32_t version_);
    static void global_remove_handler(void* data, wl_proxy* wl_obj, std::uint32_t name_);

    static const listener_t listener;

    std::function<global_handler_sig> _global_handler;
    std::function<global_remove_handler_sig> _global_remove_handler;
};

} // namespace wlcpp

#endif // _REGISTRY_HPP_

