#ifndef STATEOLD_H
#define STATEOLD_H
#include <QDebug>

class StateOld
{
public:
    StateOld(qreal, qreal);
    qreal m1;
    qreal m2;
    friend QDebug operator<<(QDebug, const StateOld&);
};

#endif // STATEOLD_H
