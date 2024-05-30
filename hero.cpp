#include "hero.h"
#include<iostream>


Hero::Hero(Magic *magic):magic(magic){}

void Hero::start_playing (){
    QSqlQuery query;

    QTextStream input(stdin);
    QString userInput;

    qDebug() << "Welcome to SU_Game. Press any button to start";
    input.readLine();

    bool validChoice = false;
    while (!validChoice) {
        qDebug() << " Please choose one of the following options: " << Qt::endl;
        qDebug() << "  >> For creating a new hero, Press (0) " << Qt::endl;
        qDebug() << "  >> For loading an existing hero, Press (1) " << Qt::endl;
        qDebug() << "  >> For exit, Press (9) " << Qt::endl;


        int t;
        std::cin >> t;

        if (t == 0) {
            qDebug() << "Enter the name of the new hero:";

            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);

            QString heroName = QString::fromStdString(name);
            Make_Hero(heroName);
            validChoice = true;

        }
        else if (t==1){
            Load_Hero();
            validChoice = true;

        }
        else if (t==9){
                qDebug() << "Exiting the program...";
            exit(0); // Exit the program

        }
        else {
                qDebug() << "Your selection was not recognized!!. Please try again " << Qt::endl;
        }
    }

}


void Hero::Make_Hero(QString name){
    QSqlQuery query;

    qDebug() << "Creating hero with name: " << name;

    _name = name;
    _hp = 10;
    _xp = 0;
    _level = 1;
    _strength = 2;
    _gold = 0;
    _magic_level=1;



      query.prepare("INSERT INTO hero (Name, HP, XP, Level, Strength, Gold, magic_level) VALUES (?, 10, 0, 1, 2, 0, 1)");
      query.bindValue(0, name);

      if(query.exec()) {
          query.prepare("SELECT LAST_INSERT_ID()");
                  query.exec();
                  query.next();
                  _id = query.value(0).toInt();
          qDebug() << "The hero" << _name <<"successfully created and saved to the database." << Qt::endl;
          qDebug() << "The hero" << _name <<" with" << _hp << "hp" << _xp << "xp" << _level << "Level" << _strength << "strength" << _gold << "Gold" << _magic_level << "magic_level" << "has been created. " << Qt::endl;
      }

      else {
          qDebug() << "Error: Failed to create hero in the database.";
      }
 }


bool Hero::Load_Hero() {

    bool validChoice = false;
    while (!validChoice) {
        QSqlQuery query;

        query.prepare("SELECT * FROM hero");

        if (query.exec()) {
             if (!query.next()) {
                 // Empty set !!

                qDebug() << "There is no heroes to load. Please choose one of the following: "  << Qt::endl;
                qDebug() << "  >> For creating a new hero, Press (1) " << Qt::endl;
                qDebug() << "  >> For exit the game, Press (2) " << Qt::endl;

                bool validChoice = false;
                while (!validChoice) {
                    int t;
                    std::cin >> t;
                    if (t == 1) {
                        qDebug() << "Enter the name of the new hero:" << Qt::endl;
                        std::string name;
                        std::cin.ignore();
                        std::getline(std::cin, name);

                        QString heroName = QString::fromStdString(name);
                        Make_Hero(heroName);

                        return true;
                    }
                    else if(t == 2) {
                        exit(0);
                        validChoice =true;
                    }

                }
             }

           qDebug() << "Enter the name of the hero, you want to upload from the list: ";

           query.prepare("SELECT * FROM hero");
           query.exec();
           int count = 1;
               while (query.next()) {
                   QString name = query.value(0).toString();
                       qDebug() << count << ". " << name << Qt::endl;
                       count++;
               }

        }


        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);

        QString heroName = QString::fromStdString(name);

        query.prepare("SELECT * FROM hero WHERE name = :name");
        query.bindValue(":name", heroName);

        if (query.exec()) {
            if (query.next()) {
                _name = query.value(0).toString();
                _hp = query.value(1).toInt();
                _xp = query.value(2).toInt();
                _level = query.value(3).toInt();
                _strength = query.value(4).toInt();
                _gold = query.value(5).toInt();
                _magic_level = query.value(6).toInt();
                _id = query.value(7).toInt();


                qDebug() << "Hero loaded successfully." << Qt::endl;

                qDebug() << "Hero with" << _hp << "hp" << _xp << "xp" << _level << "Level" << _strength << "strength" <<_gold << "gold" <<_magic_level << "magic_level" << "has been uploaded. " << Qt::endl;
                validChoice = true;
            }
            else {
                qDebug() << "Hero with name" << heroName << "not found.";
            }
        }
        else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    }
    return true;
}

QString Hero::get_name(){
    return  _name;
}

int Hero::get_hp(){
    return _hp;
}

int Hero::get_xp(){
    return _xp ;
}

