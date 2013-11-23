#!/usr/bin/python

# Copyright (c) 2013, Dennis Hamester <dennis.hamester@gmail.com>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

wlcppgen_version = (0, 1, 0)

import sys
import getopt
import xml.etree.ElementTree

def mangle_interface_name(name):
    return name.lstrip('wl_')

class ProtocolError(Exception):
    def __init__(self, msg):
        self.msg = msg

class Description:
    def __init__(self, root):
        self.root = root
        if self.root is not None:
            self.text = str()
            text = self.root.text
            if text is not None:
                text_lines = text.splitlines()
                found_first = False
                prev_has_text = False
                for line in text_lines:
                    stripped = line.strip()
                    if stripped == '':
                        prev_has_text = False
                    else:
                        if prev_has_text:
                            self.text += ' '
                        elif found_first:
                            self.text += '\n\n'

                        self.text += stripped
                        found_first = True
                        prev_has_text = True
                while self.text.find('  ') > 0:
                    self.text = self.text.replace('  ', ' ')
            self.summary = self.root.get('summary', None)
        else:
            self.text = None
            self.summary = None

    def generate(self, options, less_width=0):
        result = self.generate_header(options, less_width)
        result.extend(self.generate_footer())
        return result

    def generate_header(self, options, less_width=0):
        if self.summary is None and self.text is None:
            return ['/**']
        result = list()

        if self.summary is not None:
            wrapped_summary = self.wrap(self.summary, options.linewidth - 4 - less_width)
            result.append('/** ' + wrapped_summary[0])
            for line in wrapped_summary[1:]:
                result.append(' *  ' + line)
            if self.text != '':
                result.append(' *')
        else:
            result.append('/**')

        lines = self.text.splitlines()
        for i in range(len(lines)):
            wrapped_lines = self.wrap(lines[i], options.linewidth - 4 - less_width)
            for line in wrapped_lines:
                result.append(' *  ' + line)
            if i != len(lines) - 1 and lines[i + 1] != '':
                result.append(' *  ')

        return result

    def generate_footer(self):
        return [' */']

    def generate_request(self, options, request, less_width=0):
        result = self.generate_header(options, less_width)
        filtered_arguments = list()
        for argument in request.arguments:
            if argument != request.return_argument:
                filtered_arguments.append(argument)

        if (self.summary is not None or self.text is not None) and (request.return_argument is not None or len(filtered_arguments)) > 0:
            result.append(' *')

        for argument in filtered_arguments:
            param_doc = ' *  @param ' + argument.name
            if argument.summary is not None:
                param_doc += ' ' + argument.summary
            result.append(param_doc)

        if request.return_argument is not None:
            return_doc = ' *  @return'
            if request.return_argument.summary is not None:
                return_doc += ' ' + request.return_argument.summary
            result.append(return_doc)

        result.extend(self.generate_footer())
        return result

    def generate_handler_sig(self, options, event, less_width=0):
        result = self.generate_header(options, less_width)
        if len(event.arguments) > 0:
            result.append(' *')
        for argument in event.arguments:
            param_doc = ' *  Parameter ' + argument.name + ':'
            if argument.summary is not None:
                param_doc += ' ' + argument.summary
            result.append(param_doc)
        result.extend(self.generate_footer())
        return result

    def wrap(self, text, width):
        result = list()
        splitted = text.split(' ')
        line = str()
        for word in splitted:
            new_len = len(line) + len(word)
            is_empty = len(line) == 0
            if not is_empty:
                new_len += 1
            if new_len > width:
                result.append(line)
                line = str()
                is_empty = True
            if not is_empty:
                line += ' '
            line += word
        if line != '':
             result.append(line)
        return result

