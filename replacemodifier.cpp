#include "replacemodifier.h"

QString ReplaceModifier::replaceStr;
QString ReplaceModifier::newStr;
unsigned int ReplaceModifier::options;

QString ReplaceModifier::modify(QString currName)
{
    if(options & REPLACE_STRING){
        currName.replace(replaceStr,newStr);
    }
    return currName;
}

void ReplaceModifier::replaceString(const QString &replaceString)
{
    replaceStr = replaceString;
}

void ReplaceModifier::newString(const QString &newString)
{
    newStr = newString;
}


ReplaceModifier::ReplaceModifier()
{

}

