//Includes

#include <iostream>
#include <random>
#include <ctime>
#include <unistd.h>
#include <memory>
#include <functional>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
//#include <bits/stdc++.h>

//Namespace

using namespace std;

//Global Functions

int random_range(int min, int max, int rolls, int bonus){
    int result = 0;
    int roll = 0;

    for (int i = 0; i <= rolls; i++){
        srand(time(nullptr));
        roll = ((rand()%(max-min+1))+min);
        cout<<roll<<"\t";
        result += roll;

        usleep(10000);
    }
    result += bonus;
    return result;
}

int choose(int start, int end) {
    srand(time(nullptr));
    int result = ((rand()%(end-start+1))+start);
    return result;
}

void clear_screen()
{
    cout << string(100, '\n');
    cout.flush();
}

void line_breaker(const int space, const int length, const char symbol)
{
    cout << string(space, '\n');
    cout << "\t" << string(length,symbol);
    cout << string(space, '\n');
}

void line_write(const int space, const int length, std::string text, const char symbol)
{
    cout << string(space, '\n');
    cout << string(length/2,symbol);
    cout << text;
    cout << string(length/2,symbol);
    cout << string(space, '\n');
}

void pattern_breaker(const int space, const int length, const char symbol1, const char symbol2)
{
    cout << string(space, '\n');
    for (int i = 0; i < length/2; i++){
        cout << "\t" << symbol1;
        cout << "\t" << symbol2;
    }
    cout << string(space, '\n');
}

void pattern_write(const int space, const int length, std::string text, const char symbol1, const char symbol2)
{
    cout << string(space, '\n');
    for (int i = 0; i < length/4; i++){
        cout << string(15,symbol1);
        cout << string(15,symbol2);
    }
    cout << text;
    for (int i = 0; i < length/4; i++){
        cout << string(15,symbol1);
        cout << string(15,symbol2);
    }
    cout << string(space, '\n');
}

//Structs

struct Basic_Attribute
{
    int base;
    int current;
};

struct Complex_Attribute
{
	int base;
	int bonus;
	int max;
	int current;
};

struct XP_Sys
{
    int level;
    int xp;
    int nl_xp;
};

struct Enemy_Rewards
{
    int gold;
    int xp_reward;
};

//Foward Declaration

class Entity;
class Player;
class Monster;
class Weapon;
class Material;
class Effect {
public:

    string NAME;
    int DURATION;

    virtual void Apply(Entity& target){}

    virtual ~Effect() = default;
};

//Entity Base

class Entity {
public:

    //HP
    Complex_Attribute HP;
    Basic_Attribute REGEN;

    //DEFENSE
    Basic_Attribute DEFENSE;
    Basic_Attribute DMG_REDUCTION;
    Basic_Attribute PHS_DEF;
    Basic_Attribute MGC_DEF;

    //ATTACK
    Basic_Attribute ATTACK;
    Basic_Attribute MAGIC;
    Basic_Attribute PENETRATION;

    //SPEED
    Basic_Attribute SPEED;
    Basic_Attribute ACCURACY;
    Basic_Attribute EVASIVENESS;

    //OTHERS
    string NAME;
    vector<Effect*> effects;

    void Apply_Effects(){
        if (effects.empty()){
            return;
        }
        for (int i = effects.size() -1; i>=0; i--){

            effects[i]->Apply(*this);

            if(effects[i]->DURATION <= 0){
                delete effects[i];
                effects.erase(effects.begin() + i);

            }
        }
    }

    virtual ~Entity() = default;
};

// Monster Data Base

class Monster : public Entity
{
public:

    int LEVEL;
    Enemy_Rewards REWARDS;

    int ACTION;

    virtual void Combat_AI(){}
    virtual void Main_Atk() {}
    virtual void Secondary_Atk() {}
    virtual void Block() {}
    virtual void Rest() {}
    virtual void Especial1() {}
    virtual void Especial2() {}
};

class Goblin : public Monster
{
public:

    void Combat_AI() override {

    }
    void Main_Atk() override {

    }
    void Secondary_Atk() override {

    }
    void Block() override {

    }
    void Rest() override {

    }
    void Especial1() override {

    }
    void Especial2() override {

    }

    //Setting Up
    Goblin()
    {
        //HP
        HP.base = 20;
        HP.bonus = 0;
        HP.max = HP.base + HP.bonus;
        HP.current = HP.max;
        REGEN.base = 0;
        REGEN.current = REGEN.base;

        //DEFENSE
        DEFENSE.base = 5;
        DEFENSE.current = DEFENSE.base;
        DMG_REDUCTION.base = 0;
        DMG_REDUCTION.current = DMG_REDUCTION.base;
        PHS_DEF.base = 0;
        PHS_DEF.current = PHS_DEF.base;
        MGC_DEF.base = 0;
        MGC_DEF.current = MGC_DEF.base;

        //ATTACK
        ATTACK.base = 5;
        ATTACK.current = ATTACK.base;
        MAGIC.base = 5;
        MAGIC.current = MAGIC.base;
        PENETRATION.base = 0;
        PENETRATION.current = PENETRATION.base;

        //SPEED
        SPEED.base = 10;
        SPEED.current = SPEED.base;
        ACCURACY.base = 10;
        ACCURACY.current = ACCURACY.base;
        EVASIVENESS.base = 10;
        EVASIVENESS.current = EVASIVENESS.base;

        //OTHER
        NAME = "Goblin";
        LEVEL = 1;
        REWARDS.gold = 14;
        REWARDS.xp_reward = 21;
        ACTION = 1;
    }

