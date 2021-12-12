#ifndef APPENDMODIFIER_H
#define APPENDMODIFIER_H


#include "modifier.h"

class AppendModifier : public Modifier
{

public:
    enum Option{
            REMOVE_CHARS = 0x1,
            ADD_COUNT = 0x2
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString appendStr;
    static int remNumChars;
    static unsigned int startNum;
    static unsigned int options;


    static QString modify(QString currName);
    static int modify(QList<RenameFile*>* renameFileList);

    AppendModifier();
public slots:
    static void appendString(const QString &newAppStr);
    static void removeChars(const int &num);

};

#endif // APPENDMODIFIER_H
