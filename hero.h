#ifndef HERO_H
#define HERO_H

#include <QtSql>
#include <QSqlDatabase>
#include "enemy.h"
#include "cave.h"
#include "magic.h"


class Hero
{
private:
    QString _name;
    int _hp;
    int _level;
    int _xp;
    int _strength;
    int _gold;
    int _magic_level;
    int _id;
    Magic *magic;

public:
    Hero(Magic *magic);

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
    int get_magic_level();
    int get_id();

    bool fightEnemy(Enemy* enemy);

    bool DefeatedEnemyActions();
    void ContinueBattle();

    void SaveAndExit();

    bool fightEnemyInCave(Cave* cave);

    bool DefeatedEnemyInCave_Actions();

    bool Defeated_Cave_Actions();


    bool Buy_Magic(Magic* magic);

};
#endif
