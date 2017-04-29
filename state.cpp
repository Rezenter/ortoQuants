#include "state.h"

State::State(qreal j, qreal m)
{
    this->j = j;
    this->m = m;
    corr = QHash<QPair<qreal, qreal>, qreal>();
}

State::~State(){

}
