#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "../../managers/BloodPressureManager.h"
#include <QStandardItemModel>

QT_FORWARD_DECLARE_CLASS(QCloseEvent)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

    // This method internally calls readInput
    //
    void initialize();

    // Call after initialize, launch the application and run
    // the device
    //
    void run();

    void setInputFileName(const QString& name) { m_inputFileName = name; }
    QString getInputFileName() const { return m_inputFileName; }

    void setOutputFileName(const QString& name) { m_outputFileName = name; }
    QString getOutputFileName() const { return m_outputFileName; }

    void setMode(const QString& getMode) { m_mode = getMode.toLower(); }
    QString getMode() const { return m_mode; }

    void setVerbose(const bool& verbose) { m_verbose = verbose; }
    bool isVerbose() { return m_verbose; }

public slots:
    void writeOutput();
    void bpmDisconnected(const bool &connected);

protected:
    void closeEvent(QCloseEvent*) override;

private:
    void setupConnections();
    void initializeButtonState();
    void initializeArmBandDropDowns();
    void initializeConnectionIdsUi();
    void readInput();
    void populateBarcodeDisplay();
    void updatePossiblePidOptions();

    Ui::MainWindow* ui;
    QString m_inputFileName;
    QString m_outputFileName;
    QString m_mode;
    bool m_verbose;

    QMap<QString, QVariant> m_inputData;
    QMap<QString, QVariant> m_outputData;

    BloodPressureManager m_manager;

    QStandardItemModel m_model;
};

#endif MAINWINDOW_H