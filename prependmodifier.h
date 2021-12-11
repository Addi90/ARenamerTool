#ifndef PREPENDMODIFIER_H
#define PREPENDMODIFIER_H

#include <QDebug>
#include "modifier.h"

class PrependModifier : public Modifier
{
public:
    static QString prependStr;
    static QString modify(QString currName);
    PrependModifier();
public slots:
    static void prepend(const QString &newPrepStr);
};

#endif // PREPENDMODIFIER_H
