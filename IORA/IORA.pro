QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calendar.cpp \
    ccreatenewchannel.cpp \
    channels.cpp \
    chat.cpp \
    dashboard.cpp \
    forgotpsw.cpp \
    main.cpp \
    mainapp.cpp \
    mainwindow.cpp \
    messageencode.cpp \
    registerpage.cpp \
    tcpclient.cpp

HEADERS += \
    calendar.h \
    ccreatenewchannel.h \
    channels.h \
    chat.h \
    dashboard.h \
    forgotpsw.h \
    mainapp.h \
    mainwindow.h \
    messagedecoder.h \
    messageencode.h \
    registerpage.h \
    serverRequestTypes.h \
    tcpclient.h

FORMS += \
    calendar.ui \
    ccreatenewchannel.ui \
    channels.ui \
    chat.ui \
    dashboard.ui \
    forgotpsw.ui \
    mainapp.ui \
    mainwindow.ui \
    registerpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
