
#ifndef _CALLBACK_HPP_
#define _CALLBACK_HPP_

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


#define WLCPP_CALLBACK_VERSION 1

/** \brief callback object
 *
 *  Clients can handle the 'done' event to get notified when the related request
 *  is done.
 */
class callback final
    : public proxy {
public:
    /** \brief wl_interface for @ref callback */
    static const wl_interface interface;

    /** \brief @ref callback version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_callback object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_callback object and is responsible for destryoing it
     */
    callback(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref callback from factory
     *  @param factory Object which acts as the factory
     */
    explicit callback(proxy& factory);

    /** \brief Default move constructor */
    callback(callback&& rhs) = default;

    /** \brief Default destructor */
    virtual ~callback() = default;

    /** \brief Default move assignment operator */
    callback& operator=(callback&& rhs) = default;

    /** \brief done event
     *
     *  Notify the client when the related request is done.
     *
     *  @param serial_ serial of the event
     */
    using done_handler_sig = void (std::uint32_t serial_);

    /** \brief Set a handler for the done event
     *  @param handler Callable of signature @ref done_handler_sig
     */
    template <typename T>
    void set_done_handler(T&& handler) {
        _done_handler = std::function<done_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*done_handler) (void*, wl_proxy*, std::uint32_t);
    };

    static void done_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_);

    static const listener_t listener;

    std::function<done_handler_sig> _done_handler;
};

} // namespace wlcpp

#endif // _CALLBACK_HPP_

