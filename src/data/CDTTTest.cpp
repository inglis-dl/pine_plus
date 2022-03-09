#include "CDTTTest.h"

#include "ExcelQueryHelper.h"
#include "../auxiliary/Utilities.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>

// the minimum output data keys required from a successful a test
//
CDTTTest::CDTTTest()
{
    // test paramaters from Main sheet
    //
    m_outputKeyList << "subject_id";
    m_outputKeyList << "datetime";
    m_outputKeyList << "language";
    m_outputKeyList << "talker";
    m_outputKeyList << "mode";
    m_outputKeyList << "digits";
    m_outputKeyList << "list_number";
    m_outputKeyList << "msk_signal";
    m_outputKeyList << "test_ear";
    m_outputKeyList << "sp_level";
    m_outputKeyList << "msk_level";
    m_outputKeyList << "speech_reception_threshold";
    m_outputKeyList << "standard_deviation";
    m_outputKeyList << "reversal_count";
    m_outputKeyList << "trial_count";
}

void CDTTTest::simulate(const QString &barcode)
{
  reset();
  addMetaData("subject_id",barcode);
  addMetaData("datetime",QDateTime::currentDateTime());
  addMetaData("language","EN_CA");
  addMetaData("talker","Male");
  addMetaData("mode","Adaptive");
  addMetaData("digits","TRIPLET-80");
  addMetaData("list_number",1);
  addMetaData("msk_signal","SSNOISE");
  addMetaData("test_ear","Binaural");
  addMetaData("sp_level",65.0f);
  addMetaData("msk_level",65.0f);

  // typical double range from -14 to +2
  //
  double mu = QRandomGenerator::global()->generateDouble();
  double srt = Utilities::interp(-14.0f,2.0f,mu);
  addMetaData("speech_reception_threshold",srt);

  //typical double range 1 - 5
  //
  double stddev = Utilities::interp(1.0f,5.0f,mu);
  addMetaData("standard_deviation",stddev);

  // typical integer range 6 to 20
  //
  addMetaData("reversal_count",QRandomGenerator::global()->bounded(6, 20));
}

void CDTTTest::fromDatabase(const QSqlDatabase &db)
{
  if(db.isOpen())
  {
    reset();
    bool ok = readBarcode(db);
    if(ok)
    {
      ok = readMetaData(db);
    }
    if(ok)
    {
      ok = readSummary(db);
    }
    if(ok)
    {
      readTrialData(db);
    }
  }
}

bool CDTTTest::readBarcode(const QSqlDatabase &db)
{
    // get the barcode <=> subject_id
    //
    qDebug() << "-----------getting barcode...";

    QStringList header;
    header << "Subject ID:";
    ExcelQueryHelper helper("A1","B1","Main");
    helper.setOrder(ExcelQueryHelper::Order::Row);
    helper.setHeader(header);
    bool ok = true;
    if((ok = helper.buildQuery(db)))
    {
      helper.processQuery();
      QJsonObject obj = helper.getOutput();
      if(obj.contains("header_valid") &&
         obj["header_valid"].toBool())
      {
         addMetaData("subject_id",obj["Subject ID:"].toString());
      }
      else
          ok = false;

      qDebug() << helper.getOutput().toVariantMap();
    }
    return ok;
}

bool CDTTTest::readMetaData(const QSqlDatabase &db)
{
    qDebug() << "-----------getting meta data...";
    // get the meta data
    ExcelQueryHelper helper = ExcelQueryHelper("A4","J5","Main");
    bool ok = true;
    if((ok = helper.buildQuery(db)))
    {
      QStringList header;
      header << "Date & time"
             << "Language"
             << "Talker"
             << "Mode"
             << "Digits"
             << "List #"
             << "MSK signal"
             << "Test Ear"
             << "SP level"
             << "MSK level";
      helper.setHeader(header);
      helper.processQuery();
      QJsonObject obj = helper.getOutput();
      if(obj.contains("header_valid") &&
         obj["header_valid"].toBool())
      {
         QString s = obj["Date & time"].toString().simplified().replace(", "," ");
         addMetaData("datetime",QDateTime::fromString(s, "yyyy-MM-dd hh:mm:ss"));
         addMetaData("language",obj["Language"].toString());
         addMetaData("talker",obj["Talker"].toString());
         addMetaData("mode",obj["Mode"].toString());
         addMetaData("digits",obj["Digits"].toString());
         addMetaData("list_number",obj["List #"].toInt());
         addMetaData("msk_signal",obj["MSK signal"].toString());
         addMetaData("test_ear",obj["Test Ear"].toString());
         addMetaData("sp_level",obj["SP level"].toDouble());
         addMetaData("msk_level",obj["MSK level"].toDouble());
      }
      else
          ok = false;

      qDebug() << helper.getOutput().toVariantMap();
    }
    return ok;
}

