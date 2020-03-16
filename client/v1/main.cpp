/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** main
*/

#include <QApplication>

#include "blockingclient.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BlockingClient client;
    client.show();
    return app.exec();
}