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

#include "dbus_event_loop.h"
#include "event_loop_handler_registration.h"
#include "scoped_g_error.h"

namespace
{

// Send a synchronous request to ensure all previous requests have
// reached the dbus daemon
void repowerd_g_dbus_connection_wait_for_requests(GDBusConnection* connection)
{
    int const timeout_default = -1;
    auto const null_cancellable = nullptr;
    auto const null_args = nullptr;
    auto const null_return_args_types = nullptr;
    auto const null_error = nullptr;

    auto result = g_dbus_connection_call_sync(
        connection,
        "org.freedesktop.DBus",
        "/org/freedesktop/DBus",
        "org.freedesktop.DBus",
        "GetId",
        null_args,
        null_return_args_types,
        G_DBUS_CALL_FLAGS_NONE,
        timeout_default,
        null_cancellable,
        null_error);

    g_variant_unref(result);
}

}
