
#ifndef _SHELL_SURFACE_HPP_
#define _SHELL_SURFACE_HPP_

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

class output;
class seat;
class surface;

#define WLCPP_SHELL_SURFACE_VERSION 1

/** \brief edge values for resizing
 *
 *  These values are used to indicate which edge of a surface is being dragged
 *  in a resize operation. The server may use this information to adapt its
 *  behavior, e.g. choose an appropriate cursor image.
 */
enum shell_surface_resize {
    SHELL_SURFACE_RESIZE_NONE = 0,
    SHELL_SURFACE_RESIZE_TOP = 1,
    SHELL_SURFACE_RESIZE_BOTTOM = 2,
    SHELL_SURFACE_RESIZE_LEFT = 4,
    SHELL_SURFACE_RESIZE_TOP_LEFT = 5,
    SHELL_SURFACE_RESIZE_BOTTOM_LEFT = 6,
    SHELL_SURFACE_RESIZE_RIGHT = 8,
    SHELL_SURFACE_RESIZE_TOP_RIGHT = 9,
    SHELL_SURFACE_RESIZE_BOTTOM_RIGHT = 10,
};

/** \brief details of transient behaviour
 *
 *  These flags specify details of the expected behaviour of transient surfaces.
 *  Used in the set_transient request.
 */
enum shell_surface_transient {
    SHELL_SURFACE_TRANSIENT_INACTIVE = 0x1, /**< do not set keyboard focus */
};

/** \brief different method to set the surface fullscreen
 *
 *  Hints to indicate to the compositor how to deal with a conflict between the
 *  dimensions of the surface and the dimensions of the output. The compositor
 *  is free to ignore this parameter.
 */
enum shell_surface_fullscreen_method {
    SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT = 0, /**< no preference, apply default policy */
    SHELL_SURFACE_FULLSCREEN_METHOD_SCALE = 1, /**< scale, preserve the surface's aspect ratio and center on output */
    SHELL_SURFACE_FULLSCREEN_METHOD_DRIVER = 2, /**< switch output mode to the smallest mode that can fit the surface, add black borders to compensate size mismatch */
    SHELL_SURFACE_FULLSCREEN_METHOD_FILL = 3, /**< no upscaling, center on output and add black borders to compensate size mismatch */
};

/** \brief desktop-style metadata interface
 *
 *  An interface that may be implemented by a wl_surface, for implementations
 *  that provide a desktop-style user interface.
 *
 *  It provides requests to treat surfaces like toplevel, fullscreen or popup
 *  windows, move, resize or maximize them, associate metadata like title and
 *  class, etc.
 *
 *  On the server side the object is automatically destroyed when the related
 *  wl_surface is destroyed. On client side, wl_shell_surface_destroy() must be
 *  called before destroying the wl_surface object.
 */
