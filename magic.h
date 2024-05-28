#ifndef MAGIC_H
#define MAGIC_H

#include <QtSql>
#include <QSqlDatabase>

class Magic
{
private:
    int _id;
    QString _name;
    int _strength;
    int _Self_strength;
    int _magic_cost;
    QString _element;
    int _gold_cost;
    QString _requirement;

public:
     Magic();

    int get_id();
    QString get_name();
    int get_strength();
    int get_Self_strength();
    int get_magic_cost();
    QString get_element();
    int get_gold_cost();
    QString get_requirement();

    void Select_Magic();

    void Assign_Magic(QString ChosenMagic);









};

#endif // MAGIC_H
