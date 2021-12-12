#include "appendmodifier.h"

QString AppendModifier::appendStr;
int AppendModifier::remNumChars;
unsigned int AppendModifier::options;
unsigned int AppendModifier::startNum;

QString AppendModifier::modify(QString currName)
{
    if(options & REMOVE_CHARS){
        currName = currName.left(currName.length()-remNumChars);
    }

    return currName + appendStr;
}

int AppendModifier::modify(QList<RenameFile *>* renameFileList)
{
    int i;
    int count = startNum;

    for(i=0;i< renameFileList->length();i++){

        QString currName = (*renameFileList).at(i)->newBaseName;

        if(options & REMOVE_CHARS){
            currName = currName.left(currName.length()-remNumChars);
        }

        currName += appendStr;

        if(options & ADD_COUNT){
            currName += QString::number(count);
        }

        (*renameFileList).at(i)->newBaseName = currName;
        count++;
    }

    return i;
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