class shell_surface final
    : public proxy {
public:
    /** \brief wl_interface for @ref shell_surface */
    static const wl_interface interface;

    /** \brief @ref shell_surface version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_shell_surface object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_shell_surface object and is responsible for destryoing it
     */
    shell_surface(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref shell_surface from factory
     *  @param factory Object which acts as the factory
     */
    explicit shell_surface(proxy& factory);

    /** \brief Default move constructor */
    shell_surface(shell_surface&& rhs) = default;

    /** \brief Default destructor */
    virtual ~shell_surface() = default;

    /** \brief Default move assignment operator */
    shell_surface& operator=(shell_surface&& rhs) = default;

    /** \brief respond to a ping event
     *
     *  A client must respond to a ping event with a pong request or the client may
     *  be deemed unresponsive.
     *
     *  @param serial_ serial of the ping event
     */
    void pong(std::uint32_t serial_);

    /** \brief start an interactive move
     *
     *  Start a pointer-driven move of the surface.
     *
     *  This request must be used in response to a button press event. The server
     *  may ignore move requests depending on the state of the surface (e.g.
     *  fullscreen or maximized).
     *
     *  @param seat_ the wl_seat whose pointer is used
     *  @param serial_ serial of the implicit grab on the pointer
     */
    void move(seat& seat_, std::uint32_t serial_);

    /** \brief start an interactive resize
     *
     *  Start a pointer-driven resizing of the surface.
     *
     *  This request must be used in response to a button press event. The server
     *  may ignore resize requests depending on the state of the surface (e.g.
     *  fullscreen or maximized).
     *
     *  @param seat_ the wl_seat whose pointer is used
     *  @param serial_ serial of the implicit grab on the pointer
     *  @param edges_ which edge or corner is being dragged
     */
    void resize(seat& seat_, std::uint32_t serial_, std::uint32_t edges_);

    /** \brief make the surface a toplevel surface
     *
     *  Map the surface as a toplevel surface.
     *
     *  A toplevel surface is not fullscreen, maximized or transient.
     */
    void set_toplevel();

    /** \brief make the surface a transient surface
     *
     *  Map the surface relative to an existing surface.
     *
     *  The x and y arguments specify the locations of the upper left corner of the
     *  surface relative to the upper left corner of the parent surface, in surface
     *  local coordinates.
     *
     *  The flags argument controls details of the transient behaviour.
     *
     *  @param parent_
     *  @param x_
     *  @param y_
     *  @param flags_
     */
    void set_transient(surface& parent_, std::int32_t x_, std::int32_t y_, std::uint32_t flags_);

    /** \brief make the surface a fullscreen surface
     *
     *  Map the surface as a fullscreen surface.
     *
     *  If an output parameter is given then the surface will be made fullscreen on
     *  that output. If the client does not specify the output then the compositor
     *  will apply its policy - usually choosing the output on which the surface has
     *  the biggest surface area.
     *
     *  The client may specify a method to resolve a size conflict between the
     *  output size and the surface size - this is provided through the method
     *  parameter.
     *
     *  The framerate parameter is used only when the method is set to "driver", to
     *  indicate the preferred framerate. A value of 0 indicates that the app does
     *  not care about framerate. The framerate is specified in mHz, that is
     *  framerate of 60000 is 60Hz.
     *
     *  A method of "scale" or "driver" implies a scaling operation of the surface,
     *  either via a direct scaling operation or a change of the output mode. This
     *  will override any kind of output scaling, so that mapping a surface with a
     *  buffer size equal to the mode can fill the screen independent of
     *  buffer_scale.
     *
     *  A method of "fill" means we don't scale up the buffer, however any output
     *  scale is applied. This means that you may run into an edge case where the
     *  application maps a buffer with the same size of the output mode but
     *  buffer_scale 1 (thus making a surface larger than the output). In this case
     *  it is allowed to downscale the results to fit the screen.
     *
     *  The compositor must reply to this request with a configure event with the
     *  dimensions for the output on which the surface will be made fullscreen.
     *
     *  @param method_
     *  @param framerate_
     *  @param output_
     */
    void set_fullscreen(std::uint32_t method_, std::uint32_t framerate_, output* output_);

    /** \brief make the surface a popup surface
     *
     *  Map the surface as a popup.
     *
     *  A popup surface is a transient surface with an added pointer grab.
     *
     *  An existing implicit grab will be changed to owner-events mode, and the
     *  popup grab will continue after the implicit grab ends (i.e. releasing the
     *  mouse button does not cause the popup to be unmapped).
     *
     *  The popup grab continues until the window is destroyed or a mouse button is
     *  pressed in any other clients window. A click in any of the clients surfaces
     *  is reported as normal, however, clicks in other clients surfaces will be
     *  discarded and trigger the callback.
     *
     *  The x and y arguments specify the locations of the upper left corner of the
     *  surface relative to the upper left corner of the parent surface, in surface
     *  local coordinates.
     *
     *  @param seat_ the wl_seat whose pointer is used
     *  @param serial_ serial of the implicit grab on the pointer
     *  @param parent_
     *  @param x_
     *  @param y_
     *  @param flags_
     */
    void set_popup(seat& seat_, std::uint32_t serial_, surface& parent_, std::int32_t x_, std::int32_t y_, std::uint32_t flags_);

    /** \brief make the surface a maximized surface
     *
     *  Map the surface as a maximized surface.
     *
     *  If an output parameter is given then the surface will be maximized on that
     *  output. If the client does not specify the output then the compositor will
     *  apply its policy - usually choosing the output on which the surface has the
     *  biggest surface area.
     *
     *  The compositor will reply with a configure event telling the expected new
     *  surface size. The operation is completed on the next buffer attach to this
     *  surface.
     *
     *  A maximized surface typically fills the entire output it is bound to, except
     *  for desktop element such as panels. This is the main difference between a
     *  maximized shell surface and a fullscreen shell surface.
     *
     *  The details depend on the compositor implementation.
     *
     *  @param output_
     */
    void set_maximized(output* output_);

    /** \brief set surface title
     *
     *  Set a short title for the surface.
     *
     *  This string may be used to identify the surface in a task bar, window list,
     *  or other user interface elements provided by the compositor.
     *
     *  The string must be encoded in UTF-8.
     *
     *  @param title_
     */
    void set_title(const std::string& title_);

    /** \brief set surface class
     *
     *  Set a class for the surface.
     *
     *  The surface class identifies the general class of applications to which the
     *  surface belongs. A common convention is to use the file name (or the full
     *  path if it is a non-standard location) of the application's .desktop file as
     *  the class.
     *
     *  @param class__
     */
    void set_class(const std::string& class__);

    /** \brief ping client
     *
     *  Ping a client to check if it is receiving events and sending requests. A
     *  client is expected to reply with a pong request.
     *
     *  @param serial_
     */
    using ping_handler_sig = void (std::uint32_t serial_);

    /** \brief Set a handler for the ping event
     *  @param handler Callable of signature @ref ping_handler_sig
     */
    template <typename T>
    void set_ping_handler(T&& handler) {
        _ping_handler = std::function<ping_handler_sig>(std::forward<T>(handler));
    }

    /** \brief suggest resize
     *
     *  The configure event asks the client to resize its surface.
     *
     *  The size is a hint, in the sense that the client is free to ignore it if it
     *  doesn't resize, pick a smaller size (to satisfy aspect ratio or resize in
     *  steps of NxM pixels).
     *
     *  The edges parameter provides a hint about how the surface was resized. The
     *  client may use this information to decide how to adjust its content to the
     *  new size (e.g. a scrolling area might adjust its content position to leave
     *  the viewable content unmoved).
     *
     *  The client is free to dismiss all but the last configure event it received.
     *
     *  The width and height arguments specify the size of the window in surface
     *  local coordinates.
     *
     *  @param edges_
     *  @param width_
     *  @param height_
     */
    using configure_handler_sig = void (std::uint32_t edges_, std::int32_t width_, std::int32_t height_);

    /** \brief Set a handler for the configure event
     *  @param handler Callable of signature @ref configure_handler_sig
     */
    template <typename T>
    void set_configure_handler(T&& handler) {
        _configure_handler = std::function<configure_handler_sig>(std::forward<T>(handler));
    }

    /** \brief popup interaction is done
     *
     *  The popup_done event is sent out when a popup grab is broken, that is, when
     *  the user clicks a surface that doesn't belong to the client owning the popup
     *  surface.
     */
    using popup_done_handler_sig = void ();

    /** \brief Set a handler for the popup_done event
     *  @param handler Callable of signature @ref popup_done_handler_sig
     */
    template <typename T>
    void set_popup_done_handler(T&& handler) {
        _popup_done_handler = std::function<popup_done_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*ping_handler) (void*, wl_proxy*, std::uint32_t);
        void (*configure_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, std::int32_t);
        void (*popup_done_handler) (void*, wl_proxy*);
    };

    static void ping_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_);
    static void configure_handler(void* data, wl_proxy* wl_obj, std::uint32_t edges_, std::int32_t width_, std::int32_t height_);
    static void popup_done_handler(void* data, wl_proxy* wl_obj);

    static const listener_t listener;

    std::function<ping_handler_sig> _ping_handler;
    std::function<configure_handler_sig> _configure_handler;
    std::function<popup_done_handler_sig> _popup_done_handler;
};

} // namespace wlcpp

#endif // _SHELL_SURFACE_HPP_

