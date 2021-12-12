#ifndef COUNTMODIFIER_H
#define COUNTMODIFIER_H

#include <QList>
#include "renamefile.h"
#include "modifier.h"

class CountModifier : public Modifier
{
public:
    enum Option{
            PREPEND = 0x1,
            APPEND = 0x2
        };
    Q_DECLARE_FLAGS(Options, Option)

    static unsigned int startNum;
    static unsigned int options;

    static int modify(QList<RenameFile*>* renameFileList);

    CountModifier();
public slots:
    static void startNumber(const unsigned int &startNumber);

};

#endif // COUNTMODIFIER_H
