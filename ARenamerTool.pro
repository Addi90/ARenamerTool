QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    modifiers/addmodifier.cpp \
    modifiers/datemodifier.cpp \
    modifiers/ifthenmodifier.cpp \
    main.cpp \
    mainwindow.cpp \
    modifiers/modifier.cpp \
    modifiers/numbermodifier.cpp \
    modifiers/removemodifier.cpp \
    renamefile.cpp \
    renamefilemodel.cpp \
    renamer.cpp \
    modifiers/replacemodifier.cpp

HEADERS += \
    modifiers/addmodifier.h \
    modifiers/datemodifier.h \
    modifiers/ifthenmodifier.h \
    mainwindow.h \
    modifiers/modifier.h \
    modifiers/numbermodifier.h \
    modifiers/removemodifier.h \
    renamefile.h \
    renamefilemodel.h \
    renamer.h \
    modifiers/replacemodifier.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    languages/ARenamerTool_de_DE.ts \
    languages/ARenamerTool_en_EN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    languages/ARenamerTool_en_EN.ts \
    languages/ARenamerTool_de_DE.ts
