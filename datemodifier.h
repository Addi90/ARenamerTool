#ifndef DATEMODIFIER_H
#define DATEMODIFIER_H

#include "modifier.h"
#include <QMutex>

class DateModifier : public Modifier
{
public:
    enum Option{
            DATE_MADE = 0x1,
            DATE_MOD = 0x2,
            DATE_TODAY = 0x4,
            DATE_CUSTOM = 0x8,

            MODE_DMY = 0x10,
            MODE_YMD = 0x20,
            MODE_MDY = 0x40,

            PREFIX = 0x100,
            SUFFIX = 0x200,
            INSERT = 0x400
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString dateStr;
    static QString sepStr;
    static unsigned int insertPos;
    static unsigned int options;
    static QDate customDate;

    static int modify(QList<RenameFile*>* renameFileList);

    DateModifier();

private:
    static QString makeDate(RenameFile* renameFile);

public slots:
    static void insertPosition(const int &pos);
    static void separator(const QString &sep);
    static void userSetDate(const QDate &date);

};

#endif // DATEMODIFIER_H
