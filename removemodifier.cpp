#include "removemodifier.h"

unsigned int RemoveModifier::frontNum;
unsigned int RemoveModifier::backNum;
unsigned int RemoveModifier::options;
unsigned int RemoveModifier::rangeStart;
unsigned int RemoveModifier::rangeEnd;

int RemoveModifier::modify(QList<RenameFile *> *renameFileList)
{
    int i;

    for(i=0;i< renameFileList->length();i++){
        if(options & REMOVE_FRONT){
            (*renameFileList).at(i)->newBaseName = (*renameFileList).at(i)->newBaseName.mid(
                    frontNum
                    );
        }
        if(options & REMOVE_BACK){
            (*renameFileList).at(i)->newBaseName = (*renameFileList).at(i)->newBaseName.left(
                    (*renameFileList).at(i)->newBaseName.length()-
                    backNum
                    );
        }
        if((options & REMOVE_RANGE)
                && (rangeEnd >= rangeStart)
                && (rangeEnd < (*renameFileList).at(i)->newBaseName.length())
                ){
            (*renameFileList).at(i)->newBaseName =
                    (*renameFileList).at(i)->newBaseName.replace(rangeStart,(rangeEnd-rangeStart),"");
        }

    }

    return i;

}

RemoveModifier::RemoveModifier()
{

}

void RemoveModifier::removeFrontChars(const int &num)
{
    frontNum = num;
    qDebug() << "frontNum: "<< frontNum;
}

void RemoveModifier::removeBackChars(const int &num)
{
    backNum = num;
    qDebug() << "backNum: "<< backNum;
}

void RemoveModifier::removeRangeStart(const int &num)
{
    rangeStart = num - 1;
    qDebug() << "rangeStart: " << rangeStart;
}

void RemoveModifier::removeRangeEnd(const int &num)
{
    rangeEnd = num;
    qDebug() << "rangeEnd: " << rangeEnd;
}
