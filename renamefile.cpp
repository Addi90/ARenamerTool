#include "renamefile.h"


const QString &RenameFile::getCurrName() const
{
    return currName;
}

void RenameFile::setCurrName(const QString &newCurrName)
{
    currName = newCurrName;
}

const QString &RenameFile::getNewName() const
{
    return newName;
}

void RenameFile::setNewName(const QString &newNewName)
{
    newName = newNewName;
}

const QModelIndex &RenameFile::getModelIndex() const
{
    return modIndex;
}

void RenameFile::setModelIndex(const QModelIndex &newModelIndex)
{
    modIndex = newModelIndex;
}



QFile *RenameFile::getFile() const
{
    return file;
}

void RenameFile::setFile(QFile *newFile)
{
    file = newFile;
}

bool RenameFile::renameFile()
{
    if(newName != "" && newName != currName){
        return file->rename(fPath+"/"+newName);
    }
    return false;
}

RenameFile::RenameFile(const QModelIndex &modelIndex)
{
    currName = modelIndex.data().toString();
    newName = currName;
    modIndex = modelIndex;
    fPath = modelIndex.siblingAtColumn(5).data().toString();
    file = new QFile(fPath+"/"+currName);
}
