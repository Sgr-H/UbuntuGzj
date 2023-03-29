QT       += core gui serialbus serialport charts sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bridgemanager.cpp \
    businesslogicmanager.cpp \
    commonsetting.cpp \
    electricitymeter.cpp \
    environment.cpp \
    firep.cpp \
    gzjsqlite.cpp \
    liftmanager.cpp \
    main.cpp \
    serialsetting.cpp \
    serialsettingmanager.cpp \
    tcpclient.cpp \
    tcpclientmanager.cpp \
    waterlever.cpp \
    watermeter.cpp \
    widgetui.cpp

HEADERS += \
    ConfigDef.h \
    bridgemanager.h \
    businesslogicmanager.h \
    commonsetting.h \
    electricitymeter.h \
    environment.h \
    firep.h \
    gzjsqlite.h \
    liftmanager.h \
    serialsetting.h \
    serialsettingmanager.h \
    tcpclient.h \
    tcpclientmanager.h \
    waterlever.h \
    watermeter.h \
    widgetui.h

FORMS += \
#    MainWindowsUI.ui \
    commonsetting.ui \
    electricitymeter.ui \
    environment.ui \
    firep.ui \
    liftmanager.ui \
    serialsetting.ui \
    tcpclient.ui \
    test.ui \
    waterlever.ui \
    watermeter.ui \
    widgetui.ui

# 窗口自定义
include ($$PWD/framelesscore/framelesscore.pri)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gzj.qrc
