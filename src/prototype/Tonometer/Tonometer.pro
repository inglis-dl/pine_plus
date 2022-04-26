# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
win32 {
TEMPLATE = app
TARGET = Tonometer
DESTDIR = ../../../build/cypress/tonometer
CONFIG += debug
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
#RCC_DIR += GeneratedFiles
}

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets usb

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    ../../auxiliary/CommandLineParser.h \
    ../../auxiliary/Constants.h \
    ../../auxiliary/JsonSettings.h \
    ../../data/AccessQueryHelper.h \
    ../../data/TonometerMeasurement.h \
    ../../data/TonometerTest.h \
    ../../data/Measurement.h \
    ../../data/TestBase.h \
    ../../managers/ManagerBase.h \
    ../../managers/TonometerManager.h \
    ../../widgets/BarcodeWidget.h \
    ../../widgets/MeasureWidget.h \
    MainWindow.h

SOURCES += \
    ../../auxiliary/CommandLineParser.cpp \
    ../../auxiliary/Constants.cpp \
    ../../auxiliary/JsonSettings.cpp \
    ../../data/AccessQueryHelper.cpp \
    ../../data/TonometerMeasurement.cpp \
    ../../data/TonometerTest.cpp \
    ../../data/Measurement.cpp \
    ../../managers/ManagerBase.cpp \
    ../../managers/TonometerManager.cpp \
    ../../widgets/BarcodeWidget.cpp \
    ../../widgets/MeasureWidget.cpp \
    MainWindow.cpp \
    main.cpp

FORMS += \
    ../../widgets/barcodewidget.ui \
    ../../widgets/measurewidget.ui \
    MainWindow.ui

TRANSLATIONS += \
    Tonometer_en_CA.ts
CONFIG += lrelease
CONFIG += embed_translations

unix {
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
}
