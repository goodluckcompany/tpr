#include "alternative.h"

double Alternative::getProbability() const
{
    return probability;
}

void Alternative::setProbability(double value)
{
    probability = value;
}

bool Alternative::isProbabilityValid() const
{
    return (this->getProbability() <= 1 && this->getProbability()>=0);
}

double Alternative::getValuation() const
{
    return valuation;
}

void Alternative::setValuation(double value)
{
    valuation = value;
}

QString Alternative::getDecision() const
{
    return decision;
}

void Alternative::setDecision(const QString &value)
{
    decision = value;
}

Alternative::Alternative(QString _substance, double _probability, double _valuation, QObject *parent)
{
    this->decision = _substance;
    this->probability = _probability;
    this->valuation = _valuation;
}
