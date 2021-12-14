#ifndef NUMBERMODIFIER_H
#define NUMBERMODIFIER_H

#include "modifier.h"

class NumberModifier
{
public:
    enum Option{
            PREFIX = 0x1,
            INSERT = 0x2,
            SUFFIX = 0x4
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString appendStr;
    static unsigned int insertPos;
    static unsigned int padding;
    static unsigned int startNum;
    static unsigned int options;

    static int modify(QList<RenameFile*>* renameFileList);

    NumberModifier();

public slots:
    static void paddingSize(const int &num);
    static void startNumber(const int &num);
    static void insertPosition(const int &pos);

};

#endif // NUMBERMODIFIER_H
