
#ifndef _SURFACE_HPP_
#define _SURFACE_HPP_

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

class buffer;
class callback;
class output;
class region;

#define WLCPP_SURFACE_VERSION 3

/** \brief an onscreen surface
 *
 *  A surface is a rectangular area that is displayed on the screen. It has a
 *  location, size and pixel contents.
 *
 *  The size of a surface (and relative positions on it) is described in surface
 *  local coordinates, which may differ from the buffer local coordinates of the
 *  pixel content, in case a buffer_transform or a buffer_scale is used.
 *
 *  Surfaces are also used for some special purposes, e.g. as cursor images for
 *  pointers, drag icons, etc.
 */
class surface final
    : public proxy {
public:
    /** \brief wl_interface for @ref surface */
    static const wl_interface interface;

    /** \brief @ref surface version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** \brief Wrap existing wl_surface object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_surface object and is responsible for destryoing it
     */
    surface(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref surface from factory
     *  @param factory Object which acts as the factory
     */
    explicit surface(proxy& factory);

    /** \brief Default move constructor */
    surface(surface&& rhs) = default;

    /** \brief Destructor */
    virtual ~surface();

    /** \brief Default move assignment operator */
    surface& operator=(surface&& rhs) = default;

    /** \brief set the surface contents
     *
     *  Set a buffer as the content of this surface.
     *
     *  The new size of the surface is calculated based on the buffer size
     *  transformed by the inverse buffer_transform and the inverse buffer_scale.
     *  This means that the supplied buffer must be an integer multiple of the
     *  buffer_scale.
     *
     *  The x and y arguments specify the location of the new pending buffer's upper
     *  left corner, relative to the current buffer's upper left corner, in surface
     *  local coordinates. In other words, the x and y, combined with the new
     *  surface size define in which directions the surface's size changes.
     *
     *  Surface contents are double-buffered state, see wl_surface.commit.
     *
     *  The initial surface contents are void; there is no content.
     *  wl_surface.attach assigns the given wl_buffer as the pending wl_buffer.
     *  wl_surface.commit makes the pending wl_buffer the new surface contents, and
     *  the size of the surface becomes the size calculated from the wl_buffer, as
     *  described above. After commit, there is no pending buffer until the next
     *  attach.
     *
     *  Committing a pending wl_buffer allows the compositor to read the pixels in
     *  the wl_buffer. The compositor may access the pixels at any time after the
     *  wl_surface.commit request. When the compositor will not access the pixels
     *  anymore, it will send the wl_buffer.release event. Only after receiving
     *  wl_buffer.release, the client may re-use the wl_buffer. A wl_buffer that has
     *  been attached and then replaced by another attach instead of committed will
     *  not receive a release event, and is not used by the compositor.
     *
     *  Destroying the wl_buffer after wl_buffer.release does not change the surface
     *  contents. However, if the client destroys the wl_buffer before receiving the
     *  wl_buffer.release event, the surface contents become undefined immediately.
     *
     *  If wl_surface.attach is sent with a NULL wl_buffer, the following
     *  wl_surface.commit will remove the surface content.
     *
     *  @param buffer_
     *  @param x_
     *  @param y_
     */
    void attach(buffer* buffer_, std::int32_t x_, std::int32_t y_);

    /** \brief mark part of the surface damaged
     *
     *  This request is used to describe the regions where the pending buffer is
     *  different from the current surface contents, and where the surface therefore
     *  needs to be repainted. The pending buffer must be set by wl_surface.attach
     *  before sending damage. The compositor ignores the parts of the damage that
     *  fall outside of the surface.
     *
     *  Damage is double-buffered state, see wl_surface.commit.
     *
     *  The damage rectangle is specified in surface local coordinates.
     *
     *  The initial value for pending damage is empty: no damage. wl_surface.damage
     *  adds pending damage: the new pending damage is the union of old pending
     *  damage and the given rectangle.
     *
     *  wl_surface.commit assigns pending damage as the current damage, and clears
     *  pending damage. The server will clear the current damage as it repaints the
     *  surface.
     *
     *  @param x_
     *  @param y_
     *  @param width_
     *  @param height_
     */
    void damage(std::int32_t x_, std::int32_t y_, std::int32_t width_, std::int32_t height_);

    /** \brief request repaint feedback
     *
     *  Request notification when the next frame is displayed. Useful for throttling
     *  redrawing operations, and driving animations. The frame request will take
     *  effect on the next wl_surface.commit. The notification will only be posted
     *  for one frame unless requested again.
     *
     *  A server should avoid signalling the frame callbacks if the surface is not
     *  visible in any way, e.g. the surface is off-screen, or completely obscured
     *  by other opaque surfaces.
     *
     *  A client can request a frame callback even without an attach, damage, or any
     *  other state changes. wl_surface.commit triggers a display update, so the
     *  callback event will arrive after the next output refresh where the surface
     *  is visible.
     *
     *  The object returned by this request will be destroyed by the compositor
     *  after the callback is fired and as such the client must not attempt to use
     *  it after that point.
     *
     *  @return
     */
    callback frame();

    /** \brief set opaque region
     *
     *  This request sets the region of the surface that contains opaque content.
     *
     *  The opaque region is an optimization hint for the compositor that lets it
     *  optimize out redrawing of content behind opaque regions. Setting an opaque
     *  region is not required for correct behaviour, but marking transparent
     *  content as opaque will result in repaint artifacts.
     *
     *  The opaque region is specified in surface local coordinates.
     *
     *  The compositor ignores the parts of the opaque region that fall outside of
     *  the surface.
     *
     *  Opaque region is double-buffered state, see wl_surface.commit.
     *
     *  wl_surface.set_opaque_region changes the pending opaque region.
     *  wl_surface.commit copies the pending region to the current region.
     *  Otherwise, the pending and current regions are never changed.
     *
     *  The initial value for opaque region is empty. Setting the pending opaque
     *  region has copy semantics, and the wl_region object can be destroyed
     *  immediately. A NULL wl_region causes the pending opaque region to be set to
     *  empty.
     *
     *  @param region_
     */
    void set_opaque_region(region* region_);

    /** \brief set input region
     *
     *  This request sets the region of the surface that can receive pointer and
     *  touch events.
     *
     *  Input events happening outside of this region will try the next surface in
     *  the server surface stack. The compositor ignores the parts of the input
     *  region that fall outside of the surface.
     *
     *  The input region is specified in surface local coordinates.
     *
     *  Input region is double-buffered state, see wl_surface.commit.
     *
     *  wl_surface.set_input_region changes the pending input region.
     *  wl_surface.commit copies the pending region to the current region. Otherwise
     *  the pending and current regions are never changed, except cursor and icon
     *  surfaces are special cases, see wl_pointer.set_cursor and
     *  wl_data_device.start_drag.
     *
     *  The initial value for input region is infinite. That means the whole surface
     *  will accept input. Setting the pending input region has copy semantics, and
     *  the wl_region object can be destroyed immediately. A NULL wl_region causes
     *  the input region to be set to infinite.
     *
     *  @param region_
     */
    void set_input_region(region* region_);

    /** \brief commit pending surface state
     *
     *  Surface state (input, opaque, and damage regions, attached buffers, etc.) is
     *  double-buffered. Protocol requests modify the pending state, as opposed to
     *  current state in use by the compositor. Commit request atomically applies
     *  all pending state, replacing the current state. After commit, the new
     *  pending state is as documented for each related request.
     *
     *  On commit, a pending wl_buffer is applied first, all other state second.
     *  This means that all coordinates in double-buffered state are relative to the
     *  new wl_buffer coming into use, except for wl_surface.attach itself. If there
     *  is no pending wl_buffer, the coordinates are relative to the current surface
     *  contents.
     *
     *  All requests that need a commit to become effective are documented to affect
     *  double-buffered state.
     *
     *  Other interfaces may add further double-buffered surface state.
     */
    void commit();

    /** \brief sets the buffer transformation
     *
     *  This request sets an optional transformation on how the compositor
     *  interprets the contents of the buffer attached to the surface. The accepted
     *  values for the transform parameter are the values for wl_output.transform.
     *
     *  Buffer transform is double-buffered state, see wl_surface.commit.
     *
     *  A newly created surface has its buffer transformation set to normal.
     *
     *  The purpose of this request is to allow clients to render content according
     *  to the output transform, thus permiting the compositor to use certain
     *  optimizations even if the display is rotated. Using hardware overlays and
     *  scanning out a client buffer for fullscreen surfaces are examples of such
     *  optimizations. Those optimizations are highly dependent on the compositor
     *  implementation, so the use of this request should be considered on a
     *  case-by-case basis.
     *
     *  Note that if the transform value includes 90 or 270 degree rotation, the
     *  width of the buffer will become the surface height and the height of the
     *  buffer will become the surface width.
     *
     *  @param transform_
     */
    void set_buffer_transform(std::int32_t transform_);

    /** \brief sets the buffer scaling factor
     *
     *  This request sets an optional scaling factor on how the compositor
     *  interprets the contents of the buffer attached to the window.
     *
     *  Buffer scale is double-buffered state, see wl_surface.commit.
     *
     *  A newly created surface has its buffer scale set to 1.
     *
     *  The purpose of this request is to allow clients to supply higher resolution
     *  buffer data for use on high resolution outputs. Its intended that you pick
     *  the same	buffer scale as the scale of the output that the surface is
     *  displayed on.This means the compositor can avoid scaling when rendering the
     *  surface on that output.
     *
     *  Note that if the scale is larger than 1, then you have to attach a buffer
     *  that is larger (by a factor of scale in each dimension) than the desired
     *  surface size.
     *
     *  @param scale_
     */
    void set_buffer_scale(std::int32_t scale_);

    /** \brief surface enters an output
     *
     *  This is emitted whenever a surface's creation, movement, or resizing results
     *  in some part of it being within the scanout region of an output.
     *
     *  Note that a surface may be overlapping with zero or more outputs.
     *
     *  @param output_
     */
    using enter_handler_sig = void (output& output_);

    /** \brief Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** \brief surface leaves an output
     *
     *  This is emitted whenever a surface's creation, movement, or resizing results
     *  in it no longer having any part of it within the scanout region of an
     *  output.
     *
     *  @param output_
     */
    using leave_handler_sig = void (output& output_);

    /** \brief Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*enter_handler) (void*, wl_proxy*, wl_proxy*);
        void (*leave_handler) (void*, wl_proxy*, wl_proxy*);
    };

    static void enter_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_);
    static void leave_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_);

    static const listener_t listener;

    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
};

} // namespace wlcpp

#endif // _SURFACE_HPP_

