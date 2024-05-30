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
    QString _element;

public:
    Enemy();

    void Select_enemy();
    void Assign_enemy(QString selectedEnemy);

    QString get_name();
    int get_hp();
    int get_xp();
    int get_strength();
    QString get_element();


};
#endif // ENEMY_H
