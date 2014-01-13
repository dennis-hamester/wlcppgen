
#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_

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

class surface;

#define WLCPP_KEYBOARD_VERSION 3

/** \brief keyboard mapping format
 *
 *  This specifies the format of the keymap provided to the client with the
 *  wl_keyboard.keymap event.
 */
enum keyboard_keymap_format {
    KEYBOARD_KEYMAP_FORMAT_NO_KEYMAP = 0, /**< no keymap; client must understand how to interpret the raw keycode */
    KEYBOARD_KEYMAP_FORMAT_XKB_V1 = 1, /**< libxkbcommon compatible */
};

/** \brief physical key state
 *
 *  Describes the physical state of a key which provoked the key event.
 */
enum keyboard_key_state {
    KEYBOARD_KEY_STATE_RELEASED = 0, /**< key is not pressed */
    KEYBOARD_KEY_STATE_PRESSED = 1, /**< key is pressed */
};

/** \brief keyboard input device
 *
 *  The wl_keyboard interface represents one or more keyboards associated with a
 *  seat.
 */
class keyboard final
    : public proxy {
public:
    /** \brief wl_interface for @ref keyboard */
    static const wl_interface interface;

    /** \brief @ref keyboard version at wrapper generation time */
    static constexpr std::uint32_t version = 3;

    /** \brief Wrap existing wl_keyboard object
     *  @param obj Existing native object to wrap, can be nullptr
     *  @param managed true, if the new wrapper object owns the wl_keyboard object and is responsible for destryoing it
     */
    keyboard(wl_proxy* obj = nullptr, bool managed = true);

    /** \brief Create new @ref keyboard from factory
     *  @param factory Object which acts as the factory
     */
    explicit keyboard(proxy& factory);

    /** \brief Default move constructor */
    keyboard(keyboard&& rhs) = default;

    /** \brief Destructor */
    virtual ~keyboard();

    /** \brief Default move assignment operator */
    keyboard& operator=(keyboard&& rhs) = default;

    /** \brief keyboard mapping
     *
     *  This event provides a file descriptor to the client which can be
     *  memory-mapped to provide a keyboard mapping description.
     *
     *  @param format_
     *  @param fd_
     *  @param size_
     */
    using keymap_handler_sig = void (std::uint32_t format_, std::int32_t fd_, std::uint32_t size_);

    /** \brief Set a handler for the keymap event
     *  @param handler Callable of signature @ref keymap_handler_sig
     */
    template <typename T>
    void set_keymap_handler(T&& handler) {
        _keymap_handler = std::function<keymap_handler_sig>(std::forward<T>(handler));
    }

    /** \brief enter event
     *
     *  Notification that this seat's keyboard focus is on a certain surface.
     *
     *  @param serial_
     *  @param surface_
     *  @param keys_ the currently pressed keys
     */
    using enter_handler_sig = void (std::uint32_t serial_, surface& surface_, const wl_array& keys_);

    /** \brief Set a handler for the enter event
     *  @param handler Callable of signature @ref enter_handler_sig
     */
    template <typename T>
    void set_enter_handler(T&& handler) {
        _enter_handler = std::function<enter_handler_sig>(std::forward<T>(handler));
    }

    /** \brief leave event
     *
     *  Notification that this seat's keyboard focus is no longer on a certain
     *  surface.
     *
     *  The leave notification is sent before the enter notification for the new
     *  focus.
     *
     *  @param serial_
     *  @param surface_
     */
    using leave_handler_sig = void (std::uint32_t serial_, surface& surface_);

    /** \brief Set a handler for the leave event
     *  @param handler Callable of signature @ref leave_handler_sig
     */
    template <typename T>
    void set_leave_handler(T&& handler) {
        _leave_handler = std::function<leave_handler_sig>(std::forward<T>(handler));
    }

    /** \brief key event
     *
     *  A key was pressed or released. The time argument is a timestamp with
     *  millisecond granularity, with an undefined base.
     *
     *  @param serial_
     *  @param time_ timestamp with millisecond granularity
     *  @param key_
     *  @param state_
     */
    using key_handler_sig = void (std::uint32_t serial_, std::uint32_t time_, std::uint32_t key_, std::uint32_t state_);

    /** \brief Set a handler for the key event
     *  @param handler Callable of signature @ref key_handler_sig
     */
    template <typename T>
    void set_key_handler(T&& handler) {
        _key_handler = std::function<key_handler_sig>(std::forward<T>(handler));
    }

    /** \brief modifier and group state
     *
     *  Notifies clients that the modifier and/or group state has changed, and it
     *  should update its local state.
     *
     *  @param serial_
     *  @param mods_depressed_
     *  @param mods_latched_
     *  @param mods_locked_
     *  @param group_
     */
    using modifiers_handler_sig = void (std::uint32_t serial_, std::uint32_t mods_depressed_, std::uint32_t mods_latched_, std::uint32_t mods_locked_, std::uint32_t group_);

    /** \brief Set a handler for the modifiers event
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

} // namespace wlcpp

#endif // _KEYBOARD_HPP_

