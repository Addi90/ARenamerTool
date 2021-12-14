#include "addmodifier.h"

QString AddModifier::prefixStr;
QString AddModifier::suffixStr;
QString AddModifier::insertStr;
unsigned int AddModifier::insertPos;

unsigned int AddModifier::options;

int AddModifier::modify(QList<RenameFile *> *renameFileList)
{
    int i;

    for(i=0;i< renameFileList->length();i++){
        if(insertStr != ""){
            (*renameFileList).at(i)->newBaseName =
                    (*renameFileList).at(i)->newBaseName.insert(insertPos,insertStr);
        }
        (*renameFileList).at(i)->newBaseName = prefixStr +
                (*renameFileList).at(i)->newBaseName +
                suffixStr;
    }

    return i;
}

AddModifier::AddModifier()
{

}

void AddModifier::prefixString(const QString &newPrefixStr)
{
    prefixStr = newPrefixStr;
    qDebug() << "changed prefixStr to: " << prefixStr;
}

void AddModifier::suffixString(const QString &newSuffixStr)
{
    suffixStr = newSuffixStr;
    qDebug() << "changed suffixStr to: " << suffixStr;
}
