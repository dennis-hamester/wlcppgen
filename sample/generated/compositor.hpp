
#ifndef _COMPOSITOR_HPP_
#define _COMPOSITOR_HPP_

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

class region;
class surface;

#define WLCPP_COMPOSITOR_VERSION 3

/** \brief the compositor singleton
 *
 *  A compositor. This object is a singleton global. The compositor is in charge
 *  of combining the contents of multiple surfaces into one displayable output.
 */
class compositor final
    : public proxy {
public:
    /** \brief wl_interface for @ref compositor */
    static const wl_interface interface;

    /** \brief @ref compositor version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** \brief Wrap existing wl_compositor object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_compositor object and is responsible for destryoing it
     */
    compositor(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref compositor from factory
     *  @param factory Object which acts as the factory
     */
    explicit compositor(proxy& factory);

    /** \brief Default move constructor */
    compositor(compositor&& rhs) = default;

    /** \brief Default destructor */
    virtual ~compositor() = default;

    /** \brief Default move assignment operator */
    compositor& operator=(compositor&& rhs) = default;

    /** \brief create new surface
     *
     *  Ask the compositor to create a new surface.
     *
     *  @return
     */
    surface create_surface();

    /** \brief create new region
     *
     *  Ask the compositor to create a new region.
     *
     *  @return
     */
    region create_region();
};

} // namespace wlcpp

#endif // _COMPOSITOR_HPP_

