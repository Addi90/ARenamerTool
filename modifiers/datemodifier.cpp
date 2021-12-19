#include "datemodifier.h"


QString DateModifier::dateStr;
QString DateModifier::sepStr;
unsigned int DateModifier::insertPos;
unsigned int DateModifier::options;
QDate DateModifier::customDate;


int DateModifier::modify(QList<RenameFile *> *renameFileList)
{
    int i;
    for(i=0;i< renameFileList->length();i++){
        makeDate((*renameFileList).at(i));
        if(options & SUFFIX){
            (*renameFileList).at(i)->newBaseName.append(dateStr);
        }
        else if(options & INSERT){
            (*renameFileList).at(i)->newBaseName.insert(insertPos,dateStr);
        }
        else if(options & PREFIX){
            (*renameFileList).at(i)->newBaseName.prepend(dateStr);
        }
    }

    return i;
}

DateModifier::DateModifier()
{

}

/* Builds date string out of given format-choice and separator */
QString DateModifier::makeDate(RenameFile *renameFile)
{
    QDateTime fTime;
    QStringView dateFormat;

    /* get date information according to set source */
    if(options & DATE_MADE){
        fTime = renameFile->file->fileTime(QFileDevice::FileBirthTime);
    }
    else if(options & DATE_MOD){
        fTime = renameFile->file->fileTime(QFileDevice::FileModificationTime);
    }
    else if(options & DATE_TODAY){
        fTime = QDateTime(QDate::currentDate(),QTime::currentTime());
    }
    else if(options & DATE_CUSTOM){
        fTime = QDateTime(customDate,QTime::currentTime());
    }

    /* format date string according to set mode */
    if(options & MODE_DMY){
        dateFormat = "dd" + sepStr + "MM" + sepStr + "yyyy";
    }
    else if(options & MODE_YMD){
        dateFormat = "yyyy" + sepStr + "MM" + sepStr + "dd";
    }
    else if(options & MODE_MDY){
        dateFormat = "MM" + sepStr + "dd" + sepStr + "yyyy";
    }

    QDate date = fTime.date();
    dateStr = date.toString(dateFormat);
    return dateStr;
}


void DateModifier::insertPosition(const int &pos)
{
    insertPos = pos;
    qDebug() << "insertPos: " << insertPos;
}

void DateModifier::separator(const QString &sep)
{
    sepStr = sep;
    qDebug() << "sepStr: " << sepStr;
}

void DateModifier::userSetDate(const QDate &date)
{
    customDate = date;
    qDebug() << "customDate: " << customDate.toString();
}