class Argument:
    def __init__(self, root):
        self.root = root
        self.name = self.root.get('name')
        self.argument_type = self.root.get('type')
        self.interface = self.root.get('interface')
        self.allow_null = self.root.get('allow-null') == 'true'
        self.summary = self.root.get('summary')

    def generate_request_parameter_type(self, options):
        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        if self.argument_type == 'int':
            return std_namespace + 'int32_t'
        elif self.argument_type == 'uint':
            return std_namespace + 'uint32_t'
        elif self.argument_type == 'fixed':
            return 'wl_fixed_t'
        elif self.argument_type == 'string':
            if self.allow_null:
                return 'const ' + std_namespace + 'string*'
            else:
                return 'const ' + std_namespace + 'string&'
        elif self.argument_type == 'object':
            if self.interface is not None and not self.allow_null:
                return mangle_interface_name(self.interface) + '&'
            elif self.interface is not None and self.allow_null:
                return mangle_interface_name(self.interface) + '*'
            elif self.interface is None and not self.allow_null:
                return options.proxy + '&'
            elif self.interface is None and self.allow_null:
                return options.proxy + '*'
        elif self.argument_type == 'array':
            if self.allow_null:
                return 'const wl_array*'
            else:
                return 'const wl_array&'
        elif self.argument_type == 'fd':
            return std_namespace + 'int32_t'

    def generate_request_return_type(self, options):
        if self.argument_type == 'new_id':
            if self.interface is None:
                return options.proxy
            else:
                return mangle_interface_name(self.interface)

    def generate_request_parameter(self, options):
        return self.generate_request_parameter_type(options) + ' ' + self.name

    def generate_event_parameter_type(self, options):
        if self.argument_type == 'new_id':
            result = mangle_interface_name(self.interface)
            if self.allow_null:
                result += '*'
            else:
                result += '&&'
            return result
        else:
            return self.generate_request_parameter_type(options)

    def generate_event_parameter(self, options):
        return self.generate_event_parameter_type(options) + ' ' + self.name

    def generate_native_type(self, options):
        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        if self.argument_type == 'int':
            return std_namespace + 'int32_t'
        elif self.argument_type == 'uint':
            return std_namespace + 'uint32_t'
        elif self.argument_type == 'fixed':
            return 'wl_fixed_t'
        elif self.argument_type == 'string':
            return 'const char*'
        elif self.argument_type == 'object':
            return 'wl_proxy*'
        elif self.argument_type == 'array':
            return 'const wl_array*'
        elif self.argument_type == 'fd':
            return std_namespace + 'int32_t'
        elif self.argument_type == 'new_id':
            return 'wl_proxy*'

class Request:
    def __init__(self, root, opcode):
        self.root = root
        self.opcode = opcode
        self.name = self.root.get('name')
        self.since = int(self.root.get('since', 1))
        self.request_type = self.root.get('type')
        self.is_destructor = (self.request_type == 'destructor')
        self.description = Description(self.root.find('description'))
        self.arguments = list()
        self.return_argument = None

        for argument in self.root.iter('arg'):
            new_argument = Argument(argument)
            if new_argument.argument_type == 'new_id':
                if self.return_argument is not None:
                    raise ProtocolError('More than one new_id argument found in request ' + self.name)
                self.return_argument = new_argument
            self.arguments.append(new_argument)

        if self.return_argument is not None and self.return_argument.interface is None:
            self.is_template = True
        else:
            self.is_template = False

    def generate_signature(self, options, class_name=None):
        sig = str()
        if self.is_template:
            sig += 'T '
        elif self.return_argument is not None:
            sig += self.return_argument.generate_request_return_type(options) + ' '
        else:
            sig += 'void '

        if class_name is not None:
            sig += class_name + '::'
        sig += self.name

        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        sig += '('
        for argument in self.arguments:
            if argument.argument_type == 'new_id' and argument.interface is not None:
                continue
            if argument != self.return_argument:
                sig += argument.generate_request_parameter(options)
            elif argument.argument_type == 'new_id' and argument.interface is None:
                sig += std_namespace + 'uint32_t version'
            if argument != self.arguments[-1]:
                sig += ', '

        sig += ')'
        return sig

    def generate_decl(self, options):
        result = list()
        result.extend(self.description.generate_request(options, self))
        result.append(self.generate_signature(options) + ';')
        return result

    def generate_impl(self, options, class_name=None):
        result = list()
        if self.is_template:
            result.extend(self.description.generate_request(options, self))
            result.append('template <typename T>')
        result.append(self.generate_signature(options, class_name) + ' {')

        body = list()
        if self.return_argument is not None:
            return_var = str()
            if self.return_argument.interface is not None:
                return_var += mangle_interface_name(self.return_argument.interface) + ' ' + self.return_argument.name + '(*this);'
            else:
                return_var += 'T ' + self.return_argument.name + '(*this);'
            body.append(return_var)

        marshal_call = 'marshal(' + str(self.opcode)
        for argument in self.arguments:
            marshal_call += ', '
            if argument.argument_type == 'new_id' and argument.interface is None:
                marshal_call += 'T::interface.name, version, '
            if argument.argument_type == 'new_id':
                marshal_call += argument.name + '.wl_obj()'
            elif argument.argument_type == 'string' and argument.allow_null:
                marshal_call += argument.name + ' ? ' + argument.name + '->c_str() : nullptr'
            elif argument.argument_type == 'string' and not argument.allow_null:
                marshal_call += argument.name + '.c_str()'
            elif argument.argument_type == 'object' and argument.allow_null:
                marshal_call += argument.name + ' ? ' + argument.name + '->wl_obj() : nullptr'
            elif argument.argument_type == 'object' and not argument.allow_null:
                marshal_call += argument.name + '.wl_obj()'
            else:
                marshal_call += argument.name
        marshal_call += ');'
        body.append(marshal_call)

        if self.return_argument is not None:
            body.append('return ' + self.return_argument.name + ';')

        result.append(body)
        result.append('}')
        return result

    def generate_types_array(self, options, interface):
        result = 'static const wl_interface* ' + interface.name + '_request_' + self.name + '_types[] = { '
        for argument in self.arguments:
            if argument.argument_type == 'new_id' and argument.interface is None:
                result += 'nullptr, nullptr, nullptr'
            elif (argument.interface is not None) and (argument.argument_type == 'new_id' or argument.argument_type == 'object'):
                result += '&' + mangle_interface_name(argument.interface) + '::interface'
            else:
                result += 'nullptr'

            if argument != self.arguments[-1]:
                result += ', '
        if len(self.arguments) > 0:
            result += ' '
        result += '};'
        return result

    def generate_wl_message(self, options, interface):
        result = '{ "' + self.name + '", "'
        if self.since > 1:
            result += str(self.since)
        for argument in self.arguments:
            if argument.allow_null:
                result += '?'
            if argument.argument_type == 'int':
                result += 'i'
            elif argument.argument_type == 'uint':
                result += 'u'
            elif argument.argument_type == 'fixed':
                result += 'f'
            elif argument.argument_type == 'string':
                result += 's'
            elif argument.argument_type == 'object':
                result += 'o'
            elif argument.argument_type == 'array':
                result += 'a'
            elif argument.argument_type == 'fd':
                result += 'h'
            elif argument.argument_type == 'new_id':
                if argument.interface is None:
                    result += 'su'
                result += 'n'
        result += '", ' + interface.name + '_request_' + self.name + '_types }'
        return result

