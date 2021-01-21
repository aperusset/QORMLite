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
  operations/model/view.cpp \
  operations/query.cpp \
  operations/query/assignement.cpp \
  operations/query/condition.cpp \
  operations/query/delete.cpp \
  operations/query/insert.cpp \
  operations/query/join.cpp \
  operations/query/order.cpp \
  operations/query/select.cpp \
  operations/query/selection.cpp \
  operations/query/update.cpp \
  qormcreator.cpp \
  qormdatabase.cpp \
  qormutils.cpp

HEADERS += \
  operations/model/field.h \
  operations/model/foreignkey.h \
  operations/model/primarykey.h \
  operations/model/reference.h \
  operations/model/table.h \
  operations/model/type.h \
  operations/model/view.h \
  operations/operation.h \
  operations/query.h \
  operations/query/assignement.h \
  operations/query/bindable.h \
  operations/query/condition.h \
  operations/query/delete.h \
  operations/query/insert.h \
  operations/query/join.h \
  operations/query/order.h \
  operations/query/select.h \
  operations/query/selection.h \
  operations/query/update.h \
  qormcache.h \
  qormcreator.h \
  qormdatabase.h \
  qormentity.h \
  qormobserver.h \
  qormutils.h

