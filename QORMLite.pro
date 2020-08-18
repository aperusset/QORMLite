TEMPLATE = lib
DEFINES += QORMLITE_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x -std=gnu++11 -Wall
CONFIG += c++11

QT -= gui
QT += core sql testlib
CONFIG(release)
{
  QT.testlib.CONFIG -= console
}

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES +=

HEADERS +=

