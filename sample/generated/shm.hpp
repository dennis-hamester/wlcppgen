
#ifndef _SHM_HPP_
#define _SHM_HPP_

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

class shm_pool;

#define WLCPP_SHM_VERSION 1

/** \brief wl_shm error values
 *
 *  These errors can be emitted in response to wl_shm requests.
 */
enum shm_error {
    SHM_ERROR_INVALID_FORMAT = 0, /**< buffer format is not known */
    SHM_ERROR_INVALID_STRIDE = 1, /**< invalid size or stride during pool or buffer creation */
    SHM_ERROR_INVALID_FD = 2, /**< mmapping the file descriptor failed */
};

/** \brief pixel formats
 *
 *  This describes the memory layout of an individual pixel.
 *
 *  All renderers should support argb8888 and xrgb8888 but any other formats are
 *  optional and may not be supported by the particular renderer in use.
 */
enum shm_format {
    SHM_FORMAT_ARGB8888 = 0, /**< 32-bit ARGB format */
    SHM_FORMAT_XRGB8888 = 1, /**< 32-bit RGB format */
    SHM_FORMAT_C8 = 0x20203843,
    SHM_FORMAT_RGB332 = 0x38424752,
    SHM_FORMAT_BGR233 = 0x38524742,
    SHM_FORMAT_XRGB4444 = 0x32315258,
    SHM_FORMAT_XBGR4444 = 0x32314258,
    SHM_FORMAT_RGBX4444 = 0x32315852,
    SHM_FORMAT_BGRX4444 = 0x32315842,
    SHM_FORMAT_ARGB4444 = 0x32315241,
    SHM_FORMAT_ABGR4444 = 0x32314241,
    SHM_FORMAT_RGBA4444 = 0x32314152,
    SHM_FORMAT_BGRA4444 = 0x32314142,
    SHM_FORMAT_XRGB1555 = 0x35315258,
    SHM_FORMAT_XBGR1555 = 0x35314258,
    SHM_FORMAT_RGBX5551 = 0x35315852,
    SHM_FORMAT_BGRX5551 = 0x35315842,
    SHM_FORMAT_ARGB1555 = 0x35315241,
    SHM_FORMAT_ABGR1555 = 0x35314241,
    SHM_FORMAT_RGBA5551 = 0x35314152,
    SHM_FORMAT_BGRA5551 = 0x35314142,
    SHM_FORMAT_RGB565 = 0x36314752,
    SHM_FORMAT_BGR565 = 0x36314742,
    SHM_FORMAT_RGB888 = 0x34324752,
    SHM_FORMAT_BGR888 = 0x34324742,
    SHM_FORMAT_XBGR8888 = 0x34324258,
    SHM_FORMAT_RGBX8888 = 0x34325852,
    SHM_FORMAT_BGRX8888 = 0x34325842,
    SHM_FORMAT_ABGR8888 = 0x34324241,
    SHM_FORMAT_RGBA8888 = 0x34324152,
    SHM_FORMAT_BGRA8888 = 0x34324142,
    SHM_FORMAT_XRGB2101010 = 0x30335258,
    SHM_FORMAT_XBGR2101010 = 0x30334258,
    SHM_FORMAT_RGBX1010102 = 0x30335852,
    SHM_FORMAT_BGRX1010102 = 0x30335842,
    SHM_FORMAT_ARGB2101010 = 0x30335241,
    SHM_FORMAT_ABGR2101010 = 0x30334241,
    SHM_FORMAT_RGBA1010102 = 0x30334152,
    SHM_FORMAT_BGRA1010102 = 0x30334142,
    SHM_FORMAT_YUYV = 0x56595559,
    SHM_FORMAT_YVYU = 0x55595659,
    SHM_FORMAT_UYVY = 0x59565955,
    SHM_FORMAT_VYUY = 0x59555956,
    SHM_FORMAT_AYUV = 0x56555941,
    SHM_FORMAT_NV12 = 0x3231564e,
    SHM_FORMAT_NV21 = 0x3132564e,
    SHM_FORMAT_NV16 = 0x3631564e,
    SHM_FORMAT_NV61 = 0x3136564e,
    SHM_FORMAT_YUV410 = 0x39565559,
    SHM_FORMAT_YVU410 = 0x39555659,
    SHM_FORMAT_YUV411 = 0x31315559,
    SHM_FORMAT_YVU411 = 0x31315659,
    SHM_FORMAT_YUV420 = 0x32315559,
    SHM_FORMAT_YVU420 = 0x32315659,
    SHM_FORMAT_YUV422 = 0x36315559,
    SHM_FORMAT_YVU422 = 0x36315659,
    SHM_FORMAT_YUV444 = 0x34325559,
    SHM_FORMAT_YVU444 = 0x34325659,
};

/** \brief shared memory support
 *
 *  A global singleton object that provides support for shared memory.
 *
 *  Clients can create wl_shm_pool objects using the create_pool request.
 *
 *  At connection setup time, the wl_shm object emits one or more format events
 *  to inform clients about the valid pixel formats that can be used for
 *  buffers.
 */
class shm final
    : public proxy {
public:
    /** \brief wl_interface for @ref shm */
    static const wl_interface interface;

    /** \brief @ref shm version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_shm object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    shm(wl_proxy* obj = nullptr);

    /** \brief Create new @ref shm from factory
     *  @param factory Object which acts as the factory
     */
    explicit shm(proxy& factory);

    /** \brief Default move constructor */
    shm(shm&& rhs) = default;

    /** \brief Default destructor */
    virtual ~shm() = default;

    /** \brief Default move assignment operator */
    shm& operator=(shm&& rhs) = default;

    /** \brief create a shm pool
     *
     *  Create a new wl_shm_pool object.
     *
     *  The pool can be used to create shared memory based buffer objects. The
     *  server will mmap size bytes of the passed file descriptor, to use as backing
     *  memory for the pool.
     *
     *  @param fd_
     *  @param size_
     *  @return
     */
    shm_pool create_pool(std::int32_t fd_, std::int32_t size_);

    /** \brief pixel format description
     *
     *  Informs the client about a valid pixel format that can be used for buffers.
     *  Known formats include argb8888 and xrgb8888.
     *
     *  @param format_
     */
    using format_handler_sig = void (std::uint32_t format_);

    /** \brief Set a handler for the format event
     *  @param handler Callable of signature @ref format_handler_sig
     */
    template <typename T>
    void set_format_handler(T&& handler) {
        _format_handler = std::function<format_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*format_handler) (void*, wl_proxy*, std::uint32_t);
    };

    static void format_handler(void* data, wl_proxy* wl_obj, std::uint32_t format_);

    static const listener_t listener;

    std::function<format_handler_sig> _format_handler;
};

} // namespace wlcpp

#endif // _SHM_HPP_

