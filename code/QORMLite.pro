include(../QORMLiteParent.pri)

TEMPLATE = lib

CONFIG += skip_target_version_ext plugin
DEFINES += QORMLITE_LIBRARY

win32:CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/../lib/release/$$VERSION
else:win32:CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/../lib/debug/$$VERSION
else:unix: DESTDIR = $$OUT_PWD/../lib/$$VERSION

SOURCES += \
  connectors/connector.cpp \
  connectors/odbc.cpp \
  connectors/sqlite.cpp \
  creator.cpp \
  database.cpp \
  operations/model/constraint/constraint.cpp \
  operations/model/constraint/unique.cpp \
  operations/model/constraint/foreignkey.cpp \
  operations/model/constraint/primarykey.cpp \
  operations/model/field.cpp \
  operations/model/table.cpp \
  operations/model/type/date.cpp \
  operations/model/type/type.cpp \
  operations/model/type/varchar.cpp \
  operations/model/view.cpp \
  operations/query.cpp \
  operations/query/assignment.cpp \
  operations/query/condition/condition.cpp \
  operations/query/condition/equals.cpp \
  operations/query/condition/greater.cpp \
  operations/query/condition/greaterorequals.cpp \
  operations/query/condition/in.cpp \
  operations/query/condition/notequals.cpp \
  operations/query/condition/smaller.cpp \
  operations/query/condition/smallerorequals.cpp \
  operations/query/delete.cpp \
  operations/query/insert.cpp \
  operations/query/join/join.cpp \
  operations/query/order/order.cpp \
  operations/query/select.cpp \
  operations/query/selection/selection.cpp \
  operations/query/update.cpp \
  qormlite.cpp \
  utils.cpp

HEADERS += \
  cache.h \
  connectors/connector.h \
  connectors/odbc.h \
  connectors/sqlite.h \
  creator.h \
  database.h \
  entity.h \
  observer.h \
  operations/model/constraint/constraint.h \
  operations/model/constraint/unique.h \
  operations/model/constraint/foreignkey.h \
  operations/model/constraint/primarykey.h \
  operations/model/constraint/reference.h \
  operations/model/field.h \
  operations/model/table.h \
  operations/model/type/date.h \
  operations/model/type/decimal.h \
  operations/model/type/integer.h \
  operations/model/type/type.h \
  operations/model/type/varchar.h \
  operations/model/view.h \
  operations/operation.h \
  operations/query.h \
  operations/query/assignment.h \
  operations/query/bindable.h \
  operations/query/condition/and.h \
  operations/query/condition/condition.h \
  operations/query/condition/equals.h \
  operations/query/condition/greater.h \
  operations/query/condition/greaterorequals.h \
  operations/query/condition/in.h \
  operations/query/condition/isnotnull.h \
  operations/query/condition/isnull.h \
  operations/query/condition/like.h \
  operations/query/condition/not.h \
  operations/query/condition/notequals.h \
  operations/query/condition/or.h \
  operations/query/condition/smaller.h \
  operations/query/condition/smallerorequals.h \
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
  operations/query/selection/avg.h \
  operations/query/selection/count.h \
  operations/query/selection/dateformatter.h \
  operations/query/selection/lower.h \
  operations/query/selection/max.h \
  operations/query/selection/min.h \
  operations/query/selection/selection.h \
  operations/query/selection/sum.h \
  operations/query/selection/upper.h \
  operations/query/tablequery.h \
  operations/query/update.h \
  repositories/crudrepository.h \
  repositories/readonlyrepository.h \
  qormlite.h \
  utils.h

