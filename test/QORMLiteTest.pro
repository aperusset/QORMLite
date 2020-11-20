QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
  fixture/testentity.cpp \
  fixture/testobserver.cpp \
  main.cpp \
  operations/model/fieldtest.cpp \
  operations/model/foreignkeytest.cpp \
  operations/model/primarykeytest.cpp \
  operations/model/referencetest.cpp \
  operations/model/tabletest.cpp \
  operations/model/typetest.cpp \
  operations/query/assignementtest.cpp \
  operations/query/conditiontest.cpp \
  operations/query/jointest.cpp \
  operations/query/ordertest.cpp \
  operations/query/selectiontest.cpp \
  qormcachetest.cpp \
  qormentitytest.cpp \
  qormobservertest.cpp \
  qormutilstest.cpp

HEADERS += \
  fixture/testentity.h \
  fixture/testobserver.h \
  operations/model/fieldtest.h \
  operations/model/foreignkeytest.h \
  operations/model/primarykeytest.h \
  operations/model/referencetest.h \
  operations/model/tabletest.h \
  operations/model/typetest.h \
  operations/query/assignementtest.h \
  operations/query/conditiontest.h \
  operations/query/jointest.h \
  operations/query/ordertest.h \
  operations/query/selectiontest.h \
  qormcachetest.h \
  qormentitytest.h \
  qormobservertest.h \
  qormutilstest.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../code/release/ -lQORMLite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../code/debug/ -lQORMLite
else:unix: LIBS += -L$$OUT_PWD/../code/ -lQORMLite

INCLUDEPATH += $$PWD/../code
DEPENDPATH += $$PWD/../code
