#ifndef REPLACEMODIFIER_H
#define REPLACEMODIFIER_H

#include "modifier.h"
#include <QRegularExpression>

class ReplaceModifier : public Modifier
{

public:
    enum Option{
            REPLACE_REGEX = 0x1,
            CASE_SENSITIVE = 0x2
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString replaceStr;
    static QRegularExpression regexStr;
    static QString newStr;
    static unsigned int options;


    static QString modify(QString currName);
    static int modify(QList<RenameFile*>* renameFileList);

    ReplaceModifier();
public slots:
    static void replaceString(const QString &replaceExp); // Todo: Name it replaceExp
    static void newString(const QString &newString);
    static void setRegexOption(const int &status);
    static void setCaseSensitiveOption(const int &status);
};

#endif // REPLACEMODIFIER_H
