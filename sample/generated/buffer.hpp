
#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

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


#define WLCPP_BUFFER_VERSION 1

/** \brief content for a wl_surface
 *
 *  A buffer provides the content for a wl_surface. Buffers are created through
 *  factory interfaces such as wl_drm, wl_shm or similar. It has a width and a
 *  height and can be attached to a wl_surface, but the mechanism by which a
 *  client provides and updates the contents is defined by the buffer factory
 *  interface.
 */
class buffer final
    : public proxy {
public:
    /** \brief wl_interface for @ref buffer */
    static const wl_interface interface;

    /** \brief @ref buffer version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_buffer object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    buffer(wl_proxy* obj = nullptr);

    /** \brief Create new @ref buffer from factory
     *  @param factory Object which acts as the factory
     */
    explicit buffer(proxy& factory);

    /** \brief Default move constructor */
    buffer(buffer&& rhs) = default;

    /** \brief Destructor */
    virtual ~buffer();

    /** \brief Default move assignment operator */
    buffer& operator=(buffer&& rhs) = default;

    /** \brief compositor releases buffer
     *
     *  Sent when this wl_buffer is no longer used by the compositor. The client is
     *  now free to re-use or destroy this buffer and its backing storage.
     *
     *  If a client receives a release event before the frame callback requested in
     *  the same wl_surface.commit that attaches this wl_buffer to a surface, then
     *  the client is immediately free to re-use the buffer and its backing storage,
     *  and does not need a second buffer for the next surface content update.
     *  Typically this is possible, when the compositor maintains a copy of the
     *  wl_surface contents, e.g. as a GL texture. This is an important optimization
     *  for GL(ES) compositors with wl_shm clients.
     */
    using release_handler_sig = void ();

    /** \brief Set a handler for the release event
     *  @param handler Callable of signature @ref release_handler_sig
     */
    template <typename T>
    void set_release_handler(T&& handler) {
        _release_handler = std::function<release_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*release_handler) (void*, wl_proxy*);
    };

    static void release_handler(void* data, wl_proxy* wl_obj);

    static const listener_t listener;

    std::function<release_handler_sig> _release_handler;
};

} // namespace wlcpp

#endif // _BUFFER_HPP_

