#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include<iostream>
#include "hero.h"
#include "enemy.h"
#include "cave.h"
#include <string>

int main(int argc, char *argv[]){

    Hero hero;
    Enemy enemy;
    Cave cave;

    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("SU_Project"); // Ret til det schema navn du har valgt
    db.setUserName("root"); // Ret brugernavn
    db.setPassword("password");// Ret password
    db.open();

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
