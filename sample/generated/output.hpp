
#ifndef _OUTPUT_HPP_
#define _OUTPUT_HPP_

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


#define WLCPP_OUTPUT_VERSION 2

/** \brief subpixel geometry information
 *
 *  This enumeration describes how the physical pixels on an output are layed
 *  out.
 */
enum output_subpixel {
    OUTPUT_SUBPIXEL_UNKNOWN = 0,
    OUTPUT_SUBPIXEL_NONE = 1,
    OUTPUT_SUBPIXEL_HORIZONTAL_RGB = 2,
    OUTPUT_SUBPIXEL_HORIZONTAL_BGR = 3,
    OUTPUT_SUBPIXEL_VERTICAL_RGB = 4,
    OUTPUT_SUBPIXEL_VERTICAL_BGR = 5,
};

/** \brief transform from framebuffer to output
 *
 *  This describes the transform that a compositor will apply to a surface to
 *  compensate for the rotation or mirroring of an output device.
 *
 *  The flipped values correspond to an initial flip around a vertical axis
 *  followed by rotation.
 *
 *  The purpose is mainly to allow clients render accordingly and tell the
 *  compositor, so that for fullscreen surfaces, the compositor will still be
 *  able to scan out directly from client surfaces.
 */
enum output_transform {
    OUTPUT_TRANSFORM_NORMAL = 0,
    OUTPUT_TRANSFORM_90 = 1,
    OUTPUT_TRANSFORM_180 = 2,
    OUTPUT_TRANSFORM_270 = 3,
    OUTPUT_TRANSFORM_FLIPPED = 4,
    OUTPUT_TRANSFORM_FLIPPED_90 = 5,
    OUTPUT_TRANSFORM_FLIPPED_180 = 6,
    OUTPUT_TRANSFORM_FLIPPED_270 = 7,
};

/** \brief mode information
 *
 *  These flags describe properties of an output mode. They are used in the
 *  flags bitfield of the mode event.
 */
enum output_mode {
    OUTPUT_MODE_CURRENT = 0x1, /**< indicates this is the current mode */
    OUTPUT_MODE_PREFERRED = 0x2, /**< indicates this is the preferred mode */
};

/** \brief compositor output region
 *
 *  An output describes part of the compositor geometry. The compositor works in
 *  the 'compositor coordinate system' and an output corresponds to rectangular
 *  area in that space that is actually visible. This typically corresponds to a
 *  monitor that displays part of the compositor space. This object is published
 *  as global during start up, or when a monitor is hotplugged.
 */
