#ifndef RENAMER_H
#define RENAMER_H

#include <QList>
#include <QFlag>
#include <QString>
#include <QtAlgorithms>
#include <algorithm>

#include "renamefile.h"
#include "Modifier.h"
#include "prependmodifier.h"
#include "appendmodifier.h"
#include "replacemodifier.h"
#include "countmodifier.h"
#include "addmodifier.h"
#include "removemodifier.h"



class Renamer
{
private:


public:
    enum Modifier{
            REPLACE = 0x1,
            REMOVE = 0x2,
            ADD = 0x4
        };
    Q_DECLARE_FLAGS(Modifiers, Modifier)


    Renamer();
    static QString rename(QString);
    static int rename();
    static int save();

    static QList<RenameFile*> files;
    static unsigned int modifiers;

    static QString preview(const int );
    static int reset();
    static void sortList();
    const QList<RenameFile*> &getFiles() const;
    static void setFiles(const QList<RenameFile*> &newFiles);

};

#endif // RENAMER_H
