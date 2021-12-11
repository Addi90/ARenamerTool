#include "appendmodifier.h"

QString AppendModifier::appendStr;
int AppendModifier::remNumChars;
unsigned int AppendModifier::options;


QString AppendModifier::modify(QString currName)
{
    if(options & REMOVE_CHARS){
        currName = currName.mid(remNumChars,currName.length());
    }

    return currName + appendStr;
}

AppendModifier::AppendModifier()
{

}

void AppendModifier::appendString(const QString &newAppStr)
{
    appendStr = newAppStr;
    qDebug() << "appendStr: "<< appendStr;
}

void AppendModifier::removeChars(const int &num)
{
    remNumChars = num;
    qDebug() << "remNumChars: "<< remNumChars;
}
