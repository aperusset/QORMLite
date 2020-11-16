QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
  fixture/operations/model/fieldfixture.cpp \
  fixture/operations/model/typefixture.cpp \
  fixture/testentity.cpp \
  fixture/testobserver.cpp \
  main.cpp \
  operations/model/fieldtest.cpp \
  operations/model/foreignkeytest.cpp \
  operations/model/primarykeytest.cpp \
  operations/model/referencetest.cpp \
  operations/model/typetest.cpp \
  qormcachetest.cpp \
  qormentitytest.cpp \
  qormobservertest.cpp \
  qormutilstest.cpp

HEADERS += \
  fixture/operations/model/fieldfixture.h \
  fixture/operations/model/typefixture.h \
  fixture/testentity.h \
  fixture/testobserver.h \
  operations/model/fieldtest.h \
  operations/model/foreignkeytest.h \
  operations/model/primarykeytest.h \
  operations/model/referencetest.h \
  operations/model/typetest.h \
  qormcachetest.h \
  qormentitytest.h \
  qormobservertest.h \
  qormutilstest.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../code/release/ -lQORMLite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../code/debug/ -lQORMLite
else:unix: LIBS += -L$$OUT_PWD/../code/ -lQORMLite

INCLUDEPATH += $$PWD/../code
DEPENDPATH += $$PWD/../code
