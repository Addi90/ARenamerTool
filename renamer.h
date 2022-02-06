#ifndef RENAMER_H
#define RENAMER_H

#include <QList>
#include <QFlag>
#include <QString>
#include <QtAlgorithms>
#include <algorithm>

#include "renamefile.h"
#include "modifiers/modifier.h"
#include "modifiers/replacemodifier.h"
#include "modifiers/addmodifier.h"
#include "modifiers/removemodifier.h"
#include "modifiers/numbermodifier.h"
#include "modifiers/ifthenmodifier.h"
#include "modifiers/datemodifier.h"


class Renamer
{
private:


public:
    enum Modifier{
            REPLACE = 0x1,
            REMOVE = 0x2,
            ADD = 0x4,
            COUNTING = 0x8,
            IF_THEN = 0x10,
            DATE = 0x20,

            RENAME_DIRS = 0x40,
        };
    Q_DECLARE_FLAGS(Modifiers, Modifier)


    Renamer();
    static QString rename(QString);
    static int rename();
    static int save();

    static QList<RenameFile*> files;
    static unsigned int modifiers;

    static QString preview(const int );
    static int resetNewBaseName();
    static int resetFilesList();
    static void sortList();
    static int checkForDuplicates();
    const QList<RenameFile*> &getFiles() const;
    static void setFiles(const QList<RenameFile*> &newFiles);

};

#endif // RENAMER_H
