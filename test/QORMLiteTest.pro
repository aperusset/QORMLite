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
  creatortest.cpp \
  databasetest.cpp \
  entitytest.cpp \
  fixture/testconnector.cpp \
  fixture/testcreator.cpp \
  fixture/testentity.cpp \
  fixture/testobserver.cpp \
  fixture/testrepository.cpp \
  main.cpp \
  observertest.cpp \
  operations/model/fieldtest.cpp \
  operations/model/foreignkeytest.cpp \
  operations/model/primarykeytest.cpp \
  operations/model/referencetest.cpp \
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
  qormlitetest.cpp \
  repositorytest.cpp \
  utilstest.cpp

HEADERS += \
  cachetest.h \
  connectors/connectortest.h \
  connectors/odbctest.h \
  connectors/sqlitetest.h \
  creatortest.h \
  databasetest.h \
  entitytest.h \
  fixture/maindatabasetest.h \
  fixture/testconnector.h \
  fixture/testcreator.h \
  fixture/testentity.h \
  fixture/testobserver.h \
  fixture/testrepository.h \
  observertest.h \
  operations/model/fieldtest.h \
  operations/model/foreignkeytest.h \
  operations/model/primarykeytest.h \
  operations/model/referencetest.h \
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
  qormlitetest.h \
  repositorytest.h \
  utilstest.h
