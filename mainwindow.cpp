#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit_2,
            &QLineEdit::textChanged,
            &PrependModifier::prependString
            );
    connect(ui->lineEdit_3,
            &QLineEdit::textChanged,
            &AppendModifier::appendString
            );
    connect(ui->spinBox,
            &QSpinBox::valueChanged,
            &PrependModifier::removeChars
            );
    connect(ui->spinBox_2,
            &QSpinBox::valueChanged,
            &AppendModifier::removeChars
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

        RenameFile* rFile = new RenameFile(selection);
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

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        ui->lineEdit_2->setEnabled(true);
        ui->checkBox_3->setEnabled(true);
        Renamer::modifiers |= Renamer::PREPEND;
    }
    else if(arg1 == Qt::Unchecked){
        ui->lineEdit_2->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
        Renamer::modifiers &= ~(Renamer::PREPEND);
    }

}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1){
        ui->lineEdit_3->setEnabled(true);
        ui->checkBox_4->setEnabled(true);
        Renamer::modifiers |= Renamer::APPEND;
    }
    else if(arg1 == Qt::Unchecked){
        ui->lineEdit_3->setEnabled(false);
        ui->checkBox_4->setEnabled(false);
        Renamer::modifiers &= ~(Renamer::APPEND);
    }
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1){
        ui->spinBox->setEnabled(true);
        PrependModifier::remNumChars = ui->spinBox->value();
        PrependModifier::options |= PrependModifier::REMOVE_CHARS;
    }
    else if(arg1 == Qt::Unchecked){
        ui->spinBox->setEnabled(false);
        PrependModifier::options &= ~(PrependModifier::REMOVE_CHARS);
    }

}


void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1){
        ui->spinBox_2->setEnabled(true);
        AppendModifier::remNumChars = ui->spinBox->value();
        AppendModifier::options |= AppendModifier::REMOVE_CHARS;
    }
    else if(arg1 == Qt::Unchecked){
        ui->spinBox_2->setEnabled(false);
        AppendModifier::options &= ~(AppendModifier::REMOVE_CHARS);
    }
}


