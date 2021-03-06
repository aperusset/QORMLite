include(../QORMLiteParent.pri)

TEMPLATE = app

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

QT += testlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/$$VERSION -lQORMLite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/$$VERSION -lQORMLite
else:unix: LIBS += -L$$OUT_PWD/../../lib/$$VERSION -lQORMLite

INCLUDEPATH += $$PWD/../code
DEPENDPATH += $$PWD/../code

SOURCES +=  \
  fixture/testcreator.cpp \
  fixture/testentity.cpp \
  fixture/testobserver.cpp \
  main.cpp \
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
  qormcachetest.cpp \
  qormcreatortest.cpp \
  qormdatabasetest.cpp \
  qormentitytest.cpp \
  qormlitetest.cpp \
  qormobservertest.cpp \
  qormutilstest.cpp

HEADERS += \
  fixture/testcreator.h \
  fixture/testentity.h \
  fixture/testobserver.h \
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
  qormcachetest.h \
  qormcreatortest.h \
  qormdatabasetest.h \
  qormentitytest.h \
  qormlitetest.h \
  qormobservertest.h \
  qormutilstest.h
