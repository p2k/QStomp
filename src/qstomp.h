/*
 * This file is part of QStomp
 *
 * Copyright (C) 2009 Patrick Schneider <patrick.p2k.schneider@googlemail.com>
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; see the file
 * COPYING.LESSER.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QSTOMP_H
#define QSTOMP_H

#include "qstomp_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtNetwork/QAbstractSocket>

class QTcpSocket;
class QAuthenticator;
class QTextCodec;

class QStompFramePrivate;
class QStompResponseFramePrivate;
class QStompRequestFramePrivate;
class QStompClientPrivate;

typedef QList< QPair<QByteArray, QByteArray> > QStompHeaderList;

class QSTOMPSHARED_EXPORT QStompFrame
{
public:
	QStompFrame();
	QStompFrame(const QStompFrame &other);
	QStompFrame(const QByteArray &frame);
	virtual ~QStompFrame();

	QStompFrame &operator=(const QStompFrame &other);

	void setHeaderValue(const QByteArray &key, const QByteArray &value);
	void setHeaderValues(const QStompHeaderList &values);
	void addHeaderValue(const QByteArray &key, const QByteArray &value);
	QStompHeaderList header() const;
	bool headerHasKey(const QByteArray &key) const;
	QList<QByteArray> headerKeys() const;
	QByteArray headerValue(const QByteArray &key) const;
	QList<QByteArray> allHeaderValues(const QByteArray &key) const;
	void removeHeaderValue(const QByteArray &key);
	void removeAllHeaderValues(const QByteArray &key);

	bool hasContentLength() const;
	uint contentLength() const;
	void setContentLength(uint len);
	bool hasContentType() const;
	QByteArray contentType() const;
	void setContentType(const QByteArray &type);
	bool hasContentEncoding() const;
	QByteArray contentEncoding() const;
	void setContentEncoding(const QByteArray & name);
	void setContentEncoding(const QTextCodec * codec);

	virtual QByteArray toByteArray() const;
	bool isValid() const;

	QString body() const;
	QByteArray rawBody() const;

	void setBody(const QString &body);
	void setRawBody(const QByteArray &body);

protected:
	virtual bool parseHeaderLine(const QByteArray &line, int number);
	bool parse(const QByteArray &str);
	void setValid(bool);

private:
	QStompFramePrivate * const d;
};

class QSTOMPSHARED_EXPORT QStompResponseFrame : public QStompFrame
{
public:
	enum ResponseType {
		ResponseInvalid = 0,
		ResponseConnected,
		ResponseMessage,
		ResponseReceipt,
		ResponseError
	};

	QStompResponseFrame();
	QStompResponseFrame(const QStompResponseFrame &other);
	QStompResponseFrame(const QByteArray &frame);
	QStompResponseFrame(ResponseType type);
	QStompResponseFrame &operator=(const QStompResponseFrame &other);
	~QStompResponseFrame();

	void setType(ResponseType type);
	ResponseType type();

	bool hasDestination() const;
	QByteArray destination() const;
	void setDestination(const QByteArray &value);

	bool hasSubscriptionId() const;
	QByteArray subscriptionId() const;
	void setSubscriptionId(const QByteArray &value);

	bool hasMessageId() const;
	QByteArray messageId() const;
	void setMessageId(const QByteArray &value);

	bool hasReceiptId() const;
	QByteArray receiptId() const;
	void setReceiptId(const QByteArray &value);

	bool hasMessage() const;
	QByteArray message() const;
	void setMessage(const QByteArray &value);

	QByteArray toByteArray() const;

protected:
	bool parseHeaderLine(const QByteArray &line, int number);

private:
	QStompResponseFramePrivate * const dd;
};

class QSTOMPSHARED_EXPORT QStompRequestFrame : public QStompFrame
{
public:
	enum RequestType {
		RequestInvalid = 0,
		RequestConnect,
		RequestSend,
		RequestSubscribe,
		RequestUnsubscribe,
		RequestBegin,
		RequestCommit,
		RequestAbort,
		RequestAck,
		RequestDisconnect
	};
	enum AckType {
		AckAuto = 0,
		AckClient
	};

	QStompRequestFrame();
	QStompRequestFrame(const QStompRequestFrame &other);
	QStompRequestFrame(const QByteArray &frame);
	QStompRequestFrame(RequestType type);
	QStompRequestFrame &operator=(const QStompRequestFrame &other);
	~QStompRequestFrame();

	void setType(RequestType type);
	RequestType type();

	bool hasDestination() const;
	QByteArray destination() const;
	void setDestination(const QByteArray &value);

	bool hasTransactionId() const;
	QByteArray transactionId() const;
	void setTransactionId(const QByteArray &value);

	bool hasMessageId() const;
	QByteArray messageId() const;
	void setMessageId(const QByteArray &value);

	bool hasReceiptId() const;
	QByteArray receiptId() const;
	void setReceiptId(const QByteArray &value);

	bool hasAckType() const;
	AckType ackType() const;
	void setAckType(AckType type);

	bool hasSubscriptionId() const;
	QByteArray subscriptionId() const;
	void setSubscriptionId(const QByteArray &value);

	QByteArray toByteArray() const;

protected:
	bool parseHeaderLine(const QByteArray &line, int number);

private:
	QStompRequestFramePrivate * const dd;
};

class QSTOMPSHARED_EXPORT QStompClient : public QObject
{
	Q_OBJECT
public:

	explicit QStompClient(QObject *parent = 0);
	virtual ~QStompClient();

	enum Error {
		NoError,
		UnknownError,
		HostNotFound,
		ConnectionRefused,
		UnexpectedClose
	};

	void connectToHost(const QString &hostname, quint16 port = 61613);
	void setSocket(QTcpSocket *socket);
	QTcpSocket * socket();

	void sendFrame(const QStompRequestFrame &frame);

	void login(const QByteArray &user = QByteArray(), const QByteArray &password = QByteArray());
	void logout();

	void send(const QByteArray &destination, const QString &body, const QByteArray &transactionId = QByteArray(), const QStompHeaderList &headers = QStompHeaderList());
	void subscribe(const QByteArray &destination, bool autoAck, const QStompHeaderList &headers = QStompHeaderList());
	void unsubscribe(const QByteArray &destination, const QStompHeaderList &headers = QStompHeaderList());
	void commit(const QByteArray &transactionId, const QStompHeaderList &headers = QStompHeaderList());
	void begin(const QByteArray &transactionId, const QStompHeaderList &headers = QStompHeaderList());
	void abort(const QByteArray &transactionId, const QStompHeaderList &headers = QStompHeaderList());
	void ack(const QByteArray &messageId, const QByteArray &transactionId = QByteArray(), const QStompHeaderList &headers = QStompHeaderList());

	int framesAvailable() const;
	QStompResponseFrame fetchFrame();
	QList<QStompResponseFrame> fetchAllFrames();

	QAbstractSocket::SocketState socketState() const;
	QAbstractSocket::SocketError socketError() const;
	QString socketErrorString() const;

	QByteArray contentEncoding();
	void setContentEncoding(const QByteArray & name);
	void setContentEncoding(const QTextCodec * codec);

public Q_SLOTS:
	void disconnectFromHost();

Q_SIGNALS:
	void socketConnected();
	void socketDisconnected();
	void socketError(QAbstractSocket::SocketError);
	void socketStateChanged(QAbstractSocket::SocketState);

	void frameReceived();

private Q_SLOTS:
	void socketReadyRead();

private:
	QStompClientPrivate * const d;
};

#endif // QSTOMP_H
