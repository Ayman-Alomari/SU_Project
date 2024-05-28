#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include<iostream>
#include "hero.h"
#include "enemy.h"
#include "cave.h"
#include "magic.h"

#include <string>

int main(int argc, char *argv[]){

    Hero hero;
    Enemy enemy;
    Cave cave;
    Magic magic;

    QCoreApplication a(argc, argv);

////////////////////////////  Database ////////////////////////////

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("SU_Project");

    std::cout << "Enter database username: ";
    std::string username;
    std::cin >> username;
    db.setUserName(username.c_str());

    std::cout << "Enter database password: ";
    std::string password;
    std::cin >> password;
    db.setPassword(password.c_str());

    if (!db.open()) {
        qDebug()  << "Failed to open database: " << db.lastError().text() << Qt::endl;
        return 1;
    }

////////////////////////////////////////////////////////////////////////////////////

//      magic.Select_Magic();

    hero.start_playing();

    while(1){

        QString option;
        do {
            qDebug() << "  >> Let's start playing, Shall we !? Please choose one of the following optoins: ";
            qDebug() << "1. Select a cave to enter.";
            qDebug() << "2. Select an enemy to fight. ";
            QTextStream qtin(stdin);
            option = qtin.readLine();

            if (option == "1") {
                    //Select a cave to enter.
                magic.Select_Magic();
                hero.Buy_Magic(&magic);

                cave.Select_cave();
                if(hero.fightEnemyInCave(&cave)){

                    if(hero.DefeatedEnemyInCave_Actions()){
                        break;
                    }

                }
            }
            else if (option == "2") {
                // Select an enemy to fight.

                enemy.Select_enemy();
                if(hero.fightEnemy(&enemy)){
                    if(hero.DefeatedEnemyActions()){

                        break;
                    }
                }
            }

            else {
                qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
            }

        }
        while (option != "1" && option != "2");

    }

    return 0;
}
