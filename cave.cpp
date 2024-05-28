#include "cave.h"
#include<iostream>
#include <unistd.h>


Cave::Cave(){}

QString Cave::get_name(){
    return _name;
}
int Cave::get_gold(){
    return _gold;
}
int Cave::get_id(){
    return _id;
}
int Cave::get_enemyNr(){
    return _enemyNr;
}
void Cave::FightCaveEnemies(int caveId) {

    int t;
    std::cin >> t;

    QSqlQuery query;
        query.prepare("SELECT enemy_name, hp, xp, strength FROM Cave_enemy WHERE cave_id = :caveId");
        query.bindValue(":caveId", caveId);

        if (!query.exec()) {
            qDebug() << "Failed to fetch enemies in the cave";
        }
        while (query.next()) {
                QString enemyName = query.value(0).toString();
                int enemyHp = query.value(1).toInt();
                int enemyXp = query.value(2).toInt();
                int enemyStrength = query.value(3).toInt();

        }

}


void Cave::Select_cave() {

     QSqlQuery query;
     QTextStream input(stdin);
     QString userInput;

         sleep(1);

     qDebug() << "  >> Let's start playing, Shall we !? Please choose one of the following caves: " << Qt::endl;

         sleep(1);

     query.prepare("SELECT cave_name, gold FROM Cave");

     if (query.exec()) {
        int count = 1;
            while (query.next()) {
                QString name = query.value(0).toString();
                    qDebug() << count << ". " << name << Qt::endl;
                    count++;
            }

            bool isValidSelection = false;
            int chosenCave;
            while (!isValidSelection) {
                qDebug() << "Enter the number of the cave you want to enter: ";
                userInput = input.readLine();
                chosenCave = userInput.toInt();

                if (chosenCave > 0 && chosenCave < count) {
                    isValidSelection = true;
                }
                else {
                    qDebug() << "Invalid selection. Please choose a valid number." << Qt::endl;
                }
            }

            query.seek(chosenCave - 1);
            QString selectedCave = query.value(0).toString();
            qDebug() << "You have selected: " << selectedCave << Qt::endl;

            Assign_cave(selectedCave);

     }
     else {
            qDebug() << "Error executing query: " << query.lastError().text() << Qt::endl;
     }
}


void Cave::Assign_cave(QString chosenCave) {
    QSqlQuery query;

    query.prepare("SELECT * FROM Cave WHERE cave_name = :name");
    query.bindValue(":name", chosenCave);

    if (query.exec() && query.next()) {

        _name = chosenCave;
        _gold = query.value(2).toInt();
        _id = query.value(0).toInt();

        qDebug() << "The cave: " << _name << " has " << _gold << " gold to get " << Qt::endl << "But there are these enemies to fight: " << Qt::endl;

    }
    else {

        qDebug() << "Error retrieving cave's data from the database." << Qt::endl;
    }

    query.prepare("SELECT * FROM Cave_enemy, Cave WHERE Cave_enemy.cave_id = Cave.cave_id AND Cave.cave_id = :caveId");
    query.bindValue(":caveId", _id);


    if (query.exec()) {
        while (query.next()) {
            QString enemyName = query.value("enemy_name").toString();
            int enemyHp = query.value("HP").toInt();
            int enemyXp = query.value("XP").toInt();
            int enemyStrength = query.value("Strength").toInt();

            qDebug() << "  >>   " << enemyName << ", HP: " << enemyHp
                     << ", XP: " << enemyXp << ", Strength: " << enemyStrength << Qt::endl;
        }
    } else {
        qDebug() << "Error getting cave's enemies from the database." << Qt::endl;
    }

    query.prepare("SELECT * FROM Cave_enemy, Cave WHERE Cave_enemy.cave_id = Cave.cave_id AND Cave.cave_id = :caveId");
    query.bindValue(":caveId", _id);

        if (query.exec()) {
            while (query.next()) {
                QString enemyName = query.value("enemy_name").toString();
                int enemyHp = query.value("HP").toInt();
                int enemyXp = query.value("XP").toInt();
                int enemyStrength = query.value("Strength").toInt();


            }
        }

    QTextStream input(stdin);
    QString userInput;

    qDebug() << " >> Press any button to start fighting. ";
    input.readLine();

}


QString Cave::get_enemyName(int enemy_id){
    QSqlQuery query;
    query.prepare("SELECT enemy_name FROM Cave_enemy WHERE cave_id = :caveId AND enemy_id = :enemy_id");
    query.bindValue(":caveId", _id);
    query.bindValue(":enemy_id", enemy_id);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

int Cave::get_enemyHp(int enemy_id){
    QSqlQuery query;
    query.prepare("SELECT HP FROM Cave_enemy WHERE cave_id = :caveId AND enemy_id = :enemy_id");
    query.bindValue(":caveId", _id);
    query.bindValue(":enemy_id", enemy_id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int Cave::get_enemyXp(int enemy_id){
    QSqlQuery query;
    query.prepare("SELECT XP FROM Cave_enemy WHERE cave_id = :caveId AND enemy_id = :enemy_id");
    query.bindValue(":caveId", _id);
    query.bindValue(":enemy_id", enemy_id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int Cave::get_enemyStrength(int enemy_id){
    QSqlQuery query;
    query.prepare("SELECT Strength FROM Cave_enemy WHERE cave_id = :caveId AND enemy_id = :enemy_id");
    query.bindValue(":caveId", _id);
    query.bindValue(":enemy_id", enemy_id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}
