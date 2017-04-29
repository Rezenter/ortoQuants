#ifndef STATE_H
#define STATE_H
#include <QHash>

class State
{
public:
    State(qreal, qreal);
    ~State();
    State *left; //stores state with same proj. but less spin
    State *right; //stores state with same spin but less proj.
    qreal j; //spin new
    qreal m; //proj. new
    QHash<QPair<qreal, qreal>, qreal> corr; //stores correlation between old/new basis.
};

#endif // STATE_H