class Event:
    def __init__(self, root, index):
        self.root = root
        self.index = index
        self.name = self.root.get('name')
        self.since = int(self.root.get('since', 1))
        self.description = Description(self.root.find('description'))
        self.arguments = list()

        for argument in self.root.iter('arg'):
            self.arguments.append(Argument(argument))

    def generate_handler_sig(self, options):
        result = self.description.generate_handler_sig(options, self)
        signature = 'using ' + self.name + '_handler_sig = void ('
        for argument in self.arguments:
            signature += argument.generate_event_parameter(options)
            if argument != self.arguments[-1]:
                signature += ', '
        signature += ');'
        result.append(signature)
        return result

    def generate_set_handler_method(self, options):
        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        result = [
            '/** Set a handler for the ' + self.name + ' event',
            ' *  @param handler Callable of signature @ref ' + self.name + '_handler_sig',
            ' */',
            'template <typename T>',
            'void set_' + self.name + '_handler(T&& handler) {', [
                '_' + self.name + '_handler = ' + std_namespace + 'function<' + self.name + '_handler_sig>(' + std_namespace + 'forward<T>(handler));'
            ],
            '}'
        ]
        return result

    def generate_function_member(self, options):
        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        return std_namespace + 'function<' + self.name + '_handler_sig> _' + self.name + '_handler;'

    def generate_handler_ptr(self, options, interface):
        result = 'void (*' + self.name + '_handler) (void*, wl_proxy*'
        for argument in self.arguments:
            result += ', ' + argument.generate_native_type(options)
        result += ');'
        return result

    def generate_handler_decl(self, options, interface, impl):
        result = str()
        if not impl:
            result += 'static '
        result += 'void '
        if impl:
            result += mangle_interface_name(interface.name) + '::'
        result += self.name + '_handler(void* data, wl_proxy* wl_obj'
        for argument in self.arguments:
            result += ', ' + argument.generate_native_type(options) + ' ' + argument.name
        result += ')'
        return result

    def generate_handler(self, options, interface):
        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        result = [self.generate_handler_decl(options, interface, impl=True) + ' {']
        body = list()
        body.append('auto& handler = ' + options.proxy + '::user_data_to_wrapper_cast<' + mangle_interface_name(interface.name) + '>(data)->_' + self .name + '_handler;')
        body.append('if(handler) {')
        for argument in self.arguments:
            if argument.argument_type == 'new_id' and argument.allow_null:
                new_id_var = mangle_interface_name(argument.interface) + ' ' + argument.name + '_(' + argument.name + ');'
                body.append([new_id_var])
            elif argument.argument_type == 'string' and argument.allow_null:
                string_var = std_namespace + 'string ' + argument.name + '_ = ' + argument.name + ' ? ' + argument.name + ' : ' + std_namespace + 'string();'
                body.append([string_var])

        handler_call = 'handler('
        for argument in self.arguments:
            if argument.argument_type == 'object':
                if not argument.allow_null:
                    handler_call += '*'
                handler_call += options.proxy + '::wrapper_cast<class '
                if argument.interface is None:
                    handler_call += options.proxy
                else:
                    handler_call += mangle_interface_name(argument.interface)
                handler_call += '>(' + argument.name + ')'
            elif argument.argument_type == 'new_id':
                if argument.allow_null:
                    handler_call += argument.name + ' ? &' + argument.name + '_ : nullptr'
                else:
                    handler_call += mangle_interface_name(argument.interface) + '(' + argument.name + ')'
            elif argument.argument_type == 'string' and argument.allow_null:
                handler_call += argument.name + ' ? &' + argument.name + '_' + ' : nullptr'
            elif argument.argument_type == 'array' and not argument.allow_null:
                handler_call += '*' + argument.name
            else:
                handler_call += argument.name
            if argument != self.arguments[-1]:
                handler_call += ', '
        handler_call += ');'
        body.append([handler_call])
        body.append('}')
        result.append(body)
        result.append('}')
        return result

    def generate_types_array(self, options, interface):
        result = 'static const wl_interface* ' + interface.name + '_event_' + self.name + '_types[] = { '
        for argument in self.arguments:
            if (argument.interface is not None) and (argument.argument_type == 'new_id' or argument.argument_type == 'object'):
                result += '&' + mangle_interface_name(argument.interface) + '::interface'
            else:
                result += 'nullptr'

            if argument != self.arguments[-1]:
                result += ', '
        if len(self.arguments) > 0:
            result += ' '
        result += '};'
        return result

    def generate_wl_message(self, options, interface):
        result = '{ "' + self.name + '", "'
        if self.since > 1:
            result += str(self.since)
        for argument in self.arguments:
            if argument.allow_null:
                result += '?'
            if argument.argument_type == 'int':
                result += 'i'
            elif argument.argument_type == 'uint':
                result += 'u'
            elif argument.argument_type == 'fixed':
                result += 'f'
            elif argument.argument_type == 'string':
                result += 's'
            elif argument.argument_type == 'object':
                result += 'o'
            elif argument.argument_type == 'array':
                result += 'a'
            elif argument.argument_type == 'fd':
                result += 'h'
            elif argument.argument_type == 'new_id':
                result += 'n'
        result += '", ' + interface.name + '_event_' + self.name + '_types }'
        return result

