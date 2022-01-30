#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QAbstractItemModel>
#include <QDebug>
#include <QMessageBox>
#include <QActionGroup>
#include <QTranslator>

#include "renamefilemodel.h"
#include "renamefile.h"
#include "renamer.h"
#include "modifiers/addmodifier.h"
#include "modifiers/removemodifier.h"
#include "modifiers/replacemodifier.h"
#include "modifiers/numbermodifier.h"
#include "modifiers/ifthenmodifier.h"
#include "modifiers/datemodifier.h"


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
    QString path;
    QActionGroup* langGroup;

    void ifThenOptionResolver(int condition, int consequence);
    void controlsRedrawConnector();
    void delay();
    // loads a language by the given language shortcur (e.g. de, en)
    void loadLanguage(const QString& rLanguage);

    // creates the language menu dynamically from the content of m_langPath
    void createLanguageMenu();

    QTranslator m_translator; // contains the translations for this application
    QTranslator m_translatorQt; // contains the translations for qt
    QString currLang; // contains the currently loaded language
    QString m_langPath; // Path of language files. This is always fixed to /languages.
protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*);

protected slots:
    // this slot is called by the language menu actions
    void slotLanguageChanged(QAction* action);

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
    void on_checkBox_6_stateChanged(int arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_treeView_2_clicked(const QModelIndex &index);
    void on_checkBox_8_stateChanged(int arg1);
    void on_checkBox_11_stateChanged(int arg1);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_radioButton_6_clicked();
    void on_checkBox_12_stateChanged(int arg1);
    void on_checkBox_13_stateChanged(int arg1);

    void repaintView();
};
#endif // MAINWINDOW_H
