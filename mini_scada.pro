QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    clientwindow.cpp \
    data.cpp \
    main.cpp \
    miniscada.cpp \
    networkconnection.cpp \
    server.cpp

HEADERS += \
    client.h \
    clientwindow.h \
    data.h \
    miniscada.h \
    networkconnection.h \
    server.h

FORMS += \
    clientwindow.ui \
    miniscada.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
