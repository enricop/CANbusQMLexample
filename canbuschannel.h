#ifndef CANBUSCHANNEL_H
#define CANBUSCHANNEL_H

#include <QObject>
#include <QCanBusDevice>

class CanBusChannel : public QObject
{
    Q_OBJECT
public:
    explicit CanBusChannel(QObject *parent = nullptr);
    ~CanBusChannel();

private slots:
    void processReceivedFrames();
    void processFramesWritten(qint64);
    void sendFrame(const QString canid, QString message) const;
    void connectDevice();
    void disconnectDevice();

protected:
    //void closeEvent(QCloseEvent *event) override;

private:
    QCanBusDevice *m_canDevice;
};

#endif // CANBUSCHANNEL_H
