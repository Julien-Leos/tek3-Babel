/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** fortunethread
*/

#ifndef FORTUNETHREAD_HPP
#define FORTUNETHREAD_HPP

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class FortuneThread : public QThread
{
    Q_OBJECT

public:
    FortuneThread(QObject *parent = 0);
    ~FortuneThread();

    void requestNewFortune(const QString &hostName, quint16 port);
    void run() override;

signals:
    void newFortune(const QString &fortune);
    void error(int socketError, const QString &message);

private:
    QString hostName;
    quint16 port;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
};
#endif