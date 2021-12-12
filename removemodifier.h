#ifndef REMOVEMODIFIER_H
#define REMOVEMODIFIER_H

#include "modifier.h"

class RemoveModifier
{
public:
    enum Option{
            REMOVE_FRONT = 0x1,
            REMOVE_BACK = 0x2
        };
    Q_DECLARE_FLAGS(Options, Option)
    static unsigned int frontNum;
    static unsigned int backNum;
    static unsigned int options;

    static int modify(QList<RenameFile*>* renameFileList);

    RemoveModifier();

public slots:
    static void removeFrontChars(const int &num);
    static void removeBackChars(const int &num);

};

#endif // REMOVEMODIFIER_H
