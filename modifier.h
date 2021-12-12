#ifndef MODIFIER_H
#define MODIFIER_H


#include <QDebug>
#include <QString>
#include <QObject>
#include <QList>
#include "renamefile.h"

class Modifier : public QObject
{
Q_OBJECT
public:
    Modifier();
    virtual ~Modifier();
    QString modify(QString currName);
    int modify(QList<RenameFile*>* renameFileList);

private:
};


#endif // MODIFIER_H
