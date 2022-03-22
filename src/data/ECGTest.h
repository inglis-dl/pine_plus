#ifndef ECGTEST_H
#define ECGTEST_H

#include "TestBase.h"
#include "ECGMeasurement.h"

class ECGTest : public TestBase<ECGMeasurement>
{
public:
    ECGTest();
    ~ECGTest() = default;

    void fromFile(const QString &);

    // String representation for debug and GUI display purposes
    //
    QString toString() const override;

    bool isValid() const override;

    // String keys are converted to snake_case
    //
    QJsonObject toJsonObject() const override;

    void simulate(const QJsonObject&);

private:

    QList<QString> m_outputKeyList;

};

Q_DECLARE_METATYPE(ECGTest);

#endif // ECGTEST_H
