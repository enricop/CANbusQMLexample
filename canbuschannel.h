#ifndef CANBUSCONNECTION_H
#define CANBUSCONNECTION_H

#include <QObject>
#include <QCanBusDevice>
#include "frameitemlist.h"

class CANbusChannel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString connectioninfo READ getconninfo WRITE setconninfo NOTIFY coninfoChanged)

public:
    explicit CANbusChannel(FrameItemList *framelist, QObject *parent = nullptr);
    ~CANbusChannel();

    QString getconninfo() {
        return m_connectionInfo;
    }
    void setconninfo(QString info) {
        if (info == m_connectionInfo)
            return;
        m_connectionInfo = info;
        emit coninfoChanged();
    }

    Q_INVOKABLE void sendFrame(const QString canid, QString message) const;

signals:
    void coninfoChanged();

public slots:
    void connectDevice();
    void disconnectDevice();

    void processReceivedFrames();
    void processErrors(QCanBusDevice::CanBusError error);
    void processFramesWritten(qint64 count);
private:
    QCanBusDevice *m_canDevice;
    QString m_connectionInfo;
    FrameItemList *m_framelist;
};

#endif // CANBUSCONNECTION_H