class EnumEntry:
    def __init__(self, root):
        self.root = root
        self.name = self.root.get('name')
        self.value = self.root.get('value')
        self.summary = self.root.get('summary')

    def generate(self, options, interface, enum):
        result = mangle_interface_name(interface.name) + '_' + enum.name + '_' + self.name
        result = result.upper()
        result += ' = ' + self.value + ','
        if self.summary is not None:
            result += ' /**< ' + self.summary + ' */'
        return result

class Enum:
    def __init__(self, root):
        self.root = root
        self.name = self.root.get('name')
        self.description = Description(self.root.find('description'))
        self.entries = list()

        for entry in self.root.iter('entry'):
            self.entries.append(EnumEntry(entry))

    def generate(self, options, interface):
        result = list()
        result.extend(self.description.generate(options))
        result.append('enum ' + mangle_interface_name(interface.name) + '_' + self.name + ' {')
        entries = list()
        for entry in self.entries:
            entries.append(entry.generate(options, interface, self))
        result.append(entries)
        result.append('};')
        return result

class Interface:
    def __init__(self, root):
        self.root = root
        self.name = self.root.get('name')
        self.version = int(self.root.get('version'))
        self.description = Description(self.root.find('description'))
        self.requests = list()
        self.events = list()
        self.enums = list()
        self.destructor = None

        opcode = 0
        for request in self.root.iter('request'):
            new_request = Request(request, opcode)
            self.requests.append(new_request)
            if new_request.is_destructor:
                if self.destructor is not None:
                    raise ProtocolError('There is more than one destructor in ' + self.name + '. wlcppgen assumes that at most one destructor exists.')
                self.destructor = new_request
            opcode += 1

        event_index = 0
        for event in self.root.iter('event'):
            self.events.append(Event(event, event_index))
            event_index += 1

        for enum in self.root.iter('enum'):
            self.enums.append(Enum(enum))

    def generate_prototype(self, options):
        return 'class ' + mangle_interface_name(self.name) + ';'

    def generate_wl_obj_ctor(self, options, impl):
        result = str()
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += mangle_interface_name(self.name) + '(wl_proxy* obj'
        if not impl:
            result += ' = nullptr'
        result += ')'
        return result

    def generate_factory_ctor(self, options, impl):
        result = str()
        if not impl:
            result += 'explicit '
        else:
            result += mangle_interface_name(self.name) + '::'
        result += mangle_interface_name(self.name) + '(' + options.proxy + '& factory)'
        return result

    def generate_dtor(self, options, impl):
        result = str()
        if impl:
            result += mangle_interface_name(self.name) + '::'
        else:
            result += 'virtual '
        result += '~' + mangle_interface_name(self.name) + '()'
        return result

    def generate_move_operator(self, options, impl):
        result = mangle_interface_name(self.name) + '& '
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += 'operator=(' + mangle_interface_name(self.name) + '&& rhs)'
        return result

    def generate_interface_decl(self, options, impl):
        result = str()
        if not impl:
            result += 'static '
        result += 'const wl_interface '
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += 'interface'
        return result

    def generate_listener_t(self, options):
        result = ['struct listener_t {']
        members = list()
        for event in self.events:
            members.append(event.generate_handler_ptr(options, self))
        result.append(members)
        result.append('};')
        return result

    def generate_listener(self, options, impl):
        result = str()
        if not impl:
            result += 'static '
        result += 'const '
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += 'listener_t '
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += 'listener'
        return result

    def generate_move_ctor(self, options, impl):
        result = str()
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += mangle_interface_name(self.name) + '(' + mangle_interface_name(self.name) + '&& rhs)'
        return result

    def generate_destroy_method(self, options, impl):
        result = 'void '
        if impl:
            result += mangle_interface_name(self.name) + '::'
        result += 'destroy()'
        if not impl:
            result += ' override'
        return result

    def generate_version_define(self, options):
        return '#define ' + options.macro_prefix + mangle_interface_name(self.name).upper() + '_VERSION ' + str(self.version)

    def generate_class(self, options):
        class_name = mangle_interface_name(self.name)

        result = list()
        result.extend(self.description.generate(options))
        result.extend([
            'class ' + class_name + ' final',
            [': public ' + options.proxy + ' {'],
            'public:'
        ])

        public_part = list()
        public_part.extend([
            '/** wl_interface for ' + class_name + ' */',
            self.generate_interface_decl(options, impl=False) + ';'
        ])

        if options.qualify_std_namespace:
            std_namespace = 'std::'
        else:
            std_namespace = str()

        public_part.extend([
            '',
            '/** ' + class_name + ' version at wrapper generation time */',
            'static constexpr ' + std_namespace + 'uint32_t version = ' + str(self.version) + ';'
        ])

        public_part.extend([
            '',
            '/** Wrap existing ' + self.name + ' object',
            ' *  @param obj Object to wrap',
            ' */',
            self.generate_wl_obj_ctor(options, impl=False) + ';'
        ])

        public_part.extend([
            '',
            '/** Create new ' + class_name + ' from factory',
            ' *  @param factory Object which acts as the factory',
            ' */',
            self.generate_factory_ctor(options, impl=False) + ';'
        ])

        public_part.extend([
            '',
            '/** Default move constructor */',
            self.generate_move_ctor(options, impl=False) + ' = default;'
        ])

        if self.destructor is None:
            public_part.extend([
                '',
                '/** Default destructor */',
                self.generate_dtor(options, impl=False) + ' = default;'
            ])
        else:
            public_part.extend([
                '',
                '/** Destructor */',
                self.generate_dtor(options, impl=False) + ';'
            ])

        public_part.extend([
            '',
            '/** Default move assignment operator */',
            self.generate_move_operator(options, impl=False) + ' = default;'
        ])

        for request in self.requests:
            if request != self.destructor:
                public_part.append('')
                if request.is_template:
                    public_part.extend(request.generate_impl(options))
                else:
                    public_part.extend(request.generate_decl(options))

        if not options.ignore_events:
            for event in self.events:
                public_part.append('')
                public_part.extend(event.generate_handler_sig(options))
                public_part.append('')
                public_part.extend(event.generate_set_handler_method(options))

        result.append(public_part)

        if self.destructor is not None:
            result.append('')
            result.append('protected:')
            protected_part = [
                self.generate_destroy_method(options, impl=False) + ';'
            ]

            result.append(protected_part)

        if not options.ignore_events and len(self.events) > 0:
            result.append('')
            result.append('private:')
            private_part = list()
            private_part.extend(self.generate_listener_t(options))

            private_part.append('')
            for event in self.events:
                private_part.append(event.generate_handler_decl(options, self, impl=False) + ';')

            private_part.append('')
            private_part.append(self.generate_listener(options, impl=False) + ';')

            private_part.append('')
            for event in self.events:
                private_part.append(event.generate_function_member(options))

            result.append(private_part)

        result.append('};')
        return result

    def generate_enums(self, options):
        result = list()
        for enum in self.enums:
            result.extend(enum.generate(options, self))
            if enum != self.enums[-1]:
                result.append('')
        return result

    def generate_requests_message_array(self, options):
        result = ['static const wl_message ' + self.name + '_requests[] = {']
        for request in self.requests:
            result.append([request.generate_wl_message(options, self) + ','])
        result.append('};')
        return result

    def generate_events_message_array(self, options):
        result = ['static const wl_message ' + self.name + '_events[] = {']
        for event in self.events:
            result.append([event.generate_wl_message(options, self) + ','])
        result.append('};')
        return result

    def generate_interface(self, options):
        result = list()
        if len(self.requests) > 0:
            for request in self.requests:
                result.append(request.generate_types_array(options, self))
            result.append('')
            result.extend(self.generate_requests_message_array(options))
            result.append('')
            requests = self.name + '_requests'
        else:
            requests = 'nullptr'

        if len(self.events) > 0:
            for event in self.events:
                result.append(event.generate_types_array(options, self))
            result.append('')
            result.extend(self.generate_events_message_array(options))
            result.append('')
            events = self.name + '_events'
        else:
            events = 'nullptr'

        result.extend([
            self.generate_interface_decl(options, impl=True) + ' = {', [
                '"' + self.name + '", ' + str(self.version) + ',',
                str(len(self.requests)) + ', ' + requests + ',',
                str(len(self.events)) + ', ' + events
            ],
            '};'
        ])

        return result

    def generate_cpp(self, options):
        result = list()
        class_name = mangle_interface_name(self.name)
        have_events = len(self.events) > 0

        result.extend(self.generate_interface(options))

        if not options.ignore_events and have_events:
            result.append('')
            result.append(self.generate_listener(options, impl=True) + ' = {')
            handlers = list()
            for event in self.events:
                handlers.append('&' + event.name + '_handler,')
            result.append(handlers)
            result.append('};')

        result.append('')
        result.append(self.generate_wl_obj_ctor(options, impl=True))
        wl_obj_ctor = list()
        if not options.ignore_events and have_events:
            wl_obj_ctor.extend([
                ': ' + options.proxy + '(obj) {',
                'add_listener(listener);'
            ])
        else:
            wl_obj_ctor.append(': ' + options.proxy + '(obj) {')
        result.append(wl_obj_ctor)
        result.append('}')

        result.append('')
        result.append(self.generate_factory_ctor(options, impl=True))
        factory_ctor = list()
        if not options.ignore_events and have_events:
            factory_ctor.extend([
                ': ' + options.proxy + '(factory, interface) {',
                'add_listener(listener);'
            ])
        else:
            factory_ctor.append(': ' + options.proxy + '(factory, interface) {')
        result.append(factory_ctor)
        result.append('}')

        if self.destructor is not None:
            result.extend([
                '',
                self.generate_dtor(options, impl=True) + '{', [
                    'destroy();'
                ],
                '}'
            ])

        for request in self.requests:
            if request != self.destructor and not request.is_template:
                result.append('')
                result.extend(request.generate_impl(options, mangle_interface_name(self.name)))

        if self.destructor is not None:
            result.append('')
            result.extend([
                self.generate_destroy_method(options, impl=True) + ' {', [
                    'if(valid()) {', [
                        'marshal(' + str(self.destructor.opcode) + ');'
                    ],
                    '}',
                    options.proxy + '::destroy();'
                ],
                '}'
            ])

        if not options.ignore_events:
            for event in self.events:
                result.append('')
                result.extend(event.generate_handler(options, self))

        return result

