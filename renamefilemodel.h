#ifndef RENAMEFILEMODEL_H
#define RENAMEFILEMODEL_H

#include <QList>
#include <QDir>
#include <QFileSystemModel>
#include "renamer.h"

class RenameFileModel: public QFileSystemModel
{
    Q_OBJECT

    QFileInfo fileInfo(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /* add fifth column to QFileSystemModel for display of new renamed filename */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;


    /* for data of the last column, add new name */
    QVariant data(const QModelIndex& index,int role) const override;

    /*int rowCount(const QModelIndex& parent = QModelIndex()) const;*/
    /*bool setData(const QModelIndex &index, const QVariant &value, int role) override;*/

};

#endif // RENAMEFILEMODEL_H
