
#ifndef _REGION_HPP_
#define _REGION_HPP_

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


#define WLCPP_REGION_VERSION 1

/** \brief region interface
 *
 *  A region object describes an area.
 *
 *  Region objects are used to describe the opaque and input regions of a
 *  surface.
 */
class region final
    : public proxy {
public:
    /** \brief wl_interface for @ref region */
    static const wl_interface interface;

    /** \brief @ref region version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_region object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    region(wl_proxy* obj = nullptr);

    /** \brief Create new @ref region from factory
     *  @param factory Object which acts as the factory
     */
    explicit region(proxy& factory);

    /** \brief Default move constructor */
    region(region&& rhs) = default;

    /** \brief Destructor */
    virtual ~region();

    /** \brief Default move assignment operator */
    region& operator=(region&& rhs) = default;

    /** \brief add rectangle to region
     *
     *  Add the specified rectangle to the region.
     *
     *  @param x_
     *  @param y_
     *  @param width_
     *  @param height_
     */
    void add(std::int32_t x_, std::int32_t y_, std::int32_t width_, std::int32_t height_);

    /** \brief subtract rectangle from region
     *
     *  Subtract the specified rectangle from the region.
     *
     *  @param x_
     *  @param y_
     *  @param width_
     *  @param height_
     */
    void subtract(std::int32_t x_, std::int32_t y_, std::int32_t width_, std::int32_t height_);

protected:
    void destroy() override;
};

} // namespace wlcpp

#endif // _REGION_HPP_

