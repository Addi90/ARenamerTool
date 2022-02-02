#include "renamefilemodel.h"

QFileInfo RenameFileModel::fileInfo(const QModelIndex &index) const
{
    QFileInfo fInfo = QFileSystemModel::fileInfo(index);
    return fInfo;
}

QVariant RenameFileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // horizontal Header
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal)) {
        switch(section){
        case 0:
            return tr("Name");
        case 4:
            return tr("New Name");
        }
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

int RenameFileModel::columnCount(const QModelIndex &parent) const
{
    return QFileSystemModel::columnCount()+2;
}

QVariant RenameFileModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){return QFileSystemModel::data(index,role);}

    if(index.column()==columnCount()-2)
    {
        switch(role)
        {
        /* return data for last column for given index */
        case(Qt::DisplayRole):
        {
            QString newName = Renamer::preview(index.row());
            return newName;
            //return QString("YourText");
        }
        case(Qt::ForegroundRole):
        {return QVariant(QColor::fromRgb(10, 110, 40, 255));}
        case(Qt::TextAlignmentRole):
        {return Qt::AlignLeft;}
        default:{}
        }
    }
    if(index.column()==columnCount()-1)
    {
        switch(role)
        {
        /* return data for last column for given index */
        case(Qt::DisplayRole):
        {
            QFileInfo fInfo = QFileSystemModel::fileInfo(index);
            return fInfo.absolutePath();
            //return QString("YourText");
        }
        case(Qt::TextAlignmentRole):
        {return Qt::AlignLeft;}
        default:{}
        }
    }
    return QFileSystemModel::data(index,role);
}

/*int rowCount(const QModelIndex& parent = QModelIndex()) const
{
    return QFileSystemModel::rowCount();
}*/

/*bool setData(const QModelIndex &index, const QVariant &value, int role) override {
   emit dataChanged(index,index, QVector<int>( Qt::ItemDataRole::DisplayRole ));
   return QFileSystemModel::setData(index, value, role);
}*/
