#include "replacemodifier.h"

QString ReplaceModifier::replaceStr;
QRegularExpression ReplaceModifier::regexStr;
QString ReplaceModifier::newStr;
unsigned int ReplaceModifier::options;

QString ReplaceModifier::modify(QString currName)
{
    currName.replace(replaceStr,newStr);
    return currName;
}

int ReplaceModifier::modify(QList<RenameFile *> *renameFileList)
{
    int i;
    for(i=0;i< renameFileList->length();i++){
        if(options & REPLACE_REGEX){
            if(options & CASE_SENSITIVE){
                (*renameFileList).at(i)->newBaseName.replace(regexStr,newStr);
            }
            else{
                regexStr.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
                (*renameFileList).at(i)->newBaseName.replace(regexStr,newStr);
            }
        }
        else{
            if(options & CASE_SENSITIVE){
                (*renameFileList).at(i)->newBaseName.replace(replaceStr,newStr);
            }
            else{
                regexStr.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
                (*renameFileList).at(i)->newBaseName.replace(replaceStr,newStr);
            }
        }
            (*renameFileList).at(i)->newBaseName.replace(replaceStr,newStr);
    }
    return i;
}

void ReplaceModifier::replaceString(const QString &replaceExp)
{
    if(options & REPLACE_REGEX){
        regexStr.setPattern(replaceExp);
    }
    else
        replaceStr = replaceExp;
}

void ReplaceModifier::newString(const QString &newString)
{
    newStr = newString;
}

void ReplaceModifier::setRegexOption(const int &status)
{
    if(status == Qt::Unchecked){
        options &= ~(REPLACE_REGEX);
    }
    else
        options |= REPLACE_REGEX;
}

void ReplaceModifier::setCaseSensitiveOption(const int &status)
{
    if(status == Qt::Unchecked){
        options &= ~(CASE_SENSITIVE);
    }
    else
        options |= CASE_SENSITIVE;
}


ReplaceModifier::ReplaceModifier()
{

}

