#
# This file is part of QStomp
#
# Copyright (C) 2009 Patrick Schneider <patrick.p2k.schneider@googlemail.com>
#
# This library is free software: you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either
# version 3 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General
# Public License along with this library; see the file
# COPYING.LESSER.  If not, see <http://www.gnu.org/licenses/>.
#

QT += network
QT -= gui
TARGET = qstomp
TEMPLATE = lib
DEFINES += QSTOMP_LIBRARY
DEPENDPATH += src
INCLUDEPATH += src
SOURCES += src/qstomp.cpp
HEADERS += src/qstomp.h \
    src/qstomp_global.h \
	src/qstomp_p.h

target.path = $(QT_INSTALL_LIBS)
dist_headers.path = $(QT_INSTALL_HEADERS)/qstomp
dist_headers.files = src/qstomp.h src/qstomp_global.h

VERSION = 0.3.0
INSTALLS += target dist_headers