class Specification:
    def __init__(self, proto_str):
        self.root = xml.etree.ElementTree.fromstring(proto_str)
        self.name = self.root.get("name")
        self.interfaces = list()

        copyright_root = self.root.find("copyright")
        if copyright_root is not None:
            self.copyright = copyright_root.text
        else:
            self.copyright = None

        for interface in self.root.iter('interface'):
            self.interfaces.append(Interface(interface))

    def generate(self, hook, options):
        if hook.id_str == 'spec.hpp.prototypes':
            return self.generate_prototypes(options)
        elif hook.id_str == 'spec.hpp.classes':
            return self.generate_classes(options)
        elif hook.id_str == 'spec.cpp':
            return self.generate_cpp(options)
        elif hook.id_str == 'spec.copyright':
            return self.generate_copyright(options)
        else:
            return ['// Specification target "' + hook.id_str + '" unknown']

    def filtered_interfaces(self, options):
        result = list()
        for interface in self.interfaces:
            if len(options.only) > 0:
                if interface.name in options.only:
                    result.append(interface)
            elif interface.name not in options.exclude:
                result.append(interface)
        return result

    def generate_prototypes(self, options):
        filtered_interfaces = self.filtered_interfaces(options)
        result = list()
        for interface in filtered_interfaces:
            result.append(interface.generate_prototype(options))
        return result

    def generate_classes(self, options):
        filtered_interfaces = self.filtered_interfaces(options)
        result = list()
        for interface in filtered_interfaces:
            result.append(interface.generate_version_define(options))
            result.append('')
            result.extend(interface.generate_enums(options))
            if len(interface.enums) > 0:
                result.append('')
            result.extend(interface.generate_class(options))
            if interface != filtered_interfaces[-1]:
                result.append('')
        return result

    def generate_cpp(self, options):
        filtered_interfaces = self.filtered_interfaces(options)
        result = list()
        for interface in filtered_interfaces:
            result.extend(interface.generate_cpp(options))
            if interface != filtered_interfaces[-1]:
                result.append('')
        return result

    def generate_copyright(self, options):
        result = ['/* The following code was generated from the "' + self.name + '" protocol specification.']
        if self.copyright is not None:
            result.append(' *')
            copyright_lines = self.copyright.strip().splitlines()
            for line in copyright_lines:
                line_stripped = line.strip()
                if line_stripped != '':
                    result.append(' * ' + line_stripped)
                else:
                    result.append(' *')
        else:
            result.append(' * No copyright information was given.')
        result.append(' */')
        return result

