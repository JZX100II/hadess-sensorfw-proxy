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

#include "sensorfw_orientation_sensor.h"
#include "event_loop_handler_registration.h"

#include "socketreader.h"

namespace
{
auto const null_handler = [](sensorfw_proxy::OrientationData){};
}

sensorfw_proxy::SensorfwOrientationSensor::SensorfwOrientationSensor(
    std::shared_ptr<Log> const &log,
    std::string const &dbus_bus_address)
    : Sensorfw(log, dbus_bus_address, "Orientation", PluginType::ORIENTATION),
      handler{null_handler}
{
}

sensorfw_proxy::HandlerRegistration sensorfw_proxy::SensorfwOrientationSensor::register_orientation_handler(
    OrientationHandler const &handler)
{
    return EventLoopHandlerRegistration{
        dbus_event_loop,
        [this, &handler]{ this->handler = handler; },
        [this]{ this->handler = null_handler; }};
}

void sensorfw_proxy::SensorfwOrientationSensor::enable_orientation_events()
{
    dbus_event_loop.enqueue(
        [this]
        {
            start();
        }).get();
}

void sensorfw_proxy::SensorfwOrientationSensor::disable_orientation_events()
{
    dbus_event_loop.enqueue(
        [this]
        {
            stop();
        }).get();
}

void sensorfw_proxy::SensorfwOrientationSensor::data_recived_impl()
{
    QVector<PoseData> values;
    sensorfw_proxy::OrientationData output;
    if (m_socket->read<PoseData>(values))
        output = (sensorfw_proxy::OrientationData) values[0].orientation_;

    handler(output);
}
