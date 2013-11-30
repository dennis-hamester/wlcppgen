
#ifndef _DATA_DEVICE_HPP_
#define _DATA_DEVICE_HPP_

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

class data_offer;
class data_source;
class surface;

#define WLCPP_DATA_DEVICE_VERSION 1

/** \brief data transfer device
 *
 *  There is one wl_data_device per seat which can be obtained from the global
 *  wl_data_device_manager singleton.
 *
 *  A wl_data_device provides access to inter-client data transfer mechanisms
 *  such as copy-and-paste and drag-and-drop.
 */
class data_device final
    : public proxy {
public:
    /** \brief wl_interface for @ref data_device */
    static const wl_interface interface;

    /** \brief @ref data_device version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_data_device object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    data_device(wl_proxy* obj = nullptr);

    /** \brief Create new @ref data_device from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_device(proxy& factory);

    /** \brief Default move constructor */
    data_device(data_device&& rhs) = default;

    /** \brief Default destructor */
    virtual ~data_device() = default;

    /** \brief Default move assignment operator */
    data_device& operator=(data_device&& rhs) = default;

    /** \brief start drag-and-drop operation
     *
     *  This request asks the compositor to start a drag-and-drop operation on
     *  behalf of the client.
     *
     *  The source argument is the data source that provides the data for the
     *  eventual data transfer. If source is NULL, enter, leave and motion events
     *  are sent only to the client that initiated the drag and the client is
     *  expected to handle the data passing internally.
     *
     *  The origin surface is the surface where the drag originates and the client
     *  must have an active implicit grab that matches the serial.
     *
     *  The icon surface is an optional (can be NULL) surface that provides an icon
     *  to be moved around with the cursor. Initially, the top-left corner of the
     *  icon surface is placed at the cursor hotspot, but subsequent
     *  wl_surface.attach request can move the relative position. Attach requests
     *  must be confirmed with wl_surface.commit as usual.
     *
     *  The current and pending input regions of the icon wl_surface are cleared,
     *  and wl_surface.set_input_region is ignored until the wl_surface is no longer
     *  used as the icon surface. When the use as an icon ends, the the current and
     *  pending input regions become undefined, and the wl_surface is unmapped.
     *
     *  @param source_
     *  @param origin_
     *  @param icon_
     *  @param serial_ serial of the implicit grab on the origin
     */
    void start_drag(data_source* source_, surface& origin_, surface* icon_, std::uint32_t serial_);

    /** \brief copy data to the selection
     *
     *  This request asks the compositor to set the selection to the data from the
     *  source on behalf of the client.
     *
     *  To unset the selection, set the source to NULL.
     *
     *  @param source_
     *  @param serial_ serial of the event that triggered this request
     */
    void set_selection(data_source* source_, std::uint32_t serial_);

    /** \brief introduce a new wl_data_offer
     *
     *  The data_offer event introduces a new wl_data_offer object, which will
     *  subsequently be used in either the data_device.enter event (for
     *  drag-and-drop) or the data_device.selection event (for selections).
     *  Immediately following the data_device_data_offer event, the new data_offer
     *  object will send out data_offer.offer events to describe the mime types it
     *  offers.
     *
     *  @param id_
     */
    using data_offer_handler_sig = void (data_offer&& id_);

    /** \brief Set a handler for the data_offer event
     *  @param handler Callable of signature @ref data_offer_handler_sig
     */
    template <typename T>
    void set_data_offer_handler(T&& handler) {
        _data_offer_handler = std::function<data_offer_handler_sig>(std::forward<T>(handler));
    }

    /** \brief initiate drag-and-drop session
     *
     *  This event is sent when an active drag-and-drop pointer enters a surface
     *  owned by the client. The position of the pointer at enter time is provided
     *  by the x and y arguments, in surface local coordinates.
     *
     *  @param serial_
     *  @param surface_
     *  @param x_
     *  @param y_
     *  @param id_
     */
    using enter_handler_sig = void (std::uint32_t serial_, surface& surface_, wl_fixed_t x_, wl_fixed_t y_, data_offer* id_);

    /** \brief Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** \brief end drag-and-drop session
     *
     *  This event is sent when the drag-and-drop pointer leaves the surface and the
     *  session ends. The client must destroy the wl_data_offer introduced at enter
     *  time at this point.
     */
    using leave_handler_sig = void ();

    /** \brief Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

    /** \brief drag-and-drop session motion
     *
     *  This event is sent when the drag-and-drop pointer moves within the currently
     *  focused surface. The new position of the pointer is provided by the x and y
     *  arguments, in surface local coordinates.
     *
     *  @param time_ timestamp with millisecond granularity
     *  @param x_
     *  @param y_
     */
    using motion_handler_sig = void (std::uint32_t time_, wl_fixed_t x_, wl_fixed_t y_);

    /** \brief Set a handler for the motion event
     *  @param handler Callable of signature @ref motion_handler_sig
     */
    template <typename T>
    void set_motion_handler(T&& handler) {
        _motion_handler = std::function<motion_handler_sig>(std::forward<T>(handler));
    }

    /** \brief end drag-and-drag session successfully
     *
     *  The event is sent when a drag-and-drop operation is ended because the
     *  implicit grab is removed.
     */
    using drop_handler_sig = void ();

    /** \brief Set a handler for the drop event
     *  @param handler Callable of signature @ref drop_handler_sig
     */
    template <typename T>
    void set_drop_handler(T&& handler) {
        _drop_handler = std::function<drop_handler_sig>(std::forward<T>(handler));
    }

    /** \brief advertise new selection
     *
     *  The selection event is sent out to notify the client of a new wl_data_offer
     *  for the selection for this device. The data_device.data_offer and the
     *  data_offer.offer events are sent out immediately before this event to
     *  introduce the data offer object. The selection event is sent to a client
     *  immediately before receiving keyboard focus and when a new selection is set
     *  while the client has keyboard focus. The data_offer is valid until a new
     *  data_offer or NULL is received or until the client loses keyboard focus.
     *
     *  @param id_
     */
    using selection_handler_sig = void (data_offer* id_);

    /** \brief Set a handler for the selection event
     *  @param handler Callable of signature @ref selection_handler_sig
     */
    template <typename T>
    void set_selection_handler(T&& handler) {
        _selection_handler = std::function<selection_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*data_offer_handler) (void*, wl_proxy*, wl_proxy*);
        void (*enter_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*, wl_fixed_t, wl_fixed_t, wl_proxy*);
        void (*leave_handler) (void*, wl_proxy*);
        void (*motion_handler) (void*, wl_proxy*, std::uint32_t, wl_fixed_t, wl_fixed_t);
        void (*drop_handler) (void*, wl_proxy*);
        void (*selection_handler) (void*, wl_proxy*, wl_proxy*);
    };

    static void data_offer_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_);
    static void enter_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_, wl_fixed_t x_, wl_fixed_t y_, wl_proxy* id_);
    static void leave_handler(void* data, wl_proxy* wl_obj);
    static void motion_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, wl_fixed_t x_, wl_fixed_t y_);
    static void drop_handler(void* data, wl_proxy* wl_obj);
    static void selection_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_);

    static const listener_t listener;

    std::function<data_offer_handler_sig> _data_offer_handler;
    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
    std::function<motion_handler_sig> _motion_handler;
    std::function<drop_handler_sig> _drop_handler;
    std::function<selection_handler_sig> _selection_handler;
};

} // namespace wlcpp

#endif // _DATA_DEVICE_HPP_