bool CDTTTest::readSummary(const QSqlDatabase &db)
{
    qDebug() << "-----------getting summary...";
    // get the summary results
    ExcelQueryHelper helper = ExcelQueryHelper("K4","M5","Main");
    bool ok = true;
    if((ok = helper.buildQuery(db)))
    {
      QStringList header;
      header << "SRT" << "St# Dev#" << "Reversals";
      helper.setHeader(header);
      helper.processQuery();
      QJsonObject obj = helper.getOutput();
      if(obj.contains("header_valid") &&
         obj["header_valid"].toBool())
      {
        addMetaData("speech_reception_threshold",obj["SRT"].toDouble());
        addMetaData("standard_deviation",obj["St# Dev#"].toDouble());
        addMetaData("reversal_count",obj["Reversals"].toInt());
      }
      else
        ok = false;

      qDebug() << helper.getOutput().toVariantMap();
    }
    return ok;
}

bool CDTTTest::readTrialData(const QSqlDatabase &db)
{
    qDebug() << "-----------getting number of responses...";
    // get the number of stimulus and response digits
    // by querying the first column of the sheet
    //
    QString sheet = QString("%1-%2").arg(
      getMetaData("language").toString(),
      getMetaData("talker").toString());

    ExcelQueryHelper helper = ExcelQueryHelper("A13","A60",sheet);
    bool ok = true;
    if((ok = helper.buildQuery(db)))
    {
      helper.processQuery();
      qDebug() << helper.getOutput().toVariantMap();
    }
    else
      return ok;

    QJsonObject obj = helper.getOutput();
    QJsonArray arr = obj["column_0"].toArray();
    int num_row = arr.last().toInt();
    addMetaData("trial_count",num_row);

    QString cell_suffix = QString::number(13+num_row-1);
    QString endCell = "D" + cell_suffix;

    qDebug() << "-----------getting stimulus digits...";
    // get the stimulus digits
    helper = ExcelQueryHelper("B13",endCell,sheet);

    QVector<CDTTMeasurement> measures;
    if((ok = helper.buildQuery(db)))
    {
      helper.setOrder(ExcelQueryHelper::Order::Row);
      helper.setPrefix("stimulus_");
      helper.processQuery();
      obj = helper.getOutput();
      int index = 0;
      for(auto it = obj.constBegin(), end=obj.constEnd(); it!=end; it++)
      {
         CDTTMeasurement m;
         index++;
         m.setAttribute("trial",index);
         m.setAttribute(it.key(),it.value().toVariant());
         measures.push_back(m);
      }
    }
    else
      return ok;

    qDebug() << "-----------getting response digits...";
    // get the response digits
    endCell = "G" + cell_suffix;
    helper = ExcelQueryHelper("E13",endCell,sheet);
    if((ok = helper.buildQuery(db)))
    {
      helper.setOrder(ExcelQueryHelper::Order::Row);
      helper.setPrefix("response_");
      helper.processQuery();
      obj = helper.getOutput();
      int index = 0;
      for(auto it = obj.constBegin(), end=obj.constEnd(); it!=end; it++)
      {
        if(index < measures.size())
        {
           CDTTMeasurement m = measures.at(index);
           m.setAttribute(it.key(),it.value().toVariant());
           measures.replace(index,m);
        }
        index++;
      }
    }
    if(ok)
    {
      foreach(auto m, measures)
        addMeasurement(m);
    }
    return ok;
}

// String representation for debug and GUI display purposes
//
QString CDTTTest::toString() const
{
    QString str;
    if(isValid())
    {
        QStringList list;
        foreach(auto m, m_measurementList)
        {
          list << m.toString();
        }
        str = list.join("\n");
    }
    return str;
}

bool CDTTTest::isValid() const
{
    bool okMeta = true;
    foreach(auto key, m_outputKeyList)
    {
      if(!hasMetaData(key))
      {
         okMeta = false;
         break;
       }
    }
    bool okTest = 0 < getNumberOfMeasurements();
    if(okTest)
    {
      foreach(auto m, m_measurementList)
      {
        if(!m.isValid())
        {
          okTest = false;
          break;
        }
      }
    }
    return okMeta && okTest;
}

// String keys are converted to snake_case
//
QJsonObject CDTTTest::toJsonObject() const
{
    QJsonArray jsonArr;
    foreach(auto m, m_measurementList)
    {
      jsonArr.append(m.toJsonObject());
    }
    QJsonObject json;
    if(hasMetaData())
      json.insert("test_meta_data",m_metaData.toJsonObject());
    json.insert("test_results",jsonArr);
    return json;
}
