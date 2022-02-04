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
        if(frontNum > 0){
            (*renameFileList).at(i)->newBaseName = (*renameFileList).at(i)->newBaseName.mid(
                    frontNum
                    );
        }
        if(backNum > 0){
            (*renameFileList).at(i)->newBaseName = (*renameFileList).at(i)->newBaseName.left(
                    (*renameFileList).at(i)->newBaseName.length()-
                    backNum
                    );
        }
        if((options & REMOVE_RANGE)
                && (rangeEnd >= rangeStart)){

            if(options & REMOVE_UNTIL_END){
                (*renameFileList).at(i)->newBaseName =
                        (*renameFileList).at(i)->newBaseName.replace(
                            rangeStart,
                            ((*renameFileList).at(i)->newBaseName.length()-rangeStart),
                            "");
                continue;
            }

            /* check for length of filename in case if the set range is longer */
            if(rangeEnd < (*renameFileList).at(i)->newBaseName.length()){
                (*renameFileList).at(i)->newBaseName =
                        (*renameFileList).at(i)->newBaseName.replace(
                            rangeStart,
                            (rangeEnd-rangeStart),
                            "");
            }
            else{
                (*renameFileList).at(i)->newBaseName =
                        (*renameFileList).at(i)->newBaseName.replace(
                            rangeStart,
                            ((*renameFileList).at(i)->newBaseName.length()-rangeStart),
                            "");
            }
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
