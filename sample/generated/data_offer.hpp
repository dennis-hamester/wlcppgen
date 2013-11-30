
#ifndef _DATA_OFFER_HPP_
#define _DATA_OFFER_HPP_

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


#define WLCPP_DATA_OFFER_VERSION 1

/** \brief offer to transfer data
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
    /** \brief wl_interface for @ref data_offer */
    static const wl_interface interface;

    /** \brief @ref data_offer version at wrapper generation time */
    static constexpr std::uint32_t version = 1;

    /** \brief Wrap existing wl_data_offer object
     *  @param obj Existing native object to wrap, can be nullptr
     */
    data_offer(wl_proxy* obj = nullptr);

    /** \brief Create new @ref data_offer from factory
     *  @param factory Object which acts as the factory
     */
    explicit data_offer(proxy& factory);

    /** \brief Default move constructor */
    data_offer(data_offer&& rhs) = default;

    /** \brief Destructor */
    virtual ~data_offer();

    /** \brief Default move assignment operator */
    data_offer& operator=(data_offer&& rhs) = default;

    /** \brief accept one of the offered mime types
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

    /** \brief request that the data is transferred
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

    /** \brief advertise offered mime type
     *
     *  Sent immediately after creating the wl_data_offer object. One event per
     *  offered mime type.
     *
     *  @param mime_type_
     */
    using offer_handler_sig = void (const std::string& mime_type_);

    /** \brief Set a handler for the offer event
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

} // namespace wlcpp

#endif // _DATA_OFFER_HPP_

