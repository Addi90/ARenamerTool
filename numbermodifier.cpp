#include "numbermodifier.h"

QString NumberModifier::appendStr;
unsigned int NumberModifier::insertPos;
unsigned int NumberModifier::startNum;
unsigned int NumberModifier::options;
unsigned int NumberModifier::padding;

int NumberModifier::modify(QList<RenameFile *> *renameFileList)
{
    int i;
    for(i=0;i< renameFileList->length();i++){
        QString num = QString::number(startNum+i);

        /* add padding to number */
        if((padding > 0) && (num.length() < padding)){
            num = num.rightJustified(padding,'0');
        }

        if(options & PREFIX){
            (*renameFileList).at(i)->newBaseName.prepend(num);
        }
        if(options & INSERT){
            (*renameFileList).at(i)->newBaseName.insert(insertPos,num);
        }
        if(options & SUFFIX){
            (*renameFileList).at(i)->newBaseName.append(num);
        }
    }
    return i;
}

NumberModifier::NumberModifier()
{

}

void NumberModifier::paddingSize(const int &num)
{
    padding = num;
    qDebug() << "padding: " << padding;
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
