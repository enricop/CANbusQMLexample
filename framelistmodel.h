#ifndef FRAMELISTMODEL_H
#define FRAMELISTMODEL_H

#include <QAbstractListModel>
#include "frameitemlist.h"

class FrameListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(FrameItemList *list READ list WRITE setList)

public:
    explicit FrameListModel(QObject *parent = nullptr);

    enum FrameRoles {
        TimestampRole = Qt::UserRole + 1,
        FlagsRole,
        MessageRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int, QByteArray> roleNames() const override;

    // read/write list property
    FrameItemList *list() const;
    void setList(FrameItemList *list);

private:
    FrameItemList *mframes;
};

#endif // FRAMELISTMODEL_H
