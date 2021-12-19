#ifndef REMOVEMODIFIER_H
#define REMOVEMODIFIER_H

#include "modifier.h"

class RemoveModifier
{
public:
    enum Option{
            REMOVE_FRONT = 0x1,
            REMOVE_BACK = 0x2,
            REMOVE_RANGE = 0x4
        };
    Q_DECLARE_FLAGS(Options, Option)
    static unsigned int frontNum;
    static unsigned int backNum;
    static unsigned int options;
    static unsigned int rangeStart;
    static unsigned int rangeEnd;

    static int modify(QList<RenameFile*>* renameFileList);

    RemoveModifier();

public slots:
    static void removeFrontChars(const int &num);
    static void removeBackChars(const int &num);
    static void removeRangeStart(const int &num);
    static void removeRangeEnd(const int &num);


};

#endif // REMOVEMODIFIER_H
