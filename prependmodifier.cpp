#include "prependmodifier.h"

QString PrependModifier::prependStr;
int PrependModifier::remNumChars;
unsigned int PrependModifier::options;


QString PrependModifier::modify(QString currName)
{
    if(options & REMOVE_CHARS){
        currName = currName.mid(remNumChars,currName.length());
    }

    return prependStr + currName;
}

int PrependModifier::modify(QList<RenameFile *> &)
{

}

PrependModifier::PrependModifier()
{

}

void PrependModifier::prependString(const QString &newPrepStr)
{
    prependStr = newPrepStr;
    qDebug() << "prependStr: "<< prependStr;

}

void PrependModifier::removeChars(const int &num)
{
    remNumChars = num;
    qDebug() << "remNumChars: "<< remNumChars;
}
