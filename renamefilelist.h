#ifndef RENAMEFILELIST_H
#define RENAMEFILELIST_H

#include <QList>
#include "renamefile.h"

class RenameFileList
{
private:
    QList<RenameFile*> files;
public:
    RenameFileList();

    const QList<RenameFile*> &getFiles() const;
    void setFiles(const QList<RenameFile*> &newFiles);
    const RenameFile &getFileByRow(const int &row) const;

};

#endif // RENAMEFILELIST_H
