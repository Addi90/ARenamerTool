#ifndef REPLACEMODIFIER_H
#define REPLACEMODIFIER_H

#include "modifier.h"

class ReplaceModifier : public Modifier
{

public:
    enum Option{
            REPLACE_STRING = 0x1,
            REPLACE_REGEX = 0x2,
            CASE_SENSITIVE = 0x4
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString replaceStr;
    static QString newStr;
    static unsigned int options;


    static QString modify(QString currName);
    static int modify(QList<RenameFile*>* renameFileList);

    ReplaceModifier();
public slots:
    static void replaceString(const QString &replaceString); // Todo: Name it replaceExp
    static void newString(const QString &newString);


};

#endif // REPLACEMODIFIER_H
