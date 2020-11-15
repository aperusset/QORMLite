TEMPLATE = lib
DEFINES += QORMLITE_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x -std=gnu++11 -Wall
CONFIG += c++11

QT -= gui
QT += core sql

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
  qormutils.cpp

HEADERS += \
  qormcache.h \
  qormentity.h \
  qormobserver.h \
  qormutils.h

