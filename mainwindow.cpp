#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    dirModel = new QFileSystemModel;
    dirModel->setFilter(QDir::Dirs);
    QModelIndex homeIndex = dirModel->setRootPath(QDir::homePath());
    ui->treeView_2->setModel(dirModel);
    ui->treeView_2->scrollTo(homeIndex);
    ui->treeView_2->setColumnWidth(0,this->width());
    ui->treeView_2->hideColumn(1);
    ui->treeView_2->hideColumn(2);
    ui->treeView_2->hideColumn(3);


    fileModel = new RenameFileModel;
    fileModel->setFilter(QDir::Files);
    //ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setModel(fileModel);
    ui->treeView->setRootIndex(fileModel->setRootPath(QDir::homePath()));
    //ui->treeView->setSortingEnabled(true);
    //ui->treeView->show();

    connect(ui->treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(on_treeView_selectionChanged())
            );

    ui->treeView->setColumnWidth(0,this->width()*0.3);
    //ui->treeView->setColumnWidth(4,this->width()*0.4);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(5);

    /* ADD */
    connect(ui->lineEdit_2,
            &QLineEdit::textChanged,
            &AddModifier::prefixString
            );
    connect(ui->lineEdit_3,
            &QLineEdit::textChanged,
            &AddModifier::suffixString
            );
    /* REMOVE */
    connect(ui->spinBox,
            &QSpinBox::valueChanged,
            &RemoveModifier::removeFrontChars
            );
    connect(ui->spinBox_2,
            &QSpinBox::valueChanged,
            &RemoveModifier::removeBackChars
            );
    /* NUMBERS */
    connect(ui->spinBox_3,
            &QSpinBox::valueChanged,
            &NumberModifier::startNumber
            );
    connect(ui->spinBox_4,
            &QSpinBox::valueChanged,
            &NumberModifier::insertPosition
            );
    connect(ui->spinBox_7,
            &QSpinBox::valueChanged,
            &NumberModifier::paddingSize
            );
    /* REPLACE */
    connect(ui->lineEdit_4,
            &QLineEdit::textChanged,
            &ReplaceModifier::replaceString
            );
    connect(ui->lineEdit_5,
            &QLineEdit::textChanged,
            &ReplaceModifier::newString
            );
    connect(ui->checkBox_8,
            &QCheckBox::stateChanged,
            &ReplaceModifier::setRegexOption
            );
    connect(ui->checkBox_9,
            &QCheckBox::stateChanged,
            &ReplaceModifier::setCaseSensitiveOption
            );
    /* IF-THEN */
    connect(ui->lineEdit_6,
            &QLineEdit::textChanged,
            &IfThenModifier::conditionExp
            );
    connect(ui->lineEdit_7,
            &QLineEdit::textChanged,
            &IfThenModifier::consequenceString
            );
    connect(ui->spinBox_5,
            &QSpinBox::valueChanged,
            &IfThenModifier::insertPosition
            );
    connect(ui->checkBox_10,
            &QCheckBox::stateChanged,
            &IfThenModifier::setRegexOption
            );
    connect(ui->checkBox_11,
            &QCheckBox::stateChanged,
            &IfThenModifier::setCaseSensitiveOption
            );
    /* DATE */
    connect(ui->lineEdit_9,
            &QLineEdit::textChanged,
            &DateModifier::separator
            );
    connect(ui->spinBox_10,
            &QSpinBox::valueChanged,
            &DateModifier::insertPosition
            );
    connect(ui->dateEdit,
            &QDateEdit::userDateChanged,
            &DateModifier::userSetDate
            );
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString dirName = dialog.getExistingDirectory();

    ui->lineEdit->setText(dirName);

    //ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setRootIndex(fileModel->setRootPath(dirName));
    ui->treeView->show();
    connect(ui->treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(on_treeView_selectionChanged())
            );

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ifThenOptionResolver(int condition, int consequence)
{
    switch(condition){
        case 0:
            IfThenModifier::options &= ~(IfThenModifier::CONTAINS_NOT);
            IfThenModifier::options |= IfThenModifier::CONTAINS;
            break;
        case 1:
            IfThenModifier::options &= ~(IfThenModifier::CONTAINS);
            IfThenModifier::options |= IfThenModifier::CONTAINS_NOT;
            break;
    }
    switch(consequence){
        case 0:
            IfThenModifier::options &= ~(IfThenModifier::INSERT | IfThenModifier::ADD_SUFFIX);
            IfThenModifier::options |= IfThenModifier::ADD_PREFIX;
            break;
        case 1:
            IfThenModifier::options &= ~(IfThenModifier::ADD_PREFIX | IfThenModifier::ADD_SUFFIX);
            IfThenModifier::options |= IfThenModifier::INSERT;
            break;
        case 2:
            IfThenModifier::options &= ~(IfThenModifier::ADD_PREFIX | IfThenModifier::INSERT);
            IfThenModifier::options |= IfThenModifier::ADD_SUFFIX;
            break;
    }
}


