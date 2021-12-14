#include "ifthenmodifier.h"

QString IfThenModifier::conditionStr;
QString IfThenModifier::consequenceStr;
unsigned int IfThenModifier::insertPos;
unsigned int IfThenModifier::options;

int IfThenModifier::modify(QList<RenameFile *> *renameFileList)
{
    int ret = 0;
    /* handle condition */
    if((options & CONTAINS) && conditionStr != ""){
       ret = handleConsequence(renameFileList);
    }
    else if((options & CONTAINS_NOT) && conditionStr != ""){
       ret = handleConsequence(renameFileList);
    }
    return ret;
}

IfThenModifier::IfThenModifier()
{
    
}

void IfThenModifier::conditionString(const QString &str)
{
    conditionStr = str;
    qDebug() << "consequenceStr: " << consequenceStr;
}

void IfThenModifier::consequenceString(const QString &str)
{
    consequenceStr = str;
    qDebug() << "consequenceStr: " << consequenceStr;
}

void IfThenModifier::insertPosition(const int &pos)
{
    insertPos = pos;
    qDebug() << "consequence insert pos: " << insertPos;
}

int IfThenModifier::handleConsequence(QList<RenameFile *> *renameFileList)
{
    int i;

    for(i=0;i< renameFileList->length();i++){
        if(options & INSERT){
            (*renameFileList).at(i)->newBaseName =
                    (*renameFileList).at(i)->newBaseName.insert(insertPos,consequenceStr);
        }
        if(options & ADD_PREFIX){
            (*renameFileList).at(i)->newBaseName =
                    (*renameFileList).at(i)->newBaseName.prepend(consequenceStr);
        }
        if(options & ADD_SUFFIX){
            (*renameFileList).at(i)->newBaseName =
                    (*renameFileList).at(i)->newBaseName.append(consequenceStr);
        }
    }
    return i;
}
