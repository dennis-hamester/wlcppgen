
#include "shell.hpp"
#include "shell_surface.hpp"
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

static const wl_interface* wl_shell_request_get_shell_surface_types[] = { &shell_surface::interface, &surface::interface };

static const wl_message wl_shell_requests[] = {
    { "get_shell_surface", "no", wl_shell_request_get_shell_surface_types },
};

const wl_interface shell::interface = {
    "wl_shell", 1,
    1, wl_shell_requests,
    0, nullptr
};

shell::shell(wl_proxy* obj)
    : proxy(obj) {
}

shell::shell(proxy& factory)
    : proxy(factory, interface) {
}

shell_surface shell::get_shell_surface(surface& surface_) {
    shell_surface id_(*this);
    marshal(0, id_.wl_obj(), surface_.wl_obj());
    return id_;
}

