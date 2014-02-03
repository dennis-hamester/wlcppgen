
#ifndef _POINTER_HPP_
#define _POINTER_HPP_

#include <functional>
#include <string>
#include <utility>
#include "../proxy.hpp"

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

namespace wlcpp {

class surface;

#define WLCPP_POINTER_VERSION 3

/** \brief physical button state
 *
 *  Describes the physical state of a button which provoked the button event.
 */
enum pointer_button_state {
    POINTER_BUTTON_STATE_RELEASED = 0, /**< The button is not pressed */
    POINTER_BUTTON_STATE_PRESSED = 1, /**< The button is pressed */
};

/** \brief axis types
 *
 *  Describes the axis types of scroll events.
 */
enum pointer_axis {
    POINTER_AXIS_VERTICAL_SCROLL = 0,
    POINTER_AXIS_HORIZONTAL_SCROLL = 1,
};

/** \brief pointer input device
 *
 *  The wl_pointer interface represents one or more input devices, such as mice,
 *  which control the pointer location and pointer_focus of a seat.
 *
 *  The wl_pointer interface generates motion, enter and leave events for the
 *  surfaces that the pointer is located over, and button and axis events for
 *  button presses, button releases and scrolling.
 */
class pointer final
    : public proxy {
public:
    /** \brief wl_interface for @ref pointer */
    static const wl_interface interface;

    /** \brief @ref pointer version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** \brief Wrap existing wl_pointer object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_pointer object and is responsible for destryoing it
     */
    pointer(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref pointer from factory
     *  @param factory Object which acts as the factory
     */
    explicit pointer(proxy& factory);

    /** \brief Default move constructor */
    pointer(pointer&& rhs) = default;

    /** \brief Destructor */
    virtual ~pointer();

    /** \brief Default move assignment operator */
    pointer& operator=(pointer&& rhs) = default;

    /** \brief set the pointer surface
     *
     *  Set the pointer surface, i.e., the surface that contains the pointer image
     *  (cursor). This request only takes effect if the pointer focus for this
     *  device is one of the requesting client's surfaces or the surface parameter
     *  is the current pointer surface. If there was a previous surface set with
     *  this request it is replaced. If surface is NULL, the pointer image is
     *  hidden.
     *
     *  The parameters hotspot_x and hotspot_y define the position of the pointer
     *  surface relative to the pointer location. Its top-left corner is always at
     *  (x, y) - (hotspot_x, hotspot_y), where (x, y) are the coordinates of the
     *  pointer location, in surface local coordinates.
     *
     *  On surface.attach requests to the pointer surface, hotspot_x and hotspot_y
     *  are decremented by the x and y parameters passed to the request. Attach must
     *  be confirmed by wl_surface.commit as usual.
     *
     *  The hotspot can also be updated by passing the currently set pointer surface
     *  to this request with new values for hotspot_x and hotspot_y.
     *
     *  The current and pending input regions of the wl_surface are cleared, and
     *  wl_surface.set_input_region is ignored until the wl_surface is no longer
     *  used as the cursor. When the use as a cursor ends, the current and pending
     *  input regions become undefined, and the wl_surface is unmapped.
     *
     *  @param serial_ serial of the enter event
     *  @param surface_
     *  @param hotspot_x_ x coordinate in surface-relative coordinates
     *  @param hotspot_y_ y coordinate in surface-relative coordinates
     */
    void set_cursor(std::uint32_t serial_, surface* surface_, std::int32_t hotspot_x_, std::int32_t hotspot_y_);

    /** \brief enter event
     *
     *  Notification that this seat's pointer is focused on a certain surface.
     *
     *  When an seat's focus enters a surface, the pointer image is undefined and a
     *  client should respond to this event by setting an appropriate pointer image
     *  with the set_cursor request.
     *
     *  @param serial_
     *  @param surface_
     *  @param surface_x_ x coordinate in surface-relative coordinates
     *  @param surface_y_ y coordinate in surface-relative coordinates
     */
    using enter_handler_sig = void (std::uint32_t serial_, surface& surface_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);

    /** \brief Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** \brief leave event
     *
     *  Notification that this seat's pointer is no longer focused on a certain
     *  surface.
     *
     *  The leave notification is sent before the enter notification for the new
     *  focus.
     *
     *  @param serial_
     *  @param surface_
     */
    using leave_handler_sig = void (std::uint32_t serial_, surface& surface_);

    /** \brief Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

    /** \brief pointer motion event
     *
     *  Notification of pointer location change. The arguments surface_x and
     *  surface_y are the location relative to the focused surface.
     *
     *  @param time_ timestamp with millisecond granularity
     *  @param surface_x_ x coordinate in surface-relative coordinates
     *  @param surface_y_ y coordinate in surface-relative coordinates
     */
    using motion_handler_sig = void (std::uint32_t time_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);

    /** \brief Set a handler for the motion event
     *  @param handler Callable of signature @ref motion_handler_sig
     */
    template <typename T>
    void set_motion_handler(T&& handler) {
        _motion_handler = std::function<motion_handler_sig>(std::forward<T>(handler));
    }

    /** \brief pointer button event
     *
     *  Mouse button click and release notifications.
     *
     *  The location of the click is given by the last motion or enter event. The
     *  time argument is a timestamp with millisecond granularity, with an undefined
     *  base.
     *
     *  @param serial_
     *  @param time_ timestamp with millisecond granularity
     *  @param button_
     *  @param state_
     */
    using button_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, std::uint32_t button_, std::uint32_t state_);

    /** \brief Set a handler for the button event
     *  @param handler Callable of signature @ref button_handler_sig
     */
    template <typename T>
    void set_button_handler(T&& handler) {
        _button_handler = std::function<button_handler_sig>(std::forward<T>(handler));
    }

    /** \brief axis event
     *
     *  Scroll and other axis notifications.
     *
     *  For scroll events (vertical and horizontal scroll axes), the value parameter
     *  is the length of a vector along the specified axis in a coordinate space
     *  identical to those of motion events, representing a relative movement along
     *  the specified axis.
     *
     *  For devices that support movements non-parallel to axes multiple axis events
     *  will be emitted.
     *
     *  When applicable, for example for touch pads, the server can choose to emit
     *  scroll events where the motion vector is equivalent to a motion event
     *  vector.
     *
     *  When applicable, clients can transform its view relative to the scroll
     *  distance.
     *
     *  @param time_ timestamp with millisecond granularity
     *  @param axis_
     *  @param value_
     */
    using axis_handler_sig = void (std::uint32_t time_, std::uint32_t axis_, wl_fixed_t value_);

    /** \brief Set a handler for the axis event
     *  @param handler Callable of signature @ref axis_handler_sig
     */
    template <typename T>
    void set_axis_handler(T&& handler) {
        _axis_handler = std::function<axis_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*enter_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*, wl_fixed_t, wl_fixed_t);
        void (*leave_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*);
        void (*motion_handler) (void*, wl_proxy*, std::uint32_t, wl_fixed_t, wl_fixed_t);
        void (*button_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
        void (*axis_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, wl_fixed_t);
    };

    static void enter_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);
    static void leave_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_);
    static void motion_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);
    static void button_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, std::uint32_t button_, std::uint32_t state_);
    static void axis_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, std::uint32_t axis_, wl_fixed_t value_);

    static const listener_t listener;

    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
    std::function<motion_handler_sig> _motion_handler;
    std::function<button_handler_sig> _button_handler;
    std::function<axis_handler_sig> _axis_handler;
};

} // namespace wlcpp

#endif // _POINTER_HPP_

