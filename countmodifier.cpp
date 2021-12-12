#include "countmodifier.h"

unsigned int CountModifier::options;
unsigned int CountModifier::startNum;

int CountModifier::modify(QList<RenameFile *>* renameFileList)
{
    int count = startNum;
    for(int i=0;i< renameFileList->length();i++){
        if(options & PREPEND)
            (*renameFileList).at(i)->newBaseName = QString::number(count) + (*renameFileList).at(i)->newBaseName;
        if(options & APPEND)
            (*renameFileList).at(i)->newBaseName = (*renameFileList).at(i)->newBaseName + QString::number(count);
        qDebug() << "name after count: " << (*renameFileList).at(i)->newBaseName << " startNum: " << startNum;
        count++;
    };
    return count;
}

CountModifier::CountModifier()
{

}

void CountModifier::startNumber(const unsigned int &startNumber)
{
    startNum = startNumber;
}
