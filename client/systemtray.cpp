/******************************************************************************
 * Copyright (C) 2016 Felix Rohrbach <kde@fxrh.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "systemtray.h"

#include <QtWidgets/QWidget>

#include "lib/connection.h"
#include "lib/room.h"

SystemTray::SystemTray(QWidget* parent)
    : QSystemTrayIcon(parent)
    , m_connection(0)
    , m_parent(parent)
{
    setIcon(QIcon(":/icon.png"));
}

void SystemTray::setConnection(QMatrixClient::Connection* connection)
{
    if( m_connection )
    {
        disconnect(m_connection, &QMatrixClient::Connection::newRoom, this, &SystemTray::newRoom);
    }
    m_connection = connection;
    if( m_connection )
    {
        connect(m_connection, &QMatrixClient::Connection::newRoom, this, &SystemTray::newRoom);
    }
}

void SystemTray::newRoom(QMatrixClient::Room* room)
{
    connect(room, &QMatrixClient::Room::highlightCountChanged, this, &SystemTray::highlightCountChanged);
}

void SystemTray::highlightCountChanged(QMatrixClient::Room* room)
{
    if( room->highlightCount() > 0 )
    {
        showMessage(tr("Highlight!"), tr("%1: %2 highlight(s)").arg(room->displayName()).arg(room->highlightCount()));
        m_parent->raise();
    }
}
