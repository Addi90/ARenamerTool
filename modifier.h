#ifndef MODIFIER_H
#define MODIFIER_H



#include <QString>
#include <QObject>

class Modifier : public QObject
{
Q_OBJECT
public:
    Modifier();
    virtual ~Modifier();
    QString modify(QString currName);
private:
};


#endif // MODIFIER_H
