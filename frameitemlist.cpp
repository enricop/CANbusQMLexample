#include "frameitemlist.h"

FrameItemList::FrameItemList(QObject *parent) : QObject(parent)
{
}

int FrameItemList::size() const {
    return mItemsList.size();
}

const QCanBusFrame& FrameItemList::at(int i) const {
    return mItemsList.at(i);
}

void FrameItemList::appendItem(const QCanBusFrame &item)
{
    emit preItemAppended();

    mItemsList.append(item);

    emit postItemAppended();
}
