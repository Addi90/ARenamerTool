#include "numbermodifier.h"

QString NumberModifier::appendStr;
unsigned int NumberModifier::insertPos;
unsigned int NumberModifier::startNum;
unsigned int NumberModifier::options;

int NumberModifier::modify(QList<RenameFile *> *renameFileList)
{
    int i;
    for(i=0;i< renameFileList->length();i++){
        if(options & PREFIX){
            (*renameFileList).at(i)->newBaseName.prepend(QString::number(startNum+i));
        }
        if(options & INSERT){
            (*renameFileList).at(i)->newBaseName.insert(insertPos,QString::number(startNum+i));
        }
        if(options & SUFFIX){
            (*renameFileList).at(i)->newBaseName.append(QString::number(startNum+i));
        }
    }
    return i;
}

NumberModifier::NumberModifier()
{

}

void NumberModifier::startNumber(const int &num)
{
    startNum = num;
    qDebug() << "startNum: " << startNum;
}

void NumberModifier::insertPosition(const int &pos)
{
    insertPos = pos;
    qDebug() << "startNum: " << insertPos;
}
