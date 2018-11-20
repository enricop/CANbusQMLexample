#include "FrameListModel.h"

#include "FrameItemList.h"

FrameListModel::FrameListModel(QObject *parent)
    : QAbstractListModel(parent)
    , mframes(nullptr)
{
}

int FrameListModel::rowCount(const QModelIndex & parent) const {
    if (parent.isValid() || !mframes)
        return 0;

    return mframes->size();
}

QVariant FrameListModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid() || index.row() >= mframes->size())
        return QVariant();

    const QCanBusFrame frame = mframes->at(index.row());

    switch (role) {
    case TimestampRole:
        return QString::fromLatin1("%1.%2  ")
                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));
    case FlagsRole:
    {
        QString result = QLatin1String(" --- ");

        if (frame.hasBitrateSwitch())
            result[1] = QLatin1Char('B');
        if (frame.hasErrorStateIndicator())
            result[2] = QLatin1Char('E');
        if (frame.hasLocalEcho())
            result[3] = QLatin1Char('L');

        return result;
    }
    case MessageRole:
        return frame.toString();
    default:
        break;
    }
    return QVariant();
}

Qt::ItemFlags FrameListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable;
}


QHash<int, QByteArray> FrameListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FlagsRole] = "flags";
    roles[MessageRole] = "message";
    roles[TimestampRole] = "timestamp";
    return roles;
}

FrameItemList *FrameListModel::list() const
{
    return mframes;
}

void FrameListModel::setList(FrameItemList *list)
{
    beginResetModel();

    if (mframes)
        mframes->disconnect(this);

    mframes = list;

    if (mframes) {
        connect(mframes, &FrameItemList::preItemAppended, this, [=]() {
            const int index = mframes->size();
            beginInsertRows(QModelIndex(), index, index); // add only one row
        });
        connect(mframes, &FrameItemList::postItemAppended, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}
