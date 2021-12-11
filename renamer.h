#ifndef RENAMER_H
#define RENAMER_H

#include <QList>
#include <QFlag>
#include <QString>
#include "renamefile.h"
#include "Modifier.h"
#include "prependmodifier.h"


class Renamer
{
private:


public:
    enum Modifier{
            PREPEND = 0x1,
            APPEND = 0x2
        };
    Q_DECLARE_FLAGS(Modifiers, Modifier)


    Renamer();
    static QString rename(QString);
    static int save();

    static QList<RenameFile*> files;
    static unsigned int modifiers;

    static QString preview(const int);
    const QList<RenameFile*> &getFiles() const;
    static void setFiles(const QList<RenameFile*> &newFiles);

};

#endif // RENAMER_H
