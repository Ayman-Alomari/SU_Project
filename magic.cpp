#include "magic.h"
#include<iostream>
#include <unistd.h>


Magic::Magic() {};

int Magic::get_id(){
    return _id;
}

QString Magic::get_name(){
    return _name;
}

int Magic::get_strength(){
    return _strength;
}

int Magic::get_Self_strength(){
    return _Self_strength;
}

int Magic::get_magic_cost(){
    return _magic_cost;
}

QString Magic::get_element(){
    return _element;
}

int Magic::get_gold_cost(){
    return _gold_cost;
}

QString Magic::get_requirement(){
    return _requirement;
}



void Magic::Select_Magic() {

     QSqlQuery query;
     QTextStream input(stdin);
     QString userInput;

         sleep(1);

     qDebug() << "  >> Here is a list  of the magic, you can buy: " << Qt::endl;

         sleep(1);

     query.prepare("SELECT * FROM Magic");

     if (query.exec()) {
        int count = 1;
            while (query.next()) {
                QString name = query.value(1).toString();
                int strength = query.value(2).toInt();
                int Self_strength = query.value(3).toInt();
                int magic_cost = query.value(4).toInt();
                int gold_cost = query.value(6).toInt();
                QString requirement = query.value(7).toString();

                    qDebug() << count << ". " << name << strength << " strength " << Self_strength << " self_strength " << magic_cost << " magic_cost " << gold_cost << " gold_cost " << requirement << " requirement " <<  Qt::endl;
                    count++;
            }

            bool isValidSelection = false;
            int chosenMagic;
            while (!isValidSelection) {
                qDebug() << "Enter the number of the magic you want to buy: ";
                userInput = input.readLine();
                chosenMagic = userInput.toInt();

                if (chosenMagic > 0 && chosenMagic <= count) {
                    isValidSelection = true;
                }
                else {
                    qDebug() << "Invalid selection. Please choose a valid number." << Qt::endl;
                }
            }

            query.seek(chosenMagic - 1);
            QString selectedMagic = query.value(1).toString();
            qDebug() << "You have selected: " << selectedMagic << Qt::endl;

            Assign_Magic(selectedMagic);

     }
     else {
            qDebug() << "Error executing query: " << query.lastError().text() << Qt::endl;
     }
}


void Magic::Assign_Magic(QString ChosenMagic) {
    QSqlQuery query;


    query.prepare("SELECT * FROM Magic WHERE name = :name");
    query.bindValue(":name", ChosenMagic);

    if (query.exec() && query.next()) {
       _id = query.value(0).toInt();
       _name = ChosenMagic;
       _strength = query.value(2).toInt();
       _Self_strength = query.value(3).toInt();
       _magic_cost = query.value(4).toInt();
       _gold_cost = query.value(6).toInt();
       _requirement = query.value(7).toString();

    }

    else {
        qDebug() << "Error retrieving magic data from the database." << Qt::endl;
    }
}