class output final
    : public proxy {
public:
    /** \brief wl_interface for @ref output */
    static const wl_interface interface;

    /** \brief @ref output version at wrapper generation time */
    static constexpr std::uint32_t version = 2;

    /** \brief Wrap existing wl_output object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_output object and is responsible for destryoing it
     */
    output(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref output from factory
     *  @param factory Object which acts as the factory
     */
    explicit output(proxy& factory);

    /** \brief Default move constructor */
    output(output&& rhs) = default;

    /** \brief Default destructor */
    virtual ~output() = default;

    /** \brief Default move assignment operator */
    output& operator=(output&& rhs) = default;

    /** \brief properties of the output
     *
     *  The geometry event describes geometric properties of the output. The event
     *  is sent when binding to the output object and whenever any of the properties
     *  change.
     *
     *  @param x_ x position within the global compositor space
     *  @param y_ y position within the global compositor space
     *  @param physical_width_ width in millimeters of the output
     *  @param physical_height_ height in millimeters of the output
     *  @param subpixel_ subpixel orientation of the output
     *  @param make_ textual description of the manufacturer
     *  @param model_ textual description of the model
     *  @param transform_ transform that maps framebuffer to output
     */
    using geometry_handler_sig = void (std::int32_t x_, std::int32_t y_, std::int32_t physical_width_, std::int32_t physical_height_, std::int32_t subpixel_, const std::string& make_, const std::string& model_, std::int32_t transform_);

    /** \brief Set a handler for the geometry event
     *  @param handler Callable of signature @ref geometry_handler_sig
     */
    template <typename T>
    void set_geometry_handler(T&& handler) {
        _geometry_handler = std::function<geometry_handler_sig>(std::forward<T>(handler));
    }

    /** \brief advertise available modes for the output
     *
     *  The mode event describes an available mode for the output.
     *
     *  The event is sent when binding to the output object and there will always be
     *  one mode, the current mode. The event is sent again if an output changes
     *  mode, for the mode that is now current. In other words, the current mode is
     *  always the last mode that was received with the current flag set.
     *
     *  The size of a mode is given in physical hardware units of the output device.
     *  This is not necessarily the same as the output size in the global compositor
     *  space. For instance, the output may be scaled, as described in
     *  wl_output.scale, or transformed , as described in wl_output.transform.
     *
     *  @param flags_ bitfield of mode flags
     *  @param width_ width of the mode in hardware units
     *  @param height_ height of the mode in hardware units
     *  @param refresh_ vertical refresh rate in mHz
     */
    using mode_handler_sig = void (std::uint32_t flags_, std::int32_t width_, std::int32_t height_, std::int32_t refresh_);

    /** \brief Set a handler for the mode event
     *  @param handler Callable of signature @ref mode_handler_sig
     */
    template <typename T>
    void set_mode_handler(T&& handler) {
        _mode_handler = std::function<mode_handler_sig>(std::forward<T>(handler));
    }

    /** \brief sent all information about output
     *
     *  This event is sent after all other properties has been sent after binding to
     *  the output object and after any other property changes done after that. This
     *  allows changes to the output properties to be seen as atomic, even if they
     *  happen via multiple events.
     */
    using done_handler_sig = void ();

    /** \brief Set a handler for the done event
     *  @param handler Callable of signature @ref done_handler_sig
     */
    template <typename T>
    void set_done_handler(T&& handler) {
        _done_handler = std::function<done_handler_sig>(std::forward<T>(handler));
    }

    /** \brief output scaling properties
     *
     *  This event contains scaling geometry information that is not in the geometry
     *  event. It may be sent after binding the output object or if the output scale
     *  changes later. If it is not sent, the client should assume a scale of 1.
     *
     *  A scale larger than 1 means that the compositor will automatically scale
     *  surface buffers by this amount when rendering. This is used for very high
     *  resolution displays where applications rendering at the native resolution
     *  would be too small to be legible.
     *
     *  It is intended that scaling aware clients track the current output of a
     *  surface, and if it is on a scaled output it should use
     *  wl_surface.set_buffer_scale with the scale of the output. That way the
     *  compositor can avoid scaling the surface, and the client can supply a higher
     *  detail image.
     *
     *  @param factor_ scaling factor of output
     */
    using scale_handler_sig = void (std::int32_t factor_);

    /** \brief Set a handler for the scale event
     *  @param handler Callable of signature @ref scale_handler_sig
     */
    template <typename T>
    void set_scale_handler(T&& handler) {
        _scale_handler = std::function<scale_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*geometry_handler) (void*, wl_proxy*, std::int32_t, std::int32_t, std::int32_t, std::int32_t, std::int32_t, const char*, const char*, std::int32_t);
        void (*mode_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, std::int32_t, std::int32_t);
        void (*done_handler) (void*, wl_proxy*);
        void (*scale_handler) (void*, wl_proxy*, std::int32_t);
    };

    static void geometry_handler(void* data, wl_proxy* wl_obj, std::int32_t x_, std::int32_t y_, std::int32_t physical_width_, std::int32_t physical_height_, std::int32_t subpixel_, const char* make_, const char* model_, std::int32_t transform_);
    static void mode_handler(void* data, wl_proxy* wl_obj, std::uint32_t flags_, std::int32_t width_, std::int32_t height_, std::int32_t refresh_);
    static void done_handler(void* data, wl_proxy* wl_obj);
    static void scale_handler(void* data, wl_proxy* wl_obj, std::int32_t factor_);

    static const listener_t listener;

    std::function<geometry_handler_sig> _geometry_handler;
    std::function<mode_handler_sig> _mode_handler;
    std::function<done_handler_sig> _done_handler;
    std::function<scale_handler_sig> _scale_handler;
};

} // namespace wlcpp

#endif // _OUTPUT_HPP_

