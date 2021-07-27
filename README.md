# QORMLite
A lite ORM for QT Framework.

### Build, compatibility and conventions
QORMLite is built with QT Desktop 5.15.2 and C++11. The build has been tested on Windows 10 and Ubuntu 20.04LTS, but not on Mac OS (any version).

It is planned to upgrade step by step to [C++14](https://github.com/aperusset/QORMLite/issues/1), then [C++17](https://github.com/aperusset/QORMLite/issues/9) and finally [C++20](https://github.com/aperusset/QORMLite/issues/10). It's also planned to upgrade to [QT 6](https://github.com/aperusset/QORMLite/issues/11). Feel free to comment any of these opened issues (piece of code to upgrade or to improve, ...).

The code is continuously checked with [CppCheck](http://cppcheck.sourceforge.net/) and [CPPLint](https://github.com/cpplint/cpplint). If you want to contribute, please follow as much as possible the guidelines and fixes suggested by these tools.

### Configure, build and test
First, please install QT with the official online installer (currently [4.1.1](https://download.qt.io/official_releases/qt-installer-framework/4.1.1/)).

Then clone QORMLite Github repository to your computer with SSH.

QORMLite is a `subdirs` QT project with two sub-projects :
1. `QORMLite`, which contains the library code (includes and sources)
2. `QORMLiteTest`, which contains all the tests related to the library

To build it, just import the project into QT Editor, configure it with the compatible kit and click "Hammer" (build) button.

To run the tests, just click the green "Run" button in the IDE. Everything should be fine without any further configuration.

### Use QORMLite into your project

To use QORMLite in your project, please add these lines into your `pro` file (you can remove Windows or Linux configuration if you don't need it) :

```
QORMLITE_VERSION = {version}

win32:CONFIG(release, debug|release) {
LIBS += -L$$PWD/{pathToQORMLite}/QORMLite/lib/release/$$QORMLITE_VERSION -lQORMLite
DESTDIR = $$OUT_PWD/../lib/release/$$VERSION
}

win32:CONFIG(debug, debug|release) {
LIBS += -L$$PWD/{pathToQORMLite}/QORMLite/lib/debug/$$QORMLITE_VERSION -lQORMLite
DESTDIR = $$OUT_PWD/../lib/debug/$$VERSION
}

unix {
LIBS += -L$$PWD/{pathToQORMLite}/QORMLite/lib/$$QORMLITE_VERSION -lQORMLite
DESTDIR = $$OUT_PWD/../lib/$$VERSION
}

INCLUDEPATH += $$PWD/{pathToQORMLite}/QORMLite/code
DEPENDPATH += $$PWD/{pathToQORMLite}/QORMLite/code
```

Replace `{version}` by the version of QORMLite you want to use and `{pathToQORMLite}` by the path to the QORMLite subdirs project directory **from the build directory of your project.**

Make sure that you've built the QORMLite library in debug/release mode before building your project with code dependency to QORMLite.
