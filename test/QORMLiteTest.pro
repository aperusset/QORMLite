QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
  fixture/qormtestentity.cpp \
  fixture/qormtestobserver.cpp \
  main.cpp \
  qormentitytest.cpp \
  qormobservertest.cpp \
  qormutilstest.cpp

HEADERS += \
  fixture/qormtestentity.h \
  fixture/qormtestobserver.h \
  qormentitytest.h \
  qormobservertest.h \
  qormutilstest.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../code/release/ -lQORMLite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../code/debug/ -lQORMLite
else:unix: LIBS += -L$$OUT_PWD/../code/ -lQORMLite

INCLUDEPATH += $$PWD/../code
DEPENDPATH += $$PWD/../code
