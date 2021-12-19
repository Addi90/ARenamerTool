#ifndef IFTHENMODIFIER_H
#define IFTHENMODIFIER_H

#include <QRegularExpression>
#include "modifier.h"

class IfThenModifier : public Modifier
{
public:
    enum Option{
            INSERT = 0x1,
            REGEX = 0x2,
            CONTAINS = 0x4,
            CONTAINS_NOT = 0x8,
            ADD_PREFIX = 0x10,
            ADD_SUFFIX = 0x20,
            CASE_SENSITIVE = 0x40
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString conditionStr;
    static QRegularExpression conditionRegex;
    static QString consequenceStr;
    static unsigned int insertPos;
    static unsigned int options;

    static int modify(QList<RenameFile*>* renameFileList);

    IfThenModifier();
public slots:
    static void conditionOption(const unsigned int &opt);
    static void conditionExp(const QString &str);
    static void consequenceOption(const unsigned int &opt);
    static void consequenceString(const QString &str);
    static void insertPosition(const int &pos);
    static void setRegexOption(const int &status);
    static void setCaseSensitiveOption(const int &status);

private:
    static int handleConsequence(RenameFile * renameFile);


};

#endif // IFTHENMODIFIER_H
