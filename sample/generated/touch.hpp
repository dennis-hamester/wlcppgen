
#ifndef _TOUCH_HPP_
#define _TOUCH_HPP_

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

#define WLCPP_TOUCH_VERSION 3

/** \brief touchscreen input device
 *
 *  The wl_touch interface represents a touchscreen associated with a seat.
 *
 *  Touch interactions can consist of one or more contacts. For each contact, a
 *  series of events is generated, starting with a down event, followed by zero
 *  or more motion events, and ending with an up event. Events relating to the
 *  same contact point can be identified by the ID of the sequence.
 */
class touch final
    : public proxy {
public:
    /** \brief wl_interface for @ref touch */
    static const wl_interface interface;

    /** \brief @ref touch version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** \brief Wrap existing wl_touch object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_touch object and is responsible for destryoing it
     */
    touch(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref touch from factory
     *  @param factory Object which acts as the factory
     */
    explicit touch(proxy& factory);

    /** \brief Default move constructor */
    touch(touch&& rhs) = default;

    /** \brief Destructor */
    virtual ~touch();

    /** \brief Default move assignment operator */
    touch& operator=(touch&& rhs) = default;

    /** \brief touch down event and beginning of a touch sequence
     *
     *  A new touch point has appeared on the surface. This touch point is assigned
     *  a unique @id. Future events from this touchpoint reference this ID. The ID
     *  ceases to be valid after a touch up event and may be re-used in the future.
     *
     *  @param serial_
     *  @param time_ timestamp with millisecond granularity
     *  @param surface_
     *  @param id_ the unique ID of this touch point
     *  @param x_ x coordinate in surface-relative coordinates
     *  @param y_ y coordinate in surface-relative coordinates
     */
    using down_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, surface& surface_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);

    /** \brief Set a handler for the down event
     *  @param handler Callable of signature @ref down_handler_sig
     */
    template <typename T>
    void set_down_handler(T&& handler) {
        _down_handler = std::function<down_handler_sig>(std::forward<T>(handler));
    }

    /** \brief end of a touch event sequence
     *
     *  The touch point has disappeared. No further events will be sent for this
     *  touchpoint and the touch point's ID is released and may be re-used in a
     *  future touch down event.
     *
     *  @param serial_
     *  @param time_ timestamp with millisecond granularity
     *  @param id_ the unique ID of this touch point
     */
    using up_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, std::int32_t id_);

    /** \brief Set a handler for the up event
     *  @param handler Callable of signature @ref up_handler_sig
     */
    template <typename T>
    void set_up_handler(T&& handler) {
        _up_handler = std::function<up_handler_sig>(std::forward<T>(handler));
    }

    /** \brief update of touch point coordinates
     *
     *  A touchpoint has changed coordinates.
     *
     *  @param time_ timestamp with millisecond granularity
     *  @param id_ the unique ID of this touch point
     *  @param x_ x coordinate in surface-relative coordinates
     *  @param y_ y coordinate in surface-relative coordinates
     */
    using motion_handler_sig = void (std::uint32_t time_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);

    /** \brief Set a handler for the motion event
     *  @param handler Callable of signature @ref motion_handler_sig
     */
    template <typename T>
    void set_motion_handler(T&& handler) {
        _motion_handler = std::function<motion_handler_sig>(std::forward<T>(handler));
    }

    /** \brief end of touch frame event
     *
     *  Indicates the end of a contact point list.
     */
    using frame_handler_sig = void ();

    /** \brief Set a handler for the frame event
     *  @param handler Callable of signature @ref frame_handler_sig
     */
    template <typename T>
    void set_frame_handler(T&& handler) {
        _frame_handler = std::function<frame_handler_sig>(std::forward<T>(handler));
    }

    /** \brief touch session cancelled
     *
     *  Sent if the compositor decides the touch stream is a global gesture. No
     *  further events are sent to the clients from that particular gesture. Touch
     *  cancellation applies to all touch points currently active on this client's
     *  surface. The client is responsible for finalizing the touch points, future
     *  touch points on this surface may re-use the touch point ID.
     */
    using cancel_handler_sig = void ();

    /** \brief Set a handler for the cancel event
     *  @param handler Callable of signature @ref cancel_handler_sig
     */
    template <typename T>
    void set_cancel_handler(T&& handler) {
        _cancel_handler = std::function<cancel_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*down_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, wl_proxy*, std::int32_t, wl_fixed_t, wl_fixed_t);
        void (*up_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, std::int32_t);
        void (*motion_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, wl_fixed_t, wl_fixed_t);
        void (*frame_handler) (void*, wl_proxy*);
        void (*cancel_handler) (void*, wl_proxy*);
    };

    static void down_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, wl_proxy* surface_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);
    static void up_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, std::int32_t id_);
    static void motion_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);
    static void frame_handler(void* data, wl_proxy* wl_obj);
    static void cancel_handler(void* data, wl_proxy* wl_obj);

    static const listener_t listener;

    std::function<down_handler_sig> _down_handler;
    std::function<up_handler_sig> _up_handler;
    std::function<motion_handler_sig> _motion_handler;
    std::function<frame_handler_sig> _frame_handler;
    std::function<cancel_handler_sig> _cancel_handler;
};

} // namespace wlcpp

#endif // _TOUCH_HPP_

