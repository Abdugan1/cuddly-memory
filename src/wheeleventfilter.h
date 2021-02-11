#ifndef WHEELEVENTFILTER_H
#define WHEELEVENTFILTER_H

#include <QObject>

class WheelEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit WheelEventFilter(QObject *parent = nullptr);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
signals:

};

#endif // WHEELEVENTFILTER_H
