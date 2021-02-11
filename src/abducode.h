#ifndef ABDUCODE_H
#define ABDUCODE_H

#include "texteditor.h"

#include <QObject>

class AbduCode : public QObject
{
    Q_OBJECT
public:
    explicit AbduCode(QObject *parent = nullptr);

signals:

private:
    TextEditor textEditor_;
};

#endif // ABDUCODE_H
