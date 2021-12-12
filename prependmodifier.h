#ifndef PREPENDMODIFIER_H
#define PREPENDMODIFIER_H

#include "modifier.h"
#include "renamefile.h"

class PrependModifier : public Modifier
{
public:
    enum Option{
            REMOVE_CHARS = 0x4
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString prependStr;
    static int remNumChars;
    static unsigned int options;

    static QString modify(QString);
    static int modify(QList<RenameFile*>&);
    PrependModifier();
public slots:
    static void prependString(const QString &newPrepStr);
    static void removeChars(const int &num);
};

#endif // PREPENDMODIFIER_H
