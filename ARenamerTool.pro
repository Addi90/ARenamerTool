QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmodifier.cpp \
    datemodifier.cpp \
    ifthenmodifier.cpp \
    main.cpp \
    mainwindow.cpp \
    modifier.cpp \
    numbermodifier.cpp \
    removemodifier.cpp \
    renamefile.cpp \
    renamefilemodel.cpp \
    renamer.cpp \
    replacemodifier.cpp

HEADERS += \
    addmodifier.h \
    datemodifier.h \
    ifthenmodifier.h \
    mainwindow.h \
    modifier.h \
    numbermodifier.h \
    removemodifier.h \
    renamefile.h \
    renamefilemodel.h \
    renamer.h \
    replacemodifier.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    ARenamerTool_de_DE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
