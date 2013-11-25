
#ifndef _WLCPP_
#define _WLCPP_

#include <functional>
#include <string>
#include <utility>
#include "proxy.hpp"

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

class registry;
class callback;
class compositor;
class shm_pool;
class shm;
class buffer;
class data_offer;
class data_source;
class data_device;
class data_device_manager;
class shell;
class shell_surface;
class surface;
class seat;
class pointer;
class keyboard;
class touch;
class output;
class region;

#define WLCPP_REGISTRY_VERSION 1

/** global registry object
 *
 *  The global registry object. The server has a number of global objects that
 *  are available to all clients. These objects typically represent an actual
 *  object in the server (for example, an input device) or they are singleton
 *  objects that provide extension functionality.
 *  
 *  When a client creates a registry object, the registry object will emit a
 *  global event for each global currently in the registry. Globals come and go
 *  as a result of device or monitor hotplugs, reconfiguration or other events,
 *  and the registry will send out global and global_remove events to keep the
 *  client up to date with the changes. To mark the end of the initial burst of
 *  events, the client can use the wl_display.sync request immediately after
 *  calling wl_display.get_registry.
 *  
 *  A client can bind to a global object by using the bind request. This creates
 *  a client-side handle that lets the object emit events to the client and lets
 *  the client invoke requests on the object.
 */
class registry final
    : public proxy {
public:
    /** wl_interface for registry */
    static const wl_interface interface;

    /** registry version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_registry object
     *  @param obj Object to wrap
     */
    registry(wl_proxy* obj = nullptr);

    /** Create new registry from factory
     *  @param factory Object which acts as the factory
     */
    explicit registry(proxy& factory);

    /** Default move constructor */
    registry(registry&& rhs) = default;

    /** Default destructor */
    virtual ~registry() = default;

    /** Default move assignment operator */
    registry& operator=(registry&& rhs) = default;

    /** bind an object to the display
     *
     *  Binds a new, client-created object to the server using the specified name as
     *  the identifier.
     *
     *  @param name_ unique name for the object
     *  @return
     */
    template <typename T>
    T bind(std::uint32_t name_, std::uint32_t version_) {
        T id_(*this);
        marshal(0, name_, T::interface.name, version_, id_.wl_obj());
        return id_;
    }

    /** announce global object
     *
     *  Notify the client of global objects.
     *  
     *  The event notifies the client that a global object with the given name is
     *  now available, and it implements the given version of the given interface.
     *
     *  Parameter name_:
     *  Parameter interface_:
     *  Parameter version_:
     */
    using global_handler_sig = void (std::uint32_t name_, const std::string& interface_, std::uint32_t version_);

    /** Set a handler for the global event
     *  @param handler Callable of signature @ref global_handler_sig
     */
    template <typename T>
    void set_global_handler(T&& handler) {
        _global_handler = std::function<global_handler_sig>(std::forward<T>(handler));
    }

    /** announce removal of global object
     *
     *  Notify the client of removed global objects.
     *  
     *  This event notifies the client that the global identified by name is no
     *  longer available. If the client bound to the global using the bind request,
     *  the client should now destroy that object.
     *  
     *  The object remains valid and requests to the object will be ignored until
     *  the client destroys it, to avoid races between the global going away and a
     *  client sending a request to it.
     *
     *  Parameter name_:
     */
    using global_remove_handler_sig = void (std::uint32_t name_);

    /** Set a handler for the global_remove event
     *  @param handler Callable of signature @ref global_remove_handler_sig
     */
    template <typename T>
    void set_global_remove_handler(T&& handler) {
        _global_remove_handler = std::function<global_remove_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*global_handler) (void*, wl_proxy*, std::uint32_t, const char*, std::uint32_t);
        void (*global_remove_handler) (void*, wl_proxy*, std::uint32_t);
    };

    static void global_handler(void* data, wl_proxy* wl_obj, std::uint32_t name_, const char* interface_, std::uint32_t version_);
    static void global_remove_handler(void* data, wl_proxy* wl_obj, std::uint32_t name_);

    static const listener_t listener;

    std::function<global_handler_sig> _global_handler;
    std::function<global_remove_handler_sig> _global_remove_handler;
};

#define WLCPP_CALLBACK_VERSION 1

/** callback object
 *
 *  Clients can handle the 'done' event to get notified when the related request
 *  is done.
 */
class callback final
    : public proxy {
public:
    /** wl_interface for callback */
    static const wl_interface interface;

    /** callback version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_callback object
     *  @param obj Object to wrap
     */
    callback(wl_proxy* obj = nullptr);

    /** Create new callback from factory
     *  @param factory Object which acts as the factory
     */
    explicit callback(proxy& factory);

    /** Default move constructor */
    callback(callback&& rhs) = default;

    /** Default destructor */
    virtual ~callback() = default;

    /** Default move assignment operator */
    callback& operator=(callback&& rhs) = default;

    /** done event
     *
     *  Notify the client when the related request is done.
     *
     *  Parameter serial_: serial of the event
     */
    using done_handler_sig = void (std::uint32_t serial_);

    /** Set a handler for the done event
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

#define WLCPP_COMPOSITOR_VERSION 3

/** the compositor singleton
 *
 *  A compositor. This object is a singleton global. The compositor is in charge
 *  of combining the contents of multiple surfaces into one displayable output.
 */
class compositor final
    : public proxy {
public:
    /** wl_interface for compositor */
    static const wl_interface interface;

    /** compositor version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** Wrap existing wl_compositor object
     *  @param obj Object to wrap
     */
    compositor(wl_proxy* obj = nullptr);

    /** Create new compositor from factory
     *  @param factory Object which acts as the factory
     */
    explicit compositor(proxy& factory);

    /** Default move constructor */
    compositor(compositor&& rhs) = default;

    /** Default destructor */
    virtual ~compositor() = default;

    /** Default move assignment operator */
    compositor& operator=(compositor&& rhs) = default;

    /** create new surface
     *
     *  Ask the compositor to create a new surface.
     *
     *  @return
     */
    surface create_surface();

    /** create new region
     *
     *  Ask the compositor to create a new region.
     *
     *  @return
     */
    region create_region();
};

#define WLCPP_SHM_POOL_VERSION 1

/** a shared memory pool
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
    /** wl_interface for shm_pool */
    static const wl_interface interface;

    /** shm_pool version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_shm_pool object
     *  @param obj Object to wrap
     */
    shm_pool(wl_proxy* obj = nullptr);

    /** Create new shm_pool from factory
     *  @param factory Object which acts as the factory
     */
    explicit shm_pool(proxy& factory);

    /** Default move constructor */
    shm_pool(shm_pool&& rhs) = default;

    /** Destructor */
    virtual ~shm_pool();

    /** Default move assignment operator */
    shm_pool& operator=(shm_pool&& rhs) = default;

    /** create a buffer from the pool
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

    /** change the size of the pool mapping
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

#define WLCPP_SHM_VERSION 1

/** wl_shm error values
 *
 *  These errors can be emitted in response to wl_shm requests.
 */
enum shm_error {
    SHM_ERROR_INVALID_FORMAT = 0, /**< buffer format is not known */
    SHM_ERROR_INVALID_STRIDE = 1, /**< invalid size or stride during pool or buffer creation */
    SHM_ERROR_INVALID_FD = 2, /**< mmapping the file descriptor failed */
};

/** pixel formats
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

/** shared memory support
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
    /** wl_interface for shm */
    static const wl_interface interface;

    /** shm version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_shm object
     *  @param obj Object to wrap
     */
    shm(wl_proxy* obj = nullptr);

    /** Create new shm from factory
     *  @param factory Object which acts as the factory
     */
    explicit shm(proxy& factory);

    /** Default move constructor */
    shm(shm&& rhs) = default;

    /** Default destructor */
    virtual ~shm() = default;

    /** Default move assignment operator */
    shm& operator=(shm&& rhs) = default;

    /** create a shm pool
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

    /** pixel format description
     *
     *  Informs the client about a valid pixel format that can be used for buffers.
     *  Known formats include argb8888 and xrgb8888.
     *
     *  Parameter format_:
     */
    using format_handler_sig = void (std::uint32_t format_);

    /** Set a handler for the format event
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

#define WLCPP_BUFFER_VERSION 1

/** content for a wl_surface
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
    /** wl_interface for buffer */
    static const wl_interface interface;

    /** buffer version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_buffer object
     *  @param obj Object to wrap
     */
    buffer(wl_proxy* obj = nullptr);

    /** Create new buffer from factory
     *  @param factory Object which acts as the factory
     */
    explicit buffer(proxy& factory);

    /** Default move constructor */
    buffer(buffer&& rhs) = default;

    /** Destructor */
    virtual ~buffer();

    /** Default move assignment operator */
    buffer& operator=(buffer&& rhs) = default;

    /** compositor releases buffer
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

    /** Set a handler for the release event
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

#define WLCPP_DATA_OFFER_VERSION 1

/** offer to transfer data
 *
 *  A wl_data_offer represents a piece of data offered for transfer by another
 *  client (the source client). It is used by the copy-and-paste and
 *  drag-and-drop mechanisms. The offer describes the different mime types that
 *  the data can be converted to and provides the mechanism for transferring the
 *  data directly from the source client.
 */
class data_offer final
    : public proxy {
public:
    /** wl_interface for data_offer */
    static const wl_interface interface;

    /** data_offer version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_data_offer object
     *  @param obj Object to wrap
     */
    data_offer(wl_proxy* obj = nullptr);

    /** Create new data_offer from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_offer(proxy& factory);

    /** Default move constructor */
    data_offer(data_offer&& rhs) = default;

    /** Destructor */
    virtual ~data_offer();

    /** Default move assignment operator */
    data_offer& operator=(data_offer&& rhs) = default;

    /** accept one of the offered mime types
     *
     *  Indicate that the client can accept the given mime type, or NULL for not
     *  accepted.
     *  
     *  Used for feedback during drag-and-drop.
     *
     *  @param serial_
     *  @param mime_type_
     */
    void accept(std::uint32_t serial_, const std::string* mime_type_);

    /** request that the data is transferred
     *
     *  To transfer the offered data, the client issues this request and indicates
     *  the mime type it wants to receive. The transfer happens through the passed
     *  file descriptor (typically created with the pipe system call). The source
     *  client writes the data in the mime type representation requested and then
     *  closes the file descriptor.
     *  
     *  The receiving client reads from the read end of the pipe until EOF and the
     *  closes its end, at which point the transfer is complete.
     *
     *  @param mime_type_
     *  @param fd_
     */
    void receive(const std::string& mime_type_, std::int32_t fd_);

    /** advertise offered mime type
     *
     *  Sent immediately after creating the wl_data_offer object. One event per
     *  offered mime type.
     *
     *  Parameter mime_type_:
     */
    using offer_handler_sig = void (const std::string& mime_type_);

    /** Set a handler for the offer event
     *  @param handler Callable of signature @ref offer_handler_sig
     */
    template <typename T>
    void set_offer_handler(T&& handler) {
        _offer_handler = std::function<offer_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*offer_handler) (void*, wl_proxy*, const char*);
    };

    static void offer_handler(void* data, wl_proxy* wl_obj, const char* mime_type_);

    static const listener_t listener;

    std::function<offer_handler_sig> _offer_handler;
};

