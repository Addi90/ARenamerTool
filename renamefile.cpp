#include "renamefile.h"


const QString &RenameFile::getCurrName() const
{
    return baseName;
}

void RenameFile::setCurrName(const QString &newCurrName)
{
    baseName = newCurrName;
}

const QString &RenameFile::getNewName() const
{
    return newBaseName;
}

void RenameFile::setNewName(const QString &newNewName)
{
    newBaseName = newNewName;
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
    if(newBaseName != "" && newBaseName != baseName){
        return file->rename(filePath+"/" + newBaseName + fileEnding);
    }
    return false;
}

bool RenameFile::operator<(const RenameFile &other) const
{
    return modIndex.row() < other.modIndex.row();
}

RenameFile::RenameFile(const QModelIndex &modelIndex)
{

    modIndex = modelIndex;
    filePath = modelIndex.siblingAtColumn(5).data().toString();
    file = new QFile(filePath+"/"+modelIndex.data().toString());

    /* separate file-ending (after last dot) from file-name */
    int dotPos = modelIndex.data().toString().lastIndexOf('.');
    if(dotPos > -1){
        baseName = modelIndex.data().toString().left(dotPos);
        fileEnding = modelIndex.data().toString().right(modelIndex.data().toString().length() - dotPos);
    }
    else{
        baseName = modelIndex.data().toString();
        fileEnding = "";
    }
    newBaseName = baseName;
}
