#include "wheeleventfilter.h"

#include <QEvent>
#include <QWheelEvent>
#include <QPlainTextEdit>

WheelEventFilter::WheelEventFilter(QObject *parent)
    : QObject(parent)
{

}

bool WheelEventFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheel = static_cast<QWheelEvent*>(event);
        if (wheel->modifiers() == Qt::ControlModifier) {
            QPlainTextEdit* textEdit = static_cast<QPlainTextEdit*>(obj);
            if (wheel->delta() > 0)
                textEdit->zoomIn(2);
            else
                textEdit->zoomOut(2);
            return true;
        }
    }
    return false;
}
