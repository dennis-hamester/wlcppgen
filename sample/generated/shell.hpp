
#ifndef _SHELL_HPP_
#define _SHELL_HPP_

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

class shell_surface;
class surface;

#define WLCPP_SHELL_VERSION 1

/** \brief create desktop-style surfaces
 *
 *  This interface is implemented by servers that provide desktop-style user
 *  interfaces.
 *
 *  It allows clients to associate a wl_shell_surface with a basic surface.
 */
class shell final
    : public proxy {
public:
    /** \brief wl_interface for @ref shell */
    static const wl_interface interface;

    /** \brief @ref shell version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_shell object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_shell object and is responsible for destryoing it
     */
    shell(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref shell from factory
     *  @param factory Object which acts as the factory
     */
    explicit shell(proxy& factory);

    /** \brief Default move constructor */
    shell(shell&& rhs) = default;

    /** \brief Default destructor */
    virtual ~shell() = default;

    /** \brief Default move assignment operator */
    shell& operator=(shell&& rhs) = default;

    /** \brief create a shell surface from a surface
     *
     *  Create a shell surface for an existing surface.
     *
     *  Only one shell surface can be associated with a given surface.
     *
     *  @param surface_
     *  @return
     */
    shell_surface get_shell_surface(surface& surface_);
};

} // namespace wlcpp

#endif // _SHELL_HPP_

