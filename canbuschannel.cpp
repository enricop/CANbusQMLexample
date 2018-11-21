#include "canbuschannel.h"

#include <QCanBus>
#include <QVariant>
#include <QDebug>

CANbusChannel::CANbusChannel(FrameItemList *framelist, QObject *parent) :
    QObject(parent),
    m_canDevice(nullptr),
    m_framelist(framelist)
{

}

CANbusChannel::~CANbusChannel()
{
    delete m_canDevice;
}

void CANbusChannel::connectDevice()
{
    QString errorString;
    m_canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("vcan0"), &errorString);
    if (!m_canDevice) {
        setconninfo(tr("Error creating device '%1', reason: '%2'").arg("vcan0").arg(errorString));
        return;
    }

    connect(m_canDevice, &QCanBusDevice::errorOccurred, this, &CANbusChannel::processErrors);
    connect(m_canDevice, &QCanBusDevice::framesReceived, this, &CANbusChannel::processReceivedFrames);
    connect(m_canDevice, &QCanBusDevice::framesWritten, this, &CANbusChannel::processFramesWritten);

    m_canDevice->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, QVariant::fromValue(true));

    if (!m_canDevice->connectDevice()) {
        setconninfo(tr("Connection error: %1").arg(m_canDevice->errorString()));

        delete m_canDevice;
        m_canDevice = nullptr;
    }
}

void CANbusChannel::disconnectDevice()
{
    m_canDevice->disconnectDevice();
}

void CANbusChannel::sendFrame(const QString canid, QString message) const
{
    const uint frameId = canid.toUInt(nullptr, 16);
    const QByteArray payload = QByteArray::fromHex(message.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);

    if (!m_canDevice->writeFrame(frame))
        qDebug() << "m_canDevice->writeFrame failed";
}

void CANbusChannel::processErrors(QCanBusDevice::CanBusError error)
{
    switch (error) {
    case QCanBusDevice::ReadError:
    case QCanBusDevice::WriteError:
    case QCanBusDevice::ConnectionError:
    case QCanBusDevice::ConfigurationError:
    case QCanBusDevice::UnknownError:
        setconninfo(m_canDevice->errorString());
        break;
    default:
        break;
    }
}

void CANbusChannel::processReceivedFrames()
{
    if (!m_canDevice)
        return;

    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();

        m_framelist->appendItem(frame);
    }
}

void CANbusChannel::processFramesWritten(qint64 count) {
    setconninfo(tr("%1 frames written").arg(count));
}
