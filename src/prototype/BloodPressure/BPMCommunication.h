#ifndef BPMCOMMUNICATION_H
#define BPMCOMMUNICATION_H

#include <QObject>
#include <QHidDevice>
#include <QString>
#include <QQueue>
#include <functional>
#include <iostream>
using namespace std;

#include "BPMMessage.h"

class BPMCommunication: public QObject
{
	Q_OBJECT
public:
	explicit BPMCommunication(QObject* parent = Q_NULLPTR);
public slots:
	void Connect(const int vid, const int pid);
	void Measure();
	void Abort();

signals:
	void ConnectionStatus(bool connected);
	void MeasurementReady(QString measurement);

private:
	int Start();
	int Stop();
	int Cycle();
	int Clear();
	int Review();
	void WriteCommand(quint8 msgId, quint8 data0, quint8 data1 = 0x00, quint8 data2 = 0x00, quint8 data3 = 0x00);
	void Read();

	template <typename T>
	T TimedReadLoop(int seconds, T defaultReturnVal, T continueVal, function<T()> func);

	QHidDevice* m_bpm200;
	QQueue<BPMMessage>* m_msgQueue;

	int defaultVal = -1;
	int continueVal = -2;
};

#endif //BPMCOMMUNICATION_H
