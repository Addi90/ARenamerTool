#ifndef RENAMEFILE_H
#define RENAMEFILE_H

#include <QString>
#include <QModelIndex>
#include <QFile>
#include <QFileInfo>

class RenameFile : public QObject
{

Q_OBJECT

public:
    QModelIndex modIndex;
    QFile *file;
    QString baseName;
    QString newBaseName;
    QString fileEnding;
    QString filePath;

    RenameFile(const QModelIndex &modelIndex);

    const QString &getCurrName() const;
    void setCurrName(const QString &newCurrName);

    const QString &getNewName() const;
    void setNewName(const QString &newNewName);

    const QModelIndex &getModelIndex() const;
    void setModelIndex(const QModelIndex &newModelIndex);

    QFile *getFile() const;
    void setFile(QFile *newFile);

    bool renameFile();

    static bool renameFileLessThan(const RenameFile* a,const RenameFile* b);

};


#endif // RENAMEFILE_H