int Hero::get_level(){
    return _level ;
}

int Hero::get_strength(){
    return _strength ;
}

int Hero::get_gold(){
    return _gold;
}

int Hero::get_id(){
    return _id;
}

bool Hero::fightEnemy(Enemy* enemy) {
    QSqlQuery query;

    qDebug() << "The hero is fighting the enemy: " << enemy->get_name() << Qt::endl;

    QString enemy_name = enemy->get_name();
        int enemy_hp = enemy->get_hp();
        int enemy_xp = enemy->get_xp();
        int enemy_strength = enemy->get_strength();

    while (enemy_hp > 0 && _hp > 0){
                QString option;
        do {
            qDebug() << "Select an option:";
            qDebug() << "1. Attack with magic";
            qDebug() << "2. Attack without magic";

            QTextStream qtin(stdin);
            option = qtin.readLine();

            if (option == "1") {
                    //Attack with magic

                // check which magic the hero has and then ..
                QSqlQuery query;
                query.prepare("SELECT Magic.name, Magic.strength, Magic.self_strngth FROM Magic, Magic_Shop, hero WHERE id = :id, magic_id = :magic_id, magic_name = :magic_name");
                query.bindValue(":id", _id);
                query.bindValue(":magic_id", magic->get_id());
                query.bindValue(":magic_name", magic->get_name());

                int magic_strength = magic->get_strength();
                int magic_Self_strength = magic->get_Self_strength();

                enemy_hp -= _strength + magic_strength ;

                _hp -= enemy_strength+magic_Self_strength;

                qDebug() << "The hero attacked the enemy with power: " << _strength + magic_strength << Qt::endl;
                qDebug() << "Enemy's health after the attack: " << enemy_hp << Qt::endl;
                qDebug() << _name<<"'s health after the attack: " << _hp << Qt::endl;

            }

            else if (option == "2") {
                // Attack without magic

                enemy_hp -= _strength;

                _hp -= enemy_strength;

                qDebug() << "The hero attacked the enemy with power: " << _strength << Qt::endl;
                qDebug() << "Enemy's health after the attack: " << enemy_hp << Qt::endl;
                qDebug() << _name<<"'s health after the attack: " << _hp << Qt::endl;

            }
            else {
                qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
            }
        }
      while (option != "1" && option != "2");

        if (_hp <=0){
            qDebug() << "The hero" << this->get_name() << " has been defeated by the enemy " << enemy_name << "!" << Qt::endl;
            qDebug() << "Game Over and good luck next time ! " << Qt::endl;
            QSqlQuery query;
                    query.prepare("DELETE FROM hero WHERE name = :name");
                    query.bindValue(":name", _name);

                    query.exec();
                    if (query.exec()) {
                        qDebug() << "Hero" << _name <<" has been removed successfully." <<Qt::endl;
                    }
                    else {
                        qDebug() << "Error: Failed removing hero from the database." << query.lastError().text()<< Qt::endl;
                    }
            exit(0);
        }

        if (enemy_hp <= 0) {
            qDebug() << "The enemy has been defeated by the hero " << this->get_name() << " !" << Qt::endl;
            _xp +=enemy_xp;

            if (_hp < 10) {
                _hp = 10;
            }

            if (_xp >= _level * 1000){
              levelUp();

            }

            return true;

        }
        else {
              qDebug() << "The hero couldn't defeat the enemy in one attack. The battle continues..." << Qt::endl;

              ContinueBattle();
        }
    }

    return true;

}

bool Hero::DefeatedEnemyActions(){
    bool validChoice = false;
    while (!validChoice) {
        QString option;
        do {
            qDebug() << "Select an option:";
            qDebug() << "1. Save and exit";
            qDebug() << "2. Continue and select another enemy to fight ";
            QTextStream qtin(stdin);
            option = qtin.readLine();

            if (option == "1") {
                    //Save and exit

                SaveAndExit();

                validChoice = true;
                return true;
            }
            else if (option == "2") {
                // Continue and select another enemy to fight.

                validChoice = true;
                return false;
            }
            else {
                qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
            }
        }
      while (option != "1" && option != "2");
    }
    return true;
}

void Hero::SaveAndExit(){

    QSqlQuery query;

    query.prepare("UPDATE hero SET hp = :hp, xp = :xp, level = :level, strength = :strength, gold = :gold, magic_level = :magic_level WHERE name = :name");

    query.bindValue(":hp", _hp);
    query.bindValue(":xp", _xp);
    query.bindValue(":level", _level);
    query.bindValue(":strength", _strength);
    query.bindValue(":name", _name);
    query.bindValue(":gold", _gold);
    query.bindValue(":magic_level", _magic_level);
    query.exec();

    if (query.exec()) {
        qDebug() << "Hero's data updated successfully in the database." <<Qt::endl;
    }
    else {
        qDebug() << "Error: Failed to update hero data in the database." << query.lastError().text()<< Qt::endl;
    }

}

