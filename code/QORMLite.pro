TEMPLATE = lib
DEFINES += QORMLITE_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x -std=gnu++11 -Wall
CONFIG += c++11

QT -= gui
QT += core sql

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
  operations/model/field.cpp \
  operations/model/foreignkey.cpp \
  operations/model/primarykey.cpp \
  operations/model/reference.cpp \
  operations/model/table.cpp \
  operations/model/type.cpp \
  operations/query.cpp \
  operations/query/assignement.cpp \
  operations/query/condition.cpp \
  operations/query/join.cpp \
  operations/query/order.cpp \
  operations/query/selection.cpp \
  qormutils.cpp

HEADERS += \
  operations/model/field.h \
  operations/model/foreignkey.h \
  operations/model/primarykey.h \
  operations/model/reference.h \
  operations/model/table.h \
  operations/model/type.h \
  operations/operation.h \
  operations/query.h \
  operations/query/assignement.h \
  operations/query/bindable.h \
  operations/query/condition.h \
  operations/query/join.h \
  operations/query/order.h \
  operations/query/selection.h \
  qormcache.h \
  qormentity.h \
  qormobserver.h \
  qormutils.h

