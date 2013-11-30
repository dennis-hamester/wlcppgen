
#ifndef _SEAT_HPP_
#define _SEAT_HPP_

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

class keyboard;
class pointer;
class touch;

#define WLCPP_SEAT_VERSION 3

/** \brief seat capability bitmask
 *
 *  This is a bitmask of capabilities this seat has; if a member is set, then it
 *  is present on the seat.
 */
enum seat_capability {
    SEAT_CAPABILITY_POINTER = 1, /**< The seat has pointer devices */
    SEAT_CAPABILITY_KEYBOARD = 2, /**< The seat has one or more keyboards */
    SEAT_CAPABILITY_TOUCH = 4, /**< The seat has touch devices */
};

/** \brief group of input devices
 *
 *  A seat is a group of keyboards, pointer and touch devices. This object is
 *  published as a global during start up, or when such a device is hot plugged.
 *  A seat typically has a pointer and maintains a keyboard focus and a pointer
 *  focus.
 */
class seat final
    : public proxy {
public:
    /** \brief wl_interface for @ref seat */
    static const wl_interface interface;

    /** \brief @ref seat version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** \brief Wrap existing wl_seat object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    seat(wl_proxy* obj = nullptr);

    /** \brief Create new @ref seat from factory
     *  @param factory Object which acts as the factory
     */
    explicit seat(proxy& factory);

    /** \brief Default move constructor */
    seat(seat&& rhs) = default;

    /** \brief Default destructor */
    virtual ~seat() = default;

    /** \brief Default move assignment operator */
    seat& operator=(seat&& rhs) = default;

    /** \brief return pointer object
     *
     *  The ID provided will be initialized to the wl_pointer interface for this
     *  seat.
     *
     *  This request only takes effect if the seat has the pointer capability.
     *
     *  @return
     */
    pointer get_pointer();

    /** \brief return keyboard object
     *
     *  The ID provided will be initialized to the wl_keyboard interface for this
     *  seat.
     *
     *  This request only takes effect if the seat has the keyboard capability.
     *
     *  @return
     */
    keyboard get_keyboard();

    /** \brief return touch object
     *
     *  The ID provided will be initialized to the wl_touch interface for this seat.
     *
     *  This request only takes effect if the seat has the touch capability.
     *
     *  @return
     */
    touch get_touch();

    /** \brief seat capabilities changed
     *
     *  This is emitted whenever a seat gains or loses the pointer, keyboard or
     *  touch capabilities. The argument is a capability enum containing the
     *  complete set of capabilities this seat has.
     *
     *  @param capabilities_
     */
    using capabilities_handler_sig = void (std::uint32_t capabilities_);

    /** \brief Set a handler for the capabilities event
     *  @param handler Callable of signature @ref capabilities_handler_sig
     */
    template <typename T>
    void set_capabilities_handler(T&& handler) {
        _capabilities_handler = std::function<capabilities_handler_sig>(std::forward<T>(handler));
    }

    /** \brief unique identifier for this seat
     *
     *  In a multiseat configuration this can be used by the client to help identify
     *  which physical devices the seat represents. Based on the seat configuration
     *  used by the compositor.
     *
     *  @param name_
     */
    using name_handler_sig = void (const std::string& name_);

    /** \brief Set a handler for the name event
     *  @param handler Callable of signature @ref name_handler_sig
     */
    template <typename T>
    void set_name_handler(T&& handler) {
        _name_handler = std::function<name_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*capabilities_handler) (void*, wl_proxy*, std::uint32_t);
        void (*name_handler) (void*, wl_proxy*, const char*);
    };

    static void capabilities_handler(void* data, wl_proxy* wl_obj, std::uint32_t capabilities_);
    static void name_handler(void* data, wl_proxy* wl_obj, const char* name_);

    static const listener_t listener;

    std::function<capabilities_handler_sig> _capabilities_handler;
    std::function<name_handler_sig> _name_handler;
};

} // namespace wlcpp

#endif // _SEAT_HPP_