    ~Goblin() override = default;
};

class Slime : public Monster
{
public:

    void Combat_AI() override {

    }
    void Main_Atk() override {

    }
    void Secondary_Atk() override {

    }
    void Block() override {

    }
    void Rest() override {

    }
    void Especial1() override {

    }
    void Especial2() override {

    }

    //Setting Up
    Slime()
    {
        //HP
        HP.base = 30;
        HP.bonus = 0;
        HP.max = HP.base + HP.bonus;
        HP.current = HP.max;
        REGEN.base = 2;
        REGEN.current = REGEN.base;

        //DEFENSE
        DEFENSE.base = 6;
        DEFENSE.current = DEFENSE.base;
        DMG_REDUCTION.base = 2;
        DMG_REDUCTION.current = DMG_REDUCTION.base;
        PHS_DEF.base = 0;
        PHS_DEF.current = PHS_DEF.base;
        MGC_DEF.base = 0;
        MGC_DEF.current = MGC_DEF.base;

        //ATTACK
        ATTACK.base = 4;
        ATTACK.current = ATTACK.base;
        MAGIC.base = 2;
        MAGIC.current = MAGIC.base;
        PENETRATION.base = 0;
        PENETRATION.current = PENETRATION.base;

        //SPEED
        SPEED.base = 5;
        SPEED.current = SPEED.base;
        ACCURACY.base = 8;
        ACCURACY.current = ACCURACY.base;
        EVASIVENESS.base = 5;
        EVASIVENESS.current = EVASIVENESS.base;

        //OTHER
        NAME = "Slime";
        LEVEL = 1;
        REWARDS.gold = 8;
        REWARDS.xp_reward = 26;
        ACTION = 1;
    }

    ~Slime() override = default;
};

using MonsterFactory = function<unique_ptr<Monster>()>;

struct Spawn_Table
{
    string NAME;
    vector<MonsterFactory> ENEMIES;
};
unique_ptr<Monster> Spawn_Enemy(const Spawn_Table& spawn_table)
{
    int index = choose(0,(int)spawn_table.ENEMIES.size() - 1);

    return spawn_table.ENEMIES[index]();
}

Spawn_Table Forest =
{
    "Forest",
    {
        []() { return make_unique<Goblin>(); },
        []() { return make_unique<Slime>(); }
    }
};

Spawn_Table Desert =
{
    "Desert",
    {
        []() { return make_unique<Goblin>(); }
    }
};

//Effects Data Base

class Poison : public Effect
{
public:

    int DAMAGE;
    int INCREMENT;
    int MAX_DAMAGE;
    int DEBUFF;

    void poison(int duration, int damage, int increment, int debuff){
        NAME = "Poison";

        DURATION = duration;
        DAMAGE = damage;
        INCREMENT = increment;
        DEBUFF = debuff;
    }

    void Apply(Entity& target) override
    {
        target.REGEN.current -= DEBUFF;
        target.HP.current -= DAMAGE;
        cout << target.NAME << "levou " << DAMAGE << "De dano por envenenamento...\t";
        if (DAMAGE < MAX_DAMAGE)
        {
            DAMAGE = clamp(DAMAGE + INCREMENT,1,MAX_DAMAGE);
            cout << "O veneno piorou!";
        }
        cout << endl;

        DURATION--;
    }

    ~Poison() override = default;
};

class Burn : public Effect
{
public:

    int DAMAGE;
    int INCREMENT;
    int DEBUFF;

    void burn(int duration, int damage, int increment){
        NAME = "Burn";

        DURATION = duration;
        DAMAGE = damage;
    }

    void Apply(Entity& target) override
    {
        int damage = clamp(DAMAGE - target.DEFENSE.current,1,DAMAGE);
        target.HP.current -= damage;
        cout << target.NAME << "levou " << damage << "De dano por queimadura...\t";
        if (target.DEFENSE.current < 0)
        {
            target.DEFENSE.current = clamp(target.DEFENSE.current - damage,0,target.DEFENSE.current);
            cout << "Suas defesas queimaram!";
        }
        cout << endl;

        DURATION--;
    }

    ~Burn() override = default;
};

class Freeze : public Effect
{
public:

    int DAMAGE;
    int INCREMENT;
    int DEBUFF;

    void freeze(int duration, int debuff, int increment){
        NAME = "Burn";

        DURATION = duration;
    }

