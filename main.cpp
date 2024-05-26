#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include<iostream>
#include "hero.h"
#include "enemy.h"


#include <string>

int main(int argc, char *argv[]){

    Hero hero;
    Enemy enemy;

    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("SU_Project"); // Ret til det schema navn du har valgt
    db.setUserName("root"); // Ret brugernavn
    db.setPassword("password");// Ret password
    db.open();



    hero.start_playing();

    while(1){


                enemy.Select_enemy();
                if(hero.fightEnemy(&enemy)){
                    if(hero.DefeatedEnemyActions()){

                        break;
                    }
                }
            }



    return 0;
}
