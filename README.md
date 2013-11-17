wlcppgen
========
C++11 wrapper generator for Wayland client-side protocols


Features
--------
* Pure C++11!
* Extensively customizable
* No external dependencies besides Python 3 to generate the wrapper
* Also generates wrappers for extensions protocols, not just the Wayland core protocol
* Does not depend on code generated by the Wayland scanner (specifically, declarations in wayland-client-protocol.h are not used)
* All calls to the Wayland client API happen from a common base class *proxy*, which has to be written manually. This way you can easily write a custom *proxy* class that *dlopen*s libwayland-client.so at runtime instead of linking against it. This not so easily possible with code generated by the Wayland scanner.
* Everything that is callable can be used as an event handler: function pointers, member function pointers, bind expressions, function objects and lambda expressions.


Usage
-----
<pre>
wlcppgen [OPTIONS] protocol-specifications

At least one protocol specification must be given.

The following options are mandatory:
      --src                        Source template.
      --dst                        Output file name.

These are optional:
  -h, --help                       Display this help.
      --version                    Display version.
      --exclude                    Comma-separated list of interfaces to exclude. This is
                                   especially useful for wl_display, because a manually
                                   written wrapper is more useful.
      --include-guard (=_WLCPP_)   Name of the include guard.
      --indent (=4)                Number of spaces or tabs to indent.
      --indent_tabs                Indent using tabs instead of spaces.
      --linewidth (=80)            Maximum linewidth. Currently not very useful, because
                                   it is only respected
                                   for comments and indentation is not taken into account.
      --macro-prefix (=WLCPP_)     Prefix for preprocessor macros (default: "WLCPP_").
      --namespace (=wlcpp)         The generated code is put into the specified namespace.
                                   Can be empty or an arbitrary namespace (e.g. foo::bar).
      --only                       Comma-separated list of interfaces to generate wrappers
                                   for. This option takes precedence over --exclude.
      --proxy (=proxy)             Name of the proxy class.
      --qualify-std-namespace      Prefix std types with "std::". Should be specified
                                   when generating the header
</pre>

wlcppgen comes with a small pre-generated sample [here](https://github.com/dennishamester/wlcppgen/tree/master/sample). See [generate.sh](https://github.com/dennishamester/wlcppgen/blob/master/sample/generate.sh) on how that specific wrapper was generated. It's a good place to start.

The sample client does not do much except print information about global objects. Patches are welcome :-)


How things are mapped to C++
----------------------------

* There is a common base class for all interfaces named *proxy* by default. The *proxy* class has to be written manually, but an example is provided [here](https://github.com/dennishamester/wlcppgen/blob/master/sample/proxy.hpp) and [here](https://github.com/dennishamester/wlcppgen/blob/master/sample/proxy.cpp).
* The auto-generated class for *wl_display* is not very useful since it does not include special *wl_display* functions declared in wayland-client.h. Instead, I suggest to use the one provided in the [/sample](https://github.com/dennishamester/wlcppgen/tree/master/sample) directory or write your own.
* *proxy* sets itself (*this*) as the user data of the *wl_proxy* objects. This is required for event dispatching. The downside is that setting user data is no longer available to clients. But since you can use member functions and bind expressions as event handlers, this is also not required anymore.
* Request and event arguments that are can be null are passed as pointers. References or value types are used otherwise.
* Destructor requests (usually called *destroy* or *release* in case of *wl_{pointer,keyboard,touch}*) are not exposed directly to clients but implemented in a protected destroy member function which is called from the actual destructor and the move assignment operator.
* Requests that return a *new_id* but do not specify the interface are implemented as template member functions. To the best of my knowledge *wl_registry::bind* is the only such request.
* Setting custom dispatchers through *wl_proxy_add_dispatcher* is not possible.


Installation
------------
There is not much to install. Just copy [wlcppgen.py](https://github.com/dennishamester/wlcppgen/blob/master/wlcppgen.py) over to /usr/bin and you're done. It's probably best if you also strip the .py extension and just name it wlcppgen.

It is important to note that the generated code is **not** meant to be installed system-wide. You should compile it directly into your client application.


License
-------
wlcppgen is distributed under the ISC license. See [COPYING](https://github.com/dennishamester/wlcppgen/blob/master/COPYING).

Please note that some code under [/sample](https://github.com/dennishamester/wlcppgen/tree/master/sample) is auto-generated from the Wayland core protocol specification which is copyrighted by Kristian Høgsberg and others.