void Hero::levelUp() {
           _level++;
           _magic_level++;
           _hp += 2;
           _strength++;
           _xp=0;
}


void Hero::ContinueBattle() {
    bool validChoice = false;
    while (!validChoice) {
         QString option;
         do {
            qDebug() << "Select an option:";
            qDebug() << "1. Exit the game without saving";
            qDebug() << "2. Continue fighting the current enemy";
            QTextStream qtin(stdin);
            option = qtin.readLine();

              if (option == "1") {
                  exit(0);
              }
              else if (option == "2") {
                  // Continue fighting the current enemy
                  validChoice = true;
              }
              else {
                  qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
              }
            }
        while (option != "1" && option != "2");
    }
}

bool Hero::fightEnemyInCave(Cave* cave) {
    QSqlQuery query;
    query.prepare("Select COUNT(enemy_id) FROM Cave_enemy WHERE cave_id = :cave_id");
    query.bindValue(":cave_id", cave->get_id());

    query.exec();
    query.first();

    int enemy_count = query.value(0).toInt();

    query.prepare("Select enemy_id FROM Cave_enemy WHERE cave_id = :cave_id");
    query.bindValue(":cave_id", cave->get_id());

    query.exec();
    query.first();

    int enemy_id = query.value(0).toInt();


    for(int i = enemy_id; i <= enemy_count+enemy_id; i++){


        qDebug() << "The hero is fighting the enemy: " << cave->get_enemyName(i) << Qt::endl;

        QString enemy_name = cave->get_enemyName(i);
            int enemy_hp = cave->get_enemyHp(i);
            int enemy_xp = cave->get_enemyXp(i);
            int enemy_strength = cave->get_enemyStrength(i);

        while (enemy_hp > 0 && _hp > 0){

            QString option;
    do {
        qDebug() << "Select an option:";
        qDebug() << "1. Attack with magic";
        qDebug() << "2. Attack without magic";

        QTextStream qtin(stdin);
        option = qtin.readLine();

        if (option == "1") {
            //Attack with magic

            // check which magic the hero has and then ..

            query.prepare("SELECT Magic.name, Magic.strength, Magic.self_strength FROM Magic, Magic_Shop, hero WHERE Magic_Shop.hero_id = :id AND Magic_Shop.magic_id = :magic_id AND Magic_Shop.magic_id = Magic.id AND Magic_Shop.hero_id = hero.id");
            query.bindValue(":id", _id);
            query.bindValue(":magic_id", magic->get_id());

            int chosenMagic;
            QString selectedMagic;

                if (query.exec()) {
                    int count = 1;
                    while (query.next()) {
                        QString magic_name = query.value("Magic.name").toString();
                        int magic_self_strength = query.value("Magic.self_strength").toInt();
                        int magic_strength = query.value("Magic.strength").toInt();
                        qDebug() << count << ". " << magic_name << " with strength " << magic_strength <<" and self_strength " << magic_self_strength << Qt::endl;
                        count++;
                    }

                    bool isValidSelection = false;
                    QTextStream input(stdin);
                    QString userInput;

                    while (!isValidSelection) {
                        qDebug() << "Enter the number of the magic you want to use: ";
                        userInput = input.readLine();
                        chosenMagic = userInput.toInt();

                        if (chosenMagic > 0 && chosenMagic < count) {
                            isValidSelection = true;
                        }
                        else {
                            qDebug() << "Invalid selection. Please choose a valid number." << Qt::endl;
                        }
                    }

                    query.seek(chosenMagic - 1);
                    selectedMagic = query.value(0).toString();
                    qDebug() << "You have selected: " << selectedMagic << Qt::endl;

                }
                else {
                    qDebug() << "Error: Failed ." << query.lastError().text()<< Qt::endl;
                }


                QSqlQuery query;
                query.prepare("SELECT name, strength, self_strngth FROM Magic WHERE name = :magic_name");
                query.bindValue(":magic_name", selectedMagic);


            int magic_strength = magic->get_strength();
            int magic_Self_strength = magic->get_Self_strength();


            enemy_hp -= _strength + magic_strength ;

            _hp -= enemy_strength+magic_Self_strength;

            qDebug() << "The hero attacked the enemy with power: " << _strength + magic_strength << Qt::endl;
            qDebug() << "Enemy's health after the attack: " << enemy_hp << Qt::endl;
            qDebug() << _name<<"'s health after the attack: " << _hp << Qt::endl;

        }
        else if (option == "2") {
            // Attack without magic

            enemy_hp -= _strength;

            _hp -= enemy_strength;

            qDebug() << "The hero attacked the enemy with power: " << _strength << Qt::endl;
            qDebug() << "Enemy's health after the attack: " << enemy_hp << Qt::endl;
            qDebug() << _name<<"'s health after the attack: " << _hp << Qt::endl;

        }
        else {
            qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
        }
    }
  while (option != "1" && option != "2");



            if (_hp <=0){
                qDebug() << "The hero" << this->get_name() << " has been defeated by the enemy " << enemy_name << "!" << Qt::endl;
                qDebug() << "Game Over and good luck next time ! " << Qt::endl;
                QSqlQuery query;
                        query.prepare("DELETE FROM hero WHERE name = :name");
                        query.bindValue(":name", _name);

                        query.exec();
                        if (query.exec()) {
                            qDebug() << "Hero" << _name <<" has been removed successfully." <<Qt::endl;
                        }
                        else {
                            qDebug() << "Error: Failed removing hero from the database." << query.lastError().text()<< Qt::endl;
                        }
                exit(0);
            }

            if (enemy_hp <= 0) {
                qDebug() << "The enemy has been defeated by the hero " << this->get_name() << " !" << Qt::endl;
                _xp +=enemy_xp;

                if (_hp < 10) {
                    _hp = 10;
                }

                if (_xp >= _level * 1000){
                  levelUp();

                }
                if(i==enemy_count){
                    Defeated_Cave_Actions();
                    return true;
                }
                else {

                    if (DefeatedEnemyInCave_Actions()){
                        return true;
                    }
                }

            }
            else {
                  qDebug() << "The hero couldn't defeat the enemy in one attack. The battle continues..." << Qt::endl;

                  ContinueBattle();
            }
        }
    }
    return true;
}

