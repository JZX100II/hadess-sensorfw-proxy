/*
 * Copyright © 2020 UBports foundation
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
 * Authored by: Marius Gripsgard <marius@ubports.com>
 */

#pragma once

#include "dbus_connection_handle.h"
#include "dbus_event_loop.h"

#include "log.h"

class SocketReader;
namespace sensorfw_proxy {
class Sensorfw {
public:
    enum PluginType
    {
        LIGHT,
        PROXIMITY,
        ORIENTATION,
        COMPASS
    };

    Sensorfw(
        std::shared_ptr<Log> const& log,
        std::string const& dbus_bus_address,
        std::string const& name,
        PluginType const& plugin);
    virtual ~Sensorfw();

protected:
    virtual void data_recived_impl() = 0;

    void start();
    void stop();

    std::shared_ptr<Log> const log;
    DBusConnectionHandle dbus_connection;
    DBusEventLoop dbus_event_loop;
    std::shared_ptr<SocketReader> m_socket;

private:
    void request_sensor();
    bool release_sensor();
    bool load_plugin();

    const char* plugin_string() const;
    const char* plugin_interface() const;
    const char* plugin_path() const;

    std::thread read_loop;
    HandlerRegistration dbus_signal_handler_registration;
    PluginType m_plugin;
    pid_t m_pid;
    int m_sessionid;
    bool m_running = false;
};
}