class Hook:
    def __init__(self, hook_str):
        self.hook_str = hook_str
        self.root = xml.etree.ElementTree.fromstring(self.hook_str)
        self.id_str = self.root.get('id')
        self.id_path = self.id_str.split('.')
        self.id = self.id_path[0]
        self.options = dict()

        for name, value in self.root.items():
            self.options[name] = value

class HookHandlerIncludeGuard:
    def __init__(self):
        self.id = 'includeguard'

    def generate(self, hook, specs, options):
        target = hook.id_path[1]
        if len(options.include_guard) == 0:
            return list()
        elif target == 'ifndef':
            return ['#ifndef ' + options.include_guard]
        elif target == 'define':
            return ['#define ' + options.include_guard]
        elif target == 'endif':
            return ['#endif // ' + options.include_guard]
        else:
            return ['// HookHandlerIncludeGuard: target "' + target + '" unknown']

class HookHandlerNamespace:
    def __init__(self):
        self.id = 'namespace'

    def generate(self, hook, specs, options):
        target = hook.id_path[1]
        namespaces = options.namespace.split('::')
        result = list()
        if len(namespaces[0]) > 0:
            if target == 'open':
                for namespace in namespaces:
                    result.append('namespace ' + namespace + ' {')
            elif target == 'close':
                namespaces.reverse()
                for namespace in namespaces:
                    result.append('} // namespace ' + namespace)
            elif target == 'using':
                return ['using namespace ' + options.namespace + ';']
            else:
                return ['// HookHandlerNamespaces: target "' + target + '" unknown']
        return result