bool Hero::DefeatedEnemyInCave_Actions(){
    bool validChoice = false;
    while (!validChoice) {
        QString option;
        do {
            qDebug() << "Select an option:";
            qDebug() << "1. Exit without saving";
            qDebug() << "2. Continue and fight the other enemies ";
            QTextStream qtin(stdin);
            option = qtin.readLine();

            if (option == "1") {
                    //Exit without saving

                exit(0);

                validChoice = true;
                return true;
            }
            else if (option == "2") {
                // Continue and fight the other enemies.

                validChoice = true;
                return false;
            }
            else {
                qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
            }
        }
      while (option != "1" && option != "2");
    }
    return true;
}

bool Hero::Defeated_Cave_Actions(){

        QString option;

        do {
            qDebug() << "Select an option:";
            qDebug() << "1. Exit without saving";
            qDebug() << "2. Save and exit ";
            qDebug() << "3. Continue playing  ";

            QTextStream qtin(stdin);
            option = qtin.readLine();

            if (option == "1") {
                    //Exit without saving

                exit(0);

                return true;
            }
            else if (option == "2") {
                // Save and Exit.
                    SaveAndExit();
                    exit(0);
                return true;
            }
            else {
                qDebug() << "Invalid option. Please choose a valid option." << Qt::endl;
            }
        }
      while (option != "1" && option != "2" && option != "3");

  return true;

}

bool Hero::Buy_Magic(Magic* magic) {
    QSqlQuery query;

    int magic_id = magic->get_id();
    QString magic_name = magic->get_name();

        int magic_strength = magic->get_strength();

        int magic_Self_strength = magic->get_Self_strength();
        int magic_cost = magic->get_magic_cost();
        QString magic_element = magic->get_element();
        int magic_gold_cost = magic->get_gold_cost();
        QString magic_requirement = magic->get_requirement();

        query.prepare("SELECT Gold FROM hero WHERE name = :name");

        query.bindValue(":name", _name);
        if (query.exec() && query.next()) {
            if (_gold >= magic_gold_cost) {

                qDebug() << "You have bought the magic " << magic_name << " which has" << magic_strength << " strength " << magic_Self_strength << " self_strength " << magic_cost << " magic_cost " << magic_gold_cost << " gold_cost " << magic_requirement << " requirement " <<  Qt::endl;

                // Update hero's gold:
                query.prepare("UPDATE hero SET Gold = :gold WHERE name = :name");
                query.bindValue(":name", _name);
                query.bindValue(":gold", _gold - magic_gold_cost);
                query.exec();

                // Update hero's magic info:
                query.prepare("INSERT INTO Magic_Shop (hero_id, magic_id, purchased) VALUES (:hero_id, :magic_id, 1)");
                       query.bindValue(":hero_id", _id);
                       query.bindValue(":magic_id", magic_id);
                       // query.exec();
                       if (!query.exec()) {
                                  qDebug() << "Error executing query: " << query.lastError().text() << Qt::endl;
                       }
            }
            else {
                qDebug() << "You don't have enough gold to buy this magic." << Qt::endl;
            }

        }
        else {
            qDebug() << "Error retrieving hero data from the database." << Qt::endl;

        }



        return true;

}