#define WLCPP_DATA_SOURCE_VERSION 1

/** offer to transfer data
 *
 *  The wl_data_source object is the source side of a wl_data_offer. It is
 *  created by the source client in a data transfer and provides a way to
 *  describe the offered data and a way to respond to requests to transfer the
 *  data.
 */
class data_source final
    : public proxy {
public:
    /** wl_interface for data_source */
    static const wl_interface interface;

    /** data_source version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_data_source object
     *  @param obj Object to wrap
     */
    data_source(wl_proxy* obj = nullptr);

    /** Create new data_source from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_source(proxy& factory);

    /** Default move constructor */
    data_source(data_source&& rhs) = default;

    /** Destructor */
    virtual ~data_source();

    /** Default move assignment operator */
    data_source& operator=(data_source&& rhs) = default;

    /** add an offered mime type
     *
     *  This request adds a mime type to the set of mime types advertised to
     *  targets. Can be called several times to offer multiple types.
     *
     *  @param mime_type_
     */
    void offer(const std::string& mime_type_);

    /** a target accepts an offered mime type
     *
     *  Sent when a target accepts pointer_focus or motion events. If a target does
     *  not accept any of the offered types, type is NULL.
     *  
     *  Used for feedback during drag-and-drop.
     *
     *  Parameter mime_type_:
     */
    using target_handler_sig = void (const std::string* mime_type_);

    /** Set a handler for the target event
     *  @param handler Callable of signature @ref target_handler_sig
     */
    template <typename T>
    void set_target_handler(T&& handler) {
        _target_handler = std::function<target_handler_sig>(std::forward<T>(handler));
    }

    /** send the data
     *
     *  Request for data from the client. Send the data as the specified mime type
     *  over the passed file descriptor, then close it.
     *
     *  Parameter mime_type_:
     *  Parameter fd_:
     */
    using send_handler_sig = void (const std::string& mime_type_, std::int32_t fd_);

    /** Set a handler for the send event
     *  @param handler Callable of signature @ref send_handler_sig
     */
    template <typename T>
    void set_send_handler(T&& handler) {
        _send_handler = std::function<send_handler_sig>(std::forward<T>(handler));
    }

    /** selection was cancelled
     *
     *  This data source has been replaced by another data source. The client should
     *  clean up and destroy this data source.
     */
    using cancelled_handler_sig = void ();

    /** Set a handler for the cancelled event
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

#define WLCPP_DATA_DEVICE_VERSION 1

/** data transfer device
 *
 *  There is one wl_data_device per seat which can be obtained from the global
 *  wl_data_device_manager singleton.
 *  
 *  A wl_data_device provides access to inter-client data transfer mechanisms
 *  such as copy-and-paste and drag-and-drop.
 */
class data_device final
    : public proxy {
public:
    /** wl_interface for data_device */
    static const wl_interface interface;

    /** data_device version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_data_device object
     *  @param obj Object to wrap
     */
    data_device(wl_proxy* obj = nullptr);

    /** Create new data_device from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_device(proxy& factory);

    /** Default move constructor */
    data_device(data_device&& rhs) = default;

    /** Default destructor */
    virtual ~data_device() = default;

    /** Default move assignment operator */
    data_device& operator=(data_device&& rhs) = default;

    /** start drag-and-drop operation
     *
     *  This request asks the compositor to start a drag-and-drop operation on
     *  behalf of the client.
     *  
     *  The source argument is the data source that provides the data for the
     *  eventual data transfer. If source is NULL, enter, leave and motion events
     *  are sent only to the client that initiated the drag and the client is
     *  expected to handle the data passing internally.
     *  
     *  The origin surface is the surface where the drag originates and the client
     *  must have an active implicit grab that matches the serial.
     *  
     *  The icon surface is an optional (can be NULL) surface that provides an icon
     *  to be moved around with the cursor. Initially, the top-left corner of the
     *  icon surface is placed at the cursor hotspot, but subsequent
     *  wl_surface.attach request can move the relative position. Attach requests
     *  must be confirmed with wl_surface.commit as usual.
     *  
     *  The current and pending input regions of the icon wl_surface are cleared,
     *  and wl_surface.set_input_region is ignored until the wl_surface is no longer
     *  used as the icon surface. When the use as an icon ends, the the current and
     *  pending input regions become undefined, and the wl_surface is unmapped.
     *
     *  @param source_
     *  @param origin_
     *  @param icon_
     *  @param serial_ serial of the implicit grab on the origin
     */
    void start_drag(data_source* source_, surface& origin_, surface* icon_, std::uint32_t serial_);

    /** copy data to the selection
     *
     *  This request asks the compositor to set the selection to the data from the
     *  source on behalf of the client.
     *  
     *  To unset the selection, set the source to NULL.
     *
     *  @param source_
     *  @param serial_ serial of the event that triggered this request
     */
    void set_selection(data_source* source_, std::uint32_t serial_);

    /** introduce a new wl_data_offer
     *
     *  The data_offer event introduces a new wl_data_offer object, which will
     *  subsequently be used in either the data_device.enter event (for
     *  drag-and-drop) or the data_device.selection event (for selections).
     *  Immediately following the data_device_data_offer event, the new data_offer
     *  object will send out data_offer.offer events to describe the mime types it
     *  offers.
     *
     *  Parameter id_:
     */
    using data_offer_handler_sig = void (data_offer&& id_);

    /** Set a handler for the data_offer event
     *  @param handler Callable of signature @ref data_offer_handler_sig
     */
    template <typename T>
    void set_data_offer_handler(T&& handler) {
        _data_offer_handler = std::function<data_offer_handler_sig>(std::forward<T>(handler));
    }

    /** initiate drag-and-drop session
     *
     *  This event is sent when an active drag-and-drop pointer enters a surface
     *  owned by the client. The position of the pointer at enter time is provided
     *  by the x and y arguments, in surface local coordinates.
     *
     *  Parameter serial_:
     *  Parameter surface_:
     *  Parameter x_:
     *  Parameter y_:
     *  Parameter id_:
     */
    using enter_handler_sig = void (std::uint32_t serial_, surface& surface_, wl_fixed_t x_, wl_fixed_t y_, data_offer* id_);

    /** Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** end drag-and-drop session
     *
     *  This event is sent when the drag-and-drop pointer leaves the surface and the
     *  session ends. The client must destroy the wl_data_offer introduced at enter
     *  time at this point.
     */
    using leave_handler_sig = void ();

    /** Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

    /** drag-and-drop session motion
     *
     *  This event is sent when the drag-and-drop pointer moves within the currently
     *  focused surface. The new position of the pointer is provided by the x and y
     *  arguments, in surface local coordinates.
     *
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter x_:
     *  Parameter y_:
     */
    using motion_handler_sig = void (std::uint32_t time_, wl_fixed_t x_, wl_fixed_t y_);

    /** Set a handler for the motion event
     *  @param handler Callable of signature @ref motion_handler_sig
     */
    template <typename T>
    void set_motion_handler(T&& handler) {
        _motion_handler = std::function<motion_handler_sig>(std::forward<T>(handler));
    }

    /** end drag-and-drag session successfully
     *
     *  The event is sent when a drag-and-drop operation is ended because the
     *  implicit grab is removed.
     */
    using drop_handler_sig = void ();

    /** Set a handler for the drop event
     *  @param handler Callable of signature @ref drop_handler_sig
     */
    template <typename T>
    void set_drop_handler(T&& handler) {
        _drop_handler = std::function<drop_handler_sig>(std::forward<T>(handler));
    }

    /** advertise new selection
     *
     *  The selection event is sent out to notify the client of a new wl_data_offer
     *  for the selection for this device. The data_device.data_offer and the
     *  data_offer.offer events are sent out immediately before this event to
     *  introduce the data offer object. The selection event is sent to a client
     *  immediately before receiving keyboard focus and when a new selection is set
     *  while the client has keyboard focus. The data_offer is valid until a new
     *  data_offer or NULL is received or until the client loses keyboard focus.
     *
     *  Parameter id_:
     */
    using selection_handler_sig = void (data_offer* id_);

    /** Set a handler for the selection event
     *  @param handler Callable of signature @ref selection_handler_sig
     */
    template <typename T>
    void set_selection_handler(T&& handler) {
        _selection_handler = std::function<selection_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*data_offer_handler) (void*, wl_proxy*, wl_proxy*);
        void (*enter_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*, wl_fixed_t, wl_fixed_t, wl_proxy*);
        void (*leave_handler) (void*, wl_proxy*);
        void (*motion_handler) (void*, wl_proxy*, std::uint32_t, wl_fixed_t, wl_fixed_t);
        void (*drop_handler) (void*, wl_proxy*);
        void (*selection_handler) (void*, wl_proxy*, wl_proxy*);
    };

    static void data_offer_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_);
    static void enter_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_, wl_fixed_t x_, wl_fixed_t y_, wl_proxy* id_);
    static void leave_handler(void* data, wl_proxy* wl_obj);
    static void motion_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, wl_fixed_t x_, wl_fixed_t y_);
    static void drop_handler(void* data, wl_proxy* wl_obj);
    static void selection_handler(void* data, wl_proxy* wl_obj, wl_proxy* id_);

    static const listener_t listener;

    std::function<data_offer_handler_sig> _data_offer_handler;
    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
    std::function<motion_handler_sig> _motion_handler;
    std::function<drop_handler_sig> _drop_handler;
    std::function<selection_handler_sig> _selection_handler;
};

