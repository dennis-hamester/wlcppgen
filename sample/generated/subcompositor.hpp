
#ifndef _SUBCOMPOSITOR_HPP_
#define _SUBCOMPOSITOR_HPP_

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

class subsurface;
class surface;

#define WLCPP_SUBCOMPOSITOR_VERSION 1

/**
 */
enum subcompositor_error {
    SUBCOMPOSITOR_ERROR_BAD_SURFACE = 0, /**< the to-be sub-surface is invalid */
};

/** \brief sub-surface compositing
 *
 *  The global interface exposing sub-surface compositing capabilities. A
 *  wl_surface, that has sub-surfaces associated, is called the parent surface.
 *  Sub-surfaces can be arbitrarily nested and create a tree of sub-surfaces.
 *
 *  The root surface in a tree of sub-surfaces is the main surface. The main
 *  surface cannot be a sub-surface, because sub-surfaces must always have a
 *  parent.
 *
 *  A main surface with its sub-surfaces forms a (compound) window. For window
 *  management purposes, this set of wl_surface objects is to be considered as a
 *  single window, and it should also behave as such.
 *
 *  The aim of sub-surfaces is to offload some of the compositing work within a
 *  window from clients to the compositor. A prime example is a video player
 *  with decorations and video in separate wl_surface objects. This should allow
 *  the compositor to pass YUV video buffer processing to dedicated overlay
 *  hardware when possible.
 */
class subcompositor final
    : public proxy {
public:
    /** \brief wl_interface for @ref subcompositor */
    static const wl_interface interface;

    /** \brief @ref subcompositor version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_subcompositor object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_subcompositor object and is responsible for destryoing it
     */
    subcompositor(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref subcompositor from factory
     *  @param factory Object which acts as the factory
     */
    explicit subcompositor(proxy& factory);

    /** \brief Default move constructor */
    subcompositor(subcompositor&& rhs) = default;

    /** \brief Destructor */
    virtual ~subcompositor();

    /** \brief Default move assignment operator */
    subcompositor& operator=(subcompositor&& rhs) = default;

    /** \brief give a surface the role sub-surface
     *
     *  Create a sub-surface interface for the given surface, and associate it with
     *  the given parent surface. This turns a plain wl_surface into a sub-surface.
     *
     *  The to-be sub-surface must not already have a dedicated purpose, like any
     *  shell surface type, cursor image, drag icon, or sub-surface. Otherwise a
     *  protocol error is raised.
     *
     *  @param surface_ the surface to be turned into a sub-surface
     *  @param parent_ the parent surface
     *  @return the new subsurface object id
     */
    subsurface get_subsurface(surface& surface_, surface& parent_);

protected:
    void destroy() override;
};

} // namespace wlcpp

#endif // _SUBCOMPOSITOR_HPP_

