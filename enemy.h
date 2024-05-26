#ifndef ENEMY_H
#define ENEMY_H

#include <QtSql>
#include <QSqlDatabase>


class Enemy
{
private:
    QString _name;
    int _hp;
    int _xp;
    int _strength;

public:
    Enemy();

    void Select_enemy();
    void Assign_enemy(QString selectedEnemy);

    QString get_name();
    int get_hp();
    int get_xp();
    int get_strength();



};
#endif // ENEMY_H