#define WLCPP_DATA_DEVICE_MANAGER_VERSION 1

/** data transfer interface
 *
 *  The wl_data_device_manager is a singleton global object that provides access
 *  to inter-client data transfer mechanisms such as copy-and-paste and
 *  drag-and-drop. These mechanisms are tied to a wl_seat and this interface
 *  lets a client get a wl_data_device corresponding to a wl_seat.
 */
class data_device_manager final
    : public proxy {
public:
    /** wl_interface for data_device_manager */
    static const wl_interface interface;

    /** data_device_manager version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_data_device_manager object
     *  @param obj Object to wrap
     */
    data_device_manager(wl_proxy* obj = nullptr);

    /** Create new data_device_manager from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_device_manager(proxy& factory);

    /** Default move constructor */
    data_device_manager(data_device_manager&& rhs) = default;

    /** Default destructor */
    virtual ~data_device_manager() = default;

    /** Default move assignment operator */
    data_device_manager& operator=(data_device_manager&& rhs) = default;

    /** create a new data source
     *
     *  Create a new data source.
     *
     *  @return
     */
    data_source create_data_source();

    /** create a new data device
     *
     *  Create a new data device for a given seat.
     *
     *  @param seat_
     *  @return
     */
    data_device get_data_device(seat& seat_);
};

#define WLCPP_SHELL_VERSION 1

/** create desktop-style surfaces
 *
 *  This interface is implemented by servers that provide desktop-style user
 *  interfaces.
 *  
 *  It allows clients to associate a wl_shell_surface with a basic surface.
 */
