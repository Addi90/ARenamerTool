#include "removemodifier.h"

unsigned int RemoveModifier::frontNum;
unsigned int RemoveModifier::backNum;
unsigned int RemoveModifier::options;

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
