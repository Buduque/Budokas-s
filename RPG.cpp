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
    cout << string(length,symbol) << endl;
    cout << string(space, '\n');
}

void line_write(const int space, const int length, std::string text, const char symbol)
{
    cout << string(space, '\n');
    cout << string(length/2,symbol);
    cout << text;
    cout << string(length/2,symbol) << endl;
    cout << string(space, '\n');
}

void pattern_breaker(const int space, const int length, const char symbol1, const char symbol2)
{
    cout << string(space, '\n');
    for (int i = 0; i < length/2; i++){
        cout << symbol1;
        cout << symbol2;
    }
    cout << endl << string(space, '\n');
}

void pattern_write(const int space, const int length, std::string text, const char symbol1, const char symbol2)
{
    cout << string(space, '\n');
    for (int i = 0; i < length/4; i++){
        cout << symbol1;
        cout << symbol2;
    }
    cout << text;
    for (int i = 0; i < length/4; i++){
        cout << symbol1;
        cout << symbol2;
    }
    cout << endl << string(space, '\n');
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
            sleep(1);


            if(effects[i]->DURATION <= 0){
                delete effects[i];
                effects.erase(effects.begin() + i);

            }
        }
    }

    virtual ~Entity() = default;
};

//Material Data Base



// Player Data

class Player : public Entity
{
public:

    //OTHER
    XP_Sys LEVEL{};
    Complex_Attribute ENERGY{};

    enum ACT{MAIN_ATTACK=1,SECONDARY_ATTACK=2,PROTECT=3,REST=4,ANALISE=5,USE_ITEM=6,RUN=7,SKIP=8,INTERRUPT=9,OTHER=10};
    ACT ACTION = SKIP;

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
        ENERGY.base = 40;
        ENERGY.bonus = 0;
        ENERGY.max = ENERGY.base + ENERGY.bonus;
        ENERGY.current = ENERGY.max;

    }

    ~Player() override = default;
};


//Monster Data Base

class Monster : public Entity
{
public:

    int LEVEL;
    Enemy_Rewards REWARDS;

    //Action 0 represents the first turn of the battle,
    //just in case the enemy uses the last action as a parameter to think about a new one
    int ACTION = 0;

    virtual int Combat_AI(Player& target){return 2;}
    virtual void Main_Atk(Player& target) {}
    virtual void Secondary_Atk(Player& target) {}
    virtual void Block(Player& target) {}
    virtual void Rest(Player& target) {}
    virtual void Special1(Player& target) {}
    virtual void Special2(Player& target) {}
};

//Effects Data Base

class Poison : public Effect
{
public:

    int DAMAGE;
    int INCREMENT;
    int MAX_DAMAGE;
    int DEBUFF;

    Poison(int duration, int damage, int increment, int debuff){
        NAME = "Poison";

        DURATION = duration;
        DAMAGE = damage;
        MAX_DAMAGE = DAMAGE*5;
        INCREMENT = increment;
        DEBUFF = debuff;
    }

