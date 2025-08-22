# QORMLite [![Tweet](https://img.shields.io/twitter/url/http/shields.io.svg?style=social)](https://twitter.com/intent/tweet?text=Facilitate%20querying%20databases%20with%20QT%20Framework%20and%20C%2B%2B%20%21&url=https://github.com/aperusset/QORMLite)

[![Stable version](https://img.shields.io/badge/version-2.0-yellow)]()
[![QT Version](https://img.shields.io/badge/QT-5.15.2-brightgreen)](https://www.qt.io/blog/qt-5.15.2-released)
[![C++ Version](https://img.shields.io/badge/c%2B%2B-11-brightgreen)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![License](https://img.shields.io/badge/license-GPL--3.0-blue)](https://en.wikipedia.org/wiki/GNU_General_Public_License)
[![Price](https://img.shields.io/badge/price-free-blue)]()

A lite ORM (Object Relational Mapping) for QT Framework.

### Compatibility and conventions
QORMLite is built with QT Desktop 5.15.2 and C++11. The build has been tested on Windows 10 and Ubuntu 20.04 LTS, but not on Mac OS (any version).

It is planned to upgrade step by step to [C++14](https://github.com/aperusset/QORMLite/issues/1), then [C++17](https://github.com/aperusset/QORMLite/issues/9) and finally [C++20](https://github.com/aperusset/QORMLite/issues/10). It's also planned to upgrade to [QT 6](https://github.com/aperusset/QORMLite/issues/11). Feel free to comment any of these opened issues (piece of code to upgrade or to improve, ...).

The code is continuously checked with [CppCheck](http://cppcheck.sourceforge.net/) and [CPPLint](https://github.com/cpplint/cpplint). If you want to contribute, please follow as much as possible the guidelines and fixes suggested by these tools.

<div align="center" style="display: flex; align-items:center;">
 <img src="./logos/qt.svg" height="40px">
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 <img src="./logos/c++.svg" height="40px">
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 <img src="./logos/cppcheck.png" height="18px">
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 <img src="./logos/windows.svg" height="40px">
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 <img src="./logos/ubuntu.svg" height="40px">
</div>

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
}

win32:CONFIG(debug, debug|release) {
LIBS += -L$$PWD/{pathToQORMLite}/QORMLite/lib/debug/$$QORMLITE_VERSION -lQORMLite
}

unix {
LIBS += -L$$PWD/{pathToQORMLite}/QORMLite/lib/$$QORMLITE_VERSION -lQORMLite
}

INCLUDEPATH += $$PWD/{pathToQORMLite}/QORMLite/code
DEPENDPATH += $$PWD/{pathToQORMLite}/QORMLite/code
```

Replace `{version}` by the version of QORMLite you want to use and `{pathToQORMLite}` by the path to the QORMLite subdirs project directory **from the build directory of your project.**

Make sure that you've built the QORMLite library in debug/release mode before building your project with code dependency to QORMLite.

All of the QORMLite classes are contained in `QORM` namespace.

## <div style="display: flex; align-items:center;"><img src="./logos/connector.svg" height="18px">&nbsp;[Connector](https://github.com/aperusset/QORMLite/blob/master/code/connectors/connector.h)</div>

A connector is responsible to initiate a connection to a database and manage its life-cycle. The needed information to initiate all types of connection are :
* [QT driver name](https://doc.qt.io/qt-5/sql-driver.html) -> provided by the pure virtual method `driverName()`.
* A name to uniquely identify the connection -> provided in abstract `Connector` class constructor as single `QString` parameter.

Currently, only [ODBC](#odbc) and [SQLite 3](#sqlite-3) database are managed. [MySQL](https://github.com/aperusset/QORMLite/issues/34) and [PostgreSQL](https://github.com/aperusset/QORMLite/issues/35) connectors implementation is planned.

All methods in this class are `virtual` and could also be overridden in child classes.

`preConnect` allows to execute some actions before the database connection is opened. Called by `connect`.

`postConnect` allows to execute some actions after the database connection is opened. Called by `connect`.

`tables` returns all the database's user tables.

`views` returns all the database's user views.

Implementations of `Connector` abstract class must also provide a `backup` method which effectively backup (or dump) the entire database into a file. The file name is provided as method parameter.

#### <div style="display: flex; align-items:center;"><img src="./logos/odbc.png" height="18px">&nbsp;&nbsp;[ODBC](https://github.com/aperusset/QORMLite/blob/documentation/code/connectors/odbc.h)</div>

ODBC (Open Database Connectivity) connector allows to connect to any database that support this kind of connection. The user of this connector must provide, additionally to the database name, a complete driver definition and the connection string.

On Windows there is usually a built-in ODBC driver that support most of the connection types (Access, SQL Server, ...).

On Unix, it is necessary to install [unixODBC](http://www.unixodbc.org/) and then [build reconfigured QT ODBC driver](https://doc.qt.io/qt-5/sql-driver.html#how-to-build-the-odbc-plugin-on-unix-and-macos).

The backup functionality for this connector is currently not implemented (throw an exception if you try to call `backup` method).

**Example : Microsoft Access** (works only on Windows except if you buy [easysoft driver](https://www.easysoft.com/products/data_access/odbc-access-driver/index.html#section=tab-1)) :
* Driver definition = `Microsoft Access Driver (*.mdb, *.accdb)`
* Connection string = `DSN='';DBQ=\\path\\to\\database\\file.mdb;`

#### <div style="display: flex; align-items:center;"><img src="./logos/sqlite.svg" height="18px">&nbsp;[SQLite 3](https://github.com/aperusset/QORMLite/blob/documentation/code/connectors/sqlite.h)</div>

First note : it is not planned to implement a driver for SQLite 2 (QSQLITE2) as it is obsolete since prior QT's version than the one used to build this library.

Second note : it is not currently possible to connect to password protected SQLite database. A nice feature for new-comer ?

Third note : By default, SQLite doesn't activate foreign keys constraint.

The SQLite connector take only a name as mandatory constructor parameter. It is also possible to deactivate the foreign keys constraint by specifying `false` as second constructor parameter. Foreign keys constraints are activated by default by the connector with a `postConnect` operation.

This connector provides test functionalities. By "test", it means that you can create a database for test purpose with `true` as third constructor parameter. The connector will also create a temporary database by calling `connect` and will destroy (erase from disk) it by calling `disconnect`. This is particularly useful and used in the unit tests of this library.

Last but not least, the connector will activate automatically [SQLite regexp option](https://doc.qt.io/qt-5/qsqldatabase.html#setConnectOptions) in a `preConnect` operation.

## Creator

## Database initialization

## Entity

## Observer

## Cache

## Repository

## Utilities

## Available operations

#### Model

#### Query
