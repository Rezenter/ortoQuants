#include "stateold.h"

StateOld::StateOld(qreal m1, qreal m2)
{
    this->m1 = m1;
    this->m2 = m2;

}

QDebug operator<<(QDebug stream, const StateOld &state) {
    stream << "|" << state.m1 << ", " << state.m2 << ">";
    return stream;
}
