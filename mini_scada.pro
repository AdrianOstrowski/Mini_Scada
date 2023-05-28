QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    clientwindow.cpp \
    databuffer.cpp \
    datadepacketizer.cpp \
    datadeserializer.cpp \
    datafromdb.cpp \
    datagenerator.cpp \
    dataoperation.cpp \
    datapacketizer.cpp \
    dataserializer.cpp \
    main.cpp \
    message.cpp \
    miniscada.cpp \
    networkconnection.cpp \
    randomdata.cpp \
    server.cpp

HEADERS += \
    client.h \
    clientwindow.h \
    databuffer.h \
    datadepacketizer.h \
    datadeserializer.h \
    datafromdb.h \
    datagenerator.h \
    dataoperation.h \
    datapacketizer.h \
    dataserializer.h \
    message.h \
    miniscada.h \
    networkconnection.h \
    randomdata.h \
    server.h

FORMS += \
    clientwindow.ui \
    miniscada.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
