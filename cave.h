#ifndef CAVE_H
#define CAVE_H


#include <QtSql>
#include <QSqlDatabase>
#include "enemy.h"

class Cave
{
private:
    QString _name;
    int _gold;
    int _id;
    int _enemyNr;


public:
    Cave();

    QString get_name();
    int get_gold();
    int get_id();
    int get_enemyNr();
    void FightCaveEnemies(int caveId);
    void Select_cave();
    void Assign_cave(QString chosenCave);

    int get_enemyXp(int enemy_id);

    int get_enemyHp(int enemy_id);
    int get_enemyStrength(int enemy_id);

    QString get_enemyName(int enemy_id);
};

#endif // CAVE_H
