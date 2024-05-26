#include "enemy.h"
#include<iostream>
#include <unistd.h>

Enemy::Enemy() {}


void Enemy::Select_enemy() {

     QSqlQuery query;
     QTextStream input(stdin);
     QString userInput;

         sleep(1);

     qDebug() << "  >> Let's start playing, Shall we !? Please choose one of the following enemies: " << Qt::endl;

         sleep(1);

     query.prepare("SELECT name FROM enemy");

     if (query.exec()) {
        int count = 1;
            while (query.next()) {
                QString name = query.value(0).toString();
                    qDebug() << count << ". " << name << Qt::endl;
                    count++;
            }

            bool isValidSelection = false;
            int chosenEnemy;
            while (!isValidSelection) {
                qDebug() << "Enter the number of the enemy you want to fight: ";
                userInput = input.readLine();
                chosenEnemy = userInput.toInt();

                if (chosenEnemy > 0 && chosenEnemy < count) {
                    isValidSelection = true;
                }
                else {
                    qDebug() << "Invalid selection. Please choose a valid number." << Qt::endl;
                }
            }

            query.seek(chosenEnemy - 1);
            QString selectedEnemy = query.value(0).toString();
            qDebug() << "You have selected: " << selectedEnemy << Qt::endl;
            Assign_enemy(selectedEnemy);

     }
     else {
            qDebug() << "Error executing query: " << query.lastError().text() << Qt::endl;
     }
}

void Enemy::Assign_enemy(QString chosenEnemy) {
    QSqlQuery query;


    query.prepare("SELECT * FROM enemy WHERE name = :name");
    query.bindValue(":name", chosenEnemy);

    if (query.exec() && query.next()) {

        _name = chosenEnemy;
        _hp = query.value(1).toInt();
        _xp = query.value(2).toInt();
        _strength = query.value(3).toInt();

        qDebug() << "The enemy: " << _name << " has HP: " << _hp << ", XP: " << _xp << ", Strength: " << _strength << Qt::endl;
    } else {
        qDebug() << "Error retrieving enemy data from the database." << Qt::endl;
    }
}


int Enemy::get_hp(){
    return _hp ;
}

int Enemy::get_xp(){
    return _xp ;
}

int Enemy::get_strength(){
    return _strength ;
}

QString Enemy::get_name(){
    return  _name;
}
