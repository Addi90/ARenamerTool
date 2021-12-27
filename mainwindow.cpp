#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dirModel = new QFileSystemModel;
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    path = QDir::homePath();

    /* setup directory treeView */
    QModelIndex homeIndex = dirModel->setRootPath(path);
    ui->treeView_2->setModel(dirModel);
    ui->treeView_2->scrollTo(homeIndex);
    ui->treeView_2->setColumnWidth(0,this->width());
    ui->treeView_2->hideColumn(1);
    ui->treeView_2->hideColumn(2);
    ui->treeView_2->hideColumn(3);

    /* setup file treeView */
    fileModel = new RenameFileModel;
    fileModel->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    ui->treeView->setModel(fileModel);
    ui->treeView->setRootIndex(fileModel->setRootPath(path));

    connect(ui->treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(on_treeView_selectionChanged())
            );

    ui->treeView->setHeaderHidden(false);
    ui->treeView->setColumnWidth(0,this->width()*0.3);
    //ui->treeView->setColumnWidth(4,this->width()*0.4);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(5);

    /* clear selected items in treeView (files) when a dir in treeView_2 is clicked*/
    connect(ui->treeView_2,
                &QTreeView::clicked,
                ui->treeView->selectionModel(),
                &QItemSelectionModel::clearSelection
                );

    controlsRedrawConnector();

    /* create a language selection menu */
    createLanguageMenu();
    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

    /* ADD */
    connect(ui->lineEdit_2,
            &QLineEdit::textChanged,
            &AddModifier::prefixString
            );
    connect(ui->lineEdit_3,
            &QLineEdit::textChanged,
            &AddModifier::suffixString
            );
    connect(ui->lineEdit_8,
            &QLineEdit::textChanged,
            &AddModifier::insertString
            );
    connect(ui->spinBox_6,
            &QSpinBox::valueChanged,
            &AddModifier::insertPosition
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
    connect(ui->spinBox_8,
            &QSpinBox::valueChanged,
            &RemoveModifier::removeRangeStart
            );
    connect(ui->spinBox_9,
            &QSpinBox::valueChanged,
            &RemoveModifier::removeRangeEnd
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

/* Settings -> Languages menu - menu entries dynamically created from translation files
   Example Code for dynamically loading: wiki.qt.io/How_to_create_a_multi_language_application */
void MainWindow::createLanguageMenu() {
    langGroup = new QActionGroup(ui->menuLanguage);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

    /* get system locale */
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"

    /* get available translation files (in app. dir) */
    QDir dir(QApplication::applicationDirPath());
    QStringList fileNames = dir.entryList(QStringList("ARenamerTool_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        /* extract locale from filename */
        QString locale;
        locale = fileNames[i]; // "TranslationExample_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());

        QAction *action = new QAction(lang, this);
        action->setCheckable(true);
        action->setData(locale);

        ui->menuLanguage->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLocale == locale) {
            action->setChecked(true);
        }
    }
}

/* Called every time, when a menu entry of the language menu is called */
void MainWindow::slotLanguageChanged(QAction* action)
{
    if(0 != action) {
        loadLanguage(action->data().toString());
        setWindowIcon(action->icon());
    }
}

void switchTranslator(QTranslator& translator, const QString& filename) {
    // remove the old translator
    QApplication::removeTranslator(&translator);

    // load the new translator
    QString path = QApplication::applicationDirPath();
    if(translator.load(path + '/'+ filename)) // load a .qm file
        QApplication::installTranslator(&translator);
}

void MainWindow::loadLanguage(const QString& rLanguage) {
    if(m_currLang != rLanguage) {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());
        switchTranslator(m_translator, QString("ARenamerTool_%1.qm").arg(rLanguage));
        switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
        ui->statusbar->showMessage(tr("Current Language changed to %1").arg(languageName),3000);
    }
}

/* retranslate the UI if translator was changed */
void MainWindow::changeEvent(QEvent* event) {
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;

        // this event is sent if the system language changes
        case QEvent::LocaleChange:
            {
                QString locale = QLocale::system().name();
                locale.truncate(locale.lastIndexOf('_'));
                loadLanguage(locale);
            }
            break;
        }
    }
    QMainWindow::changeEvent(event);
}

/* reload and display the treeView (files) */
void MainWindow::repaintView()
{
    ui->treeView->setRootIndex(fileModel->setRootPath(path));
}

/* Open - Button for opening directory from filebrowser dialog */
void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString dirName = dialog.getExistingDirectory();

    ui->lineEdit->setText(dirName);

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

/* connect all controls (Buttons, CheckBoxes, LineEdits...) for instant refresh of treeView preview */
void MainWindow::controlsRedrawConnector()
{
    QList<QLineEdit*>lineEdits = ui->tabWidget->findChildren<QLineEdit*>();
    QList<QCheckBox*>checkBoxes = ui->tabWidget->findChildren<QCheckBox*>();
    QList<QSpinBox*>spinBoxes = ui->tabWidget->findChildren<QSpinBox*>();
    QList<QComboBox*>comboBoxes = ui->tabWidget->findChildren<QComboBox*>();
    QList<QDateEdit*>dateEdits = ui->tabWidget->findChildren<QDateEdit*>();


    foreach(QLineEdit* lineEdit,lineEdits){
        connect(lineEdit,
                &QLineEdit::textEdited,
                this,
                &MainWindow::repaintView);
    }
    foreach(QCheckBox* checkBox,checkBoxes){
        connect(checkBox,
                &QCheckBox::stateChanged,
                this,
                &MainWindow::repaintView);
    }
    foreach(QSpinBox* spinBox,spinBoxes){
        connect(spinBox,
                &QSpinBox::valueChanged,
                this,
                &MainWindow::repaintView);
    }
    foreach(QComboBox* comboBox,comboBoxes){
        connect(comboBox,
                &QComboBox::currentIndexChanged,
                this,
                &MainWindow::repaintView);
    }
    foreach(QDateEdit* dateEdit,dateEdits){
        connect(dateEdit,
                &QDateEdit::userDateChanged,
                this,
                &MainWindow::repaintView);
    }
}

/* Directory Selection - treeView2 */
void MainWindow::on_treeView_2_clicked(const QModelIndex &index)
{
    path = dirModel->filePath(index);
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

/* Remove range - CheckBox */
void MainWindow::on_checkBox_13_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->spinBox_8->setEnabled(false);
        ui->spinBox_9->setEnabled(false);
        RemoveModifier::options &= ~(RemoveModifier::REMOVE_RANGE);
    }
    else {
        ui->spinBox_8->setEnabled(true);
        ui->spinBox_9->setEnabled(true);
        RemoveModifier::options |= RemoveModifier::REMOVE_RANGE;
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
        on_comboBox_4_currentIndexChanged(ui->comboBox_4->currentIndex());

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
        DateModifier::options |= DateModifier::DATE_MADE;
        ui->dateEdit->setEnabled(false);
        break;
    case 1:
        DateModifier::options |= DateModifier::DATE_MOD;
        ui->dateEdit->setEnabled(false);
        break;
    case 2:
        DateModifier::options |= DateModifier::DATE_TODAY;
        ui->dateEdit->setEnabled(false);
        break;
    case 3:
        DateModifier::options |= DateModifier::DATE_CUSTOM;
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






