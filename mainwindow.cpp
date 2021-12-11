#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit_2,
            &QLineEdit::textChanged,
            &PrependModifier::prepend
            );
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString dirName = dialog.getExistingDirectory();

    ui->lineEdit->setText(dirName);

    RenameFileModel *fileModel = new RenameFileModel;

    fileModel->setFilter(QDir::Files);
    //ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setModel(fileModel);
    ui->treeView->setRootIndex(fileModel->setRootPath(dirName));
    ui->treeView->show();
    connect(ui->treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(on_treeView_selectionChanged())
            );


    //ui->treeView->setColumnWidth(0,this->width()*0.5);
    //ui->treeView->setColumnWidth(4,this->width()*0.5);

    //ui->treeView->hideColumn(1);
    //ui->treeView->hideColumn(2);
    //ui->treeView->hideColumn(3);


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_selectionChanged()
{
    QModelIndexList selectionList = ui->treeView->selectionModel()->selectedRows();

    QModelIndex selection;
    QList<RenameFile*> rFiles;

    foreach(selection,selectionList){
        qDebug() << "selected: " << selection.row();
        qDebug() << "name info: " << selection.data().toString();

        RenameFile* rFile = new RenameFile(
                    selection
                    );
        rFiles.append(rFile);
    };
    Renamer::setFiles(rFiles);

}



void MainWindow::on_pushButton_2_clicked()
{
    int renamed = 0;
    renamed = Renamer::save();
    QMessageBox msgBox;
    msgBox.setText(QString("Successfully renamed ") + QVariant(renamed).toString()+ QString(" Files!"));
    msgBox.exec();
}


void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        Renamer::modifiers |= Renamer::PREPEND;
    }
    else if(!ui->checkBox->isChecked()){
        Renamer::modifiers |= Renamer::PREPEND;
    }

}



