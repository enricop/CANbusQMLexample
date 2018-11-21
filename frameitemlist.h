#ifndef FRAMEITEMLIST_H
#define FRAMEITEMLIST_H

#include <QCanBusFrame>

class FrameItemList : public QObject
{
    Q_OBJECT

public:
    explicit FrameItemList(QObject *parent = nullptr);

    int size() const;
    const QCanBusFrame& at(int i) const;

    void appendItem(const QCanBusFrame &item);

signals:
    void preItemAppended();
    void postItemAppended();

private:
    QList<QCanBusFrame> mItemsList;
};

#endif // FRAMEITEMLIST_H
