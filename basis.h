#ifndef BASIS_H
#define BASIS_H
#include "state.h"
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>

class Basis
{
public:
    Basis(qreal, qreal);
    ~Basis();
    State *root; //state with max projection
    qreal j1; //spin 1
    qreal j2; //spin 2
    void J_(State*); // J_ operator applied to the State
    QPair<qreal, qreal> J_(QPair<qreal, qreal>);//J_ = (J1_ + J2_) operator applied to the StateOld
    void mRow(State *);
    QFile *out;
    QTextStream *outStream;
    QFile *in;
    QTextStream *inStream;
    QProcess *orto;
    QString path = QCoreApplication::applicationFilePath();
    QString file = "ortoQuants.exe";
    QList<QPair<qreal, qreal>> order;
    bool listed = false;
    void start();

private:
    void level(State*, int);
};

#endif // BASIS_H
