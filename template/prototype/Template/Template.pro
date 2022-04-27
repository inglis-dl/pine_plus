# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
win32 {
TEMPLATE = app
TARGET = Template
DESTDIR = ../../../build/cypress/template
CONFIG += debug
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
#RCC_DIR += GeneratedFiles
}

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += ./MainWindow.h \
    ../../../src/data/Measurement.h \
    ../../../src/data/TestBase.h \
    ../../../src/auxiliary/CommandLineParser.h \
    ../../../src/auxiliary/Constants.h \
    ../../../src/auxiliary/JsonSettings.h \
    ../../../src/managers/ManagerBase.h \
    ../../data/TemplateMeasurement.h \
    ../../data/TemplateTest.h \
    ../../managers/TemplateManager.h \
    ../../../src/widgets/BarcodeWidget.h \
    ../../../src/widgets/MeasureWidget.h

SOURCES += ./MainWindow.cpp \
    ./main.cpp \
    ../../../src/auxiliary/CommandLineParser.cpp \
    ../../../src/auxiliary/Constants.cpp \
    ../../../src/auxiliary/JsonSettings.cpp \
    ../../../src/data/Measurement.cpp \
    ../../../src/managers/ManagerBase.cpp \
    ../../data/TemplateMeasurement.cpp \
    ../../data/TemplateTest.cpp \
    ../../managers/TemplateManager.cpp \
    ../../../src/widgets/BarcodeWidget.cpp \
    ../../../src/widgets/MeasureWidget.cpp

FORMS += \
    ../../../src/widgets/barcodewidget.ui \
    ../../../src/widgets/measurewidget.ui \
    MainWindow.ui

TRANSLATIONS += \
    TEMPLATE_en_CA.ts
CONFIG += lrelease
CONFIG += embed_translations

unix {
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
}
