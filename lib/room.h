/******************************************************************************
 * Copyright (C) 2015 Felix Rohrbach <kde@fxrh.de>
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

#ifndef QMATRIXCLIENT_ROOM_H
#define QMATRIXCLIENT_ROOM_H

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QJsonObject>

namespace QMatrixClient
{
    class LogMessage;

    class Room: public QObject
    {
            Q_OBJECT
        public:
            Room(QString id);
            virtual ~Room();

            QString id() const;
            QList<LogMessage*> logMessages() const;
            QString alias() const;

            void addMessages(const QList<LogMessage*>& messages);
            void addMessage( LogMessage* message );
            void setAlias( QString alias );

            bool parseEvents(const QJsonObject& json);
            bool parseSingleEvent(const QJsonObject& json);
            bool parseState(const QJsonObject& json);

        signals:
            void newMessages(QList<LogMessage*> messages);
            void aliasChanged(Room* room);

        private:
            class Private;
            Private* d;
    };
}

#endif // QMATRIXCLIENT_ROOM_H