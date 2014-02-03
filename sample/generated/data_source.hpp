
#ifndef _DATA_SOURCE_HPP_
#define _DATA_SOURCE_HPP_

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


#define WLCPP_DATA_SOURCE_VERSION 1

/** \brief offer to transfer data
 *
 *  The wl_data_source object is the source side of a wl_data_offer. It is
 *  created by the source client in a data transfer and provides a way to
 *  describe the offered data and a way to respond to requests to transfer the
 *  data.
 */
class data_source final
    : public proxy {
public:
    /** \brief wl_interface for @ref data_source */
    static const wl_interface interface;

    /** \brief @ref data_source version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_data_source object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_data_source object and is responsible for destryoing it
     */
    data_source(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref data_source from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_source(proxy& factory);

    /** \brief Default move constructor */
    data_source(data_source&& rhs) = default;

    /** \brief Destructor */
    virtual ~data_source();

    /** \brief Default move assignment operator */
    data_source& operator=(data_source&& rhs) = default;

    /** \brief add an offered mime type
     *
     *  This request adds a mime type to the set of mime types advertised to
     *  targets. Can be called several times to offer multiple types.
     *
     *  @param mime_type_
     */
    void offer(const std::string& mime_type_);

    /** \brief a target accepts an offered mime type
     *
     *  Sent when a target accepts pointer_focus or motion events. If a target does
     *  not accept any of the offered types, type is NULL.
     *
     *  Used for feedback during drag-and-drop.
     *
     *  @param mime_type_
     */
    using target_handler_sig = void (const std::string* mime_type_);

    /** \brief Set a handler for the target event
     *  @param handler Callable of signature @ref target_handler_sig
     */
    template <typename T>
    void set_target_handler(T&& handler) {
        _target_handler = std::function<target_handler_sig>(std::forward<T>(handler));
    }

    /** \brief send the data
     *
     *  Request for data from the client. Send the data as the specified mime type
     *  over the passed file descriptor, then close it.
     *
     *  @param mime_type_
     *  @param fd_
     */
    using send_handler_sig = void (const std::string& mime_type_, std::int32_t fd_);

    /** \brief Set a handler for the send event
     *  @param handler Callable of signature @ref send_handler_sig
     */
    template <typename T>
    void set_send_handler(T&& handler) {
        _send_handler = std::function<send_handler_sig>(std::forward<T>(handler));
    }

    /** \brief selection was cancelled
     *
     *  This data source has been replaced by another data source. The client should
     *  clean up and destroy this data source.
     */
    using cancelled_handler_sig = void ();

    /** \brief Set a handler for the cancelled event
     *  @param handler Callable of signature @ref cancelled_handler_sig
     */
    template <typename T>
    void set_cancelled_handler(T&& handler) {
        _cancelled_handler = std::function<cancelled_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*target_handler) (void*, wl_proxy*, const char*);
        void (*send_handler) (void*, wl_proxy*, const char*, std::int32_t);
        void (*cancelled_handler) (void*, wl_proxy*);
    };

    static void target_handler(void* data, wl_proxy* wl_obj, const char* mime_type_);
    static void send_handler(void* data, wl_proxy* wl_obj, const char* mime_type_, std::int32_t fd_);
    static void cancelled_handler(void* data, wl_proxy* wl_obj);

    static const listener_t listener;

    std::function<target_handler_sig> _target_handler;
    std::function<send_handler_sig> _send_handler;
    std::function<cancelled_handler_sig> _cancelled_handler;
};

} // namespace wlcpp

#endif // _DATA_SOURCE_HPP_

