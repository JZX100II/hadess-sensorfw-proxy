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

#include "dbus_connection_handle.h"
#include "scoped_g_error.h"

#include <stdexcept>

sensorfw_proxy::DBusConnectionHandle::DBusConnectionHandle(std::string const& address)
{
    sensorfw_proxy::ScopedGError error;

    connection = g_dbus_connection_new_for_address_sync(
        address.c_str(),
        GDBusConnectionFlags(
            G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION |
            G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT),
        nullptr,
        nullptr,
        error);

    if (!connection)
    {
        throw std::runtime_error(
            "Failed to connect to DBus bus with address '" +
                address + "': " + error.message_str());
    }
}

sensorfw_proxy::DBusConnectionHandle::~DBusConnectionHandle()
{
    g_dbus_connection_close_sync(connection, nullptr, nullptr);
}

sensorfw_proxy::DBusConnectionHandle::operator GDBusConnection*() const
{
    return connection;
}