    void Apply(Entity& target) override
    {
        target.REGEN.current -= DEBUFF;
        target.HP.current -= DAMAGE;
        cout << target.NAME << " levou " << DAMAGE << " De dano por envenenamento... ";
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

    Burn(int duration, int damage){
        NAME = "Burn";

        DURATION = duration;
        DAMAGE = damage;
    }

    void Apply(Entity& target) override
    {
        int damage = clamp(DAMAGE - target.DEFENSE.current,1,DAMAGE);
        target.HP.current -= damage;
        cout << target.NAME << " levou " << damage << " De dano por queimadura... ";
        if (target.DEFENSE.current > 0)
        {
            target.DEFENSE.current = max(target.DEFENSE.current - damage,0);

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

    int DEBUFF;

    Freeze(int duration, int debuff){
        NAME = "Freeze";

        DURATION = duration;
        DEBUFF = debuff;
    }

    void Apply(Entity& target) override
    {
        target.SPEED.current -= DEBUFF;
        cout << target.NAME << " está congelando... ";
        cout << endl;

        DURATION--;
    }

    ~Freeze() override = default;
};

class Acid : public Effect
{
public:

    int DAMAGE;
    int DEBUFF;

    Acid(int duration, int damage, int debuff){
        NAME = "Poison";

        DURATION = duration;
        DAMAGE = damage;
        DEBUFF = debuff;
    }

    void Apply(Entity& target) override
    {
        target.HP.current -= DAMAGE;
        cout << target.NAME << " levou " << DAMAGE << " de dano por ácido... ";
        if (target.HP.max > 1) {
            target.HP.max = max(target.HP.max-DEBUFF,1);
            cout << "Sua pele derrete!";
        }

        cout << endl;

        DURATION--;
    }

    ~Acid() override = default;
};

class Muddy : public Effect
{
public:

    int DEBUFF1;
    int DEBUFF2;

    Muddy(int duration, int debuff1, int debuff2){
        NAME = "Muddy";

        DURATION = duration;
        DEBUFF1 = debuff1;
        DEBUFF2 = debuff2;
    }

    void Apply(Entity& target) override
    {
        cout << target.NAME << " está coberto de lama... ";
        cout << endl;
        if (target.DEFENSE.current > 0){
        	target.DEFENSE.current = max(target.DEFENSE.current - DEBUFF1,0);
        	cout << "A lama enfraquece suas defesas! ";
        }
        if (target.SPEED.current > 0){
        	target.SPEED.current = max(target.SPEED.current - DEBUFF2,0);
        	cout << "A lama dificulta sua movimentação! ";
        }

        DURATION--;
    }

    ~Muddy() override = default;
};

//Monsters Data Base

class Goblin : public Monster
{
public:

    int Combat_AI(Player& target) override {

        int action = 2;

        return action;
    }
    void Main_Atk(Player& target) override {

    }
    void Secondary_Atk(Player& target) override {

    }
    void Block(Player& target) override {

    }
    void Rest(Player& target) override {

    }
    void Special1(Player& target) override {

    }
    void Special2(Player& target) override {

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
    }

    ~Goblin() override = default;
};

class Slime : public Monster
{
public:

    int Combat_AI(Player& target) override {

        int action = 2;

        return action;
    }
    void Main_Atk(Player& target) override {

    }
    void Secondary_Atk(Player& target) override {

    }
    void Block(Player& target) override {

    }
    void Rest(Player& target) override {

    }
    void Special1(Player& target) override {

    }
    void Special2(Player& target) override {

    }

    //Setting Up
    Slime()
    {
        //HP
        HP.base = 30; HP.bonus = 0; HP.max = HP.base + HP.bonus; HP.current = HP.max;
        REGEN.base = 2; REGEN.current = REGEN.base;

        //DEFENSE
        DEFENSE.base = 6; DEFENSE.current = DEFENSE.base;
        DMG_REDUCTION.base = 2; DMG_REDUCTION.current = DMG_REDUCTION.base;
        PHS_DEF.base = 0; PHS_DEF.current = PHS_DEF.base;
        MGC_DEF.base = 0; MGC_DEF.current = MGC_DEF.base;

        //ATTACK
        ATTACK.base = 4; ATTACK.current = ATTACK.base;
        MAGIC.base = 2; MAGIC.current = MAGIC.base;
        PENETRATION.base = 0; PENETRATION.current = PENETRATION.base;

        //SPEED
        SPEED.base = 5; SPEED.current = SPEED.base;
        ACCURACY.base = 8; ACCURACY.current = ACCURACY.base;
        EVASIVENESS.base = 5; EVASIVENESS.current = EVASIVENESS.base;

        //OTHER
        NAME = "Slime";
        LEVEL = 1;
        REWARDS.gold = 8; REWARDS.xp_reward = 26;
    }

    ~Slime() override = default;
};

class Mutant_Pig : public Monster
{
    public:

    int Combat_AI(Player& target) override {

        if (ACTION == 0) {
            ACTION = 5;
        }
        else {
            if (static_cast<float>(HP.current)/HP.max >= 0.6) {
                ACTION = choose(1,3);
            }
            else {
                ACTION = choose(1,4);
            }
        }
        return ACTION;
    }
    void Main_Atk(Player& target) override {
        int damage = max(ATTACK.current-target.DEFENSE.current,1);
        target.HP.current -= damage;

        cout << NAME << " avançou contra você e lhe mordeu, causando " << damage << " de dano!";
    }
    void Secondary_Atk(Player& target) override {
        int damage = max((ATTACK.current/2)-target.DEFENSE.current,1);
        target.HP.current -= damage;
        target.effects.push_back(new Acid(2,1,1));

        cout << NAME << " cuspiu ácido em você, causando " << damage << " de dano e aplicando ÁCIDO!";
    }
    void Block(Player& target) override {
        DEFENSE.current++;

        cout << NAME << " se protegeu... Sua defesa aumentou em 1";
    }
    void Rest(Player& target) override {
        HP.current += REGEN.current*2;

        cout << NAME << " descançou um pouco, recuperando " << REGEN.current*2 << " de vida...";
    }
    void Special1(Player& target) override {
        target.effects.push_back(new Muddy(3,1,1));

        cout << NAME << " jogou lama na sua cara!";
    }
    void Special2(Player& target) override {

    }

    //Setting Up
    Mutant_Pig()
    {
        //HP
        HP.base = 28;
        HP.bonus = 0;
        HP.max = HP.base + HP.bonus;
        HP.current = HP.max;
        REGEN.base = 0;
        REGEN.current = REGEN.base;

        //DEFENSE
        DEFENSE.base = 4;
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
        MAGIC.base = 1;
        MAGIC.current = MAGIC.base;
        PENETRATION.base = 0;
        PENETRATION.current = PENETRATION.base;

        //SPEED
        SPEED.base = 3;
        SPEED.current = SPEED.base;
        ACCURACY.base = 6;
        ACCURACY.current = ACCURACY.base;
        EVASIVENESS.base = 2;
        EVASIVENESS.current = EVASIVENESS.base;

        //OTHER
        NAME = "Mutant pig";
        LEVEL = 1;
        REWARDS.gold = 9;
        REWARDS.xp_reward = 29;
    }

    ~Mutant_Pig() override = default;
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

//Loot Tables

//Spawn Tables

Spawn_Table Forest =
{
    "Forest",
    {
        []() { return make_unique<Goblin>(); },
        []() { return make_unique<Slime>(); },
        []() { return make_unique<Mutant_Pig>(); }
    }
};

Spawn_Table Desert =
{
    "Desert",
    {
        []() { return make_unique<Goblin>(); }
    }
};

// Weapon Data Base

class Weapon {

};

//Entity's Func

void entity_view(Monster& target)
{
    cout << "-----  " << target.NAME << " LV " << target.LEVEL << "  -----\n" << endl << endl;
    cout << "HP: " << target.HP.current << "/" << target.HP.max << endl;

    line_breaker(1,20,'-');

    for (int i = 0; i < target.effects.size(); i++) {
        cout << target.effects[i]->NAME << "  -  " << target.effects[i]->DURATION << " Turnos" << endl;

    if (target.effects.size() > 0)
    {
    	line_breaker(1,20,'-');
    }
    }
}

void entity_check(Monster& target)
{
    cout << "-=-=-=- "<<target.NAME<<" -=-=-=-\n";
    cout << "LEVEL: " << target.LEVEL << endl;
    cout << "HP: " << target.HP.current << "/" << target.HP.max << endl;
    cout << "ATTACK: " << target.ATTACK.current << "\t" << "MAGIC: " << target.MAGIC.current << endl;
    cout << "DEFENSE: " << target.DEFENSE.current << "\t" << "SPEED: " << target.SPEED.current;

    for (int i = 0; i < target.effects.size(); i++) {
        cout << target.effects[i]->NAME << "\t" << target.effects[i]->DURATION << endl;
    }
}

void player_check(Player& player)
{
    cout << "-----  " << player.NAME << " LV " << player.LEVEL.level << "  -----\n" << endl << endl;
    cout << "HP: " << player.HP.current << "/" << player.HP.max << "\t";

    cout << "ENERGY: " << player.ENERGY.current << "/" << player.ENERGY.max << endl;
    cout << "ATTACK: " << player.ATTACK.current << "\t" << "MAGIC: " << player.MAGIC.current << endl;
    cout << "DEFENSE: " << player.DEFENSE.current << "\t" << "SPEED: " << player.SPEED.current << endl;

    line_breaker(1,20,'-');

    for (int i = 0; i < player.effects.size(); i++) {
        cout << player.effects[i]->NAME << "  -  " << player.effects[i]->DURATION << " Turnos" << endl;

    if (player.effects.size() > 0)
    {
    	line_breaker(1,20,'-');
    }
    }
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
        enemy.ACTION = enemy.Combat_AI(player);

    }

    int choice;

    while (enemy.HP.current > 0) {
        do {

            // Player's turn, this code will keep repeating until the player ran out of actions/moves to do.

            player_check(player);
            cout << endl;
        	entity_view(enemy);
            cout << endl;

            cout << "O que você irá fazer?" << endl;
            cout << "1 - Usar arma principal..." << endl;
            cout << "2 - Usar arma secundária..." << endl;
            cout << "3 - Defender..." << endl;
            cout << "4 - Descançar..." << endl;
            cout << "5 - Analisar..." << endl;
            cout << "6 - Usar item..." << endl;
            cout << "7 - Correr..." << endl;
            cout << endl;

            cin >> choice;
            if (choice < 1 || choice > 7)
            {
                choice = 0;
            }

            player.ACTION = static_cast<Player::ACT>(choice);
            enemy.ACTION = enemy.Combat_AI(player);

            //"Action validation", if the enemy interrupt you, your action won't move further than this!
            //The enemy will reset your action to "interrupt" (9), IF he does cancel your action

            switch (player.ACTION) {
                case Player::MAIN_ATTACK:
                    cout << enemy.NAME << " Atacou" << endl;
                    turn = ENEMY_TURN;
                    break;

                case Player::SECONDARY_ATTACK:
                    enemy.effects.push_back(new Poison(3,3,1,1));
                    cout << player.NAME << " Aplicou teste de veneno" << endl;
                    turn = ENEMY_TURN;
                    break;

                case Player::PROTECT:
                    cout << player.NAME << " Defendeu" << endl;
                    turn = ENEMY_TURN;
                    break;

                case Player::REST:
                    cout << player.NAME << " Descançou" << endl;
                    turn = ENEMY_TURN;
                    break;

                case Player::ANALISE:
                    cout << player.NAME << " Analisou" << endl;
                    break;

                case Player::USE_ITEM:
                    cout << player.NAME << " Usou item" << endl;
                    turn = ENEMY_TURN;
                    break;

                case Player::RUN:
                    cout << player.NAME << " Tentou correr" << endl;
                    turn = ENEMY_TURN;
                    break;
                case Player::INTERRUPT:
                    cout << player.NAME << "Algo te interrompeu..." << endl;
                    turn = ENEMY_TURN;
                    break;
                default:
                    cout << "Erro, digite um número referente a uma ação válida..." << endl << endl;
            }
            sleep(3);
        } while (turn == PLAYER_TURN);

        switch (enemy.ACTION) {
            case 1:
                enemy.Main_Atk(player);
                break;
            case 2:
                enemy.Secondary_Atk(player);
                break;
            case 3:
                enemy.Block(player);
                break;
            case 4:
                enemy.Rest(player);
                break;
            case 5:
                enemy.Special1(player);
                break;
            case 6:
                enemy.Special2(player);
                break;
            default:
                cout << enemy.NAME << " não moveu um músculo..." << endl;
        }

        sleep(2);

        player.Apply_Effects();
        enemy.Apply_Effects();

        line_breaker(2,60,'=');

        sleep(5);
        turn = PLAYER_TURN;
    }
}

// Main Code

int main(){

    srand(time(nullptr));

    line_breaker(2,60,'=');

    cout << "Generating seed...";

    line_breaker(2,60,'=');

    usleep(1000000);

    enum GameState{EXPLORATION,COMBAT,DIALOG,SHOP,INVENTORY,LEVEL_UP,GAME_OVER};
    GameState state = COMBAT;

    Player player;
    unique_ptr<Monster> enemy = Spawn_Enemy(Forest);
    combat(player, *enemy);

    return 0;
}