class HookHandlerSpec:
    def __init__(self):
        self.id = 'spec'

    def generate(self, hook, specs, options):
        result = list()
        for spec in specs:
            result.extend(spec.generate(hook, options))
            if spec is not specs[-1]:
                result.append('')
        return result

class GeneratorOptions:
    def __init__(self):
        self.exclude = list()
        self.ignore_events = False
        self.include_guard = '_WLCPP_'
        self.indent = 4
        self.indent_tabs = False
        self.linewidth = 80
        self.macro_prefix = 'WLCPP_'
        self.namespace = 'wlcpp'
        self.only = list()
        self.proxy = 'proxy'
        self.qualify_std_namespace = False

class SourceTemplate:
    def __init__(self, template_str):
        self.template_str = template_str
        self.template = list()
        self.hookhandlers = dict()

        for name, handler_init in globals().items():
            if name.startswith('HookHandler'):
                handler = handler_init()
                self.hookhandlers[handler.id] = handler

        template_lines = self.template_str.splitlines()
        for line in template_lines:
            if line.startswith('// wlcpp <hook'):
                hook_str = line[9:]
                self.template.append(Hook(hook_str))
            else:
                self.template.append(line)

    def generate(self, specs, options=GeneratorOptions()):
        result = list()
        for item in self.template:
            generated = None
            if type(item) is str:
                result.append(item)
            elif item.id in self.hookhandlers:
                handler = self.hookhandlers[item.id]
                generated = handler.generate(item, specs, options)
                for line in generated:
                    if line is None:
                        continue
                    if type(line) is str:
                        result.append(line)
                    else:
                        result.extend(self.indent_source(line, options.indent_tabs, options.indent))
            else:
                result.append('// Hook "' + item.id + '" unknown')

        return result

    def indent_source(self, src, indent_tabs, indent_incr, indent=0):
        if src is None:
            return None

        if indent_tabs:
            indent_str = indent * '\t'
        else:
            indent_str = indent * ' '

        if type(src) is str:
            if src == '':
                return [src]
            return [indent_str + src]

        result = list()
        for line in src:
            result.extend(self.indent_source(line, indent_tabs, indent_incr, indent + indent_incr))
        return result

class UsageError(Exception):
    def __init__(self, msg):
        self.msg = msg