class shell final
    : public proxy {
public:
    /** wl_interface for shell */
    static const wl_interface interface;

    /** shell version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_shell object
     *  @param obj Object to wrap
     */
    shell(wl_proxy* obj = nullptr);

    /** Create new shell from factory
     *  @param factory Object which acts as the factory
     */
    explicit shell(proxy& factory);

    /** Default move constructor */
    shell(shell&& rhs) = default;

    /** Default destructor */
    virtual ~shell() = default;

    /** Default move assignment operator */
    shell& operator=(shell&& rhs) = default;

    /** create a shell surface from a surface
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

#define WLCPP_SHELL_SURFACE_VERSION 1

/** edge values for resizing
 *
 *  These values are used to indicate which edge of a surface is being dragged
 *  in a resize operation. The server may use this information to adapt its
 *  behavior, e.g. choose an appropriate cursor image.
 */
enum shell_surface_resize {
    SHELL_SURFACE_RESIZE_NONE = 0,
    SHELL_SURFACE_RESIZE_TOP = 1,
    SHELL_SURFACE_RESIZE_BOTTOM = 2,
    SHELL_SURFACE_RESIZE_LEFT = 4,
    SHELL_SURFACE_RESIZE_TOP_LEFT = 5,
    SHELL_SURFACE_RESIZE_BOTTOM_LEFT = 6,
    SHELL_SURFACE_RESIZE_RIGHT = 8,
    SHELL_SURFACE_RESIZE_TOP_RIGHT = 9,
    SHELL_SURFACE_RESIZE_BOTTOM_RIGHT = 10,
};

/** details of transient behaviour
 *
 *  These flags specify details of the expected behaviour of transient surfaces.
 *  Used in the set_transient request.
 */
enum shell_surface_transient {
    SHELL_SURFACE_TRANSIENT_INACTIVE = 0x1, /**< do not set keyboard focus */
};

/** different method to set the surface fullscreen
 *
 *  Hints to indicate to the compositor how to deal with a conflict between the
 *  dimensions of the surface and the dimensions of the output. The compositor
 *  is free to ignore this parameter.
 */
enum shell_surface_fullscreen_method {
    SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT = 0, /**< no preference, apply default policy */
    SHELL_SURFACE_FULLSCREEN_METHOD_SCALE = 1, /**< scale, preserve the surface's aspect ratio and center on output */
    SHELL_SURFACE_FULLSCREEN_METHOD_DRIVER = 2, /**< switch output mode to the smallest mode that can fit the surface, add black borders to compensate size mismatch */
    SHELL_SURFACE_FULLSCREEN_METHOD_FILL = 3, /**< no upscaling, center on output and add black borders to compensate size mismatch */
};

/** desktop-style metadata interface
 *
 *  An interface that may be implemented by a wl_surface, for implementations
 *  that provide a desktop-style user interface.
 *  
 *  It provides requests to treat surfaces like toplevel, fullscreen or popup
 *  windows, move, resize or maximize them, associate metadata like title and
 *  class, etc.
 *  
 *  On the server side the object is automatically destroyed when the related
 *  wl_surface is destroyed. On client side, wl_shell_surface_destroy() must be
 *  called before destroying the wl_surface object.
 */
class shell_surface final
    : public proxy {
public:
    /** wl_interface for shell_surface */
    static const wl_interface interface;

    /** shell_surface version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_shell_surface object
     *  @param obj Object to wrap
     */
    shell_surface(wl_proxy* obj = nullptr);

    /** Create new shell_surface from factory
     *  @param factory Object which acts as the factory
     */
    explicit shell_surface(proxy& factory);

    /** Default move constructor */
    shell_surface(shell_surface&& rhs) = default;

    /** Default destructor */
    virtual ~shell_surface() = default;

    /** Default move assignment operator */
    shell_surface& operator=(shell_surface&& rhs) = default;

    /** respond to a ping event
     *
     *  A client must respond to a ping event with a pong request or the client may
     *  be deemed unresponsive.
     *
     *  @param serial_ serial of the ping event
     */
    void pong(std::uint32_t serial_);

    /** start an interactive move
     *
     *  Start a pointer-driven move of the surface.
     *  
     *  This request must be used in response to a button press event. The server
     *  may ignore move requests depending on the state of the surface (e.g.
     *  fullscreen or maximized).
     *
     *  @param seat_ the wl_seat whose pointer is used
     *  @param serial_ serial of the implicit grab on the pointer
     */
    void move(seat& seat_, std::uint32_t serial_);

    /** start an interactive resize
     *
     *  Start a pointer-driven resizing of the surface.
     *  
     *  This request must be used in response to a button press event. The server
     *  may ignore resize requests depending on the state of the surface (e.g.
     *  fullscreen or maximized).
     *
     *  @param seat_ the wl_seat whose pointer is used
     *  @param serial_ serial of the implicit grab on the pointer
     *  @param edges_ which edge or corner is being dragged
     */
    void resize(seat& seat_, std::uint32_t serial_, std::uint32_t edges_);

    /** make the surface a toplevel surface
     *
     *  Map the surface as a toplevel surface.
     *  
     *  A toplevel surface is not fullscreen, maximized or transient.
     */
    void set_toplevel();

    /** make the surface a transient surface
     *
     *  Map the surface relative to an existing surface.
     *  
     *  The x and y arguments specify the locations of the upper left corner of the
     *  surface relative to the upper left corner of the parent surface, in surface
     *  local coordinates.
     *  
     *  The flags argument controls details of the transient behaviour.
     *
     *  @param parent_
     *  @param x_
     *  @param y_
     *  @param flags_
     */
    void set_transient(surface& parent_, std::int32_t x_, std::int32_t y_, std::uint32_t flags_);

    /** make the surface a fullscreen surface
     *
     *  Map the surface as a fullscreen surface.
     *  
     *  If an output parameter is given then the surface will be made fullscreen on
     *  that output. If the client does not specify the output then the compositor
     *  will apply its policy - usually choosing the output on which the surface has
     *  the biggest surface area.
     *  
     *  The client may specify a method to resolve a size conflict between the
     *  output size and the surface size - this is provided through the method
     *  parameter.
     *  
     *  The framerate parameter is used only when the method is set to "driver", to
     *  indicate the preferred framerate. A value of 0 indicates that the app does
     *  not care about framerate. The framerate is specified in mHz, that is
     *  framerate of 60000 is 60Hz.
     *  
     *  A method of "scale" or "driver" implies a scaling operation of the surface,
     *  either via a direct scaling operation or a change of the output mode. This
     *  will override any kind of output scaling, so that mapping a surface with a
     *  buffer size equal to the mode can fill the screen independent of
     *  buffer_scale.
     *  
     *  A method of "fill" means we don't scale up the buffer, however any output
     *  scale is applied. This means that you may run into an edge case where the
     *  application maps a buffer with the same size of the output mode but
     *  buffer_scale 1 (thus making a surface larger than the output). In this case
     *  it is allowed to downscale the results to fit the screen.
     *  
     *  The compositor must reply to this request with a configure event with the
     *  dimensions for the output on which the surface will be made fullscreen.
     *
     *  @param method_
     *  @param framerate_
     *  @param output_
     */
    void set_fullscreen(std::uint32_t method_, std::uint32_t framerate_, output* output_);

    /** make the surface a popup surface
     *
     *  Map the surface as a popup.
     *  
     *  A popup surface is a transient surface with an added pointer grab.
     *  
     *  An existing implicit grab will be changed to owner-events mode, and the
     *  popup grab will continue after the implicit grab ends (i.e. releasing the
     *  mouse button does not cause the popup to be unmapped).
     *  
     *  The popup grab continues until the window is destroyed or a mouse button is
     *  pressed in any other clients window. A click in any of the clients surfaces
     *  is reported as normal, however, clicks in other clients surfaces will be
     *  discarded and trigger the callback.
     *  
     *  The x and y arguments specify the locations of the upper left corner of the
     *  surface relative to the upper left corner of the parent surface, in surface
     *  local coordinates.
     *
     *  @param seat_ the wl_seat whose pointer is used
     *  @param serial_ serial of the implicit grab on the pointer
     *  @param parent_
     *  @param x_
     *  @param y_
     *  @param flags_
     */
    void set_popup(seat& seat_, std::uint32_t serial_, surface& parent_, std::int32_t x_, std::int32_t y_, std::uint32_t flags_);

    /** make the surface a maximized surface
     *
     *  Map the surface as a maximized surface.
     *  
     *  If an output parameter is given then the surface will be maximized on that
     *  output. If the client does not specify the output then the compositor will
     *  apply its policy - usually choosing the output on which the surface has the
     *  biggest surface area.
     *  
     *  The compositor will reply with a configure event telling the expected new
     *  surface size. The operation is completed on the next buffer attach to this
     *  surface.
     *  
     *  A maximized surface typically fills the entire output it is bound to, except
     *  for desktop element such as panels. This is the main difference between a
     *  maximized shell surface and a fullscreen shell surface.
     *  
     *  The details depend on the compositor implementation.
     *
     *  @param output_
     */
    void set_maximized(output* output_);

    /** set surface title
     *
     *  Set a short title for the surface.
     *  
     *  This string may be used to identify the surface in a task bar, window list,
     *  or other user interface elements provided by the compositor.
     *  
     *  The string must be encoded in UTF-8.
     *
     *  @param title_
     */
    void set_title(const std::string& title_);

    /** set surface class
     *
     *  Set a class for the surface.
     *  
     *  The surface class identifies the general class of applications to which the
     *  surface belongs. A common convention is to use the file name (or the full
     *  path if it is a non-standard location) of the application's .desktop file as
     *  the class.
     *
     *  @param class__
     */
    void set_class(const std::string& class__);

    /** ping client
     *
     *  Ping a client to check if it is receiving events and sending requests. A
     *  client is expected to reply with a pong request.
     *
     *  Parameter serial_:
     */
    using ping_handler_sig = void (std::uint32_t serial_);

    /** Set a handler for the ping event
     *  @param handler Callable of signature @ref ping_handler_sig
     */
    template <typename T>
    void set_ping_handler(T&& handler) {
        _ping_handler = std::function<ping_handler_sig>(std::forward<T>(handler));
    }

    /** suggest resize
     *
     *  The configure event asks the client to resize its surface.
     *  
     *  The size is a hint, in the sense that the client is free to ignore it if it
     *  doesn't resize, pick a smaller size (to satisfy aspect ratio or resize in
     *  steps of NxM pixels).
     *  
     *  The edges parameter provides a hint about how the surface was resized. The
     *  client may use this information to decide how to adjust its content to the
     *  new size (e.g. a scrolling area might adjust its content position to leave
     *  the viewable content unmoved).
     *  
     *  The client is free to dismiss all but the last configure event it received.
     *  
     *  The width and height arguments specify the size of the window in surface
     *  local coordinates.
     *
     *  Parameter edges_:
     *  Parameter width_:
     *  Parameter height_:
     */
    using configure_handler_sig = void (std::uint32_t edges_, std::int32_t width_, std::int32_t height_);

    /** Set a handler for the configure event
     *  @param handler Callable of signature @ref configure_handler_sig
     */
    template <typename T>
    void set_configure_handler(T&& handler) {
        _configure_handler = std::function<configure_handler_sig>(std::forward<T>(handler));
    }

    /** popup interaction is done
     *
     *  The popup_done event is sent out when a popup grab is broken, that is, when
     *  the user clicks a surface that doesn't belong to the client owning the popup
     *  surface.
     */
    using popup_done_handler_sig = void ();

    /** Set a handler for the popup_done event
     *  @param handler Callable of signature @ref popup_done_handler_sig
     */
    template <typename T>
    void set_popup_done_handler(T&& handler) {
        _popup_done_handler = std::function<popup_done_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*ping_handler) (void*, wl_proxy*, std::uint32_t);
        void (*configure_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, std::int32_t);
        void (*popup_done_handler) (void*, wl_proxy*);
    };

    static void ping_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_);
    static void configure_handler(void* data, wl_proxy* wl_obj, std::uint32_t edges_, std::int32_t width_, std::int32_t height_);
    static void popup_done_handler(void* data, wl_proxy* wl_obj);

    static const listener_t listener;

    std::function<ping_handler_sig> _ping_handler;
    std::function<configure_handler_sig> _configure_handler;
    std::function<popup_done_handler_sig> _popup_done_handler;
};

#define WLCPP_SURFACE_VERSION 3

/** an onscreen surface
 *
 *  A surface is a rectangular area that is displayed on the screen. It has a
 *  location, size and pixel contents.
 *  
 *  The size of a surface (and relative positions on it) is described in surface
 *  local coordinates, which may differ from the buffer local coordinates of the
 *  pixel content, in case a buffer_transform or a buffer_scale is used.
 *  
 *  Surfaces are also used for some special purposes, e.g. as cursor images for
 *  pointers, drag icons, etc.
 */