void MainWindow::on_treeView_2_clicked(const QModelIndex &index)
{
    QString path = dirModel->filePath(index);
    ui->treeView->setRootIndex(fileModel->setRootPath(path));
}

/* Open - Button */
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
        ui->lineEdit_8->setEnabled(true);
        ui->spinBox_6->setEnabled(true);
        Renamer::modifiers |= Renamer::ADD;
    }
    else if(arg1 == Qt::Unchecked){
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_8->setEnabled(false);
        ui->spinBox_6->setEnabled(false);
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
        ui->checkBox_13->setEnabled(true);
        Renamer::modifiers |= Renamer::REMOVE;
    }
    else if(arg1 == Qt::Unchecked){
        ui->checkBox_3->setEnabled(false);
        ui->checkBox_4->setEnabled(false);
        ui->checkBox_13->setEnabled(false);
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
        ui->checkBox_8->setEnabled(true);
        ui->checkBox_9->setEnabled(true);
        ReplaceModifier::replaceStr = ui->lineEdit_4->text();
        Renamer::modifiers |= Renamer::REPLACE;
    }
    else if(arg1 == Qt::Unchecked){
        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_5->setEnabled(false);
        ui->checkBox_8->setEnabled(false);
        ui->checkBox_9->setEnabled(false);
        Renamer::modifiers &= ~(Renamer::REPLACE);
    }
}

/* Numbers - CheckBox*/
void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    if(arg1){
        ui->radioButton->setEnabled(true);
        ui->radioButton_2->setEnabled(true);
        ui->radioButton_3->setEnabled(true);
        ui->spinBox_3->setEnabled(true);
        ui->spinBox_7->setEnabled(true);
        NumberModifier::startNum = ui->spinBox_3->value();
        NumberModifier::insertPos = ui->spinBox_4->value();
        Renamer::modifiers |= Renamer::COUNTING;
    }
    else if(arg1 == Qt::Unchecked){
        ui->radioButton->setEnabled(false);
        ui->radioButton_2->setEnabled(false);
        ui->radioButton_3->setEnabled(false);
        ui->spinBox_3->setEnabled(false);
        ui->spinBox_7->setEnabled(true);
        Renamer::modifiers &= ~(Renamer::COUNTING);
    }
}



/* Numbers - Prefix RadioButton */
void MainWindow::on_radioButton_clicked()
{
    if(ui->radioButton->isChecked()){
        ui->radioButton_2->setChecked(false);
        ui->radioButton_3->setChecked(false);
        ui->spinBox_4->setEnabled(false);
        NumberModifier::options |= NumberModifier::PREFIX;
        NumberModifier::options &= ~(NumberModifier::SUFFIX | NumberModifier::INSERT);
    }
}

/* Numbers - Insert RadioButton */
void MainWindow::on_radioButton_2_clicked()
{
    if(ui->radioButton_2->isChecked()){
        ui->radioButton->setChecked(false);
        ui->radioButton_3->setChecked(false);
        ui->spinBox_4->setEnabled(true);
        NumberModifier::options |= NumberModifier::INSERT;
        NumberModifier::options &= ~(NumberModifier::PREFIX | NumberModifier::SUFFIX);
    }
}

/* Numbers - Suffix RadioButton */
void MainWindow::on_radioButton_3_clicked()
{
    if(ui->radioButton_3->isChecked()){
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);
        ui->spinBox_4->setEnabled(false);
        NumberModifier::options |= NumberModifier::SUFFIX;
        NumberModifier::options &= ~(NumberModifier::PREFIX | NumberModifier::INSERT);
    }
}


/* If-Then - activate CheckBox */
void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1){
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->lineEdit_7->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);
        ui->checkBox_10->setEnabled(true);
        ui->checkBox_11->setEnabled(true);
        ifThenOptionResolver(ui->comboBox->currentIndex(),ui->comboBox_2->currentIndex());
        Renamer::modifiers |= Renamer::IF_THEN;
    }
    else if(arg1 == Qt::Unchecked){
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_6->setEnabled(false);
        ui->spinBox_5->setEnabled(false);
        ui->checkBox_10->setEnabled(false);
        ui->checkBox_11->setEnabled(false);
        Renamer::modifiers &= ~(Renamer::IF_THEN);
    }
}

/* If-Then - select Condition ComboBox */
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ifThenOptionResolver(index,ui->comboBox_2->currentIndex());
}

