QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport bluetooth sql usb

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auxiliary/Constants.cpp \
    auxiliary/CRC8.cpp \
    auxiliary/CommandLineParser.cpp \
    data/Measurement.cpp \
    data/HearingTest.cpp \
    data/BloodPressureTest.cpp \
    data/TonometerTest.cpp \
    data/BodyCompositionTest.cpp \
    data/CDTTTest.cpp \
    data/ExcelQueryHelper.cpp \
    data/AccessQueryHelper.cpp \
    data/FraxTest.cpp \
    data/WeighScaleTest.cpp \
    data/ChoiceReactionTest.cpp \
    data/TemperatureTest.cpp \
    data/HearingMeasurement.cpp \
    data/BloodPressureMeasurement.cpp \
    data/BodyCompositionMeasurement.cpp \
    data/CDTTMeasurement.cpp \
    data/FraxMeasurement.cpp \
    data/TonometerMeasurement.cpp \
    data/WeightMeasurement.cpp \
    data/ChoiceReactionMeasurement.cpp \
    data/TemperatureMeasurement.cpp \
    managers/ManagerBase.cpp \
    managers/AudiometerManager.cpp \
    managers/ChoiceReactionManager.cpp \
    managers/SerialPortManager.cpp \
    managers/BluetoothLEManager.cpp \
    managers/BloodPressureManager.cpp \
    managers/BPMMessage.cpp \
    managers/BPMCommunication.cpp \
    managers/FraxManager.cpp \
    managers/TonometerManager.cpp \
    managers/CDTTManager.cpp \
    managers/WeighScaleManager.cpp \
    managers/BodyCompositionAnalyzerManager.cpp \
    widgets/BarcodeWidget.cpp \
    dialogs/AudiometerDialog.cpp \
    dialogs/BodyCompositionDialog.cpp \
    dialogs/BloodPressureDialog.cpp \
    dialogs/CDTTDialog.cpp \
    dialogs/ChoiceReactionDialog.cpp \
    dialogs/FraxDialog.cpp \
    dialogs/ThermometerDialog.cpp \
    dialogs/TonometerDialog.cpp \
    dialogs/WeighScaleDialog.cpp \
    dialogs/DialogBase.cpp \
    dialogs/DialogFactory.cpp \
    CypressApplication.cpp \
    main.cpp 

HEADERS += \
    auxiliary/Constants.h \
    auxiliary/Utilities.h \
    auxiliary/CRC8.h \
    auxiliary/CommandLineParser.h \
    data/Measurement.h \
    data/TestBase.h \
    data/HearingTest.h \
    data/BloodPressureTest.cpp \
    data/TonometerTest.h \
    data/BodyCompositionTest.h \
    data/CDTTTest.h \
    data/ExcelQueryHelper.h \
    data/AccessQueryHelper.h \
    data/FraxTest.h \
    data/WeighScaleTest.h \
    data/TonometerMeasurement.h \
    data/ChoiceReactionTest.h \
    data/TemperatureTest.h \
    data/HearingMeasurement.h \
    data/BloodPressureMeasurement.h \
    data/BodyCompositionMeasurement.h \
    data/CDTTMeasurement.h \
    data/FraxMeasurement.h \
    data/WeightMeasurement.h \
    data/ChoiceReactionMeasurement.h \
    data/TemperatureMeasurement.h \
    managers/ManagerBase.h \
    managers/AudiometerManager.h \
    managers/ChoiceReactionManager.h \
    managers/SerialPortManager.h \
    managers/BluetoothLEManager.h \
    managers/BloodPressureManager.h \
    managers/BPMMessage.h \
    managers/BPMCommunication.h \
    managers/FraxManager.h \
    managers/BodyCompositionAnalyzerManager.h \
    managers/TonometerManager.h \
    managers/CDTTManager.h \
    managers/WeighScaleManager.h \
    widgets/BarcodeWidget.h \
    dialogs/AudiometerDialog.h \
    dialogs/BodyCompositionDialog.h \
    dialogs/BloodPressureDialog.h \
    dialogs/CDTTDialog.h \
    dialogs/ChoiceReactionDialog.h \
    dialogs/FraxDialog.h \
    dialogs/ThermometerDialog.h \
    dialogs/TonometerDialog.h \
    dialogs/WeighScaleDialog.h \
    dialogs/DialogBase.h \
    dialogs/DialogFactory.h \
    CypressApplication.h

TRANSLATIONS += \
    Cypress_en_CA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
  widgets/barcodewidget.ui \
  dialogs/audiometerdialog.ui \
  dialogs/bloodpressuredialog.ui \
  dialogs/bodycompositiondialog.ui \
  dialogs/thermometerdialog.ui \
  dialogs/runnabledialog.ui \
  dialogs/weighscaledialog.ui

RESOURCES += \
