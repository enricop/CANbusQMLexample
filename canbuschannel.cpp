#include "canbuschannel.h"

#include <QCanBus>
#include <QVariant>

CanBusChannel::CanBusChannel(QObject *parent) : QObject(parent)
{
    QString errorString;
    m_canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
    if (!m_canDevice) {
        //m_status->setText(tr("Error creating device '%1', reason: '%2'")
        //                  .arg(p.pluginName).arg(errorString));
        return;
    }

    /*
    m_numberFramesWritten = 0;

    connect(m_canDevice, &QCanBusDevice::errorOccurred, this, &MainWindow::processErrors);
    connect(m_canDevice, &QCanBusDevice::framesReceived, this, &MainWindow::processReceivedFrames);
    connect(m_canDevice, &QCanBusDevice::framesWritten, this, &MainWindow::processFramesWritten);
    */

    m_canDevice->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, QVariant::fromValue(true));

    /*
    if (!m_canDevice->connectDevice()) {
        m_status->setText(tr("Connection error: %1").arg(m_canDevice->errorString()));

        delete m_canDevice;
        m_canDevice = nullptr;
    } else {
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);

        m_ui->sendFrameBox->setEnabled(true);

        QVariant bitRate = m_canDevice->configurationParameter(QCanBusDevice::BitRateKey);
        if (bitRate.isValid()) {
            m_status->setText(tr("Plugin: %1, connected to %2 at %3 kBit/s")
                    .arg(p.pluginName).arg(p.deviceInterfaceName)
                    .arg(bitRate.toInt() / 1000));
        } else {
            m_status->setText(tr("Plugin: %1, connected to %2")
                    .arg(p.pluginName).arg(p.deviceInterfaceName));
        }
    }*/
}

CanBusChannel::~CanBusChannel()
{

}

void CanBusChannel::processReceivedFrames()
{

}

void CanBusChannel::processFramesWritten(qint64)
{

}

void CanBusChannel::sendFrame(const QString canid, QString message) const
{
    const uint frameId = canid.toUInt(nullptr, 16);
    const QByteArray payload = QByteArray::fromHex(message.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);

    m_canDevice->writeFrame(frame);
}

void CanBusChannel::connectDevice()
{

}

void CanBusChannel::disconnectDevice()
{

}
