#ifndef RENAMEFILEMODEL_H
#define RENAMEFILEMODEL_H

#include <QList>
#include <QDir>
#include <QFileSystemModel>
#include "renamer.h"

class RenameFileModel: public QFileSystemModel
{
    Q_OBJECT

    QFileInfo fileInfo(const QModelIndex &index) const
    {
        QFileInfo fInfo = QFileSystemModel::fileInfo(index);
        return fInfo;
    }


    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
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

    /* add fifth column to QFileSystemModel for display of new renamed filename */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return QFileSystemModel::columnCount()+2;
    }

    /*int rowCount(const QModelIndex& parent = QModelIndex()) const
    {
        return QFileSystemModel::rowCount();
    }*/

    /* for data of the last column, add new name */
    QVariant data(const QModelIndex& index,int role) const override
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

    /*bool setData(const QModelIndex &index, const QVariant &value, int role) override {
       emit dataChanged(index,index, QVector<int>( Qt::ItemDataRole::DisplayRole ));
       return QFileSystemModel::setData(index, value, role);
    }*/

};

#endif // RENAMEFILEMODEL_H
