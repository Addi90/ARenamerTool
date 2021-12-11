#include "renamer.h"

QList<RenameFile*> Renamer::files;
unsigned int Renamer::modifiers = 0;

const QList<RenameFile*> &Renamer::getFiles() const
{
    return files;
}

void Renamer::setFiles(const QList<RenameFile*> &newFiles)
{
    files = newFiles;
}

Renamer::Renamer()
{

}

QString Renamer::rename(QString currName)
{ 
    int count = 0;

    if(modifiers & PREPEND){
        currName = PrependModifier::modify(currName);
    }
    if(modifiers & APPEND){
    }

    return currName;
}

int Renamer::save()
{
    int count = 0;
    foreach(RenameFile* rFile,files){
        rFile->newName = rename(rFile->currName);
        if(rFile->renameFile()){
            count++;
            qDebug() << "renamed to: " << rFile->getFile()->fileName();
        }
    }
    return count;
}



QString Renamer::preview(const int row)
{
    foreach(RenameFile* rFile,files){
        if(rFile->modIndex.row() == row){
            //rFile->setNewName("NEW"+rFile->getCurrName());
            QString previewName = rFile->currName;
            previewName = rename(previewName);
            return previewName;
            break;
        };
    }

    return "";
}
