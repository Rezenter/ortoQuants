#include "basis.h"
#include <qDebug>
#include <QtMath>

Basis::Basis(qreal j1n, qreal j2n)
{
    j1 = j1n;
    j2 = j2n;
    path.chop(8);
    root = new State(j1 + j2, j1 + j2);
    root->corr.insert(QPair<qreal, qreal>(j1, j2), 1);
}

void Basis::start(){
    State *curr = root;
    while(curr->j > 1){
        listed = false;
        mRow(curr);
        curr->left = new State(curr->j - 1, curr->j - 1);
        out = new QFile("state.txt");
        out->open(QIODevice::WriteOnly);
        outStream = new QTextStream(out);
        order = QList<QPair<qreal, qreal>>();
        level(root, curr->j - 1);
        out->close();
        orto = new QProcess();
        orto->start(path + file);
        while(orto->waitForFinished()){

        }
        in = new QFile("coeffs.txt");
        in->open(QIODevice::ReadOnly);
        inStream = new QTextStream(in);
        int i = 0;
        while(!inStream->atEnd()) {
            QString line = inStream->readLine();
            curr->left->corr.insert(order.at(i), line.toDouble());
            i++;
        }
        in->close();
        curr = curr->left;
    }
    mRow(curr);
    out->remove();
    in->remove();
}

void Basis::J_(State *state){
    qreal down = (state->j + state->m)*(state->j - state->m + 1);//?
    QList<QPair<qreal, qreal>> keys = state->corr.keys();
    QPair<qreal, qreal> tmp;
    QPair<qreal, qreal> key;
    foreach (key, keys) {
        QPair<qreal, qreal> contrib = J_(key);
        if(contrib.first != 0){
            tmp = QPair<qreal, qreal>(key.first - 1, key.second);
            if(state->right->corr.contains(tmp)){
                state->right->corr.insert(tmp, qSqrt((contrib.first)/down)*state->corr.value(key) + state->right->corr.take(tmp));
            }else{
                state->right->corr.insert(tmp, qSqrt(contrib.first/down)*state->corr.value(key));
            }
        }
        if(contrib.second != 0){
            tmp = QPair<qreal, qreal>(key.first, key.second - 1);
            if(state->right->corr.contains(tmp)){
                state->right->corr.insert(tmp, qSqrt(contrib.second/down)*state->corr.value(key) + state->right->corr.take(tmp));
            }else{
                state->right->corr.insert(tmp, qSqrt(contrib.second/down)*state->corr.value(key));
            }
        }
    }
    QHash<QPair<qreal, qreal>, qreal>::iterator i;
    for (i = state->right->corr.begin(); i != state->right->corr.end(); ++i){
    }

}

QPair<qreal, qreal> Basis::J_(QPair<qreal, qreal> state){
    return QPair<qreal, qreal>((j1 + state.first)*(j1 - state.first + 1), (j2 + state.second)*(j2 - state.second + 1));
}

void Basis::mRow(State *curr){
    curr->right = new State(curr->j, curr->m - 1);
    J_(curr);
    curr = curr->right;
    while(abs(curr->m) < curr->j){
        curr->right = new State(curr->j, curr->m - 1);
        J_(curr);
        curr = curr->right;
    }
}

 void Basis::level(State *curr, int l){
     if(curr->m == l && curr->j == l){
     }else{
        if(curr->m == l || curr->j == l){
            if(!listed){
                QHash<QPair<qreal, qreal>, qreal>::iterator i;
                for (i = curr->corr.begin(); i != curr->corr.end(); ++i){
                    order.append(QPair<qreal, qreal>(i.key().first, i.key().second));
                }
                listed = true;
            }
            QPair<qreal, qreal> tmp;
            foreach (tmp, order) {
                *outStream << curr->corr.value(tmp) << " ";
            }
            *outStream << endl;
        }else{
                level(curr->right, l);
                if(curr->m == curr->j){
                    level(curr->left, l);
                }

        }
    }
}