/* If-Then - select Consequence ComboBox */
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    ifThenOptionResolver(ui->comboBox->currentIndex(),index);
    if(index == 1)
        ui->spinBox_5->setEnabled(true);
    else
        ui->spinBox_5->setEnabled(false);
}

void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->checkBox_9->setChecked(false);
    } else
        ui->checkBox_9->setChecked(true);
}


void MainWindow::on_checkBox_11_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->checkBox_10->setChecked(false);
    } else
        ui->checkBox_10->setChecked(true);
}


/* Date - activate CheckBox */
void MainWindow::on_checkBox_12_stateChanged(int arg1)
{
    if(arg1){
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->lineEdit_9->setEnabled(true);
        ui->radioButton_4->setEnabled(true);
        ui->radioButton_5->setEnabled(true);
        ui->radioButton_6->setEnabled(true);
        ifThenOptionResolver(ui->comboBox->currentIndex(),ui->comboBox_2->currentIndex());

        /* set standard settings */
        ui->radioButton_5->setChecked(true);
        DateModifier::options &= ~(DateModifier::PREFIX | DateModifier::INSERT);
        DateModifier::options |= DateModifier::SUFFIX;

        on_comboBox_3_currentIndexChanged(ui->comboBox_3->currentIndex());

        ui->lineEdit_9->setText("-");

        ui->dateEdit->setDate(QDate::currentDate());

        Renamer::modifiers |= Renamer::DATE;
    }
    else if(arg1 == Qt::Unchecked){
        ui->comboBox_3->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->lineEdit_9->setEnabled(false);
        ui->radioButton_4->setEnabled(false);
        ui->radioButton_5->setEnabled(false);
        ui->radioButton_6->setEnabled(false);
        ui->spinBox_10->setEnabled(false);
        ui->dateEdit->setEnabled(false);
        Renamer::modifiers &= ~(Renamer::DATE);
    }
}

/* Date - Date Display Mode ComboBox */
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    switch(index){
        case 0:
            DateModifier::options &= ~(DateModifier::MODE_YMD | DateModifier::MODE_MDY);
            DateModifier::options |= DateModifier::MODE_DMY;
            break;
        case 1:
            DateModifier::options &= ~(DateModifier::MODE_MDY | DateModifier::MODE_DMY);
            DateModifier::options |= DateModifier::MODE_YMD;
            break;
        case 2:
            DateModifier::options &= ~(DateModifier::MODE_YMD | DateModifier::MODE_DMY);
            DateModifier::options |= DateModifier::MODE_MDY;
            break;
    }
}

/* Date - Date Source ComboBox */
void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    DateModifier::options &= ~(0xF);
    switch(index){
    case 0:
        DateModifier::options |= ~(DateModifier::DATE_MADE);
        ui->dateEdit->setEnabled(false);
        break;
    case 1:
        DateModifier::options |= ~(DateModifier::DATE_MOD);
        ui->dateEdit->setEnabled(false);
        break;
    case 2:
        DateModifier::options |= ~(DateModifier::DATE_TODAY);
        ui->dateEdit->setEnabled(false);
        break;
    case 3:
        DateModifier::options |= ~(DateModifier::DATE_CUSTOM);
        ui->dateEdit->setEnabled(true);
        break;
    }
}

/* Date - Prefix RadioButton */
void MainWindow::on_radioButton_4_clicked()
{
    if(ui->radioButton->isChecked()){
        ui->radioButton_5->setChecked(false);
        ui->radioButton_6->setChecked(false);
        ui->spinBox_10->setEnabled(false);
        DateModifier::options |= DateModifier::PREFIX;
        DateModifier::options &= ~(DateModifier::SUFFIX | DateModifier::INSERT);
    }
}

/* Date - Suffix RadioButton */
void MainWindow::on_radioButton_5_clicked()
{
    if(ui->radioButton->isChecked()){
        ui->radioButton_4->setChecked(false);
        ui->radioButton_6->setChecked(false);
        ui->spinBox_10->setEnabled(false);
        DateModifier::options |= DateModifier::SUFFIX;
        DateModifier::options &= ~(DateModifier::PREFIX | DateModifier::INSERT);
    }
}

/* Date - Insert RadioButton */
void MainWindow::on_radioButton_6_clicked()
{
    if(ui->radioButton->isChecked()){
        ui->radioButton_4->setChecked(false);
        ui->radioButton_5->setChecked(false);
        ui->spinBox_10->setEnabled(true);
        DateModifier::options |= DateModifier::INSERT;
        DateModifier::options &= ~(DateModifier::SUFFIX | DateModifier::PREFIX);
    }
}




