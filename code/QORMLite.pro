TEMPLATE = lib
DEFINES += QORMLITE_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x -std=gnu++11 -Wall
CONFIG += c++11

QT -= gui
QT += core sql

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
  operations/model/field.cpp \
  operations/model/primarykey.cpp \
  operations/model/type.cpp \
  qormutils.cpp

HEADERS += \
  operations/model/field.h \
  operations/model/primarykey.h \
  operations/model/type.h \
  operations/operation.h \
  qormcache.h \
  qormentity.h \
  qormobserver.h \
  qormutils.h

