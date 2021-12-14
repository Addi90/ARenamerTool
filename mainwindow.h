#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QAbstractItemModel>
#include <QDebug>
#include <QMessageBox>
#include "renamefilemodel.h"
#include "renamefile.h"
#include "renamer.h"
#include "addmodifier.h"
#include "removemodifier.h"
#include "replacemodifier.h"
#include "numbermodifier.h"
#include "ifthenmodifier.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RenameFileModel *fileModel;
    QFileSystemModel *dirModel;
    void ifThenOptionResolver(int condition, int consequence);
private slots:
    void on_pushButton_clicked();
    void on_treeView_selectionChanged();
    void on_pushButton_2_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_5_stateChanged(int arg1);
    void on_checkBox_7_stateChanged(int arg1);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_spinBox_3_valueChanged(int arg1);
    void on_spinBox_4_valueChanged(int arg1);
    void on_checkBox_6_stateChanged(int arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_treeView_2_clicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
