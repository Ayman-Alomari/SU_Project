#ifndef HERO_H
#define HERO_H

//#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include "enemy.h"



class Hero
{
private:
    QString _name;
    int _hp;
    int _level;
    int _xp;
    int _strength;

public:
    Hero();

    void levelUp();

    void start_playing();
    void Make_Hero(QString name);
    bool Load_Hero();

    QString get_name();
    int get_hp();
    int get_xp();
    int get_level();
    int get_strength();
    int get_gold();
    int get_id();

    bool fightEnemy(Enemy* enemy);

    bool DefeatedEnemyActions();
    void ContinueBattle();

    void SaveAndExit();


};
#endif
