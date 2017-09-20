#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T02:21:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordManager2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    src/Crypt.cpp \
    src/main.cpp \
    src/principal.cpp \
    src/DAO.cpp \
    libs/pugi/pugixml.cpp \
    src/addentry.cpp \
    src/login.cpp \
    src/passdialog.cpp \
    src/changepassword.cpp

HEADERS += \
    headers/DAO.hpp \
    headers/principal.h \
    headers/Crypt.hpp \
    libs/pugi/pugiconfig.hpp \
    libs/pugi/pugixml.hpp \
    libs/base-n/basen.hpp \
    headers/login.h \
    headers/addentry.h \
    headers/customexceptions.hpp \
    headers/passdialog.h \
    headers/changepassword.h

SUBDIRS += \
    PasswordManager2.pro

FORMS += \
    view/principal.ui \
    view/addentry.ui \
    view/login.ui \
    view/passdialog.ui \
    view/changepassword.ui

DISTFILES +=

INCLUDEPATH += /usr/local/include/cryptopp

LIBS += -lcryptopp
