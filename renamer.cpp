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
    resetNewBaseName();
    sortList();

    if(modifiers & REPLACE){
        ReplaceModifier::modify(&files);
    }
    if(modifiers & IF_THEN){
        IfThenModifier::modify(&files);
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
    if(modifiers & DATE){
        DateModifier::modify(&files);
    }
    return count;
}

int Renamer::save()
{
    int count = 0;

    /* apply modifiers */
    rename();

    /* rename all, check if it is a file (exists=true) or a dir (exists=false),
     * increment count if renaming worked */
    foreach(RenameFile* rFile,files){
        if(rFile->file->exists()){
            if(rFile->renameFile()){
                count++;
                qDebug() << "renamed to: " << rFile->getFile()->fileName();
            }
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

int Renamer::resetNewBaseName()
{
    int count = 0;
    foreach(RenameFile* rFile,files){
        rFile->newBaseName = rFile->baseName;
    }
    return count;
}

int Renamer::resetFilesList()
{
    int count = files.length();
     files.clear();
     return count;
}

void Renamer::sortList()
{
    std::sort(files.begin(),files.end());
}
