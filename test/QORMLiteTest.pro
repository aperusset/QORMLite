include(../QORMLiteParent.pri)

TEMPLATE = app

CONFIG += qt console warn_on depend_includepath testcase no_testcase_installs
CONFIG -= app_bundle

QT += testlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/$$VERSION -lQORMLite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/$$VERSION -lQORMLite
else:unix: LIBS += -L$$OUT_PWD/../lib/$$VERSION -lQORMLite

INCLUDEPATH += $$PWD/../code
DEPENDPATH += $$PWD/../code

SOURCES +=  \
  cachetest.cpp \
  connectors/connectortest.cpp \
  connectors/odbctest.cpp \
  connectors/sqlitetest.cpp \
  schema/creatortest.cpp \
  databasetest.cpp \
  entities/entitytest.cpp \
  fixture/testcreator.cpp \
  fixture/testcrudrepository.cpp \
  fixture/testentity.cpp \
  fixture/testobserver.cpp \
  main.cpp \
  observertest.cpp \
  operations/model/constraint/uniquetest.cpp \
  operations/model/fieldtest.cpp \
  operations/model/constraint/foreignkeytest.cpp \
  operations/model/constraint/primarykeytest.cpp \
  operations/model/constraint/referencetest.cpp \
  operations/model/tabletest.cpp \
  operations/model/typetest.cpp \
  operations/model/viewtest.cpp \
  operations/query/assignmenttest.cpp \
  operations/query/conditiontest.cpp \
  operations/query/deletetest.cpp \
  operations/query/inserttest.cpp \
  operations/query/jointest.cpp \
  operations/query/ordertest.cpp \
  operations/query/selectiontest.cpp \
  operations/query/selecttest.cpp \
  operations/query/updatetest.cpp \
  repositories/crudrepositorytest.cpp \
  qormlitetest.cpp \
  utilstest.cpp

HEADERS += \
  cachetest.h \
  connectors/connectortest.h \
  connectors/odbctest.h \
  connectors/sqlitetest.h \
  fixture/testupgrader.h \
  schema/creatortest.h \
  databasetest.h \
  entities/entitytest.h \
  fixture/maindatabasetest.h \
  fixture/testconnector.h \
  fixture/testcreator.h \
  fixture/testcrudrepository.h \
  fixture/testentity.h \
  fixture/testobserver.h \
  observertest.h \
  operations/model/constraint/uniquetest.h \
  operations/model/fieldtest.h \
  operations/model/constraint/foreignkeytest.h \
  operations/model/constraint/primarykeytest.h \
  operations/model/constraint/referencetest.h \
  operations/model/tabletest.h \
  operations/model/typetest.h \
  operations/model/viewtest.h \
  operations/query/assignmenttest.h \
  operations/query/conditiontest.h \
  operations/query/deletetest.h \
  operations/query/inserttest.h \
  operations/query/jointest.h \
  operations/query/ordertest.h \
  operations/query/selectiontest.h \
  operations/query/selecttest.h \
  operations/query/updatetest.h \
  repositories/crudrepositorytest.h \
  qormlitetest.h \
  utilstest.h