    void Apply(Entity& target) override
    {
        int damage = clamp(DAMAGE - target.DEFENSE.current,1,DAMAGE);
        target.HP.current -= damage;
        cout << target.NAME << "levou " << damage << "De dano por queimadura...\t";
        if (target.DEFENSE.current < 0)
        {
            target.DEFENSE.current = clamp(target.DEFENSE.current - damage,0,target.DEFENSE.current);
            cout << "Suas defesas queimaram!";
        }
        cout << endl;

        DURATION--;
    }

    ~Freeze() override = default;
};

//Material Data Base

// Weapon Data Base

class Weapon {

};

// Player Data

class Player : public Entity
{
public:

    //OTHER
    string NAME = "Paulinho Gameplay";
    XP_Sys LEVEL{};
	Complex_Attribute ENERGY{};

    int ACTION;

    //Setting Up
    Player()
    {
        //HP
        HP.base = 20;
        HP.bonus = 0;
        HP.max = HP.base + HP.bonus;
        HP.current = HP.max;
        REGEN.base = 0;
        REGEN.current = REGEN.base;

        //DEFENSE
        DEFENSE.base = 5;
        DEFENSE.current = DEFENSE.base;
        DMG_REDUCTION.base = 0;
        DMG_REDUCTION.current = DMG_REDUCTION.base;
        PHS_DEF.base = 0;
        PHS_DEF.current = PHS_DEF.base;
        MGC_DEF.base = 0;
        MGC_DEF.current = MGC_DEF.base;

        //ATTACK
        ATTACK.base = 5;
        ATTACK.current = ATTACK.base;
        MAGIC.base = 5;
        MAGIC.current = MAGIC.base;
        PENETRATION.base = 0;
        PENETRATION.current = PENETRATION.base;

        //SPEED
        SPEED.base = 10;
        SPEED.current = SPEED.base;
        ACCURACY.base = 10;
        ACCURACY.current = ACCURACY.base;
        EVASIVENESS.base = 10;
        EVASIVENESS.current = EVASIVENESS.base;

        //OTHER
        NAME = "Paulinho Gameplay";
        LEVEL.level = 1;
        LEVEL.xp = 0;
        LEVEL.nl_xp = 30;
        ACTION = 0;
        ENERGY.base = 40;
        ENERGY.bonus = 0;
        ENERGY.max = ENERGY.base + ENERGY.bonus;
        ENERGY.current = ENERGY.max;

    }

    ~Player() override = default;
};

void entity_view(Monster& target)
{
    cout << "-=-=-=- "<<target.NAME<<" -=-=-=-\n";
    cout << "LEVEL: " << target.LEVEL << endl << endl;
    cout << "HP: " << target.HP.current << "/" << target.HP.max << endl;
    cout << "ATTACK: " << target.ATTACK.current << "\t" << "MAGIC: " << target.MAGIC.current << endl;
    cout << "DEFENSE: " << target.DEFENSE.current << "\t" << "SPEED: " << target.SPEED.current;
    for (int i = 0; i < target.effects.size(); i++) {
        cout << target.effects[i]->NAME << "\t" << target.effects[i]->DURATION << endl;
    }
}

void entity_check(Monster& target)
{
    cout << "-=-=-=- "<<target.NAME<<" -=-=-=-\n";
    cout << "LEVEL: " << target.LEVEL << endl;
    cout << "HP: " << target.HP.current << "/" << target.HP.max << endl;
    cout << "ATTACK: " << target.ATTACK.current << "\t" << "MAGIC: " << target.MAGIC.current << endl;
    cout << "DEFENSE: " << target.DEFENSE.current << "\t" << "SPEED: " << target.SPEED.current;
}

void player_check(Player& player)
{
    cout << "-=-=-=- "<<player.NAME<<" -=-=-=-\n";
    cout << "LEVEL: " << player.LEVEL.level << endl;
    cout << "HP: " << player.HP.current << "/" << player.HP.base << endl;
    cout << "ATTACK: " << player.ATTACK.current << "\t" << "MAGIC: " << player.MAGIC.current << endl;
    cout << "DEFENSE: " << player.DEFENSE.current << "\t" << "SPEED: " << player.SPEED.current << endl;
}

// Game States

void combat(Player& player, Monster& enemy)
{
    enum Turn{PLAYER_TURN,ENEMY_TURN};
    Turn turn;

    if (player.SPEED.current >= enemy.SPEED.current) {
        turn = PLAYER_TURN;
    } else
    {
     	turn = ENEMY_TURN;
    }

    while (enemy.HP.current > 0) {
        do {

        	line_breaker(2,40,'=');

            player_check(player);
            cout << endl;
        	entity_view(enemy);

        	sleep(2);
        } while (turn == PLAYER_TURN);


    }
}

// Main Code

int main(){

    srand(time(nullptr));

    line_breaker(2,40,'=');

    cout << "Generating seed...";

    usleep(1000000);

    enum GameState{EXPLORATION,COMBAT,DIALOG,SHOP,INVENTORY,LEVEL_UP,GAME_OVER};

    GameState state = COMBAT;

    Player player;
    unique_ptr<Monster> enemy = Spawn_Enemy(Forest);

    combat(player, *enemy);

    return 0;
}