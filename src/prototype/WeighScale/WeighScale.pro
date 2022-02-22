# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
win32 {
TEMPLATE = app
TARGET = WeighScale
DESTDIR = ../../../build/cypress/weigh_scale
CONFIG += debug
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
#RCC_DIR += GeneratedFiles
}

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../auxiliary/CommandLineParser.cpp \
    ../../auxiliary/CypressConstants.cpp \
    ../../data/WeighScaleTest.cpp \
    ../../data/WeightMeasurement.cpp \
    ../../data/MeasurementBase.cpp \
    ../../managers/ManagerBase.cpp \
    ../../managers/SerialPortManager.cpp \
    ../../managers/WeighScaleManager.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ../../auxiliary/CommandLineParser.h \
    ../../auxiliary/CypressConstants.h \
    ../../data/MeasurementBase.h \
    ../../data/WeighScaleTest.h \
    ../../data/WeightMeasurement.h \
    ../../data/TestBase.h \
    ../../managers/ManagerBase.h \
    ../../managers/SerialPortManager.h \
    ../../managers/WeighScaleManager.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

TRANSLATIONS += \
    WeighScale_en_CA.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
