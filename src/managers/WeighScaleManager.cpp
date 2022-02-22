#include "WeighScaleManager.h"

#include "../data/WeighScaleTest.h"

#include <QDateTime>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QSerialPortInfo>
#include <QSettings>
#include <QStandardItemModel>
#include <QtMath>

WeighScaleManager::WeighScaleManager(QObject *parent) : SerialPortManager(parent)
{
  setGroup("weigh_scale");

  // all managers must check for barcode and language input values
  //
  m_inputKeyList << "barcode";
  m_inputKeyList << "language";

  m_test.setMaximumNumberOfMeasurements(2);
}

void WeighScaleManager::buildModel(QStandardItemModel* model) const
{
    for(int row = 0; row < m_test.getMaximumNumberOfMeasurements(); row++)
    {
        QString s = "NA";
        WeightMeasurement m = m_test.getMeasurement(row);
        if(m.isValid())
           s = m.toString();
        QStandardItem* item = model->item(row,0);
        item->setData(s, Qt::DisplayRole);
    }
}

void WeighScaleManager::loadSettings(const QSettings &settings)
{
    QString name = settings.value(getGroup() + "/client/port").toString();
    if(!name.isEmpty())
    {
      setProperty("deviceName", name);
      if(m_verbose)
          qDebug() << "using serial port " << m_deviceName << " from settings file";
    }
}

void WeighScaleManager::saveSettings(QSettings *settings) const
{
    if(!m_deviceName.isEmpty())
    {
      settings->beginGroup(getGroup());
      settings->setValue("client/port",m_deviceName);
      settings->endGroup();
      if(m_verbose)
          qDebug() << "wrote serial port to settings file";
    }
}

void WeighScaleManager::setInputData(const QMap<QString, QVariant> &input)
{
    if(CypressConstants::RunMode::Simulate == m_mode)
    {
        m_inputData["barcode"] = "00000000";
        m_inputData["language"] = "english";
        return;
    }
    bool ok = true;
    m_inputData = input;
    for(auto&& x : m_inputKeyList)
    {
        if(!input.contains(x))
        {
            ok = false;
            qDebug() << "ERROR: missing expected input " << x;
            break;
        }
    }
    if(!ok)
        m_inputData.clear();
}

void WeighScaleManager::clearData()
{
    m_test.reset();
    emit dataChanged();
}

void WeighScaleManager::finish()
{
    m_deviceData.reset();
    m_deviceList.clear();
    m_test.reset();
    if(m_port.isOpen())
        m_port.close();
}

void WeighScaleManager::connectDevice()
{
    clearData();

    if(CypressConstants::RunMode::Simulate == m_mode)
    {
        m_request = QByteArray("i");
        writeDevice();
        return;
    }

    if(m_port.isOpen())
        m_port.close();

    if(m_port.open(QSerialPort::ReadWrite))
    {
      m_port.setDataBits(QSerialPort::Data8);
      m_port.setParity(QSerialPort::NoParity);
      m_port.setStopBits(QSerialPort::OneStop);
      m_port.setBaudRate(QSerialPort::Baud9600);

      connect(&m_port, &QSerialPort::readyRead,
               this, &WeighScaleManager::readDevice);

      connect(&m_port, &QSerialPort::errorOccurred,
              this,[this](QSerialPort::SerialPortError error){
                  Q_UNUSED(error)
                  qDebug() << "AN ERROR OCCURED: " << m_port.errorString();
              });

      connect(&m_port, &QSerialPort::dataTerminalReadyChanged,
              this,[](bool set){
          qDebug() << "data terminal ready DTR changed to " << (set?"high":"low");
      });

      connect(&m_port, &QSerialPort::requestToSendChanged,
              this,[](bool set){
          qDebug() << "request to send RTS changed to " << (set?"high":"low");
      });

      // try and read the scale ID, if we can do that then emit the
      // canMeasure signal
      // the canMeasure signal is emitted from readDevice slot on successful read
      //
      m_request = QByteArray("i");
      writeDevice();
    }
}

void WeighScaleManager::zeroDevice()
{
    m_request = QByteArray("z");
    writeDevice();
}

void WeighScaleManager::measure()
{
    m_request = QByteArray("p");
    writeDevice();
}

void WeighScaleManager::readDevice()
{
    if(CypressConstants::RunMode::Simulate == m_mode)
    {
        QString simdata;
        if("i" == QString(m_request))
         {
           simdata = "12345";
         }
         else if("z" == QString(m_request))
         {
           simdata = "0.0 C body";
         }
         else if("p" == QString(m_request))
         {
            simdata = "36.1 C body";
         }
         m_buffer = QByteArray(simdata.toUtf8());
    }
    else
    {
      QByteArray data = m_port.readAll();
      m_buffer += data;
    }
    if(m_verbose)
      qDebug() << "read device received buffer " << QString(m_buffer);

    if(!m_buffer.isEmpty())
    {
      if("i" == QString(m_request))
      {
        m_deviceData.setCharacteristic("software ID", QString(m_buffer.simplified()));
        // signal the GUI that the measure button can be clicked
        //
        emit message(tr("Ready to measure..."));
        emit canMeasure();
      }
      else if("p" == QString(m_request))
      {
         m_test.fromArray(m_buffer);
         if(m_test.isValid())
         {
           // emit the can write signal
           emit message(tr("Ready to save results..."));
           emit canWrite();
         }
      }
      else if("z" == QString(m_request))
      {
          WeightMeasurement m;
          m.fromArray(m_buffer);
          if(m.isZero())
          {
            // signal the GUI that the measure button can be clicked
            //
            emit message(tr("Ready to measure..."));
            emit canMeasure();
          }
      }

      emit dataChanged();
    }
}

void WeighScaleManager::writeDevice()
{
    // prepare to receive data
    //
    m_buffer.clear();

    if(CypressConstants::RunMode::Simulate == m_mode)
    {
        if(m_verbose)
          qDebug() << "in simulate mode writeDevice with request " << QString(m_request);
        readDevice();
        return;
    }

    m_port.write(m_request);
}

QJsonObject WeighScaleManager::toJsonObject() const
{
    QJsonObject json = m_test.toJsonObject();
    json.insert("device",m_deviceData.toJsonObject());
    return json;
}