class surface final
    : public proxy {
public:
    /** wl_interface for surface */
    static const wl_interface interface;

    /** surface version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** Wrap existing wl_surface object
     *  @param obj Object to wrap
     */
    surface(wl_proxy* obj = nullptr);

    /** Create new surface from factory
     *  @param factory Object which acts as the factory
     */
    explicit surface(proxy& factory);

    /** Default move constructor */
    surface(surface&& rhs) = default;

    /** Destructor */
    virtual ~surface();

    /** Default move assignment operator */
    surface& operator=(surface&& rhs) = default;

    /** set the surface contents
     *
     *  Set a buffer as the content of this surface.
     *  
     *  The new size of the surface is calculated based on the buffer size
     *  transformed by the inverse buffer_transform and the inverse buffer_scale.
     *  This means that the supplied buffer must be an integer multiple of the
     *  buffer_scale.
     *  
     *  The x and y arguments specify the location of the new pending buffer's upper
     *  left corner, relative to the current buffer's upper left corner, in surface
     *  local coordinates. In other words, the x and y, combined with the new
     *  surface size define in which directions the surface's size changes.
     *  
     *  Surface contents are double-buffered state, see wl_surface.commit.
     *  
     *  The initial surface contents are void; there is no content.
     *  wl_surface.attach assigns the given wl_buffer as the pending wl_buffer.
     *  wl_surface.commit makes the pending wl_buffer the new surface contents, and
     *  the size of the surface becomes the size calculated from the wl_buffer, as
     *  described above. After commit, there is no pending buffer until the next
     *  attach.
     *  
     *  Committing a pending wl_buffer allows the compositor to read the pixels in
     *  the wl_buffer. The compositor may access the pixels at any time after the
     *  wl_surface.commit request. When the compositor will not access the pixels
     *  anymore, it will send the wl_buffer.release event. Only after receiving
     *  wl_buffer.release, the client may re-use the wl_buffer. A wl_buffer that has
     *  been attached and then replaced by another attach instead of committed will
     *  not receive a release event, and is not used by the compositor.
     *  
     *  Destroying the wl_buffer after wl_buffer.release does not change the surface
     *  contents. However, if the client destroys the wl_buffer before receiving the
     *  wl_buffer.release event, the surface contents become undefined immediately.
     *  
     *  If wl_surface.attach is sent with a NULL wl_buffer, the following
     *  wl_surface.commit will remove the surface content.
     *
     *  @param buffer_
     *  @param x_
     *  @param y_
     */
    void attach(buffer* buffer_, std::int32_t x_, std::int32_t y_);

    /** mark part of the surface damaged
     *
     *  This request is used to describe the regions where the pending buffer is
     *  different from the current surface contents, and where the surface therefore
     *  needs to be repainted. The pending buffer must be set by wl_surface.attach
     *  before sending damage. The compositor ignores the parts of the damage that
     *  fall outside of the surface.
     *  
     *  Damage is double-buffered state, see wl_surface.commit.
     *  
     *  The damage rectangle is specified in surface local coordinates.
     *  
     *  The initial value for pending damage is empty: no damage. wl_surface.damage
     *  adds pending damage: the new pending damage is the union of old pending
     *  damage and the given rectangle.
     *  
     *  wl_surface.commit assigns pending damage as the current damage, and clears
     *  pending damage. The server will clear the current damage as it repaints the
     *  surface.
     *
     *  @param x_
     *  @param y_
     *  @param width_
     *  @param height_
     */
    void damage(std::int32_t x_, std::int32_t y_, std::int32_t width_, std::int32_t height_);

    /** request repaint feedback
     *
     *  Request notification when the next frame is displayed. Useful for throttling
     *  redrawing operations, and driving animations. The frame request will take
     *  effect on the next wl_surface.commit. The notification will only be posted
     *  for one frame unless requested again.
     *  
     *  A server should avoid signalling the frame callbacks if the surface is not
     *  visible in any way, e.g. the surface is off-screen, or completely obscured
     *  by other opaque surfaces.
     *  
     *  A client can request a frame callback even without an attach, damage, or any
     *  other state changes. wl_surface.commit triggers a display update, so the
     *  callback event will arrive after the next output refresh where the surface
     *  is visible.
     *  
     *  The object returned by this request will be destroyed by the compositor
     *  after the callback is fired and as such the client must not attempt to use
     *  it after that point.
     *
     *  @return
     */
    callback frame();

    /** set opaque region
     *
     *  This request sets the region of the surface that contains opaque content.
     *  
     *  The opaque region is an optimization hint for the compositor that lets it
     *  optimize out redrawing of content behind opaque regions. Setting an opaque
     *  region is not required for correct behaviour, but marking transparent
     *  content as opaque will result in repaint artifacts.
     *  
     *  The opaque region is specified in surface local coordinates.
     *  
     *  The compositor ignores the parts of the opaque region that fall outside of
     *  the surface.
     *  
     *  Opaque region is double-buffered state, see wl_surface.commit.
     *  
     *  wl_surface.set_opaque_region changes the pending opaque region.
     *  wl_surface.commit copies the pending region to the current region.
     *  Otherwise, the pending and current regions are never changed.
     *  
     *  The initial value for opaque region is empty. Setting the pending opaque
     *  region has copy semantics, and the wl_region object can be destroyed
     *  immediately. A NULL wl_region causes the pending opaque region to be set to
     *  empty.
     *
     *  @param region_
     */
    void set_opaque_region(region* region_);

    /** set input region
     *
     *  This request sets the region of the surface that can receive pointer and
     *  touch events.
     *  
     *  Input events happening outside of this region will try the next surface in
     *  the server surface stack. The compositor ignores the parts of the input
     *  region that fall outside of the surface.
     *  
     *  The input region is specified in surface local coordinates.
     *  
     *  Input region is double-buffered state, see wl_surface.commit.
     *  
     *  wl_surface.set_input_region changes the pending input region.
     *  wl_surface.commit copies the pending region to the current region. Otherwise
     *  the pending and current regions are never changed, except cursor and icon
     *  surfaces are special cases, see wl_pointer.set_cursor and
     *  wl_data_device.start_drag.
     *  
     *  The initial value for input region is infinite. That means the whole surface
     *  will accept input. Setting the pending input region has copy semantics, and
     *  the wl_region object can be destroyed immediately. A NULL wl_region causes
     *  the input region to be set to infinite.
     *
     *  @param region_
     */
    void set_input_region(region* region_);

    /** commit pending surface state
     *
     *  Surface state (input, opaque, and damage regions, attached buffers, etc.) is
     *  double-buffered. Protocol requests modify the pending state, as opposed to
     *  current state in use by the compositor. Commit request atomically applies
     *  all pending state, replacing the current state. After commit, the new
     *  pending state is as documented for each related request.
     *  
     *  On commit, a pending wl_buffer is applied first, all other state second.
     *  This means that all coordinates in double-buffered state are relative to the
     *  new wl_buffer coming into use, except for wl_surface.attach itself. If there
     *  is no pending wl_buffer, the coordinates are relative to the current surface
     *  contents.
     *  
     *  All requests that need a commit to become effective are documented to affect
     *  double-buffered state.
     *  
     *  Other interfaces may add further double-buffered surface state.
     */
    void commit();

    /** sets the buffer transformation
     *
     *  This request sets an optional transformation on how the compositor
     *  interprets the contents of the buffer attached to the surface. The accepted
     *  values for the transform parameter are the values for wl_output.transform.
     *  
     *  Buffer transform is double-buffered state, see wl_surface.commit.
     *  
     *  A newly created surface has its buffer transformation set to normal.
     *  
     *  The purpose of this request is to allow clients to render content according
     *  to the output transform, thus permiting the compositor to use certain
     *  optimizations even if the display is rotated. Using hardware overlays and
     *  scanning out a client buffer for fullscreen surfaces are examples of such
     *  optimizations. Those optimizations are highly dependent on the compositor
     *  implementation, so the use of this request should be considered on a
     *  case-by-case basis.
     *  
     *  Note that if the transform value includes 90 or 270 degree rotation, the
     *  width of the buffer will become the surface height and the height of the
     *  buffer will become the surface width.
     *
     *  @param transform_
     */
    void set_buffer_transform(std::int32_t transform_);

    /** sets the buffer scaling factor
     *
     *  This request sets an optional scaling factor on how the compositor
     *  interprets the contents of the buffer attached to the window.
     *  
     *  Buffer scale is double-buffered state, see wl_surface.commit.
     *  
     *  A newly created surface has its buffer scale set to 1.
     *  
     *  The purpose of this request is to allow clients to supply higher resolution
     *  buffer data for use on high resolution outputs. Its intended that you pick
     *  the same	buffer scale as the scale of the output that the surface is
     *  displayed on.This means the compositor can avoid scaling when rendering the
     *  surface on that output.
     *  
     *  Note that if the scale is larger than 1, then you have to attach a buffer
     *  that is larger (by a factor of scale in each dimension) than the desired
     *  surface size.
     *
     *  @param scale_
     */
    void set_buffer_scale(std::int32_t scale_);

    /** surface enters an output
     *
     *  This is emitted whenever a surface's creation, movement, or resizing results
     *  in some part of it being within the scanout region of an output.
     *  
     *  Note that a surface may be overlapping with zero or more outputs.
     *
     *  Parameter output_:
     */
    using enter_handler_sig = void (output& output_);

    /** Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** surface leaves an output
     *
     *  This is emitted whenever a surface's creation, movement, or resizing results
     *  in it no longer having any part of it within the scanout region of an
     *  output.
     *
     *  Parameter output_:
     */
    using leave_handler_sig = void (output& output_);

    /** Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*enter_handler) (void*, wl_proxy*, wl_proxy*);
        void (*leave_handler) (void*, wl_proxy*, wl_proxy*);
    };

    static void enter_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_);
    static void leave_handler(void* data, wl_proxy* wl_obj, wl_proxy* output_);

    static const listener_t listener;

    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
};

#define WLCPP_SEAT_VERSION 3

/** seat capability bitmask
 *
 *  This is a bitmask of capabilities this seat has; if a member is set, then it
 *  is present on the seat.
 */
enum seat_capability {
    SEAT_CAPABILITY_POINTER = 1, /**< The seat has pointer devices */
    SEAT_CAPABILITY_KEYBOARD = 2, /**< The seat has one or more keyboards */
    SEAT_CAPABILITY_TOUCH = 4, /**< The seat has touch devices */
};

/** group of input devices
 *
 *  A seat is a group of keyboards, pointer and touch devices. This object is
 *  published as a global during start up, or when such a device is hot plugged.
 *  A seat typically has a pointer and maintains a keyboard focus and a pointer
 *  focus.
 */
class seat final
    : public proxy {
public:
    /** wl_interface for seat */
    static const wl_interface interface;

    /** seat version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** Wrap existing wl_seat object
     *  @param obj Object to wrap
     */
    seat(wl_proxy* obj = nullptr);

    /** Create new seat from factory
     *  @param factory Object which acts as the factory
     */
    explicit seat(proxy& factory);

    /** Default move constructor */
    seat(seat&& rhs) = default;

    /** Default destructor */
    virtual ~seat() = default;

    /** Default move assignment operator */
    seat& operator=(seat&& rhs) = default;

    /** return pointer object
     *
     *  The ID provided will be initialized to the wl_pointer interface for this
     *  seat.
     *  
     *  This request only takes effect if the seat has the pointer capability.
     *
     *  @return
     */
    pointer get_pointer();

    /** return keyboard object
     *
     *  The ID provided will be initialized to the wl_keyboard interface for this
     *  seat.
     *  
     *  This request only takes effect if the seat has the keyboard capability.
     *
     *  @return
     */
    keyboard get_keyboard();

    /** return touch object
     *
     *  The ID provided will be initialized to the wl_touch interface for this seat.
     *  
     *  This request only takes effect if the seat has the touch capability.
     *
     *  @return
     */
    touch get_touch();

    /** seat capabilities changed
     *
     *  This is emitted whenever a seat gains or loses the pointer, keyboard or
     *  touch capabilities. The argument is a capability enum containing the
     *  complete set of capabilities this seat has.
     *
     *  Parameter capabilities_:
     */
    using capabilities_handler_sig = void (std::uint32_t capabilities_);

    /** Set a handler for the capabilities event
     *  @param handler Callable of signature @ref capabilities_handler_sig
     */
    template <typename T>
    void set_capabilities_handler(T&& handler) {
        _capabilities_handler = std::function<capabilities_handler_sig>(std::forward<T>(handler));
    }

    /** unique identifier for this seat
     *
     *  In a multiseat configuration this can be used by the client to help identify
     *  which physical devices the seat represents. Based on the seat configuration
     *  used by the compositor.
     *
     *  Parameter name_:
     */
    using name_handler_sig = void (const std::string& name_);

    /** Set a handler for the name event
     *  @param handler Callable of signature @ref name_handler_sig
     */
    template <typename T>
    void set_name_handler(T&& handler) {
        _name_handler = std::function<name_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*capabilities_handler) (void*, wl_proxy*, std::uint32_t);
        void (*name_handler) (void*, wl_proxy*, const char*);
    };

    static void capabilities_handler(void* data, wl_proxy* wl_obj, std::uint32_t capabilities_);
    static void name_handler(void* data, wl_proxy* wl_obj, const char* name_);

    static const listener_t listener;

    std::function<capabilities_handler_sig> _capabilities_handler;
    std::function<name_handler_sig> _name_handler;
};

