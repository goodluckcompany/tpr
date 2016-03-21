#ifndef ANSWER_H
#define ANSWER_H

#include <QObject>

class Answer : public QObject
{
    Q_OBJECT
    double usefulness;
    QString decision;
public:
    Answer(double _usefuleness, QString _decision, QObject *parent = 0);

    double getUsefulness() const;
    void setUsefulness(double value);

    QString getDecision() const;
    void setDecision(const QString &value);

signals:

public slots:
};

#endif // ANSWER_H
