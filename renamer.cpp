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

QString Renamer::rename(QString baseName)
{ 
    int count = 0;

    if(modifiers & PREPEND){
        baseName = PrependModifier::modify(baseName);
    }
    if(modifiers & APPEND){
        baseName = AppendModifier::modify(baseName);
    }

    return baseName;
}


int Renamer::save()
{
    int count = 0;
    foreach(RenameFile* rFile,files){
        rFile->newBaseName = rename(rFile->baseName);
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
            QString previewName = rFile->baseName;
            previewName = rename(previewName);
            return previewName + rFile->fileEnding;
            break;
        };
    }

    return "";
}
