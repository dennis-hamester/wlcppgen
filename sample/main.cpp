
#include <functional>
#include <iostream>
#include <map>
#include <poll.h>
#include "display.hpp"
#include "wlcpp.hpp"

using namespace std;
using namespace std::placeholders;

wlcpp::display display;
wlcpp::registry registry;
wlcpp::compositor compositor;
wlcpp::shm shm;
map<uint32_t, wlcpp::seat> seats;
map<uint32_t, wlcpp::output> outputs;

static void shm_format_handler(uint32_t format) {
    cout << "shm::format(" << format << ")" << endl;
}

static void seat_capabilities_handler(uint32_t seat_name, uint32_t capabilities) {
    cout << "seat::capabilities(" << seat_name << ", " << capabilities << ")" << endl;
}

static void seat_name_handler(uint32_t seat_name, const string& name) {
    cout << "seat::name(" << seat_name << ", \"" << name << "\")" << endl;
}

static void output_geometry_handler(uint32_t output_name, int32_t x, int32_t y, int32_t physical_width, int32_t physical_height, int32_t subpixel, const string& make, const string& model, int32_t transform) {
    cout << "output::geometry(" << output_name << ", " << x << ", " << y << ", " << physical_width << ", " << physical_height << ", " << subpixel << ", \"" << make << "\", \"" << model << "\", " << transform << ")" << endl;
}

static void output_mode_handler(uint32_t output_name, uint32_t flags, int32_t width, int32_t height, int32_t refresh) {
    cout << "output::mode(" << output_name << ", " << flags << ", " << width << ", " << height << ", " << refresh << ")" << endl;
}

static void output_done_handler(uint32_t output_name) {
    cout << "output::done(" << output_name << ")" << endl;
}

static void output_scale_handler(uint32_t output_name, int32_t factor) {
    cout << "output::scale(" << output_name << ", " << factor << ")" << endl;
}

static void registry_global_handler(uint32_t name, const string& interface, uint32_t version) {
    cout << "registry::global(" << name << ", \"" << interface  << "\", " << version << ")" << endl;

    if(!compositor && (interface == wlcpp::compositor::interface.name)) {
        compositor = registry.bind<wlcpp::compositor>(name, version);
    }
    else if(!shm && (interface == wlcpp::shm::interface.name)) {
        shm = registry.bind<wlcpp::shm>(name, version);
        shm.set_format_handler(&shm_format_handler);
    }
    else if(interface == wlcpp::seat::interface.name) {
        wlcpp::seat seat = registry.bind<wlcpp::seat>(name, version);
        seat.set_name_handler(bind(&seat_name_handler, name, _1));
        seat.set_capabilities_handler(bind(&seat_capabilities_handler, name, _1));
        seats.emplace(name, move(seat));
    }
    else if(interface == wlcpp::output::interface.name) {
        wlcpp::output output = registry.bind<wlcpp::output>(name, version);
        output.set_geometry_handler(bind(&output_geometry_handler, name, _1, _2, _3, _4, _5, _6, _7, _8));
        output.set_mode_handler(bind(&output_mode_handler, name, _1, _2, _3, _4));
        output.set_done_handler(bind(&output_done_handler, name));
        output.set_scale_handler(bind(output_scale_handler, name, _1));
        outputs.emplace(name, move(output));
    }
}

static void registry_global_remove_handler(uint32_t name) {
    cout << "registry::global_remove(" << name << ")" << endl;

    seats.erase(name);
    outputs.erase(name);
}

int main(int argc, char* argv[]) {
    display = wlcpp::display(string());
    if(!display) {
        cerr << "Failed to connect to Wayland display" << endl;
        return 1;
    }

    registry = display.get_registry();
    registry.set_global_handler(&registry_global_handler);
    registry.set_global_remove_handler(&registry_global_remove_handler);

    pollfd pfd = {
        display.get_fd(),
        POLLIN | POLLOUT,
        0
    };

    while(true) {
        if(!(pfd.events & POLLOUT)) {
            display.flush();
        }

        if(poll(&pfd, 1, 1000) > 0) {
            if(pfd.revents & POLLIN) {
                display.dispatch();
            }

            if(pfd.revents & POLLHUP) {
                pfd.events = POLLIN | POLLOUT;
            }

            if(pfd.revents & POLLOUT) {
                pfd.events = POLLIN;
            }
        }
        else {
            break;
        }
    }

    return 0;
}

