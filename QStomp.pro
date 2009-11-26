# -------------------------------------------------
# Project created by QtCreator 2009-11-26T09:26:50
# -------------------------------------------------
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

target.path = $$DESTDIR/lib
dist_headers.path = $$DESTDIR/include/qstomp
dist_headers.files = src/qstomp.h src/qstomp_global.h

VERSION = 0.2.0
INSTALLS += target dist_headers