#define WLCPP_POINTER_VERSION 3

/** physical button state
 *
 *  Describes the physical state of a button which provoked the button event.
 */
enum pointer_button_state {
    POINTER_BUTTON_STATE_RELEASED = 0, /**< The button is not pressed */
    POINTER_BUTTON_STATE_PRESSED = 1, /**< The button is pressed */
};

/** axis types
 *
 *  Describes the axis types of scroll events.
 */
enum pointer_axis {
    POINTER_AXIS_VERTICAL_SCROLL = 0,
    POINTER_AXIS_HORIZONTAL_SCROLL = 1,
};

/** pointer input device
 *
 *  The wl_pointer interface represents one or more input devices, such as mice,
 *  which control the pointer location and pointer_focus of a seat.
 *  
 *  The wl_pointer interface generates motion, enter and leave events for the
 *  surfaces that the pointer is located over, and button and axis events for
 *  button presses, button releases and scrolling.
 */
class pointer final
    : public proxy {
public:
    /** wl_interface for pointer */
    static const wl_interface interface;

    /** pointer version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** Wrap existing wl_pointer object
     *  @param obj Object to wrap
     */
    pointer(wl_proxy* obj = nullptr);

    /** Create new pointer from factory
     *  @param factory Object which acts as the factory
     */
    explicit pointer(proxy& factory);

    /** Default move constructor */
    pointer(pointer&& rhs) = default;

    /** Destructor */
    virtual ~pointer();

    /** Default move assignment operator */
    pointer& operator=(pointer&& rhs) = default;

    /** set the pointer surface
     *
     *  Set the pointer surface, i.e., the surface that contains the pointer image
     *  (cursor). This request only takes effect if the pointer focus for this
     *  device is one of the requesting client's surfaces or the surface parameter
     *  is the current pointer surface. If there was a previous surface set with
     *  this request it is replaced. If surface is NULL, the pointer image is
     *  hidden.
     *  
     *  The parameters hotspot_x and hotspot_y define the position of the pointer
     *  surface relative to the pointer location. Its top-left corner is always at
     *  (x, y) - (hotspot_x, hotspot_y), where (x, y) are the coordinates of the
     *  pointer location, in surface local coordinates.
     *  
     *  On surface.attach requests to the pointer surface, hotspot_x and hotspot_y
     *  are decremented by the x and y parameters passed to the request. Attach must
     *  be confirmed by wl_surface.commit as usual.
     *  
     *  The hotspot can also be updated by passing the currently set pointer surface
     *  to this request with new values for hotspot_x and hotspot_y.
     *  
     *  The current and pending input regions of the wl_surface are cleared, and
     *  wl_surface.set_input_region is ignored until the wl_surface is no longer
     *  used as the cursor. When the use as a cursor ends, the current and pending
     *  input regions become undefined, and the wl_surface is unmapped.
     *
     *  @param serial_ serial of the enter event
     *  @param surface_
     *  @param hotspot_x_ x coordinate in surface-relative coordinates
     *  @param hotspot_y_ y coordinate in surface-relative coordinates
     */
    void set_cursor(std::uint32_t serial_, surface* surface_, std::int32_t hotspot_x_, std::int32_t hotspot_y_);

    /** enter event
     *
     *  Notification that this seat's pointer is focused on a certain surface.
     *  
     *  When an seat's focus enters a surface, the pointer image is undefined and a
     *  client should respond to this event by setting an appropriate pointer image
     *  with the set_cursor request.
     *
     *  Parameter serial_:
     *  Parameter surface_:
     *  Parameter surface_x_: x coordinate in surface-relative coordinates
     *  Parameter surface_y_: y coordinate in surface-relative coordinates
     */
    using enter_handler_sig = void (std::uint32_t serial_, surface& surface_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);

    /** Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** leave event
     *
     *  Notification that this seat's pointer is no longer focused on a certain
     *  surface.
     *  
     *  The leave notification is sent before the enter notification for the new
     *  focus.
     *
     *  Parameter serial_:
     *  Parameter surface_:
     */
    using leave_handler_sig = void (std::uint32_t serial_, surface& surface_);

    /** Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

    /** pointer motion event
     *
     *  Notification of pointer location change. The arguments surface_x and
     *  surface_y are the location relative to the focused surface.
     *
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter surface_x_: x coordinate in surface-relative coordinates
     *  Parameter surface_y_: y coordinate in surface-relative coordinates
     */
    using motion_handler_sig = void (std::uint32_t time_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);

    /** Set a handler for the motion event
     *  @param handler Callable of signature @ref motion_handler_sig
     */
    template <typename T>
    void set_motion_handler(T&& handler) {
        _motion_handler = std::function<motion_handler_sig>(std::forward<T>(handler));
    }

    /** pointer button event
     *
     *  Mouse button click and release notifications.
     *  
     *  The location of the click is given by the last motion or enter event. The
     *  time argument is a timestamp with millisecond granularity, with an undefined
     *  base.
     *
     *  Parameter serial_:
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter button_:
     *  Parameter state_:
     */
    using button_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, std::uint32_t button_, std::uint32_t state_);

    /** Set a handler for the button event
     *  @param handler Callable of signature @ref button_handler_sig
     */
    template <typename T>
    void set_button_handler(T&& handler) {
        _button_handler = std::function<button_handler_sig>(std::forward<T>(handler));
    }

    /** axis event
     *
     *  Scroll and other axis notifications.
     *  
     *  For scroll events (vertical and horizontal scroll axes), the value parameter
     *  is the length of a vector along the specified axis in a coordinate space
     *  identical to those of motion events, representing a relative movement along
     *  the specified axis.
     *  
     *  For devices that support movements non-parallel to axes multiple axis events
     *  will be emitted.
     *  
     *  When applicable, for example for touch pads, the server can choose to emit
     *  scroll events where the motion vector is equivalent to a motion event
     *  vector.
     *  
     *  When applicable, clients can transform its view relative to the scroll
     *  distance.
     *
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter axis_:
     *  Parameter value_:
     */
    using axis_handler_sig = void (std::uint32_t time_, std::uint32_t axis_, wl_fixed_t value_);

    /** Set a handler for the axis event
     *  @param handler Callable of signature @ref axis_handler_sig
     */
    template <typename T>
    void set_axis_handler(T&& handler) {
        _axis_handler = std::function<axis_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*enter_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*, wl_fixed_t, wl_fixed_t);
        void (*leave_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*);
        void (*motion_handler) (void*, wl_proxy*, std::uint32_t, wl_fixed_t, wl_fixed_t);
        void (*button_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
        void (*axis_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, wl_fixed_t);
    };

    static void enter_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);
    static void leave_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_);
    static void motion_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, wl_fixed_t surface_x_, wl_fixed_t surface_y_);
    static void button_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, std::uint32_t button_, std::uint32_t state_);
    static void axis_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, std::uint32_t axis_, wl_fixed_t value_);

    static const listener_t listener;

    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
    std::function<motion_handler_sig> _motion_handler;
    std::function<button_handler_sig> _button_handler;
    std::function<axis_handler_sig> _axis_handler;
};

#define WLCPP_KEYBOARD_VERSION 3

/** keyboard mapping format
 *
 *  This specifies the format of the keymap provided to the client with the
 *  wl_keyboard.keymap event.
 */
enum keyboard_keymap_format {
    KEYBOARD_KEYMAP_FORMAT_NO_KEYMAP = 0, /**< no keymap; client must understand how to interpret the raw keycode */
    KEYBOARD_KEYMAP_FORMAT_XKB_V1 = 1, /**< libxkbcommon compatible */
};

/** physical key state
 *
 *  Describes the physical state of a key which provoked the key event.
 */
enum keyboard_key_state {
    KEYBOARD_KEY_STATE_RELEASED = 0, /**< key is not pressed */
    KEYBOARD_KEY_STATE_PRESSED = 1, /**< key is pressed */
};

