#ifndef APPENDMODIFIER_H
#define APPENDMODIFIER_H


#include <QDebug>
#include "modifier.h"

class AppendModifier : public Modifier
{

public:
    enum Option{
            REMOVE_CHARS = 0x4
        };
    Q_DECLARE_FLAGS(Options, Option)

    static QString appendStr;
    static int remNumChars;
    static unsigned int options;


    static QString modify(QString currName);
    AppendModifier();
public slots:
    static void appendString(const QString &newAppStr);
    static void removeChars(const int &num);

};

#endif // APPENDMODIFIER_H
