/*
 * This file is part of QStomp
 *
 * Copyright (C) 2009 Patrick Schneider <patrick.p2k.schneider@googlemail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef QSTOMP_P_H
#define QSTOMP_P_H

#include <QtCore/QObject>

class QStompFramePrivate
{
public:
	QStompHeaderList m_header;
	bool m_valid;
	QByteArray m_body;
	const QTextCodec * m_textCodec;
};

class QStompResponseFramePrivate : public QStompFramePrivate
{
public:
	QStompResponseFrame::ResponseType m_type;
};

class QStompRequestFramePrivate : public QStompFramePrivate
{
public:
	QStompRequestFrame::RequestType m_type;
};

class QStompClientPrivate
{
public:
	QTcpSocket * m_socket;
	const QTextCodec * m_textCodec;

	QByteArray m_buffer;
	QList<QStompResponseFrame> m_framebuffer;

	quint32 findMessageBytes();
};

#endif // QSTOMP_P_H
