/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#pragma once

#include "event_loop.h"
#include "handler_registration.h"

#include <gio/gio.h>

namespace sensorfw_proxy
{

using DBusEventLoopMethodCallHandler =
    std::function<
        void(
            GDBusConnection* connection,
            char const* sender,
            char const* object_path,
            char const* interface_name,
            char const* method_name,
            GVariant* parameters,
            GDBusMethodInvocation* invocation)>;

using DBusEventLoopSignalHandler =
    std::function<
        void(
            GDBusConnection* connection,
            char const* sender,
            char const* object_path,
            char const* interface_name,
            char const* signal_name,
            GVariant* parameters)>;

class DBusEventLoop : public EventLoop
{
public:
    using EventLoop::EventLoop;
};

}
