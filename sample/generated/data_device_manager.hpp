
#ifndef _DATA_DEVICE_MANAGER_HPP_
#define _DATA_DEVICE_MANAGER_HPP_

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

class data_device;
class data_source;
class seat;

#define WLCPP_DATA_DEVICE_MANAGER_VERSION 1

/** \brief data transfer interface
 *
 *  The wl_data_device_manager is a singleton global object that provides access
 *  to inter-client data transfer mechanisms such as copy-and-paste and
 *  drag-and-drop. These mechanisms are tied to a wl_seat and this interface
 *  lets a client get a wl_data_device corresponding to a wl_seat.
 */
class data_device_manager final
    : public proxy {
public:
    /** \brief wl_interface for @ref data_device_manager */
    static const wl_interface interface;

    /** \brief @ref data_device_manager version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_data_device_manager object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_data_device_manager object and is responsible for destryoing it
     */
    data_device_manager(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref data_device_manager from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_device_manager(proxy& factory);

    /** \brief Default move constructor */
    data_device_manager(data_device_manager&& rhs) = default;

    /** \brief Default destructor */
    virtual ~data_device_manager() = default;

    /** \brief Default move assignment operator */
    data_device_manager& operator=(data_device_manager&& rhs) = default;

    /** \brief create a new data source
     *
     *  Create a new data source.
     *
     *  @return
     */
    data_source create_data_source();

    /** \brief create a new data device
     *
     *  Create a new data device for a given seat.
     *
     *  @param seat_
     *  @return
     */
    data_device get_data_device(seat& seat_);
};

} // namespace wlcpp

#endif // _DATA_DEVICE_MANAGER_HPP_

