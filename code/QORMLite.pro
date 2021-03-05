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
  operations/model/table.cpp \
  operations/model/type.cpp \
  operations/model/view.cpp \
  operations/query.cpp \
  operations/query/assignment.cpp \
  operations/query/condition/condition.cpp \
  operations/query/condition/equals.cpp \
  operations/query/condition/in.cpp \
  operations/query/condition/notequals.cpp \
  operations/query/delete.cpp \
  operations/query/insert.cpp \
  operations/query/join/join.cpp \
  operations/query/order/order.cpp \
  operations/query/select.cpp \
  operations/query/selection.cpp \
  operations/query/update.cpp \
  qormcreator.cpp \
  qormdatabase.cpp \
  qormlite.cpp \
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
  operations/query/assignment.h \
  operations/query/bindable.h \
  operations/query/condition/and.h \
  operations/query/condition/condition.h \
  operations/query/condition/equals.h \
  operations/query/condition/in.h \
  operations/query/condition/isnotnull.h \
  operations/query/condition/isnull.h \
  operations/query/condition/like.h \
  operations/query/condition/notequals.h \
  operations/query/condition/or.h \
  operations/query/delete.h \
  operations/query/insert.h \
  operations/query/join/crossjoin.h \
  operations/query/join/innerjoin.h \
  operations/query/join/join.h \
  operations/query/join/leftjoin.h \
  operations/query/join/rightjoin.h \
  operations/query/order/asc.h \
  operations/query/order/desc.h \
  operations/query/order/order.h \
  operations/query/select.h \
  operations/query/selection.h \
  operations/query/update.h \
  qormcache.h \
  qormcreator.h \
  qormdatabase.h \
  qormentity.h \
  qormlite.h \
  qormobserver.h \
  qormutils.h

