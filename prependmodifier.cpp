#include "prependmodifier.h"

QString PrependModifier::prependStr;

QString PrependModifier::modify(QString currName)
{
    return prependStr + currName;
}

PrependModifier::PrependModifier()
{

}

void PrependModifier::prepend(const QString &newPrepStr)
{
    prependStr = newPrepStr;
    qDebug() << "prependStr: "<< prependStr;

}
