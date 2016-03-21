#include "answer.h"

Answer::Answer(double _usefuleness, QString _decision, QObject *parent)
{
    this->usefulness = _usefuleness;
    this->decision = _decision;
}

double Answer::getUsefulness() const
{
    return usefulness;
}

void Answer::setUsefulness(double value)
{
    usefulness = value;
}

QString Answer::getDecision() const
{
    return decision;
}

void Answer::setDecision(const QString &value)
{
    decision = value;
}
