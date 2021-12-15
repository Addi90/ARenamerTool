#include "ifthenmodifier.h"

QString IfThenModifier::conditionStr;
QString IfThenModifier::consequenceStr;
unsigned int IfThenModifier::insertPos;
unsigned int IfThenModifier::options;
QRegularExpression IfThenModifier::conditionRegex;

int IfThenModifier::modify(QList<RenameFile *> *renameFileList)
{
    /* handle condition */
    int i;
    for(i=0;i< renameFileList->length();i++){

        if((options & CONTAINS) && conditionStr != ""){
            if(options & CASE_SENSITIVE){
                if((options & REGEX) && conditionRegex.match((*renameFileList).at(i)->baseName).hasMatch()){
                    handleConsequence(renameFileList->at(i));
                }
                else if((*renameFileList).at(i)->baseName.contains(conditionStr,Qt::CaseSensitive)){
                    handleConsequence(renameFileList->at(i));
                }
            }
            else if((options & REGEX) && conditionRegex.match((*renameFileList).at(i)->baseName,QRegularExpression::CaseInsensitiveOption).hasMatch()){
                handleConsequence(renameFileList->at(i));
            }
            else if((*renameFileList).at(i)->baseName.contains(conditionStr,Qt::CaseInsensitive)){
                handleConsequence(renameFileList->at(i));
            }
        }
        else if((options & CONTAINS_NOT) && conditionStr != ""){
            if(options & CASE_SENSITIVE){
                if((options & REGEX) && !conditionRegex.match((*renameFileList).at(i)->baseName).hasMatch()){
                    handleConsequence(renameFileList->at(i));
                }
                else if(!(*renameFileList).at(i)->baseName.contains(conditionStr,Qt::CaseSensitive)){
                    handleConsequence(renameFileList->at(i));
                }
            }
            else if((options & REGEX) && !conditionRegex.match((*renameFileList).at(i)->baseName,QRegularExpression::CaseInsensitiveOption).hasMatch()){
                handleConsequence(renameFileList->at(i));
            }
            else if(!(*renameFileList).at(i)->baseName.contains(conditionStr,Qt::CaseInsensitive)){
                handleConsequence(renameFileList->at(i));
            }
        }
    }



    return i;
}

IfThenModifier::IfThenModifier()
{
    
}

void IfThenModifier::conditionExp(const QString &str)
{
    if(options & REGEX){
        conditionRegex.setPattern(str);
    }
    else
        conditionStr = str;
    qDebug() << "conditionStr: " << conditionStr;
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

void IfThenModifier::setRegexOption(const int &status)
{
    if(status == 1){
        options |= REGEX;
    }else
        options &= ~(REGEX);
}

void IfThenModifier::setCaseSensitiveOption(const int &status)
{
    if(status == 1){
        options |= CASE_SENSITIVE;
    }else
        options &= ~(CASE_SENSITIVE);
}

int IfThenModifier::handleConsequence(RenameFile *renameFile)
{
    int i;

        if(options & INSERT){     
            renameFile->newBaseName =
                    renameFile->newBaseName.insert(insertPos,consequenceStr);
        }
        if(options & ADD_PREFIX){
            renameFile->newBaseName =
                    renameFile->newBaseName.prepend(consequenceStr);
        }
        if(options & ADD_SUFFIX){
            renameFile->newBaseName =
                    renameFile->newBaseName.append(consequenceStr);
        }

    return 0;
}
