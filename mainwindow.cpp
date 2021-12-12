#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit_2,
            &QLineEdit::textChanged,
            &AddModifier::prefixString
            );
    connect(ui->lineEdit_3,
            &QLineEdit::textChanged,
            &AddModifier::suffixString
            );
    connect(ui->spinBox,
            &QSpinBox::valueChanged,
            &RemoveModifier::removeFrontChars
            );
    connect(ui->spinBox_2,
            &QSpinBox::valueChanged,
            &RemoveModifier::removeBackChars
            );
    connect(ui->lineEdit_4,
            &QLineEdit::textChanged,
            &ReplaceModifier::replaceString
            );
    connect(ui->lineEdit_5,
            &QLineEdit::textChanged,
            &ReplaceModifier::newString
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


    ui->treeView->setColumnWidth(0,this->width()*0.3);
    //ui->treeView->setColumnWidth(4,this->width()*0.4);

    //ui->treeView->hideColumn(1);
    //ui->treeView->hideColumn(2);
    //ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(5);

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


/* Rename - Button */
void MainWindow::on_pushButton_2_clicked()
{
    int renamed = 0;
    renamed = Renamer::save();
    QMessageBox msgBox;
    msgBox.setText(QString("Successfully renamed ") + QVariant(renamed).toString()+ QString(" Files!"));
    msgBox.exec();
}


/* Add - CheckBox */
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        /* Prefix & Suffix LineEdits */
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        Renamer::modifiers |= Renamer::ADD;
    }
    else if(arg1 == Qt::Unchecked){
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);

        Renamer::modifiers &= ~(Renamer::ADD);
    }

}

/* Remove - CheckBox */
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1){
        /* rem. front & back n chars CheckBoxes/SpinBoxes */
        ui->checkBox_3->setEnabled(true);
        ui->checkBox_4->setEnabled(true);
        ui->spinBox->setEnabled(true);
        ui->spinBox_2->setEnabled(true);
        Renamer::modifiers |= Renamer::REMOVE;
    }
    else if(arg1 == Qt::Unchecked){
        ui->checkBox_3->setEnabled(false);
        ui->checkBox_4->setEnabled(false);
        ui->spinBox->setEnabled(false);
        ui->spinBox_2->setEnabled(false);
        Renamer::modifiers &= ~(Renamer::REMOVE);
    }
}

/* Remove n chars front - CheckBox */
void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1){
        ui->spinBox->setEnabled(true);
        RemoveModifier::frontNum = ui->spinBox->value();
        RemoveModifier::options |= RemoveModifier::REMOVE_FRONT;
    }
    else if(arg1 == Qt::Unchecked){
        ui->spinBox->setEnabled(false);
        RemoveModifier::options &= ~(RemoveModifier::REMOVE_FRONT);
    }

}

/* Remove n chars back - CheckBox */
void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1){
        ui->spinBox_2->setEnabled(true);
        RemoveModifier::backNum = ui->spinBox->value();
        RemoveModifier::options |= RemoveModifier::REMOVE_BACK;
    }
    else if(arg1 == Qt::Unchecked){
        ui->spinBox_2->setEnabled(false);
        RemoveModifier::options &= ~(RemoveModifier::REMOVE_BACK);
    }
}


/* Replace - CheckBox */
void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1){
        ui->lineEdit_4->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ReplaceModifier::replaceStr = ui->lineEdit_4->text();
        ReplaceModifier::options |= ReplaceModifier::REPLACE_STRING;

        Renamer::modifiers |= Renamer::REPLACE;
    }
    else if(arg1 == Qt::Unchecked){
        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_5->setEnabled(false);
        ReplaceModifier::options &= ~(ReplaceModifier::REPLACE_STRING);

        Renamer::modifiers &= ~(Renamer::REPLACE);
    }
}

