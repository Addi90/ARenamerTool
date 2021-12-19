#ifndef ADDMODIFIER_H
#define ADDMODIFIER_H

#include "modifier.h"

class AddModifier : public Modifier
{

public:

    static QString prefixStr;
    static QString suffixStr;
    static QString insertStr;
    static unsigned int insertPos;
    static unsigned int options;

    static int modify(QList<RenameFile*>* renameFileList);

    AddModifier();
public slots:
    static void prefixString(const QString &newPrefixStr);
    static void suffixString(const QString &newSuffixStr);
    static void insertString(const QString &newInsertStr);
    static void insertPosition(const int &pos);

};

#endif // ADDMODIFIER_H