/** keyboard input device
 *
 *  The wl_keyboard interface represents one or more keyboards associated with a
 *  seat.
 */
class keyboard final
    : public proxy {
public:
    /** wl_interface for keyboard */
    static const wl_interface interface;

    /** keyboard version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** Wrap existing wl_keyboard object
     *  @param obj Object to wrap
     */
    keyboard(wl_proxy* obj = nullptr);

    /** Create new keyboard from factory
     *  @param factory Object which acts as the factory
     */
    explicit keyboard(proxy& factory);

    /** Default move constructor */
    keyboard(keyboard&& rhs) = default;

    /** Destructor */
    virtual ~keyboard();

    /** Default move assignment operator */
    keyboard& operator=(keyboard&& rhs) = default;

    /** keyboard mapping
     *
     *  This event provides a file descriptor to the client which can be
     *  memory-mapped to provide a keyboard mapping description.
     *
     *  Parameter format_:
     *  Parameter fd_:
     *  Parameter size_:
     */
    using keymap_handler_sig = void (std::uint32_t format_, std::int32_t fd_, std::uint32_t size_);

    /** Set a handler for the keymap event
     *  @param handler Callable of signature @ref keymap_handler_sig
     */
    template <typename T>
    void set_keymap_handler(T&& handler) {
        _keymap_handler = std::function<keymap_handler_sig>(std::forward<T>(handler));
    }

    /** enter event
     *
     *  Notification that this seat's keyboard focus is on a certain surface.
     *
     *  Parameter serial_:
     *  Parameter surface_:
     *  Parameter keys_: the currently pressed keys
     */
    using enter_handler_sig = void (std::uint32_t serial_, surface& surface_, const wl_array& keys_);

    /** Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** leave event
     *
     *  Notification that this seat's keyboard focus is no longer on a certain
     *  surface.
     *  
     *  The leave notification is sent before the enter notification for the new
     *  focus.
     *
     *  Parameter serial_:
     *  Parameter surface_:
     */
    using leave_handler_sig = void (std::uint32_t serial_, surface& surface_);

    /** Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

    /** key event
     *
     *  A key was pressed or released. The time argument is a timestamp with
     *  millisecond granularity, with an undefined base.
     *
     *  Parameter serial_:
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter key_:
     *  Parameter state_:
     */
    using key_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, std::uint32_t key_, std::uint32_t state_);

    /** Set a handler for the key event
     *  @param handler Callable of signature @ref key_handler_sig
     */
    template <typename T>
    void set_key_handler(T&& handler) {
        _key_handler = std::function<key_handler_sig>(std::forward<T>(handler));
    }

    /** modifier and group state
     *
     *  Notifies clients that the modifier and/or group state has changed, and it
     *  should update its local state.
     *
     *  Parameter serial_:
     *  Parameter mods_depressed_:
     *  Parameter mods_latched_:
     *  Parameter mods_locked_:
     *  Parameter group_:
     */
    using modifiers_handler_sig = void (std::uint32_t serial_, std::uint32_t mods_depressed_, std::uint32_t mods_latched_, std::uint32_t mods_locked_, std::uint32_t group_);

    /** Set a handler for the modifiers event
     *  @param handler Callable of signature @ref modifiers_handler_sig
     */
    template <typename T>
    void set_modifiers_handler(T&& handler) {
        _modifiers_handler = std::function<modifiers_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*keymap_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, std::uint32_t);
        void (*enter_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*, const wl_array*);
        void (*leave_handler) (void*, wl_proxy*, std::uint32_t, wl_proxy*);
        void (*key_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
        void (*modifiers_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
    };

    static void keymap_handler(void* data, wl_proxy* wl_obj, std::uint32_t format_, std::int32_t fd_, std::uint32_t size_);
    static void enter_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_, const wl_array* keys_);
    static void leave_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, wl_proxy* surface_);
    static void key_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, std::uint32_t key_, std::uint32_t state_);
    static void modifiers_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t mods_depressed_, std::uint32_t mods_latched_, std::uint32_t mods_locked_, std::uint32_t group_);

    static const listener_t listener;

    std::function<keymap_handler_sig> _keymap_handler;
    std::function<enter_handler_sig> _enter_handler;
    std::function<leave_handler_sig> _leave_handler;
    std::function<key_handler_sig> _key_handler;
    std::function<modifiers_handler_sig> _modifiers_handler;
};

#define WLCPP_TOUCH_VERSION 3

/** touchscreen input device
 *
 *  The wl_touch interface represents a touchscreen associated with a seat.
 *  
 *  Touch interactions can consist of one or more contacts. For each contact, a
 *  series of events is generated, starting with a down event, followed by zero
 *  or more motion events, and ending with an up event. Events relating to the
 *  same contact point can be identified by the ID of the sequence.
 */
class touch final
    : public proxy {
public:
    /** wl_interface for touch */
    static const wl_interface interface;

    /** touch version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** Wrap existing wl_touch object
     *  @param obj Object to wrap
     */
    touch(wl_proxy* obj = nullptr);

    /** Create new touch from factory
     *  @param factory Object which acts as the factory
     */
    explicit touch(proxy& factory);

    /** Default move constructor */
    touch(touch&& rhs) = default;

    /** Destructor */
    virtual ~touch();

    /** Default move assignment operator */
    touch& operator=(touch&& rhs) = default;

    /** touch down event and beginning of a touch sequence
     *
     *  A new touch point has appeared on the surface. This touch point is assigned
     *  a unique @id. Future events from this touchpoint reference this ID. The ID
     *  ceases to be valid after a touch up event and may be re-used in the future.
     *
     *  Parameter serial_:
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter surface_:
     *  Parameter id_: the unique ID of this touch point
     *  Parameter x_: x coordinate in surface-relative coordinates
     *  Parameter y_: y coordinate in surface-relative coordinates
     */
    using down_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, surface& surface_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);

    /** Set a handler for the down event
     *  @param handler Callable of signature @ref down_handler_sig
     */
    template <typename T>
    void set_down_handler(T&& handler) {
        _down_handler = std::function<down_handler_sig>(std::forward<T>(handler));
    }

    /** end of a touch event sequence
     *
     *  The touch point has disappeared. No further events will be sent for this
     *  touchpoint and the touch point's ID is released and may be re-used in a
     *  future touch down event.
     *
     *  Parameter serial_:
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter id_: the unique ID of this touch point
     */
    using up_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, std::int32_t id_);

    /** Set a handler for the up event
     *  @param handler Callable of signature @ref up_handler_sig
     */
    template <typename T>
    void set_up_handler(T&& handler) {
        _up_handler = std::function<up_handler_sig>(std::forward<T>(handler));
    }

    /** update of touch point coordinates
     *
     *  A touchpoint has changed coordinates.
     *
     *  Parameter time_: timestamp with millisecond granularity
     *  Parameter id_: the unique ID of this touch point
     *  Parameter x_: x coordinate in surface-relative coordinates
     *  Parameter y_: y coordinate in surface-relative coordinates
     */
    using motion_handler_sig = void (std::uint32_t time_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);

    /** Set a handler for the motion event
     *  @param handler Callable of signature @ref motion_handler_sig
     */
    template <typename T>
    void set_motion_handler(T&& handler) {
        _motion_handler = std::function<motion_handler_sig>(std::forward<T>(handler));
    }

    /** end of touch frame event
     *
     *  Indicates the end of a contact point list.
     */
    using frame_handler_sig = void ();

    /** Set a handler for the frame event
     *  @param handler Callable of signature @ref frame_handler_sig
     */
    template <typename T>
    void set_frame_handler(T&& handler) {
        _frame_handler = std::function<frame_handler_sig>(std::forward<T>(handler));
    }

    /** touch session cancelled
     *
     *  Sent if the compositor decides the touch stream is a global gesture. No
     *  further events are sent to the clients from that particular gesture. Touch
     *  cancellation applies to all touch points currently active on this client's
     *  surface. The client is responsible for finalizing the touch points, future
     *  touch points on this surface may re-use the touch point ID.
     */
    using cancel_handler_sig = void ();

    /** Set a handler for the cancel event
     *  @param handler Callable of signature @ref cancel_handler_sig
     */
    template <typename T>
    void set_cancel_handler(T&& handler) {
        _cancel_handler = std::function<cancel_handler_sig>(std::forward<T>(handler));
    }

protected:
    void destroy() override;

private:
    struct listener_t {
        void (*down_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, wl_proxy*, std::int32_t, wl_fixed_t, wl_fixed_t);
        void (*up_handler) (void*, wl_proxy*, std::uint32_t, std::uint32_t, std::int32_t);
        void (*motion_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, wl_fixed_t, wl_fixed_t);
        void (*frame_handler) (void*, wl_proxy*);
        void (*cancel_handler) (void*, wl_proxy*);
    };

    static void down_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, wl_proxy* surface_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);
    static void up_handler(void* data, wl_proxy* wl_obj, std::uint32_t serial_, std::uint32_t time_, std::int32_t id_);
    static void motion_handler(void* data, wl_proxy* wl_obj, std::uint32_t time_, std::int32_t id_, wl_fixed_t x_, wl_fixed_t y_);
    static void frame_handler(void* data, wl_proxy* wl_obj);
    static void cancel_handler(void* data, wl_proxy* wl_obj);

    static const listener_t listener;

    std::function<down_handler_sig> _down_handler;
    std::function<up_handler_sig> _up_handler;
    std::function<motion_handler_sig> _motion_handler;
    std::function<frame_handler_sig> _frame_handler;
    std::function<cancel_handler_sig> _cancel_handler;
};

