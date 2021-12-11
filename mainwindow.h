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
#include "prependmodifier.h"


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

private slots:
    void on_pushButton_clicked();
    void on_treeView_selectionChanged();
    void on_pushButton_2_clicked();
    void on_checkBox_clicked();
};
#endif // MAINWINDOW_H
