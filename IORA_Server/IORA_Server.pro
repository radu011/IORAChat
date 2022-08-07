QT -= gui
QT +=network
QT += sql
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
        absmesaj.cpp \
        canal.cpp \
        chat.cpp \
        database.cpp \
        decoder.cpp \
        emailsender.cpp \
        encoder.cpp \
        file.cpp \
        main.cpp \
        meet.cpp \
        mesaj.cpp \
        qtcpserver.cpp \
        solver.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    IMesaj.h \
    absmesaj.h \
    canal.h \
    chat.h \
    database.h \
    decoder.h \
    emailsender.h \
    encoder.h \
    file.h \
    meet.h \
    mesaj.h \
    qtcpserver.h \
    solver.h \