#define WLCPP_OUTPUT_VERSION 2

/** subpixel geometry information
 *
 *  This enumeration describes how the physical pixels on an output are layed
 *  out.
 */
enum output_subpixel {
    OUTPUT_SUBPIXEL_UNKNOWN = 0,
    OUTPUT_SUBPIXEL_NONE = 1,
    OUTPUT_SUBPIXEL_HORIZONTAL_RGB = 2,
    OUTPUT_SUBPIXEL_HORIZONTAL_BGR = 3,
    OUTPUT_SUBPIXEL_VERTICAL_RGB = 4,
    OUTPUT_SUBPIXEL_VERTICAL_BGR = 5,
};

/** transform from framebuffer to output
 *
 *  This describes the transform that a compositor will apply to a surface to
 *  compensate for the rotation or mirroring of an output device.
 *  
 *  The flipped values correspond to an initial flip around a vertical axis
 *  followed by rotation.
 *  
 *  The purpose is mainly to allow clients render accordingly and tell the
 *  compositor, so that for fullscreen surfaces, the compositor will still be
 *  able to scan out directly from client surfaces.
 */
enum output_transform {
    OUTPUT_TRANSFORM_NORMAL = 0,
    OUTPUT_TRANSFORM_90 = 1,
    OUTPUT_TRANSFORM_180 = 2,
    OUTPUT_TRANSFORM_270 = 3,
    OUTPUT_TRANSFORM_FLIPPED = 4,
    OUTPUT_TRANSFORM_FLIPPED_90 = 5,
    OUTPUT_TRANSFORM_FLIPPED_180 = 6,
    OUTPUT_TRANSFORM_FLIPPED_270 = 7,
};

/** mode information
 *
 *  These flags describe properties of an output mode. They are used in the
 *  flags bitfield of the mode event.
 */
enum output_mode {
    OUTPUT_MODE_CURRENT = 0x1, /**< indicates this is the current mode */
    OUTPUT_MODE_PREFERRED = 0x2, /**< indicates this is the preferred mode */
};

/** compositor output region
 *
 *  An output describes part of the compositor geometry. The compositor works in
 *  the 'compositor coordinate system' and an output corresponds to rectangular
 *  area in that space that is actually visible. This typically corresponds to a
 *  monitor that displays part of the compositor space. This object is published
 *  as global during start up, or when a monitor is hotplugged.
 */
class output final
    : public proxy {
public:
    /** wl_interface for output */
    static const wl_interface interface;

    /** output version at wrapper generation time */
    static constexpr std::uint32_t version = 2;

    /** Wrap existing wl_output object
     *  @param obj Object to wrap
     */
    output(wl_proxy* obj = nullptr);

    /** Create new output from factory
     *  @param factory Object which acts as the factory
     */
    explicit output(proxy& factory);

    /** Default move constructor */
    output(output&& rhs) = default;

    /** Default destructor */
    virtual ~output() = default;

    /** Default move assignment operator */
    output& operator=(output&& rhs) = default;

    /** properties of the output
     *
     *  The geometry event describes geometric properties of the output. The event
     *  is sent when binding to the output object and whenever any of the properties
     *  change.
     *
     *  Parameter x_: x position within the global compositor space
     *  Parameter y_: y position within the global compositor space
     *  Parameter physical_width_: width in millimeters of the output
     *  Parameter physical_height_: height in millimeters of the output
     *  Parameter subpixel_: subpixel orientation of the output
     *  Parameter make_: textual description of the manufacturer
     *  Parameter model_: textual description of the model
     *  Parameter transform_: transform that maps framebuffer to output
     */
    using geometry_handler_sig = void (std::int32_t x_, std::int32_t y_, std::int32_t physical_width_, std::int32_t physical_height_, std::int32_t subpixel_, const std::string& make_, const std::string& model_, std::int32_t transform_);

    /** Set a handler for the geometry event
     *  @param handler Callable of signature @ref geometry_handler_sig
     */
    template <typename T>
    void set_geometry_handler(T&& handler) {
        _geometry_handler = std::function<geometry_handler_sig>(std::forward<T>(handler));
    }

    /** advertise available modes for the output
     *
     *  The mode event describes an available mode for the output.
     *  
     *  The event is sent when binding to the output object and there will always be
     *  one mode, the current mode. The event is sent again if an output changes
     *  mode, for the mode that is now current. In other words, the current mode is
     *  always the last mode that was received with the current flag set.
     *  
     *  The size of a mode is given in physical hardware units of the output device.
     *  This is not necessarily the same as the output size in the global compositor
     *  space. For instance, the output may be scaled, as described in
     *  wl_output.scale, or transformed , as described in wl_output.transform.
     *
     *  Parameter flags_: bitfield of mode flags
     *  Parameter width_: width of the mode in hardware units
     *  Parameter height_: height of the mode in hardware units
     *  Parameter refresh_: vertical refresh rate in mHz
     */
    using mode_handler_sig = void (std::uint32_t flags_, std::int32_t width_, std::int32_t height_, std::int32_t refresh_);

    /** Set a handler for the mode event
     *  @param handler Callable of signature @ref mode_handler_sig
     */
    template <typename T>
    void set_mode_handler(T&& handler) {
        _mode_handler = std::function<mode_handler_sig>(std::forward<T>(handler));
    }

    /** sent all information about output
     *
     *  This event is sent after all other properties has been sent after binding to
     *  the output object and after any other property changes done after that. This
     *  allows changes to the output properties to be seen as atomic, even if they
     *  happen via multiple events.
     */
    using done_handler_sig = void ();

    /** Set a handler for the done event
     *  @param handler Callable of signature @ref done_handler_sig
     */
    template <typename T>
    void set_done_handler(T&& handler) {
        _done_handler = std::function<done_handler_sig>(std::forward<T>(handler));
    }

    /** output scaling properties
     *
     *  This event contains scaling geometry information that is not in the geometry
     *  event. It may be sent after binding the output object or if the output scale
     *  changes later. If it is not sent, the client should assume a scale of 1.
     *  
     *  A scale larger than 1 means that the compositor will automatically scale
     *  surface buffers by this amount when rendering. This is used for very high
     *  resolution displays where applications rendering at the native resolution
     *  would be too small to be legible.
     *  
     *  It is intended that scaling aware clients track the current output of a
     *  surface, and if it is on a scaled output it should use
     *  wl_surface.set_buffer_scale with the scale of the output. That way the
     *  compositor can avoid scaling the surface, and the client can supply a higher
     *  detail image.
     *
     *  Parameter factor_: scaling factor of output
     */
    using scale_handler_sig = void (std::int32_t factor_);

    /** Set a handler for the scale event
     *  @param handler Callable of signature @ref scale_handler_sig
     */
    template <typename T>
    void set_scale_handler(T&& handler) {
        _scale_handler = std::function<scale_handler_sig>(std::forward<T>(handler));
    }

private:
    struct listener_t {
        void (*geometry_handler) (void*, wl_proxy*, std::int32_t, std::int32_t, std::int32_t, std::int32_t, std::int32_t, const char*, const char*, std::int32_t);
        void (*mode_handler) (void*, wl_proxy*, std::uint32_t, std::int32_t, std::int32_t, std::int32_t);
        void (*done_handler) (void*, wl_proxy*);
        void (*scale_handler) (void*, wl_proxy*, std::int32_t);
    };

    static void geometry_handler(void* data, wl_proxy* wl_obj, std::int32_t x_, std::int32_t y_, std::int32_t physical_width_, std::int32_t physical_height_, std::int32_t subpixel_, const char* make_, const char* model_, std::int32_t transform_);
    static void mode_handler(void* data, wl_proxy* wl_obj, std::uint32_t flags_, std::int32_t width_, std::int32_t height_, std::int32_t refresh_);
    static void done_handler(void* data, wl_proxy* wl_obj);
    static void scale_handler(void* data, wl_proxy* wl_obj, std::int32_t factor_);

    static const listener_t listener;

    std::function<geometry_handler_sig> _geometry_handler;
    std::function<mode_handler_sig> _mode_handler;
    std::function<done_handler_sig> _done_handler;
    std::function<scale_handler_sig> _scale_handler;
};

#define WLCPP_REGION_VERSION 1

/** region interface
 *
 *  A region object describes an area.
 *  
 *  Region objects are used to describe the opaque and input regions of a
 *  surface.
 */
class region final
    : public proxy {
public:
    /** wl_interface for region */
    static const wl_interface interface;

    /** region version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** Wrap existing wl_region object
     *  @param obj Object to wrap
     */
    region(wl_proxy* obj = nullptr);

    /** Create new region from factory
     *  @param factory Object which acts as the factory
     */
    explicit region(proxy& factory);

    /** Default move constructor */
    region(region&& rhs) = default;

    /** Destructor */
    virtual ~region();

    /** Default move assignment operator */
    region& operator=(region&& rhs) = default;

    /** add rectangle to region
     *
     *  Add the specified rectangle to the region.
     *
     *  @param x_
     *  @param y_
     *  @param width_
     *  @param height_
     */
    void add(std::int32_t x_, std::int32_t y_, std::int32_t width_, std::int32_t height_);

    /** subtract rectangle from region
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

#endif // _WLCPP_

