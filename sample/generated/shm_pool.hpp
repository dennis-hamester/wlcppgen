
#ifndef _SHM_POOL_HPP_
#define _SHM_POOL_HPP_

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

#define WLCPP_SHM_POOL_VERSION 1

/** \brief a shared memory pool
 *
 *  The wl_shm_pool object encapsulates a piece of memory shared between the
 *  compositor and client. Through the wl_shm_pool object, the client can
 *  allocate shared memory wl_buffer objects. All objects created through the
 *  same pool share the same underlying mapped memory. Reusing the mapped memory
 *  avoids the setup/teardown overhead and is useful when interactively resizing
 *  a surface or for many small buffers.
 */
class shm_pool final
    : public proxy {
public:
    /** \brief wl_interface for @ref shm_pool */
    static const wl_interface interface;

    /** \brief @ref shm_pool version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_shm_pool object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_shm_pool object and is responsible for destryoing it
     */
    shm_pool(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref shm_pool from factory
     *  @param factory Object which acts as the factory
     */
    explicit shm_pool(proxy& factory);

    /** \brief Default move constructor */
    shm_pool(shm_pool&& rhs) = default;

    /** \brief Destructor */
    virtual ~shm_pool();

    /** \brief Default move assignment operator */
    shm_pool& operator=(shm_pool&& rhs) = default;

    /** \brief create a buffer from the pool
     *
     *  Create a wl_buffer object from the pool.
     *
     *  The buffer is created offset bytes into the pool and has width and height as
     *  specified. The stride arguments specifies the number of bytes from beginning
     *  of one row to the beginning of the next. The format is the pixel format of
     *  the buffer and must be one of those advertised through the wl_shm.format
     *  event.
     *
     *  A buffer will keep a reference to the pool it was created from so it is
     *  valid to destroy the pool immediately after creating a buffer from it.
     *
     *  @param offset_
     *  @param width_
     *  @param height_
     *  @param stride_
     *  @param format_
     *  @return
     */
    buffer create_buffer(std::int32_t offset_, std::int32_t width_, std::int32_t height_, std::int32_t stride_, std::uint32_t format_);

    /** \brief change the size of the pool mapping
     *
     *  This request will cause the server to remap the backing memory for the pool
     *  from the file descriptor passed when the pool was created, but using the new
     *  size.
     *
     *  @param size_
     */
    void resize(std::int32_t size_);

protected:
    void destroy() override;
};

} // namespace wlcpp

#endif // _SHM_POOL_HPP_

