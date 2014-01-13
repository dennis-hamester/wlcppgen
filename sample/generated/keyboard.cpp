
#include "keyboard.hpp"
#include "surface.hpp"

using namespace std;
using namespace wlcpp;

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

static const wl_interface* wl_keyboard_request_release_types[] = { };

static const wl_message wl_keyboard_requests[] = {
    { "release", "3", wl_keyboard_request_release_types },
};

static const wl_interface* wl_keyboard_event_keymap_types[] = { nullptr, nullptr, nullptr };
static const wl_interface* wl_keyboard_event_enter_types[] = { nullptr, &surface::interface, nullptr };
static const wl_interface* wl_keyboard_event_leave_types[] = { nullptr, &surface::interface };
static const wl_interface* wl_keyboard_event_key_types[] = { nullptr, nullptr, nullptr, nullptr };
static const wl_interface* wl_keyboard_event_modifiers_types[] = { nullptr, nullptr, nullptr, nullptr, nullptr };

static const wl_message wl_keyboard_events[] = {
    { "keymap", "uhu", wl_keyboard_event_keymap_types },
    { "enter", "uoa", wl_keyboard_event_enter_types },
    { "leave", "uo", wl_keyboard_event_leave_types },
    { "key", "uuuu", wl_keyboard_event_key_types },
    { "modifiers", "uuuuu", wl_keyboard_event_modifiers_types },
};

const wl_interface keyboard::interface = {
    "wl_keyboard", 3,
    1, wl_keyboard_requests,
    5, wl_keyboard_events
};

const keyboard::listener_t keyboard::listener = {
    &keymap_handler,
    &enter_handler,
    &leave_handler,
    &key_handler,
    &modifiers_handler,
};

keyboard::keyboard(wl_proxy* obj, bool managed)
    : proxy(obj, managed) {
    add_listener(listener);
}

keyboard::keyboard(proxy& factory)
    : proxy(factory, interface) {
    add_listener(listener);
}

keyboard::~keyboard(){
    destroy();
}

void keyboard::destroy() {
    if(valid() && managed()) {
        marshal(0);
    }
    proxy::destroy();
}

void keyboard::keymap_handler(void* data, wl_proxy* wl_obj, uint32_t format_, int32_t fd_, uint32_t size_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_keymap_handler;
    if(handler) {
        handler(format_, fd_, size_);
    }
}

void keyboard::enter_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_, const wl_array* keys_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_enter_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_), *keys_);
    }
}

void keyboard::leave_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, wl_proxy* surface_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_leave_handler;
    if(handler) {
        handler(serial_, *proxy::wrapper_cast<surface>(surface_));
    }
}

void keyboard::key_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t time_, uint32_t key_, uint32_t state_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_key_handler;
    if(handler) {
        handler(serial_, time_, key_, state_);
    }
}

void keyboard::modifiers_handler(void* data, wl_proxy* wl_obj, uint32_t serial_, uint32_t mods_depressed_, uint32_t mods_latched_, uint32_t mods_locked_, uint32_t group_) {
    auto& handler = proxy::user_data_to_wrapper_cast<keyboard>(data)->_modifiers_handler;
    if(handler) {
        handler(serial_, mods_depressed_, mods_latched_, mods_locked_, group_);
    }
}

