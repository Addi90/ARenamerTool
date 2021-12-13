#include "renamefilelist.h"

const QList<RenameFile*> &RenameFileList::getFiles() const
{
    return files;
}

void RenameFileList::setFiles(const QList<RenameFile*> &newFiles)
{
    files = newFiles;
}

const RenameFile &RenameFileList::getFileByRow(const int &row) const
{

}


RenameFileList::RenameFileList()
{

}
