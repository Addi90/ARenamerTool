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


int Renamer::rename()
{
    int count = 0;
    reset();
    sortList();

    if(modifiers & REPLACE){
        ReplaceModifier::modify(&files);
    }
    if(modifiers & REMOVE){
        RemoveModifier::modify(&files);
    }
    if(modifiers & ADD){
        AddModifier::modify(&files);
    }
    if(modifiers & COUNTING){
        NumberModifier::modify(&files);
    }

    return count;
}



int Renamer::save()
{
    int count = 0;
    rename();

    foreach(RenameFile* rFile,files){
        if(rFile->renameFile()){
            count++;
            qDebug() << "renamed to: " << rFile->getFile()->fileName();
        }
    }
    return count;
}



QString Renamer::preview(const int row)
{
    rename();
    foreach(RenameFile* rFile,files){
        if(rFile->modIndex.row() == row){
            return rFile->newBaseName + rFile->fileEnding;
            break;
        };
    }

    return "";
}

int Renamer::reset()
{
    int count = 0;
    foreach(RenameFile* rFile,files){
        rFile->newBaseName = rFile->baseName;
    }
    return count;
}

void Renamer::sortList()
{
    std::sort(files.begin(),files.end());
}