def print_usage():
    print('wlcppgen [command] [options] [protocols]')
    print()
    print('Available commands:')
    print('  --generate                   Generate wrappers. This is the default command.')
    print('                               Requires --src, --dst and at least one protocol.')
    print('  --help, -h                   Display this help.')
    print('  --list-interfaces            List interfaces in every protocol.')
    print('                               Requires at least one protocol.')
    print('  --version                    Display version.')
    print()
    print('Available options:')
    print('  --dst                        Output filename.')
    print('  --exclude                    Comma-separated list of interfaces to exclude. This is')
    print('                               especially useful for wl_display, because a manually')
    print('                               written wrapper is more useful.')
    print('  --ignore-events              Do not generate code for events.')
    print('  --include-guard (=_WLCPP_)   Name of the include guard.')
    print('  --indent (=4)                Number of spaces or tabs to indent.')
    print('  --indent-tabs                Indent using tabs instead of spaces.')
    print('  --linewidth (=80)            Maximum linewidth. Currently not very useful, because')
    print('                               it is only respected')
    print('                               for comments and indentation is not taken into account.')
    print('  --macro-prefix (=WLCPP_)     Prefix for preprocessor macros (default: "WLCPP_").')
    print('  --namespace (=wlcpp)         The generated code is put into the specified namespace.')
    print('                               Can be empty or an arbitrary namespace (e.g. foo::bar).')
    print('  --only                       Comma-separated list of interfaces to generate wrappers')
    print('                               for. This option takes precedence over --exclude.')
    print('  --proxy (=proxy)             Name of the proxy class.')
    print('  --qualify-std-namespace      Prefix std types with "std::". Should be specified')
    print('                               when generating the header')
    print('  --src                        Source template filename.')

def list_interfaces(specs, options):
    for spec in specs:
        for interface in spec.interfaces:
            if len(options.only) > 0:
                if interface.name in options.only:
                    print(interface.name)
            elif interface.name not in options.exclude:
                print(interface.name)

def print_version():
    print('wlcppgen ', end='')
    print(wlcppgen_version[0], wlcppgen_version[1], wlcppgen_version[2], sep='.')

def main(argv=None):
    if argv is None:
        argv = sys.argv

    commands = set()
    spec_files = list()
    src_file = None
    dst_file = None
    options = GeneratorOptions()

    try:
        try:
            opts, args = getopt.getopt(argv[1:], 'h', [
                # Commands
                'generate',
                'help',
                'list-interfaces',
                'version',
                # Options
                'src=', 'dst=',
                'exclude=',
                'ignore-events',
                'include-guard=',
                'indent=',
                'indent-tabs',
                'linewidth=',
                'macro-prefix=',
                'namespace=',
                'only=',
                'proxy=',
                'qualify-std-namespace'
            ])

            for opt, val in opts:
                # Commands
                if opt == '--generate':
                    commands.add('generate')
                elif opt in ['-h', '--help']:
                    commands.add('help')
                elif opt == '--list-interfaces':
                    commands.add('list-interfaces')
                elif opt == '--version':
                    commands.add('version')
                # Options
                elif opt == '--src':
                    src_file = val
                elif opt == '--dst':
                    dst_file = val
                elif opt == '--exclude':
                    options.exclude = val.split(',')
                elif opt == '--ignore-events':
                    options.ignore_events = True
                elif opt == '--include-guard':
                    options.include_guard = val
                elif opt == '--indent':
                    options.indent = int(val)
                elif opt == '--indent-tabs':
                    options.indent_tabs = True
                elif opt == '--linewidth':
                    options.linewidth = int(val)
                elif opt == '--macro-prefix':
                    options.macro_prefix = val
                elif opt == '--namespace':
                    options.namespace = val
                elif opt == '--only':
                    options.only = val.split(',')
                elif opt == '--proxy':
                    options.proxy = val
                elif opt == '--qualify-std-namespace':
                    options.qualify_std_namespace = True

            # Check that only one command is given and default to generate
            if len(commands) == 0:
                commands.add('generate')

            if len(commands) > 1:
                raise UsageError('More than one command was given')

            # Check required options for each command
            if 'generate' in commands:
                if src_file is None:
                    raise UsageError('--src must be specified')
                if dst_file is None:
                    raise UsageError('--dst must be specified')

            if commands.intersection(['generate', 'list-interfaces']):
                if len(args) == 0:
                    raise UsageError('Path to at least one protocol specification must be given')
                else:
                    spec_files = args

            # Read source template
            if 'generate' in commands:
                with open(src_file) as f:
                    src_hpp_template = SourceTemplate(f.read())

            # Read protocols
            if commands.intersection(['generate', 'list-interfaces']):
                specs = list()
                for spec_file in spec_files:
                    with open(spec_file) as f:
                        specs.append(Specification(f.read()))

            # Execute specified command
            if 'generate' in commands:
                result = src_hpp_template.generate(specs, options)
                with open(dst_file, 'w') as f:
                    for line in result:
                        f.write(line)
                        f.write('\n')

            if 'help' in commands:
                print_usage()

            if 'list-interfaces' in commands:
                list_interfaces(specs, options)

            if 'version' in commands:
                print_version()

        except getopt.error as msg:
            raise UsageError(msg)
    except UsageError as err:
        print(err.msg)
        print('Use --help to display usage information')
        return 1

    return 0

if __name__ == '__main__':
    sys.exit(main())

