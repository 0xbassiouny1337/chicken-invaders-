
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>


using namespace std;
using namespace sf;
int countercounter = -1;
int levelcount = 0;

const int NUM_BULLETS = 3000;

int volcount = 4;
int score = 0;
int health = 4;
int werkcounter = 0;
int fatencounter = 0;
int lockcounter = 0;
int ChHp = 6;
const int NUM_CHICKENS = 8;
int chickenHitCount[NUM_CHICKENS] = { 0 };

// move eggs
int f_rand = rand() % 8;
int s_rand = rand() % 8; // 0 > 7 index of chickens
int t_rand = rand() % 8;
int forth_rand = rand() % 8;
int fifth_rand = rand() % 8;

Font font;
Font Efont;


Clock GameClock;

float DeltaTime = 0, chiken_animation_delay = 0, wrek_animation_delay = 0;

int Canimation_idx = 1;
int Wanimation_idx = 1;


static int c = 0, wrk = 0;

static Vector2f shipPos(900, 950);
static Vector2f shieldPos(860, 890);
static Vector2f bossPos(450, -200);
static Vector2f bossPos2(350, -200);



//structs
struct bossstruct
{
    int BossAppeartimer = 0;
    float randx = rand() % 5 - 2; // (3*2+1) -3 rand value between 3 and -3
    float randy = rand() % 5 - 2;
    int HpBoss = 30;
    int Banimation_idx = 1;
    int B = 0;
    float boss_animation_delay = 0;
    Sprite boss;

    int Boss2Appeartimer = 0;
    float randx2 = rand() % 5 - 2; // (3*2+1) -3 rand value between 3 and -3
    float randy2 = rand() % 5 - 2;
    int HpBoss2 = 30;
    int B2animation_idx = 1;
    int B2 = 0;
    float boss2_animation_delay = 0;
    Sprite boss2;


}BossStruct;

struct explosion
{
    bool BossExplo = false;
    bool explo = false;
    bool Boss2Explo = false;

    float explosion_animation_delay = 0;
    float Bossbomb_animation_delay = 0;
    float Bossbomb2_animation_delay = 0;

    int Bbanimation_idx = 1;
    int E = 0;
    int Eanimation_idx = 1;
    int explotimer = 0;
    int Bb = 0;
    int Bb2animation_idx = 1;
    int Bb2 = 0;

    Sprite bomb;
    Sprite chickenBomb;
    Sprite chickenBomb2;

}Explosion;

struct bulletss
{
    int ctrBull = 0;
    int chBull = 0;

    bool isShot[NUM_BULLETS] = { false };

    Sprite bullets[NUM_BULLETS];

}BULLets;

struct giftsandstar
{
    float gift_animation_delay = 0;
    float star_animation_delay = 0;

    int Ganimation_idx = 1;
    int Sanimation_idx = 1;
    int g = 0;
    int  S = 0;
    int gifttimer = 0;
    int startimer = 0;

    Sprite star;
    Sprite gift;

}StarGift;


struct rocks
{
    float redRock_animation_delay = 0;
    float greyRock_animation_delay = 0;

    int redrockTimer = 0;
    int greyRockTimer = 0;
    int Rranimation_idx = 1;
    int Granimation_idx = 1;
    int Rr = 0;
    int Gr = 0;

    Sprite greyrocks;
    Sprite redrocks;

}Rocks;

struct shipshieldstruct
{
    float ship_animation_delay = 0;
    int x = 0;
    int y = 0;

    float shieldTimer = 0;

    bool isShielded = true;
    // bool ShieldRespawn = true;

    Sprite ship;
    Sprite shield;

}ShipShieldStruct;


//functions
void incrementBullet(int& ctrBull)
{
    ctrBull++;
}

void changeBullet(int& chBull)
{
    chBull = rand() % 3;
}


void explosion(bool& explo, Sprite& ship, Sprite& bomb, int& explotimer, Sprite& shield, bool& isShielded, bool& BossExplo, Sprite& boss, Sprite& chickenBomb, int& BossAppeartimer, Sound& explosound)
{
    if (!isShielded)
    {               

        if (explo)
        {


            if (Explosion.explosion_animation_delay > 0.018)
            {
                Explosion.E += Explosion.Eanimation_idx;
                if ((Explosion.E >= 47 || Explosion.E <= 0)) Explosion.Eanimation_idx *= -1;
                Explosion.explosion_animation_delay = 0;
            }

            else
            {
                Explosion.explosion_animation_delay += DeltaTime;
            }

            ship.setScale(0, 0);
            explotimer++;
            // cout << explotimer << endl;
            bomb.setPosition(ship.getPosition().x, ship.getPosition().y);
            bomb.setScale(1, 1);
            bomb.setTextureRect(IntRect(Explosion.E * 256, 0, 256, 256));



            if (explotimer > 140)
            {
                explosound.play();

                //cout << "hi" << endl;
                ship.setScale(0.5, 0.5);
                ship.setPosition(shipPos);
                shield.setPosition(shieldPos);
                bomb.setScale(0, 0);
                explotimer = 0;
                explo = false;
                isShielded = true;
                Explosion.explosion_animation_delay = 0;
                Explosion.E = 0;
                Explosion.Eanimation_idx = 1;
            }


        }
    }
}
void Bossexplo(Sprite& boss) {

    BossStruct.BossAppeartimer++;


    if (BossStruct.HpBoss == 0)
    {
       // cout << "boss" << endl;

        boss.setScale(0, 0);
        boss.move(0, 0);

        if (Explosion.Bossbomb_animation_delay > 0.2)
        {
            Explosion.Bb += Explosion.Bbanimation_idx;
            if ((Explosion.Bb >= 9 || Explosion.Bb <= 0)) Explosion.Bbanimation_idx *= -1;
            {
                Explosion.Bossbomb_animation_delay = 0;
            }
            if (Explosion.Bb >= 9)
            {
                Explosion.Bbanimation_idx = 1;
            }
        }

        else
        {
            Explosion.Bossbomb_animation_delay += DeltaTime;
        }

        Explosion.chickenBomb.setTextureRect(IntRect(766 * Explosion.Bb, 0, 766, 811));


        if (BossStruct.BossAppeartimer <= 50)
        {
            Explosion.chickenBomb.setPosition(boss.getPosition().x, boss.getPosition().y);
            Explosion.chickenBomb.setScale(0.3, 0.3);
            Explosion.BossExplo = true;

        }

        else if (BossStruct.BossAppeartimer > 60)
        {
            Explosion.chickenBomb.setScale(0, 0);
            BossStruct.BossAppeartimer = 0;
            Explosion.BossExplo = false;
        }

    }

}






void updateEgg(RenderWindow& window, Sprite& egg1, Sprite& egg2, Sprite& egg3, Sprite& egg4, Sprite& egg5, Sprite& ship, Sprite& bomb, Sprite& c_egg, Sprite& c_egg2, Sprite& c_egg3, Sprite& c_egg4, Sprite& c_egg5, Sprite chickenSprites[], Sprite chickenSprites2[], Sprite chickenSprites3[], Sprite chickenSprites4[], Sprite chickenSprites5[], bool  collisionchicken[], bool  collisionchicken2[], bool  collisionchicken3[], bool  collisionchicken4[], bool  collisionchicken5[], const int NUM_CHICKENS, int& explotimer, bool& explo, Sprite& shield, bool& isShielded, bool& BossExplo, Sprite& boss, Sprite& chickenBomb, int& BossAppeartimer, int& f_rand, int& s_rand, int& t_rand, int& forth_rand, int& fifth_rand, float& eggclock, float& eggclock2, float& eggclock3, float& eggclock4) {



    bool bomb_egg = egg1.getGlobalBounds().intersects(ship.getGlobalBounds());



    egg1.move(0, 180 * DeltaTime);

    if (eggclock > 3.93318 && eggclock < 3.99999 && !collisionchicken[f_rand])
    {
        egg1.setPosition(chickenSprites[f_rand].getPosition().x + 32, chickenSprites[f_rand].getPosition().y + 37);

    }

    if (eggclock >= 4.0199999 && !collisionchicken[f_rand]) {

        if (egg1.getPosition().y > 1010) {
            c_egg.setPosition(egg1.getPosition().x - 20, 1010);
            egg1.setPosition(chickenSprites[f_rand].getPosition().x + 32, chickenSprites[f_rand].getPosition().y + 37);
            //egg1.move(0, 120*DeltaTime);

                //egg1.setPosition(-1000, -600);
                //Egg.play();
            eggclock = 0;
        }

        if (bomb_egg) {

            // bomb.setPosition(ship.getPosition().x, ship.getPosition().y);
           // egg1.setPosition(-1000, -600);
            egg1.setPosition(chickenSprites[f_rand].getPosition().x + 32, chickenSprites[f_rand].getPosition().y + 37);

            health--;
            //ship.setScale(0, 0);
            //exp.play();
            explo = true;
            eggclock = 0;

        }


    }




    // egg2



    bool     bomb_egg2 = egg2.getGlobalBounds().intersects(ship.getGlobalBounds()); // true
    egg2.move(0, 180 * DeltaTime);


    if (eggclock2 > 3.93318 && eggclock2 < 3.99999 && !collisionchicken2[s_rand]) {
        //     cout << s_rand<<endl;
        egg2.setPosition(chickenSprites2[s_rand].getPosition().x + 32, chickenSprites2[s_rand].getPosition().y + 37);


    }

    if (eggclock2 >= 4.0199999 && !collisionchicken2[s_rand]) {
        //

          //cout << s_rand << endl;


        if (egg2.getPosition().y > 1010) {
            //egg2.move(0, -3);
            c_egg2.setPosition(egg2.getPosition().x - 20, 1010);
            //egg2.setPosition(-500, -500);
            egg2.setPosition(chickenSprites2[s_rand].getPosition().x + 32, chickenSprites2[s_rand].getPosition().y + 37);
            //egg2.move(0, 120 * DeltaTime);

            // Egg.play();
            eggclock2 = 0;
            //  egg_timer2 = 0;
        }
        if (bomb_egg2) {

            //bomb.setPosition(ship.getPosition().x, ship.getPosition().y);
            //egg2.setScale(0, 0);
            //c_egg2.setScale(0, 0);
            //egg2.setPosition(-500, -500);
            egg2.setPosition(chickenSprites2[s_rand].getPosition().x + 32, chickenSprites2[s_rand].getPosition().y + 37);

            health--;
            //c_egg2.setPosition(500, 650);
            //ship.setScale(0, 0);
            // exp.play();
            explo = true;
            eggclock2 = 0;

        }



    }


    // egg3


    bool  bomb_egg3 = egg3.getGlobalBounds().intersects(ship.getGlobalBounds()); // true


    egg3.move(0, 180 * DeltaTime);




    if (eggclock3 > 3.93318 && eggclock3 < 3.99999 && !collisionchicken3[t_rand]) {
        egg3.setPosition(chickenSprites3[t_rand].getPosition().x + 32, chickenSprites3[t_rand].getPosition().y + 37);
    }


    if (eggclock3 >= 4.0199999 && !collisionchicken3[t_rand])
    {
        if (egg3.getPosition().y > 1010)
        {
            // egg3.move(0, 120 * DeltaTime);
            c_egg3.setPosition(egg3.getPosition().x - 20, 1010);
            // egg3.setPosition(-400, -700);
            egg3.setPosition(chickenSprites3[t_rand].getPosition().x + 32, chickenSprites3[t_rand].getPosition().y + 37);
            // egg3.move(0, 120 * DeltaTime);

             //Egg.play();

             //crack_egg3 = true;
            eggclock3 = 0;
            // egg_timer3 = 0;
        }
        if (bomb_egg3) {

            //bomb.setPosition(ship.getPosition().x, ship.getPosition().y);
            ////  egg3.setScale(0, 0);
            ////  c_egg3.setScale(0, 0);
            //egg3.setPosition(-400, -700);
            egg3.setPosition(chickenSprites3[t_rand].getPosition().x + 32, chickenSprites3[t_rand].getPosition().y + 37);

            //c_egg3.setPosition(10500,1000);
            //ship.setScale(0, 0);
            //explo3 = true;
            health--;
            //// exp.play();
            explo = true;
            eggclock3 = 0;

        }

    }


    // egg4

    bool bomb_egg4 = egg4.getGlobalBounds().intersects(ship.getGlobalBounds());
    egg4.move(0, 180 * DeltaTime);


    if (eggclock4 > 3.93318 && eggclock4 < 3.99999 && !collisionchicken4[forth_rand]) {
        egg4.setPosition(chickenSprites4[forth_rand].getPosition().x + 32, chickenSprites4[forth_rand].getPosition().y + 37);
    }

    if (eggclock4 >= 4.0199999 && !collisionchicken4[forth_rand]) {

        if (egg4.getPosition().y > 1010) {
            c_egg4.setPosition(egg4.getPosition().x - 20, 1010);
            egg4.setPosition(chickenSprites4[forth_rand].getPosition().x + 32, chickenSprites4[forth_rand].getPosition().y + 37);
            //egg4.move(0, 120 * DeltaTime);

            //egg4.setPosition(-1000, -600);
            // Egg.play();
            eggclock4 = 0;
        }

        if (bomb_egg4) {

            //bomb.setPosition(ship.getPosition().x, ship.getPosition().y);
           // egg4.setPosition(-1000, -600);
            egg4.setPosition(chickenSprites4[forth_rand].getPosition().x + 32, chickenSprites4[forth_rand].getPosition().y + 37);

            health--;
            //ship.setScale(0, 0);
            // exp.play();
            explo = true;
            eggclock4 = 0;


        }


    }


}




void move_werk(RenderWindow& window, Sprite& ship, Sprite werk[], Sprite werk2[], Sprite werk3[], Sprite werk4[], Sprite werk5[], Sprite chickenSprites[], Sprite chickenSprites2[], Sprite chickenSprites3[], Sprite chickenSprites4[], Sprite chickenSprites5[], bool collisionchicken[], bool collisionchicken2[], bool collisionchicken3[], bool collisionchicken4[], bool collisionchicken5[], Sound& eatingsound)
{

    if (wrek_animation_delay > 0.08)
    {
        wrk += Wanimation_idx;
        if ((wrk >= 11 || wrk <= 0)) Wanimation_idx *= -1;
        wrek_animation_delay = 0;

    }
    else wrek_animation_delay += DeltaTime;


    for (int i = 0; i < 8; i++) {
        werk[i].setTextureRect(IntRect(403 * wrk, 0, 403, 430));
        werk2[i].setTextureRect(IntRect(403 * wrk, 0, 403, 430));
        werk3[i].setTextureRect(IntRect(403 * wrk, 0, 403, 430));
        werk4[i].setTextureRect(IntRect(403 * wrk, 0, 403, 430));
        werk5[i].setTextureRect(IntRect(403 * wrk, 0, 403, 430));


    }








    for (int i = 0; i < 8; i++) {

        if (!collisionchicken[i]) {
            werk[i].setScale(0.1, 0.1);
            werk[i].setPosition(chickenSprites[i].getPosition().x + 23, chickenSprites[i].getPosition().y + 32);
        }

        if (collisionchicken[i]) {
            werk[i].setScale(0.2, 0.2);
            werk[i].move(0, 120 * DeltaTime);
            if (werk[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
                werk[i].setScale(0, 0);
                werkcounter++;
                werk[i].setPosition(-100, -100);
                eatingsound.play();

                //  cout << ch_counter;   
            }

        }




    }
    for (int i = 0; i < 8; i++) {
        if (!collisionchicken2[i]) {
            werk2[i].setScale(0.1, 0.1);
            werk2[i].setPosition(chickenSprites2[i].getPosition().x + 23, chickenSprites2[i].getPosition().y + 32);
        }

        if (collisionchicken2[i]) {
            werk2[i].setScale(0.2, 0.2);
            werk2[i].move(0, 120 * DeltaTime);
            if (werk2[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
                werk2[i].setScale(0, 0);
                werkcounter++;
                werk2[i].setPosition(-100, -100);
                eatingsound.play();

            }



        }

    }
    for (int i = 0; i < 8; i++) {
        if (!collisionchicken3[i]) {
            werk3[i].setScale(0.1, 0.1);
            werk3[i].setPosition(chickenSprites3[i].getPosition().x + 23, chickenSprites3[i].getPosition().y + 32);
        }

        if (collisionchicken3[i]) {
            werk3[i].setScale(0.2, 0.2);
            werk3[i].move(0, 120 * DeltaTime);
            if (werk3[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
                werk3[i].setScale(0, 0);
                werkcounter++;
                werk3[i].setPosition(-100, -100);
                eatingsound.play();

            }
        }
    }

    //werk 4
    for (int i = 0; i < 8; i++) {
        if (!collisionchicken4[i]) {
            werk4[i].setScale(0.1, 0.1);
            werk4[i].setPosition(chickenSprites4[i].getPosition().x + 23, chickenSprites4[i].getPosition().y + 32);
        }

        if (collisionchicken4[i]) {
            werk4[i].setScale(0.2, 0.2);
            werk4[i].move(0, 120 * DeltaTime);
            if (werk4[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
                werk4[i].setScale(0, 0);
                werkcounter++;
                werk4[i].setPosition(-100, -100);
                eatingsound.play();

            }
        }
    }

    //werk 5
    for (int i = 0; i < 8; i++) {
        if (!collisionchicken5[i]) {
            werk5[i].setScale(0.1, 0.1);
            werk5[i].setPosition(chickenSprites5[i].getPosition().x + 23, chickenSprites5[i].getPosition().y + 32);
        }

        if (collisionchicken5[i]) {
            werk5[i].setScale(0.2, 0.2);
            werk5[i].move(0, 120 * DeltaTime);
            if (werk5[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
                werk5[i].setScale(0, 0);
                werkcounter++;
                werk5[i].setPosition(-100, -100);
                eatingsound.play();
            }
        }
    }



}


void exp(Sprite& boss2) {

    BossStruct.Boss2Appeartimer++;

    if (BossStruct.HpBoss2 == 0)
    {
        //cout << "boss2" << endl;

        boss2.setScale(0, 0);
        boss2.move(0, 0);

        if (Explosion.Bossbomb2_animation_delay > 0.2)
        {
            Explosion.Bb2 += Explosion.Bb2animation_idx;
            if ((Explosion.Bb2 >= 9 || Explosion.Bb2 <= 0)) Explosion.Bb2animation_idx *= -1;
            {
                Explosion.Bossbomb2_animation_delay = 0;
            }
            if (Explosion.Bb2 >= 9)
            {
                Explosion.Bb2animation_idx = 1;
            }
        }

        else
        {
            Explosion.Bossbomb2_animation_delay += DeltaTime;
        }

        Explosion.chickenBomb2.setTextureRect(IntRect(766 * Explosion.Bb2, 0, 766, 811));


        if (BossStruct.Boss2Appeartimer <= 50)
        {
            Explosion.chickenBomb2.setPosition(boss2.getPosition().x, boss2.getPosition().y);
            Explosion.chickenBomb2.setScale(0.3, 0.3);
            Explosion.Boss2Explo = true;

        }

        else if (BossStruct.Boss2Appeartimer > 60)
        {
            Explosion.chickenBomb2.setScale(0, 0);
            BossStruct.Boss2Appeartimer = 0;
            Explosion.Boss2Explo = false;
        }

    }
}


void BossAnimation(Sprite& boss, float& randx, float& randy, Sprite& ship, bool& explo, bool& isShielded, Sprite& bomb, int& explotimer, Sprite& shield, Sprite bullets[], bool& BossExplo, int& chBull, Sprite& chickenBomb, int& BossAppeartimer)
{
    if (!BossExplo)
    {

        if (BossStruct.boss_animation_delay > 0.015) {
            BossStruct.B += BossStruct.Banimation_idx;
            if ((BossStruct.B >= 44 || BossStruct.B <= 0)) BossStruct.Banimation_idx *= -1;
            BossStruct.boss_animation_delay = 0;
        }
        else {
            BossStruct.boss_animation_delay += DeltaTime;
        }
        boss.setTextureRect(IntRect(BossStruct.B * 256, 0, 256, 256));

        if (randy == 0)
        {
            randy = rand() % 7 - 3;
        }
        else if (randx == 0)
        {
            randx = rand() % 7 - 3;
        }
        boss.move(randx, randy);

        if (bossPos.x < 0 || bossPos.x>1880)
        {
            randx *= -1;
        }
        if (bossPos.y > 300 || bossPos.y < -200)
        {
            randy *= -1;
        }

        bossPos.x += randx;
        bossPos.y += randy;
        boss.setPosition(bossPos);
    }

    if (ship.getGlobalBounds().intersects(boss.getGlobalBounds()))
    {
        if (!isShielded)
        {
            explo = true;
        }
        // shield.setPosition(10000, 10000);
    }


    if (countercounter == 2)
    {
        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (chBull == 0)
            {
                if (bullets[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {
                    BossStruct.HpBoss -= 1;
                    if (BossStruct.HpBoss <= 0)
                    {
                        boss.setScale(0, 0);
                        score += 500;
                        BossExplo = true;

                    }
                }
                if (bullets[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {

                    bullets[i].setScale(0, 0);
                }
            }

            if (chBull == 1)
            {
                if (bullets[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {
                    BossStruct.HpBoss -= 2;
                    if (BossStruct.HpBoss <= 0)
                    {
                        boss.setScale(0, 0);
                        score += 500;
                        BossExplo = true;

                    }
                }

                if (bullets[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {

                    bullets[i].setScale(0, 0);
                }


            }


            if (chBull == 2)
            {
                if (bullets[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {
                    BossStruct.HpBoss -= 3;
                    //cout << BossStruct.HpBoss << endl;
                    if (BossStruct.HpBoss <= 0)
                    {
                        boss.setScale(0, 0);
                        score += 500;
                        BossExplo = true;

                    }

                }
                if (bullets[i].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {

                    bullets[i].setScale(0, 0);
                }

            }
        }
    }

}

void BossAnimation2(Sprite& boss2, float& randx2, float& randy2, Sprite& ship, bool& explo, bool& isShielded, Sprite& bomb, int& explotimer, Sprite& shield, Sprite bullets[], bool& Boss2Explo, int& chBull, Sprite& chickenBomb2, int& Boss2Appeartimer)
{
    if (!Boss2Explo)
    {

        if (BossStruct.boss2_animation_delay > 0.015) {
            BossStruct.B2 += BossStruct.B2animation_idx;
            if ((BossStruct.B2 >= 44 || BossStruct.B2 <= 0)) BossStruct.B2animation_idx *= -1;
            BossStruct.boss2_animation_delay = 0;
        }
        else {
            BossStruct.boss2_animation_delay += DeltaTime;
        }
        boss2.setTextureRect(IntRect(BossStruct.B2 * 256, 0, 256, 256));

        if (randy2 == 0)
        {
            randy2 = rand() % 7 - 3;
        }
        else if (randx2 == 0)
        {
            randx2 = rand() % 7 - 3;
        }
        boss2.move(randx2, randy2);

        if (bossPos2.x < 0 || bossPos2.x>1880)
        {
            randx2 *= -1;
        }
        if (bossPos2.y > 300 || bossPos2.y < -200)
        {
            randy2 *= -1;
        }

        bossPos2.x += randx2;
        bossPos2.y += randy2;
        boss2.setPosition(bossPos2);
    }

    if (countercounter == 2)
    {


        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (chBull == 0)
            {
                if (bullets[i].getGlobalBounds().intersects(boss2.getGlobalBounds()))
                {
                    BossStruct.HpBoss2 -= 1;
                    if (BossStruct.HpBoss2 <= 0)
                    {
                        boss2.setScale(0, 0);
                        score += 500;
                        Boss2Explo = true;

                    }
                }
                if (bullets[i].getGlobalBounds().intersects(boss2.getGlobalBounds()))
                {

                    bullets[i].setScale(0, 0);
                }
            }
            if (chBull == 1)
            {
                if (bullets[i].getGlobalBounds().intersects(boss2.getGlobalBounds()))
                {
                    BossStruct.HpBoss2 -= 2;
                    if (BossStruct.HpBoss2 <= 0)
                    {
                        boss2.setScale(0, 0);
                        score += 500;
                        Boss2Explo = true;

                    }
                }

                if (bullets[i].getGlobalBounds().intersects(boss2.getGlobalBounds()))
                {

                    bullets[i].setScale(0, 0);
                }


            }


            if (chBull == 2)
            {
                if (bullets[i].getGlobalBounds().intersects(boss2.getGlobalBounds()))
                {
                    BossStruct.HpBoss2 -= 3;

                    if (BossStruct.HpBoss2 <= 0)
                    {
                        boss2.setScale(0, 0);
                        score += 500;
                        Boss2Explo = true;

                    }

                }
                if (bullets[i].getGlobalBounds().intersects(boss2.getGlobalBounds()))
                {

                    bullets[i].setScale(0, 0);
                }

            }

        }
    }


}



void Bullets(Sprite bullets[], Sprite& ship, float& fireTimer, bool isShot[], int ctrBull, int chBull, Texture& RedBullettex1, Texture& RedBullettex2, Texture& RedBullettex3, Texture& GreenBullettex1, Texture& GreenBullettex2, Texture& GreenBullettex3, Texture& BlueBullettex1, Texture& BlueBullettex2, Texture& BlueBullettex3, Sound& lasersound, Sound& greensound, Sound& bluesound) {

    //bullets update

    const float FIRE_INTERVAL = 0.2;
    fireTimer += DeltaTime;

    if (Keyboard::isKeyPressed(Keyboard::Key::Space))
    {
        if (fireTimer >= FIRE_INTERVAL)
        {
            fireTimer = 0.0;
            for (int i = 0; i < NUM_BULLETS; i++)
            {
                if (!isShot[i])
                {
                    isShot[i] = true;
                    if (ctrBull == 0 && chBull == 0)
                    {
                        lasersound.play();
                        bullets[i].setTexture(RedBullettex1);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull == 1 && chBull == 0)
                    {
                        lasersound.play();
                        bullets[i].setTexture(RedBullettex2);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull >= 2 && chBull == 0)
                    {
                        lasersound.play();
                        bullets[i].setTexture(RedBullettex3);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull == 0 && chBull == 1)
                    {
                        greensound.play();
                        bullets[i].setTexture(GreenBullettex1);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull == 1 && chBull == 1)
                    {
                        greensound.play();
                        bullets[i].setTexture(GreenBullettex2);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull >= 2 && chBull == 1)
                    {
                        greensound.play();
                        bullets[i].setTexture(GreenBullettex3);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }


                    if (ctrBull == 0 && chBull == 2)
                    {
                         bluesound.play();
                        bullets[i].setTexture(BlueBullettex1);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull == 1 && chBull == 2)
                    {
                        bluesound.play();
                        bullets[i].setTexture(BlueBullettex2);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }

                    if (ctrBull >= 2 && chBull == 2)
                    {
                        bluesound.play();
                        bullets[i].setTexture(BlueBullettex3);
                        bullets[i].setPosition(ship.getPosition().x + 13.8, ship.getPosition().y);
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < NUM_BULLETS; i++)
    {
        if (isShot[i])
        {
            if (chBull == 0)
            {
                bullets[i].move(0, -1800 * DeltaTime);

            }
            if (chBull == 1)
            {
                bullets[i].move(0, -2400 * DeltaTime);

            }

            if (chBull == 2)
            {
                bullets[i].move(0, -3000 * DeltaTime);

            }
        }
    }
}

void GreyRockMovement(Sprite& greyrocks, Sprite& ship, int& ctrBull, int& greyRockTimer, bool& explo, Sprite& bomb, int& explotimer, Sprite& shield, bool& isShielded, bool& BossExplo, Sprite& boss, Sprite& chickenBomb, int& BossAppeartimer) {
    const int num = 90;
    float xeg = 100 + rand() % 1200;

    if (Rocks.redRock_animation_delay > 0.05)
    {
        Rocks.Gr += Rocks.Granimation_idx;
        if ((Rocks.Gr >= 29 || Rocks.Gr <= 0)) Rocks.Granimation_idx *= -1;
        Rocks.greyRock_animation_delay = 0;
    }

    else
    {
        Rocks.greyRock_animation_delay += DeltaTime;
    }


    greyrocks.move(-100 * DeltaTime, 250 * DeltaTime);


    if (greyRockTimer <= 0)
    {
        greyrocks.setTextureRect(IntRect(Rocks.Gr * 256, 0, 256, 1076));
        greyRockTimer = 0.1;

    }
    else
        greyRockTimer -= DeltaTime;

    // shield collision with rocks
    if (shield.getGlobalBounds().intersects(greyrocks.getGlobalBounds()))
    {
        greyrocks.setPosition(xeg, -250);
    }

    //ship coll with rocks
    if (ship.getGlobalBounds().intersects(greyrocks.getGlobalBounds()))
    {
        ctrBull = 0;
        for (int i = 0; i < num; i++)
        {
            greyrocks.setPosition(5000, 5000);
        }
        //explosion ship
        health--;
        explo = true;
    }

    if (greyrocks.getPosition().y >= 1080)
    {

        // rocks[i].setPosition(0, -10);
        greyrocks.setScale(0.35, 0.35);

        greyrocks.setPosition(xeg, -250);

    }


}


void RedRockMovement(Sprite& redrocks, Sprite& ship, int& ctrBull, int& redRockTimer, Sprite& bomb, bool& explo, int& explotimer, Sprite& shield, bool& isShielded, bool& BossExplo, Sprite& boss, Sprite& chickenBomb, int& BossAppeartimer) {
    const int num = 90;
    float xe = 100 + rand() % 1200;

    if (Rocks.redRock_animation_delay > 0.05)
    {
        Rocks.Rr += Rocks.Rranimation_idx;
        if ((Rocks.Rr >= 29 || Rocks.Rr <= 0)) Rocks.Rranimation_idx *= -1;
        Rocks.redRock_animation_delay = 0;
    }

    else
    {
        Rocks.redRock_animation_delay += DeltaTime;
    }



    redrocks.move(100 * DeltaTime, 250 * DeltaTime);

    if (redRockTimer <= 0)
    {
        redrocks.setTextureRect(IntRect(Rocks.Rr * 256, 0, 256, 1076));
        redRockTimer = 0.1;

    }
    else
        redRockTimer -= DeltaTime;
    // shield collision with rocks
    if (shield.getGlobalBounds().intersects(redrocks.getGlobalBounds()))
    {
        redrocks.setPosition(xe, -250);
    }

    //ship coll with rocks

    if (ship.getGlobalBounds().intersects(redrocks.getGlobalBounds()))
    {

        ctrBull = 0;
        for (int i = 0; i < num; i++)
        {
            redrocks.setPosition(5000, 5000);
        }

        //explosion ship
        health--;
        explo = true;
    }

    if (redrocks.getPosition().y >= 1080)
    {

        // rocks[i].setPosition(0, -10);
        redrocks.setScale(0.35, 0.35);

        redrocks.setPosition(xe, -250);

    }


}




void GiftMovement(Sprite& gift, Sprite& ship, int& chBull, int& gifttimer)

{

    if (StarGift.gift_animation_delay > 0.05)
    {

        StarGift.g += StarGift.Ganimation_idx;
        if ((StarGift.g >= 44 || StarGift.g <= 0)) StarGift.Ganimation_idx *= -1;
        StarGift.gift_animation_delay = 0;
    }

    else
    {

        StarGift.gift_animation_delay += DeltaTime;

    }

    float xg = 300 + rand() % 1600;

    /*if (DeltaTime * 60 >= 1)
    {


    }*/
    gifttimer++;

    if (gifttimer >= 5)
    {
        //cout << gifttimer << endl;
        gift.move(0, 4);
        gift.setTextureRect(IntRect(StarGift.g * 256, 0, 256, 256));

        //ship collision with gifts

        if (ship.getGlobalBounds().intersects(gift.getGlobalBounds()))
        {
            gift.setPosition(xg, -90);
            gifttimer = 0;
            changeBullet(chBull);
            //cout << chBull << endl;
        }

        if (gift.getPosition().y >= 1080)
        {
            gift.setPosition(xg, -90);
            gifttimer = 0;
        }
    }
}


void starMovemnt(Sprite& star, Sprite& ship, int& startimer, int& ctrBull) {


    if (StarGift.star_animation_delay > 0.05)
    {
        StarGift.S += StarGift.Sanimation_idx;
        if ((StarGift.S >= 24 || StarGift.S <= 0)) StarGift.Sanimation_idx *= -1;
        StarGift.star_animation_delay = 0;
    }

    else
    {
        StarGift.star_animation_delay += DeltaTime;
    }

    float xs = 300 + rand() % 1600;

    //if (DeltaTime * 240 >= 4)
    //{
    //}
    startimer++;

    if (startimer >= 5)
    {
        star.move(0, 4);
        star.setTextureRect(IntRect(StarGift.S * 98, 0, 98, 82));

        // ship coll with star and ctrBull increment

        if (ship.getGlobalBounds().intersects(star.getGlobalBounds()))
        {
            star.setPosition(xs, -50);
            startimer = 0;
            incrementBullet(ctrBull);
            //cout << ctrBull << endl;

        }

        if (star.getPosition().y >= 1080)
        {
            star.setPosition(xs, -50);
            startimer = 0;

        }

    }

}

void moveChickens(RenderWindow& window, Sprite chickenSprites[], Sprite chickenSprites2[], Sprite chickenSprites3[], Sprite chickenSprites4[], Sprite chickenSprites5[], const int NUM_CHICKENS, const int CHICKEN_WIDTH, bool& moveLeft1, bool& moveLeft2, bool& moveLeft3, bool& moveLeft4, bool& moveLeft5, bool isShot[], Sprite bullets[], bool collisonchicken[], bool collisionchicken2[], bool collisionchicken3[], bool collisionchicken4[], bool collisionchicken5[], Sound& chickensound,Sprite& ship, bool& explo) {

    if (chiken_animation_delay > 0.2)
    {
        c += Canimation_idx;
        if ((c >= 2 || c <= 0)) Canimation_idx *= -1;
        chiken_animation_delay = 0;

    }

    else chiken_animation_delay += DeltaTime;


    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        chickenSprites[i].move(moveLeft1 ? -(DeltaTime * 60) : (DeltaTime * 60), 0); // move left if moveLeft2 is true, else move right

        // check if the last chicken hits the window right edge
        if (i == NUM_CHICKENS - 1 && (chickenSprites[i].getPosition().x + chickenSprites[i].getGlobalBounds().width >= window.getSize().x)) {
            moveLeft1 = !moveLeft1; // toggle the flag to change direction of movement
        }
        else if (i == 0 && (chickenSprites[0].getPosition().x <= 0))
        {
            moveLeft1 = false;
        }
        //  cout << c;
        chickenSprites[i].setTextureRect(IntRect(c * 568, 0, 568, 479));

    }


    for (int i = 0; i < NUM_CHICKENS; i++)
    {


        chickenSprites2[i].move(moveLeft2 ? -(DeltaTime * 60) : (DeltaTime * 60), 0); // move left if moveLeft2 is true, else move right

        // check if the last chicken hits the window right edge
        if (i == NUM_CHICKENS - 1 && (chickenSprites2[i].getPosition().x + chickenSprites2[i].getGlobalBounds().width >= window.getSize().x)) {
            moveLeft2 = !moveLeft2; // toggle the flag to change direction of movement
        }
        else if (i == 0 && (chickenSprites2[0].getPosition().x <= 0))
        {
            moveLeft2 = false;
        }

        chickenSprites2[i].setTextureRect(IntRect(c * 568, 0, 568, 479));

    }



    for (int i = 0; i < NUM_CHICKENS; i++)
    {


        chickenSprites3[i].move(moveLeft3 ? -(DeltaTime * 60) : (DeltaTime * 60), 0); // move left if moveLeft2 is true, else move right

        // check if the last chicken hits the window right edge
        if (i == NUM_CHICKENS - 1 && (chickenSprites3[i].getPosition().x + chickenSprites3[i].getGlobalBounds().width >= window.getSize().x)) {
            moveLeft3 = !moveLeft3; // toggle the flag to change direction of movement
        }
        else if (i == 0 && (chickenSprites3[0].getPosition().x <= 0))
        {
            moveLeft3 = false;
        }

        chickenSprites3[i].setTextureRect(IntRect(c * 568, 0, 568, 479));

    }
    //forth   

    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        chickenSprites4[i].move(moveLeft4 ? -(DeltaTime * 60) : (DeltaTime * 60), 0); // move left if moveLeft2 is true, else move right

        // check if the last chicken hits the window right edge
        if (i == NUM_CHICKENS - 1 && (chickenSprites4[i].getPosition().x + chickenSprites4[i].getGlobalBounds().width >= window.getSize().x)) {
            moveLeft4 = !moveLeft4; // toggle the flag to change direction of movement
        }
        else if (i == 0 && (chickenSprites4[0].getPosition().x <= 0))
        {
            moveLeft4 = false;
        }
        //  cout << c;
        chickenSprites4[i].setTextureRect(IntRect(c * 568, 0, 568, 479));

    }


    //fifth array
    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        chickenSprites5[i].move(moveLeft5 ? -(DeltaTime * 60) : (DeltaTime * 60), 0); // move left if moveLeft2 is true, else move right

        // check if the last chicken hits the window right edge
        if (i == NUM_CHICKENS - 1 && (chickenSprites5[i].getPosition().x + chickenSprites5[i].getGlobalBounds().width >= window.getSize().x)) {
            moveLeft5 = !moveLeft5; // toggle the flag to change direction of movement
        }
        else if (i == 0 && (chickenSprites5[0].getPosition().x <= 0))
        {
            moveLeft5 = false;
        }
        //  cout << c;
        chickenSprites5[i].setTextureRect(IntRect(c * 568, 0, 568, 479));

    }




    for (int i = 0; i < NUM_BULLETS; i++) {
        if (isShot[i]) {
            for (int j = 0; j < NUM_CHICKENS; j++) {
                if (bullets[i].getGlobalBounds().intersects(chickenSprites5[j].getGlobalBounds())) {
                   
                   
                        isShot[i] = false;
                        fatencounter++;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen
                        chickenSprites5[j].setScale(0, 0); // Move chicken offscreen
                        score += 100;
                        collisionchicken5[j] = true;

                        chickensound.play();
                   
                } 
            }
            
        }
    }

    for (int i = 0; i < NUM_BULLETS; i++) {

        if (isShot[i]) {
            for (int j = 0; j < NUM_CHICKENS; j++) {
                if (bullets[i].getGlobalBounds().intersects(chickenSprites4[j].getGlobalBounds())) {
                    if (chickenHitCount[j] == 1) {
                        chickenHitCount[j] = 0;
                        cout << chickenHitCount[j];
                        isShot[i] = false;
                        fatencounter++;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen
                        chickenSprites4[j].setScale(0, 0); // Move chicken offscreen
                        score += 100;
                        collisionchicken4[j] = true;

                        chickensound.play();
                    }
                    else {
                        chickenHitCount[j]+=1 ;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen

                    }
                    
                    
                    
                }
            }
        }
    }

    for (int i = 0; i < NUM_BULLETS; i++) {
        if (isShot[i]) {
            for (int j = 0; j < NUM_CHICKENS; j++) {
                if (bullets[i].getGlobalBounds().intersects(chickenSprites3[j].getGlobalBounds())) {
                    if (chickenHitCount[j] == 2) {
                        chickenHitCount[j] = 0;

                        isShot[i] = false;
                        fatencounter++;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen
                        chickenSprites3[j].setScale(0, 0); // Move chicken offscreen
                        score += 100;
                        collisionchicken3[j] = true;

                        chickensound.play();


                    }

                    else {
                        chickenHitCount[j] += 1;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen

                    }
                
                }
            }
        }
    }


    for (int i = 0; i < NUM_BULLETS; i++) {
        if (isShot[i]) {
            for (int j = 0; j < NUM_CHICKENS; j++) {
                if (bullets[i].getGlobalBounds().intersects(chickenSprites2[j].getGlobalBounds())) {
                    if (chickenHitCount[j] == 2) {
                        chickenHitCount[j] = 0;

                        isShot[i] = false;
                        fatencounter++;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen
                        chickenSprites2[j].setScale(0, 0);
                        // Move chicken offscreen
                        score += 100;
                        collisionchicken2[j] = true;
                        chickensound.play();


                    }

                    else {
                        chickenHitCount[j] += 1;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen

                    }
                
                }
            }
        }
    }
    for (int i = 0; i < NUM_BULLETS; i++) {
        if (isShot[i]) {
            for (int j = 0; j < NUM_CHICKENS; j++) {
                if (bullets[i].getGlobalBounds().intersects(chickenSprites[j].getGlobalBounds())) {

                    if (chickenHitCount[j] == 2) {
                        chickenHitCount[j] = 0;
                        isShot[i] = false;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen
                        fatencounter++;
                        chickenSprites[j].setScale(0, 0); // Move chicken offscreen
                        score += 100;

                        collisonchicken[j] = true;
                        // counter++;
                        chickensound.play();

                    }

                    else {
                        chickenHitCount[j] += 1;
                        bullets[i].setPosition(10000, 10000); // Move bullet offscreen

                    }
                }
            }
        }
    }


    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        if (ship.getGlobalBounds().intersects(chickenSprites[i].getGlobalBounds()))
        {
            explo = true;


        }
    }

    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        if (ship.getGlobalBounds().intersects(chickenSprites2[i].getGlobalBounds()))
        {
            explo = true;


        }
    }

    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        if (ship.getGlobalBounds().intersects(chickenSprites3[i].getGlobalBounds()))
        {
            explo = true;


        }
    }

    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        if (ship.getGlobalBounds().intersects(chickenSprites4[i].getGlobalBounds()))
        {
            explo = true;


        }
    }


    for (int i = 0; i < NUM_CHICKENS; i++)
    {

        if (ship.getGlobalBounds().intersects(chickenSprites5[i].getGlobalBounds()))
        {
            explo = true;


        }
    }

}

void shipmove(Sprite& ship, bool explo, Sprite& shield, float& shieldTimer, bool& isShielded)

{
    int x = 0;
    int y = 0;
    shieldTimer += DeltaTime;


    if (shieldTimer >= 6)
    {
        isShielded = false;
        shield.setPosition(10000, 10000);
        shieldTimer = 0;
    }


    if (Keyboard::isKeyPressed(Keyboard::Key::W) && ship.getPosition().y > 0)
    {
        if (!explo)
        {
            shield.move(0, -8);
            ship.move(0, -8);

            x++;
            x %= 10;
            y = 0;
            ship.setTextureRect(IntRect(x * 256, y * 256, 256, 256));

        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::A) && ship.getPosition().x > 0)
    {
        if (!explo)
        {


            shield.move(DeltaTime * -600, 0);
            ship.move(DeltaTime * -600, 0);
            x = 1;
            if (x != 6)

            {
                x++;
                x %= 10;
                y = 3;
                ship.setTextureRect(IntRect(x * 256, y * 256, 256, 256));

            }

        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::S) && ship.getPosition().y < 950)
    {
        if (!explo)
        {


            shield.move(0, 8);
            ship.move(0, 8);


            x++;
            x %= 10;
            y = 1;
            ship.setTextureRect(IntRect(x * 256, y * 256, 256, 256));

        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::D) && ship.getPosition().x < 1800)
    {
        if (!explo)
        {


            shield.move(DeltaTime * 600, 0);
            ship.move(DeltaTime * 600, 0);
            x = 1;
            if (x != 6)
            {
                x++;
                x %= 10;
                y = 2;
                ship.setTextureRect(IntRect(x * 256, y * 256, 256, 256));

            }


        }
    }
}

void hover(RenderWindow& window, RectangleShape& Button, Mouse& mouse, Sprite& Earth, Sprite& Planet, Sprite& Planet2, RectangleShape& Exit, RectangleShape& Options, RectangleShape& greenbutton, RectangleShape& redbutton, RectangleShape& mutebutton, RectangleShape& nextbutton, RectangleShape& nextbuttonl1, RectangleShape& nextbuttonl2, RectangleShape& nextbuttongg, RectangleShape& nextbuttone, RectangleShape& Optionexit, RectangleShape& Optionstart, RectangleShape& Emptymenu, RectangleShape& Setting, RectangleShape& Back) {



    if (Back.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Back.setFillColor(Color::Magenta);
    }
    else {
        Back.setFillColor(Color::White);
    }

    if (Setting.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Setting.setFillColor(Color::Blue);
    }
    else {
        Setting.setFillColor(Color::White);
    }

    if (Emptymenu.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Emptymenu.setFillColor(Color::Cyan);
    }
    else {
        Emptymenu.setFillColor(Color::White);
    }

    if (Optionstart.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Optionstart.setFillColor(Color::Cyan);
    }
    else {
        Optionstart.setFillColor(Color::White);
    }

    if (Optionexit.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Optionexit.setFillColor(Color::Cyan);
    }
    else {
        Optionexit.setFillColor(Color::White);
    }

    if (nextbuttongg.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        nextbuttongg.setFillColor(Color::Cyan);
    }
    else {
        nextbuttongg.setFillColor(Color::White);
    }

    if (nextbuttone.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        nextbuttone.setFillColor(Color::Cyan);
    }
    else {
        nextbuttone.setFillColor(Color::White);
    }

    if (nextbuttonl2.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        nextbuttonl2.setFillColor(Color::Cyan);
    }
    else {
        nextbuttonl2.setFillColor(Color::White);
    }

    if (nextbuttonl1.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        nextbuttonl1.setFillColor(Color::Cyan);
    }
    else {
        nextbuttonl1.setFillColor(Color::White);
    }

    if (nextbutton.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        nextbutton.setFillColor(Color::Cyan);
    }
    else {
        nextbutton.setFillColor(Color::White);
    }


    if (greenbutton.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        greenbutton.setFillColor(Color::Green);
    }
    else {
        greenbutton.setFillColor(Color::White);
    }


    if (redbutton.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        redbutton.setFillColor(Color::Yellow);
    }
    else {
        redbutton.setFillColor(Color::White);
    }


    if (mutebutton.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        mutebutton.setFillColor(Color::Yellow);
    }
    else {
        mutebutton.setFillColor(Color::White);
    }


    if (Options.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Options.setFillColor(Color::Cyan);
    }
    else {
        Options.setFillColor(Color::White);
    }

    if (Exit.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Exit.setFillColor(Color::Cyan);
    }
    else {
        Exit.setFillColor(Color::White);
    }


    if (Button.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Button.setFillColor(Color::Cyan);
    }
    else {
        Button.setFillColor(Color::White);
    }

    if (Earth.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Earth.setScale(1.2f, 1.2f);
    }
    else {
        Earth.setScale(1.1f, 1.1f);
    }
    if (Planet.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Planet.setScale(1.2f, 1.2f);
    }
    else {
        Planet.setScale(1.1f, 1.1f);
    }
    if (Planet2.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
        Planet2.setScale(1.2f, 1.2f);
    }
    else {
        Planet2.setScale(1.1f, 1.1f);
    }

}

void drawObjects(RenderWindow& window, int count, Sprite Option, RectangleShape& Back, Sprite Menu[], RectangleShape& Button, Sprite Logo, RectangleShape& Exit, RectangleShape& Options, Sprite Levelback, Sprite Earth, Sprite Planet, Sprite Planet2, Sprite Level1back, Sprite Level2back, Sprite Level3back, Sprite& ship, Sprite chickenSprites[], Sprite chickenSprites2[], Sprite chickenSprites3[], Sprite star, Sprite gift, Sprite bullets[], bool explo, Sprite& redrocks, Sprite& greyrocks, Sprite bomb, Sprite& shield, bool& isShielded, Sprite& boss, Sprite& chickenBomb, bool& BossExplo, RectangleShape& greenbutton, RectangleShape& redbutton, RectangleShape& soundbar, RectangleShape& mutebutton, RectangleShape& volumetext, RectangleShape& fatenwelcome, RectangleShape& nextbutton, Sprite werk[], Sprite werk2[], Sprite werk3[], Sprite& boss2, RectangleShape& Setting, int menuoption, RectangleShape& Optionstart, RectangleShape& Optionexit, RectangleShape& Emptymenu, Sprite chickenSprites4[], Sprite chickenSprites5[], Sprite egg1, Sprite egg2, Sprite egg3, Sprite egg4, Sprite c_egg, Sprite c_egg2, Sprite c_egg3, Sprite c_egg4, Sprite N_bomb, Sprite werk4[], Sprite werk5[], Text scoretex, Text healthtex, RectangleShape& fatenwin, Sprite& gamebar, Text& werktex, RectangleShape& nextbuttonl1, RectangleShape& nextbuttonl2, RectangleShape& fatengameover, RectangleShape& nextbuttongg, RectangleShape& fatenend, RectangleShape& nextbuttone, Sprite& gameEndingback, RectangleShape& credentials) {




    if (count == -1)   // options menue
    {

        window.draw(Option);

        window.draw(Back);
        window.draw(greenbutton);
        window.draw(redbutton);
        window.draw(soundbar);
        window.draw(mutebutton);
        window.draw(volumetext);
    }

    else if (count == 0)   // main menue
    {


        for (int i = 0; i < 2; i++)
        {
            window.draw(Menu[i]);
        }

        window.draw(Button);

        window.draw(Logo);

        window.draw(Exit);
        window.draw(Options);

    }

    else if (count == 1)  // planets menue
    {

        window.draw(Levelback);

        window.draw(Earth);

        window.draw(Planet);

        window.draw(Planet2);

        window.draw(Back);

        window.draw(fatenwelcome);
        window.draw(nextbutton);


    }

    else if (count == 2)  // level1
    {

        //window.draw(Level1back);

        for (int i = 0; i < 2; i++)
        {
            window.draw(Menu[i]);
        }

        for (int i = 0; i < 2; i++)
        {
            Menu[i].move(Vector2f(0, -50 * DeltaTime));
        }
        if (Menu[0].getPosition().y <= -1080 - 0.2) {
            Menu[0].setPosition(Vector2f(0, 1080 - 0.2));
        }
        else if (Menu[1].getPosition().y <= -1080 - 0.2) {
            Menu[1].setPosition(Vector2f(0, 1080 - 0.2));
        }

        window.draw(Setting);
        window.draw(ship);

        if (isShielded)
        {
            window.draw(shield);
        }

        for (int i = 0; i < 8; i++) {
            window.draw(werk[i]);
            window.draw(werk2[i]);
            window.draw(werk3[i]);
            window.draw(werk4[i]);
            window.draw(werk5[i]);

        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites2[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites3[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites4[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites5[i]);
        }


        window.draw(star);



        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (!explo)
            {
                window.draw(bullets[i]);
            }
        }
        window.draw(egg1);
        window.draw(c_egg);
        window.draw(egg2);
        window.draw(c_egg2);
        window.draw(N_bomb);
        window.draw(c_egg3);
        window.draw(egg3);
        window.draw(c_egg4);
        window.draw(egg4);


        window.draw(gamebar);
        window.draw(scoretex);
        window.draw(healthtex);
        window.draw(werktex);
        window.draw(bomb);
        window.draw(fatenwin);
        window.draw(nextbuttonl1);

        window.draw(fatengameover);
        window.draw(nextbuttongg);

    }
    if (count == 2 && menuoption > 0)
    {
        window.draw(Emptymenu);
        window.draw(Optionstart);
        window.draw(Optionexit);

    }

    else if (count == 3)   // level 2
    {

        window.draw(Level2back);
        window.draw(ship);
        window.draw(Setting);

        if (isShielded)
        {
            window.draw(shield);
        }

        for (int i = 0; i < 8; i++) {
            window.draw(werk[i]);
            window.draw(werk2[i]);
            window.draw(werk3[i]);
            window.draw(werk4[i]);
            window.draw(werk5[i]);

        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites2[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites3[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites4[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites5[i]);
        }


        window.draw(redrocks);
        window.draw(greyrocks);



        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (!explo)
            {
                window.draw(bullets[i]);
            }
        }


        window.draw(egg1);
        window.draw(c_egg);
        window.draw(egg2);
        window.draw(c_egg2);
        window.draw(N_bomb);
        window.draw(c_egg3);
        window.draw(egg3);
        window.draw(c_egg4);
        window.draw(egg4);

        window.draw(gift);
        window.draw(star);



        window.draw(gamebar);
        window.draw(scoretex);
        window.draw(healthtex);
        window.draw(werktex);
        window.draw(bomb);
        window.draw(fatenwin);
        window.draw(nextbuttonl2);

        window.draw(fatengameover);
        window.draw(nextbuttongg);

        if (count == 3 && menuoption > 0)
        {
            window.draw(Emptymenu);
            window.draw(Optionstart);
            window.draw(Optionexit);

        }


    }

    else if (count == 4)  // level 3
    {
        window.draw(Level3back);



        for (int i = 0; i < 8; i++) {
            window.draw(werk[i]);
            window.draw(werk2[i]);
            window.draw(werk3[i]);
            window.draw(werk4[i]);
            window.draw(werk5[i]);

        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites2[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites3[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites4[i]);
        }

        for (int i = 0; i < 8; i++)
        {
            window.draw(chickenSprites5[i]);
        }

        window.draw(redrocks);
        window.draw(greyrocks);

        if (BossExplo)
        {
            chickenBomb.setPosition(boss.getPosition().x, boss.getPosition().y);
            chickenBomb.setScale(0.3, 0.3);
            window.draw(chickenBomb);
        }

        if (Explosion.Boss2Explo)
        {
            Explosion.chickenBomb2.setPosition(boss2.getPosition().x, boss2.getPosition().y);
            Explosion.chickenBomb2.setScale(0.3, 0.3);
            window.draw(Explosion.chickenBomb2);
        }



        window.draw(ship);

        if (isShielded)
        {
            window.draw(shield);
        }

        window.draw(Setting);
        window.draw(boss);
        window.draw(boss2);

        window.draw(scoretex);
        window.draw(healthtex);
        window.draw(bomb);
        window.draw(gift);
        window.draw(star);

        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (!explo)
            {
                window.draw(bullets[i]);
            }
        }

        window.draw(egg1);
        window.draw(c_egg);
        window.draw(egg2);
        window.draw(c_egg2);
        window.draw(N_bomb);
        window.draw(c_egg3);
        window.draw(egg3);
        window.draw(c_egg4);
        window.draw(egg4);



        window.draw(fatengameover);
        window.draw(nextbuttongg);

        if (count == 4 && menuoption > 0)
        {
            window.draw(Emptymenu);
            window.draw(Optionstart);
            window.draw(Optionexit);

        }
        window.draw(fatenend);
        window.draw(nextbuttone);

        window.draw(gamebar);
        window.draw(scoretex);
        window.draw(healthtex);
        window.draw(werktex);
    }
    if (count == 5)
    {
        window.draw(gameEndingback);
        window.draw(credentials);
        window.draw(Back);

    }

}
void counterr(RenderWindow& window, int& count, int& levelcount, int& volcount, int& clicktimer, Texture& SoundBar, Texture& SoundBar2, Texture& SoundBar3, Texture& SoundBar4, Texture& SoundBar5, RectangleShape& soundbar, int& clicktimer2, bool& clicked, RectangleShape& fatenwelcome, int& yPos, RectangleShape& nextbutton, int& menuoption, RectangleShape& fatenwin, RectangleShape& nextbuttonl1, RectangleShape& nextbuttonl2, RectangleShape& fatengameover, RectangleShape& nextbuttongg, Sound& clicksound, Music& music, RectangleShape& credentials) {

    Vector2i mousePos = Mouse::getPosition(window);


    if (Mouse::isButtonPressed(Mouse::Left))
    {
        clicksound.play();
        clicktimer++;
        clicktimer2++;
        if (count == 2 && menuoption > 0) // start
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 500 && mousePos.y < 650)
            {
                menuoption = 0;
            }
        }

        if (count == 2 && menuoption > 0)// exit
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 750 && mousePos.y < 900)
            {
                window.close();
            }
        }

        if (count == 2 && menuoption > 0)  //menuea
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 250 && mousePos.y < 380)
            {
                menuoption = 0;
                count = 0;
                fatencounter = 0;
            }
        }


        if (count == 3 && menuoption > 0)  // start
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 500 && mousePos.y < 650)
            {
                menuoption = 0;
            }
        }

        if (count == 3 && menuoption > 0)  // exit
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 750 && mousePos.y < 900)
            {
                window.close();
            }
        }

        if (count == 3 && menuoption > 0) // menue
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 250 && mousePos.y < 380)
            {
                menuoption = 0;
                count = 0;
                fatencounter = 0;
            }
        }

        //if (fatencounter == 40 && count == 2) // level2 lock
        //{
        //    if (mousePos.x > 350 && mousePos.x < 700 && mousePos.y > 400 && mousePos.y < 700) {

        //        lockcounter = 1;    

        //    }
        //}



        //if (fatencounter == 40 && count == 3) // level3 lock
        //{
        //    if (mousePos.x > 350 && mousePos.x < 700 && mousePos.y > 400 && mousePos.y < 700) {


        //        lockcounter = 2;

        //    }
        //}





        if (count == 4 && menuoption > 0) // start
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 500 && mousePos.y < 650)
            {
                menuoption = 0;
            }
        }

        if (count == 4 && menuoption > 0) // exit
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 750 && mousePos.y < 900)
            {
                window.close();
            }
        }

        if (count == 4 && menuoption > 0) // menue
        {
            if (mousePos.x > 700 && mousePos.x < 1230 && mousePos.y > 250 && mousePos.y < 380)
            {
                menuoption = 0;
                count = 0;
                fatencounter = 0;
            }
        }






        if (count == 2)   // level 1
        {
            if (mousePos.x > 25 && mousePos.x < 80 && mousePos.y > 10 && mousePos.y < 80)
            {
                menuoption++;
            }
            //wining screen l1
            if (fatencounter == 40)
            {


                if (mousePos.x > 771 && mousePos.x < 1450 && mousePos.y > 750 && mousePos.y < 880)

                {
                    count = 1;
                    lockcounter = 1;
                    fatencounter = 0;

                    fatenwin.setPosition(305, 1600);
                    nextbuttonl1.setPosition(905, 1600);
                }
            }
            //gameover screen
            if (health == 0)
            {


                if (mousePos.x > 771 && mousePos.x < 1450 && mousePos.y > 750 && mousePos.y < 880)

                {
                    count = 1;
                    health = 4;


                    fatencounter = 0;

                    fatengameover.setPosition(305, 1600);
                    nextbuttongg.setPosition(905, 1600);
                }
            }
        }
        if (count == 3)   // level 2
        {
            if (mousePos.x > 25 && mousePos.x < 80 && mousePos.y > 10 && mousePos.y < 80)
            {
                menuoption++;
            }
            //wining
            if (fatencounter == 40)
            {
                if (mousePos.x > 771 && mousePos.x < 1450 && mousePos.y > 750 && mousePos.y < 880)

                {
                    count = 1;
                    lockcounter = 2;
                    fatencounter = 0;
                    fatenwin.setPosition(305, 1600);
                    nextbuttonl2.setPosition(905, 1600);
                }
            }
            //gameover screen
            if (health == 0)
            {


                if (mousePos.x > 771 && mousePos.x < 1450 && mousePos.y > 750 && mousePos.y < 880)

                {
                    count = 1;
                    health = 4;


                    fatencounter = 0;

                    fatengameover.setPosition(305, 1600);
                    nextbuttongg.setPosition(905, 1600);
                }
            }
        }

        if (count == 4)   // level 3
        {
            if (mousePos.x > 25 && mousePos.x < 80 && mousePos.y > 10 && mousePos.y < 80)
            {
                menuoption++;
            }
            //game endong screen
            if (mousePos.x > 521 && mousePos.x < 1200 && mousePos.y > 750 && mousePos.y < 880)

            {
                count = 5;
            }



            //gameover screen
            if (health == 0)
            {

                if (mousePos.x > 771 && mousePos.x < 1450 && mousePos.y > 750 && mousePos.y < 880)

                {
                    count = 1;
                    health = 4;
                    lockcounter = 2;

                    fatencounter = 0;

                    fatengameover.setPosition(305, 1600);
                    nextbuttongg.setPosition(905, 1600);
                }
            }
        }


        if (count == 5)  // options menu
        {
            if (mousePos.x > 25 && mousePos.x < 80 && mousePos.y > 10 && mousePos.y < 80)
            {
                count = 0;
                credentials.setPosition(0, 2300);

            }
        }

            if (count == -1)  // options menu
            {
                if (mousePos.x > 25 && mousePos.x < 80 && mousePos.y > 10 && mousePos.y < 80)
                {
                    count++;
                }

                // Increment volcount only if the click interval has elapsed



                if (mousePos.x > 258 && mousePos.x < 458 && mousePos.y > 456 && mousePos.y < 545)
                {
                    //cout << clicktimer; 
                    if (clicktimer >= 6)
                    {
                        if (volcount < 4)
                        {
                            volcount++;
                            // cout << "Volume: " << volcount << endl;
                        }
                        clicktimer = 0;
                    }
                }
                if (volcount == 1)
                {
                    soundbar.setTexture(&SoundBar2);
                    music.setVolume(25);

                }
                if (volcount == 2)
                {
                    soundbar.setTexture(&SoundBar3);
                    music.setVolume(50);

                }
                if (volcount == 3)
                {
                    soundbar.setTexture(&SoundBar4);
                    music.setVolume(75);

                }
                if (volcount == 4)
                {
                    soundbar.setTexture(&SoundBar);
                    music.setVolume(100);

                }

                if (mousePos.x > 1357 && mousePos.x < 1587 && mousePos.y > 456 && mousePos.y < 545)
                {
                    //cout << clicktimer;

                    if (clicktimer >= 6)
                    {
                        if (volcount <= 4 && volcount > 0)
                        {

                            volcount--;
                            // cout << "Volume: " << volcount << endl;
                        }
                        clicktimer = 0;
                    }
                }
                if (volcount == 3)
                {
                    soundbar.setTexture(&SoundBar2);
                    music.setVolume(75);

                }
                if (volcount == 2)
                {
                    soundbar.setTexture(&SoundBar3);
                    music.setVolume(50);

                }
                if (volcount == 1)
                {
                    soundbar.setTexture(&SoundBar4);
                    music.setVolume(25);

                }
                if (volcount == 0)
                {
                    soundbar.setTexture(&SoundBar5);
                    music.setVolume(0);

                }


                if (mousePos.x > 853 && mousePos.x < 993 && mousePos.y > 750 && mousePos.y < 874)
                {

                    soundbar.setTexture(&SoundBar5);
                    music.setVolume(0);


                }

            }


            else if (count == 0)  // main menue

            {

                if (mousePos.x > 650 && mousePos.x < 1190 && mousePos.y > 500 && mousePos.y < 650)

                {
                    // cout << clicktimer2 << endl;

                    clicked = true;
                    count++;
                    if (clicktimer2 > 5)
                    {
                        clicktimer2 = 0;
                    }

                }

                else if (mousePos.x > 650 && mousePos.x < 1190 && mousePos.y > 900 && mousePos.y < 1050)

                {
                    window.close();
                }

                else if (mousePos.x > 650 && mousePos.x < 1190 && mousePos.y > 700 && mousePos.y < 860)

                {

                    count--;
                }

            }

            else if (count == 1)  // planets menue

            {
                //welcoming screen

                if (mousePos.x > 771 && mousePos.x < 1450 && mousePos.y > 750 && mousePos.y < 880)

                {
                    fatenwelcome.setPosition(10000, 10000);
                    nextbutton.setPosition(10000, 10000);
                }


                if (mousePos.x > 70 && mousePos.x < 300 && mousePos.y > 70 && mousePos.y < 300)//earth

                {
                    count = 2;
                    levelcount = 1;
                    countercounter = 0;

                }

                else if (mousePos.x > 800 && mousePos.x < 1000 && mousePos.y > 500 && mousePos.y < 650 && count != 0 && lockcounter == 1) // planet2 

                {
                    if (clicktimer2 > 5)
                    {
                        count = 3;
                        countercounter = 1;
                        levelcount = 2;
                    }
                }

                else if (mousePos.x > 1600 && mousePos.x < 1800 && mousePos.y > 750 && mousePos.y < 1000 && lockcounter == 2) //planet 3

                {
                    count = 4;
                    levelcount = 3;
                    countercounter = 2;
                }

                else if (mousePos.x > 25 && mousePos.x < 80 && mousePos.y > 10 && mousePos.y < 80)

                {
                    count--;
                }

            }

        }

    }



int main() {

    srand(time(NULL));

    RenderWindow window(VideoMode(1920, 1080), "Chicken Invaders");

    //Texture mouseTexture;
    //mouseTexture.loadFromFile("textures/fork.png");
    //Cursor cursor;
    //cursor.loadFromPixels(mouseTexture.copyToImage().getPixelsPtr(), mouseTexture.getSize(), { 0, 0 });
    //window.setMouseCursor(cursor);


    window.setFramerateLimit(60);


    //variabls
    int count = 0;
    int counter = 0;
    bool clicked = false;


    const int CHICKEN_WIDTH = 568 * 0.2;

    bool isShot[NUM_BULLETS] = { false };

    bool isShielded = true;

    float fireTimer = 0.0;


    float shieldTimer = 0;
    bool ShieldRespawn = true;

    bool moveLeft1 = false;
    bool moveLeft2 = false;
    bool moveLeft3 = false;
    bool moveLeft4 = false;
    bool moveLeft5 = false;
    int menuoption = 0;
    int clicktimer = 0;
    int clicktimer2 = 0;
    int yPos = 0;
    float eggclock = 0.00000000f;
    float eggclock2 = 0.00000000f;
    float eggclock3 = 0.00000000f;
    float eggclock4 = 0.00000000f;
    Mouse mouse;



    //music
    Music music;
    music.openFromFile("textures/interstellar-space-117482.ogg");
    music.play();
    music.setVolume(50);
    music.setLoop(true);

    Music music2;
    music2.openFromFile("textures/Chicken invaders.ogg");
    music2.setVolume(50);
    music2.setLoop(true);

    //settings
    Texture setting;
    setting.loadFromFile("textures/settings.png");
    RectangleShape Setting;
    Setting.setTexture(&setting);
    Setting.setSize(Vector2f(288, 288));

    Setting.setScale(0.4, 0.4);



    //start2
    Texture optionstart;
    optionstart.loadFromFile("textures/Start2.png");
    RectangleShape Optionstart;
    Optionstart.setTexture(&optionstart);
    Optionstart.setPosition(700, 450);
    Optionstart.setSize(Vector2f(542, 215));

    //exit2
    Texture optionexit;
    optionexit.loadFromFile("textures/Exit2.png");
    RectangleShape Optionexit;
    Optionexit.setTexture(&optionexit);
    Optionexit.setPosition(680, 700);
    Optionexit.setSize(Vector2f(577, 228));


    //emptymenu
    Texture emptymenu;
    emptymenu.loadFromFile("textures/emptymenu.png");
    RectangleShape Emptymenu;
    Emptymenu.setTexture(&emptymenu);
    Emptymenu.setPosition(650, 200);
    Emptymenu.setScale(1.4, 1.4);
    Emptymenu.setSize(Vector2f(462, 540));





    //egg
    Texture texture_egg;
    texture_egg.loadFromFile("textures/egg.png");
    Sprite egg1;
    egg1.setTexture(texture_egg);
    egg1.setScale(0.03, 0.03);
    egg1.setPosition(-100, 100);


    Texture cracked_egg;
    cracked_egg.loadFromFile("textures/smashed egg.png");
    Sprite c_egg;
    c_egg.setTexture(cracked_egg);
    c_egg.setPosition(-400, 700);
    c_egg.setScale(1, 1);


    //egg2
    Texture texture_egg2;
    texture_egg2.loadFromFile("textures/egg.png");
    Sprite egg2;
    egg2.setTexture(texture_egg);
    egg2.setScale(0.03, 0.03);
    egg2.setPosition(-200, 900);

    Texture cracked_egg2;
    cracked_egg2.loadFromFile("textures/smashed egg.png");
    Sprite c_egg2;
    c_egg2.setTexture(cracked_egg2);
    c_egg2.setPosition(-400, 700);
    c_egg2.setScale(1, 1);



    //egg3

    Texture texture_egg3;
    texture_egg3.loadFromFile("textures/egg.png");
    Sprite egg3;
    egg3.setTexture(texture_egg);
    egg3.setScale(0.03, 0.03);
    egg3.setPosition(-1300, 100);


    Texture cracked_egg3;
    cracked_egg3.loadFromFile("textures/smashed egg.png");
    Sprite c_egg3;
    c_egg3.setTexture(cracked_egg3);
    c_egg3.setPosition(-400, 700);
    c_egg3.setScale(1, 1);

    //egg4

    Texture texture_egg4;
    texture_egg4.loadFromFile("textures/egg.png");
    Sprite egg4;
    egg4.setTexture(texture_egg4);
    egg4.setScale(0.03, 0.03);
    egg4.setPosition(-1300, 100);


    Texture cracked_egg4;
    cracked_egg4.loadFromFile("textures/smashed egg.png");
    Sprite c_egg4;
    c_egg4.setTexture(cracked_egg3);
    c_egg4.setPosition(-400, 700);
    c_egg4.setScale(1, 1);

    //egg5

    Texture texture_egg5;
    texture_egg5.loadFromFile("textures/egg.png");
    Sprite egg5;
    egg5.setTexture(texture_egg);
    egg5.setScale(0.03, 0.03);
    egg5.setPosition(-1300, 100);


    Texture cracked_egg5;
    cracked_egg5.loadFromFile("textures/smashed egg.png");
    Sprite c_egg5;
    c_egg5.setTexture(cracked_egg5);
    c_egg5.setPosition(-400, 700);
    c_egg5.setScale(1, 1);



    // bomb
    Texture  texture_bomb;
    texture_bomb.loadFromFile("textures/bomb.png");
    Sprite N_bomb;
    N_bomb.setTexture(texture_bomb);
    N_bomb.setScale(0, 0);

    bool bomb_egg = false;
    bool bomb_egg2 = false;
    bool bomb_egg3 = false;

    //Clock clockegg;
    //Clock clockegg2;
    //Clock clockegg3;
    //Clock clockegg4;
    //Clock clockegg5;




    //fork
    Texture textfork;
    textfork.loadFromFile("textures/fork.png");
    Sprite fork(textfork);
    fork.setScale(0.04, 0.04);

    //bullets
    Sprite bullets[NUM_BULLETS];

    Texture RedBullettex1;
    Texture RedBullettex2;
    Texture RedBullettex3;

    Texture BlueBullettex1;
    Texture BlueBullettex2;
    Texture BlueBullettex3;

    Texture GreenBullettex1;
    Texture GreenBullettex2;
    Texture GreenBullettex3;

    RedBullettex1.loadFromFile("textures/bullets 1.png");
    RedBullettex2.loadFromFile("textures/bullets 2.png");
    RedBullettex3.loadFromFile("textures/bullets 3.png");

    BlueBullettex1.loadFromFile("textures/blue bullet 1.png");
    BlueBullettex2.loadFromFile("textures/blue bullet 2.png");
    BlueBullettex3.loadFromFile("textures/blue bullet 3.png");

    GreenBullettex1.loadFromFile("textures/green bullet 1.png");
    GreenBullettex2.loadFromFile("textures/green bullet 2.png");
    GreenBullettex3.loadFromFile("textures/green bullet 3.png");

    for (int i = 0; i < NUM_BULLETS; i++)
    {
        bullets[i].scale(0.2, 0.2);
        bullets[i].setPosition(10000, 10000);
    }





    //gift
    Sprite gift;
    Texture gifttex;
    gifttex.loadFromFile("textures/gift.png");
    gift.setTexture(gifttex);
    //gift.setPosition(-50, -510);
    gift.setScale(0.35, 0.35);
    gift.setTextureRect(IntRect(0, 0, 256, 256));



    //star
    Sprite star;
    Texture startex;
    startex.loadFromFile("textures/atom.png");
    star.setTexture(startex);
    //star.setPosition(-50, -510);
    star.setScale(1, 1);
    star.setTextureRect(IntRect(0, 0, 98, 82));

    //rock
    Sprite redrocks;
    Texture rockstex;
    rockstex.loadFromFile("textures/asteroidFlame.png");
    redrocks.setScale(0.35, 0.35);
    redrocks.setRotation(315);
    redrocks.setTexture(rockstex);
    redrocks.setTextureRect(IntRect(0, 0, 256, 256));

    //grey rocks
    Sprite greyrocks;
    Texture greyrockstex;
    greyrockstex.loadFromFile("textures/asteroidNormal.png");
    greyrocks.setScale(0.35, 0.35);
    greyrocks.setRotation(45);
    greyrocks.setTexture(greyrockstex);
    greyrocks.setTextureRect(IntRect(0, 0, 256, 256));



    //shield
    Sprite shield;
    Texture Shield;
    Shield.loadFromFile("textures/Shield.png");
    shield.setTexture(Shield);
    shield.setPosition(shieldPos);


    //bomb
    Sprite bomb;
    Texture Bomb;
    Bomb.loadFromFile("textures/explosion.png");
    bomb.setTexture(Bomb);
    bomb.setScale(0, 0);
    bomb.setTextureRect(IntRect(0, 0, 256, 256));
    shield.setScale(0.38, 0.38);


    //chickens1

    Texture chickenTextureB;
    Texture chickenTextureR;
    Texture chickenTextureG;
    chickenTextureB.loadFromFile("textures/Chicken Sprite blue.png");
    chickenTextureR.loadFromFile("textures/Chicken.png");
    chickenTextureG.loadFromFile("textures/Chicken Sprite green.png");

    Sprite chickenSprites[NUM_CHICKENS];



    for (int i = 0; i < NUM_CHICKENS; i++)
    {
        chickenSprites[i].setTexture(chickenTextureR);
        chickenSprites[i].setPosition(200 + i * 200, 350); // Set the initial position of the chicken
        chickenSprites[i].setTextureRect(sf::IntRect(0, 0, 568, 479));
    }

    FloatRect bounds = chickenSprites[0].getGlobalBounds();
    float desiredSize = 100.0f; // Replace with your desired size
    float scaleX = desiredSize / bounds.width;
    float scaleY = desiredSize / bounds.height;

    for (int i = 0; i < NUM_CHICKENS; i++)
    {
        chickenSprites[i].setScale(scaleX, scaleY);
    }


    //chickens 2


    Sprite chickenSprites2[NUM_CHICKENS];
    for (int i = 0; i < NUM_CHICKENS; i++)
    {
        chickenSprites2[i].setTexture(chickenTextureR);
        chickenSprites2[i].setPosition(200 + i * 200, 235); // Set the initial position of the chicken
        chickenSprites2[i].setTextureRect(sf::IntRect(0, 0, 568, 479));
        chickenSprites2[i].setScale(scaleX, scaleY);
    }

    //chickens 3

    Sprite chickenSprites3[NUM_CHICKENS];
    for (int i = 0; i < NUM_CHICKENS; i++)
    {
        chickenSprites3[i].setTexture(chickenTextureR);
        chickenSprites3[i].setPosition(200 + i * 200, 100); // Set the initial position of the chicken
        chickenSprites3[i].setTextureRect(sf::IntRect(0, 0, 537, 479));
        chickenSprites3[i].setScale(scaleX, scaleY);
    }

    Sprite chickenSprites4[NUM_CHICKENS];
    for (int i = 0; i < NUM_CHICKENS; i++) {
        chickenSprites4[i].setTexture(chickenTextureB);
        chickenSprites4[i].setPosition(200 + i * 200, 450); // Set the initial position of the chicken
        chickenSprites4[i].setTextureRect(IntRect(0, 0, 537, 479));
        chickenSprites4[i].setScale(scaleX, scaleY);
    }



    Sprite chickenSprites5[NUM_CHICKENS];
    for (int i = 0; i < NUM_CHICKENS; i++) {
        chickenSprites5[i].setTexture(chickenTextureG);
        chickenSprites5[i].setPosition(200 + i * 200, 550); // Set the initial position of the chicken
        chickenSprites5[i].setTextureRect(IntRect(0, 0, 537, 479));
        chickenSprites5[i].setScale(scaleX, scaleY);
    }



    bool collisionchicken[NUM_CHICKENS] = { false };
    for (int i = 0; i < 8; i++) {
        collisionchicken[i] = false;
    }


    bool collisionchicken2[NUM_CHICKENS] = { false };
    for (int i = 0; i < 8; i++) {
        collisionchicken2[i] = false;
    }

    bool collisionchicken3[NUM_CHICKENS] = { false };
    for (int i = 0; i < 8; i++) {
        collisionchicken3[i] = false;
    }


    bool collisionchicken4[NUM_CHICKENS] = { false };
    for (int i = 0; i < 8; i++) {
        collisionchicken4[i] = false;
    }

    bool collisionchicken5[NUM_CHICKENS] = { false };
    for (int i = 0; i < 8; i++) {
        collisionchicken5[i] = false;
    }



    //werk
    Texture tex_werk;
    tex_werk.loadFromFile("textures/werk.png");
    Sprite werk[NUM_CHICKENS];
    for (int i = 0; i < 8; i++) {
        werk[i].setTexture(tex_werk);
        werk[i].setScale(0.15, 0.15);
        werk[i].setPosition(chickenSprites[i].getPosition().x, chickenSprites[i].getPosition().y + 32);
        werk[i].setTextureRect(IntRect(0, 0, 403, 430));
    }
    bool check_werk[NUM_CHICKENS] = {};

    for (int i = 0; i < 8; i++) {
        check_werk[i] = false;
    }

    // werk2
    Texture tex_werk2;
    tex_werk2.loadFromFile("textures/werk.png");
    Sprite werk2[NUM_CHICKENS];
    for (int i = 0; i < 8; i++) {
        werk2[i].setTexture(tex_werk2);
        werk2[i].setScale(0.15, 0.15);
        werk2[i].setPosition(chickenSprites2[i].getPosition().x, chickenSprites2[i].getPosition().y + 32);
        werk2[i].setTextureRect(IntRect(0, 0, 403, 430));
    }
    bool check_werk2[NUM_CHICKENS] = {};

    for (int i = 0; i < 8; i++) {
        check_werk2[i] = false;
    }


    // werk3   
    Texture tex_werk3;
    tex_werk3.loadFromFile("textures/werk.png");
    Sprite werk3[NUM_CHICKENS];
    for (int i = 0; i < 8; i++) {
        werk3[i].setTexture(tex_werk3);
        werk3[i].setScale(0.15, 0.15);
        werk3[i].setPosition(chickenSprites3[i].getPosition().x, chickenSprites3[i].getPosition().y + 32);
        werk3[i].setTextureRect(IntRect(0, 0, 403, 430));
    }
    bool check_werk3[NUM_CHICKENS] = {};

    for (int i = 0; i < 8; i++) {
        check_werk3[i] = false;
    }


    // werk4
    Texture tex_werk4;
    tex_werk4.loadFromFile("textures/werk.png");
    Sprite werk4[NUM_CHICKENS];
    for (int i = 0; i < 8; i++) {
        werk4[i].setTexture(tex_werk4);
        werk4[i].setScale(0.15, 0.15);
        werk4[i].setPosition(chickenSprites4[i].getPosition().x, chickenSprites4[i].getPosition().y + 32);
        werk4[i].setTextureRect(IntRect(0, 0, 403, 430));
    }

    // werk5
    Texture tex_werk5;
    tex_werk4.loadFromFile("textures/werk.png");
    Sprite werk5[NUM_CHICKENS];
    for (int i = 0; i < 8; i++) {
        werk5[i].setTexture(tex_werk4);
        werk5[i].setScale(0.15, 0.15);
        werk5[i].setPosition(chickenSprites5[i].getPosition().x, chickenSprites5[i].getPosition().y + 32);
        werk5[i].setTextureRect(IntRect(0, 0, 403, 430));

    }

    //boss
    Texture Boss;
    Boss.loadFromFile("textures/boss.png");
    BossStruct.boss.setTexture(Boss);
    BossStruct.boss.setPosition(bossPos);
    BossStruct.boss.setTextureRect(IntRect(0, 0, 256, 256));
    BossStruct.boss.scale(1.8, 1.8);


    //boss2
    Texture Boss2;
    Boss2.loadFromFile("textures/boss.png");
    BossStruct.boss2.setTexture(Boss2);
    BossStruct.boss2.setPosition(bossPos2);
    BossStruct.boss2.setTextureRect(IntRect(0, 0, 256, 256));
    BossStruct.boss2.scale(1.8, 1.8);

    //ship

    Texture shiptex;
    shiptex.loadFromFile("textures/ship sheet beta.png");
    Sprite ship;
    ship.setPosition(shipPos);
    ship.setTexture(shiptex);
    ship.setTextureRect(IntRect(ShipShieldStruct.x * 256, ShipShieldStruct.y * 256, 256, 256));
    ship.scale(0.5, 0.5);

    //back button

    Texture back;
    back.loadFromFile("textures/xButton1.png");
    RectangleShape Back;
    Back.setTexture(&back);
    Back.setPosition(0, 0);
    Back.setSize(Vector2f(331, 329));
    Back.setScale(0.3, 0.3);


    //option menu

    Texture option;
    option.loadFromFile("textures/option background.png");
    Sprite Option;
    Option.setTexture(option);
    //Option.setScale(2, 2);

    //volume buttons
    Texture GreenButton;
    GreenButton.loadFromFile("textures/volume up.png");
    RectangleShape greenbutton;
    greenbutton.setTexture(&GreenButton);
    greenbutton.setPosition(350, 440);
    greenbutton.setSize(Vector2f(120, 120));


    Texture RedButton;
    RedButton.loadFromFile("textures/volume down.png");
    RectangleShape redbutton;
    redbutton.setTexture(&RedButton);
    redbutton.setPosition(1470, 440);
    redbutton.setSize(Vector2f(120, 120));

    Texture MuteButton;
    MuteButton.loadFromFile("textures/mute.png");
    RectangleShape mutebutton;
    mutebutton.setTexture(&MuteButton);
    mutebutton.setPosition(900, 740);
    mutebutton.setSize(Vector2f(120, 120));

    Texture SoundBar;
    SoundBar.loadFromFile("textures/soundbar100.png");
    RectangleShape soundbar;
    soundbar.setTexture(&SoundBar);
    soundbar.setPosition(465, 470);
    soundbar.setSize(Vector2f(1000, 70));


    Texture VolumeText;
    VolumeText.loadFromFile("textures/volume text.png");
    RectangleShape volumetext;
    volumetext.setTexture(&VolumeText);
    volumetext.setPosition(555, 130);
    volumetext.setSize(Vector2f(800, 400));


    Texture SoundBar2;
    SoundBar2.loadFromFile("textures/soundbar75.png");


    Texture SoundBar3;
    SoundBar3.loadFromFile("textures/soundbar50.png");

    Texture SoundBar4;
    SoundBar4.loadFromFile("textures/soundbar25.png");


    Texture SoundBar5;
    SoundBar5.loadFromFile("textures/soundbar00.png");


    // welcoming screen


    Texture FatenWelcome;
    FatenWelcome.loadFromFile("textures/faten welcome.png");
    RectangleShape fatenwelcome;
    fatenwelcome.setTexture(&FatenWelcome);
    fatenwelcome.setPosition(305, 1600);
    fatenwelcome.setSize(Vector2f(1260, 1040));


    Texture NextButton;
    NextButton.loadFromFile("textures/next.png");
    RectangleShape nextbutton;
    nextbutton.setTexture(&NextButton);
    nextbutton.setPosition(905, 1600);
    nextbutton.setSize(Vector2f(552, 203));


    Texture NextButtonl1;
    NextButtonl1.loadFromFile("textures/next.png");
    RectangleShape nextbuttonl1;
    nextbuttonl1.setTexture(&NextButtonl1);
    nextbuttonl1.setPosition(905, 1600);
    nextbuttonl1.setSize(Vector2f(552, 203));


    Texture NextButtonl2;
    NextButtonl2.loadFromFile("textures/next.png");
    RectangleShape nextbuttonl2;
    nextbuttonl2.setTexture(&NextButtonl2);
    nextbuttonl2.setPosition(905, 1600);
    nextbuttonl2.setSize(Vector2f(552, 203));

    Texture NextButtonE;
    NextButtonE.loadFromFile("textures/next.png");
    RectangleShape nextbuttone;
    nextbuttone.setTexture(&NextButtonE);
    nextbuttone.setPosition(655, 1600);
    nextbuttone.setSize(Vector2f(552, 203));

    //  fatenwelcome.setScale(1.35, 1.35);

      //level 1

    Texture earth;
    earth.loadFromFile("textures/earth.png");
    Sprite Earth;
    Earth.setTexture(earth);

    //level 1 background

    Texture level1back;
    level1back.loadFromFile("textures/234234234.png");
    Sprite Level1back;
    Level1back.setTexture(level1back);
    //Level1back.setScale(1.5, 1.5);


    //level 2 background

    Texture level2back;
    level2back.loadFromFile("textures/redblue.png");
    Sprite Level2back;
    Level2back.setTexture(level2back);
    //Level2back.setScale(2.1, 2.1);
    //Level2back.setPosition(20, -1000);

    //level 3 background

    Texture level3back;
    level3back.loadFromFile("textures/mars.png");
    Sprite Level3back;
    Level3back.setTexture(level3back);
    //Level3back.setScale(1.3, 1.3);

    //level 2

    Texture planet;
    planet.loadFromFile("textures/planet 2.png");
    Sprite Planet;
    Planet.setTexture(planet);
    Planet.setPosition(800, 400);


    //level 3

    Texture planet2;
    planet2.loadFromFile("textures/planet 3.png");
    Sprite Planet2;
    Planet2.setTexture(planet2);
    Planet2.setPosition(1550, 750);

    //level backgorund

    Texture levelback;
    levelback.loadFromFile("textures/background.jpg");
    Sprite Levelback;
    Levelback.setTexture(levelback);

    // Levelback.setScale(4, 4);

     //back ground

    Texture background;
    background.loadFromFile("textures/extended level1 back.png");
    Sprite Menu[2];
    for (int i = 0; i < 2; i++) {
        Menu[i].setTexture(background);
        Menu[i].setPosition(Vector2f(0, i * 1080));
    }


    //game ending back
    

    Texture GameEndingBack;
    GameEndingBack.loadFromFile("textures/background1.jpg");
    Sprite gameEndingback;
    gameEndingback.setTexture(GameEndingBack);



    //Menu.setScale(0.5, 0.5);

    //start button

    Texture button;
    button.loadFromFile("textures/play_button.png");
    RectangleShape Button;
    Button.setTexture(&button);
    Button.setPosition(650, 500);
    Button.setSize(Vector2f(550, 150));

    //Boss explo
    Texture ChickenBomb;
    ChickenBomb.loadFromFile("textures/boss explosion.png");
    Explosion.chickenBomb.setTexture(ChickenBomb);
    Explosion.chickenBomb.setScale(0, 0);
    Explosion.chickenBomb.setTextureRect(IntRect(0, 0, 766, 811));

    //Boss explo2
    Texture ChickenBomb2;
    ChickenBomb2.loadFromFile("textures/boss explosion.png");
    Explosion.chickenBomb2.setTexture(ChickenBomb2);
    Explosion.chickenBomb2.setScale(0, 0);
    Explosion.chickenBomb2.setTextureRect(IntRect(0, 0, 766, 811));

    //logo

    Texture logo;
    logo.loadFromFile("textures/Logo.png");
    Sprite Logo;
    Logo.setTexture(logo);
    Logo.setPosition(500, 20);
    Logo.setScale(1.4, 1.4);

    //exit button

    Texture exit;
    exit.loadFromFile("textures/quit_buttom.png");
    RectangleShape Exit;
    Exit.setTexture(&exit);
    Exit.setPosition(650, 900);
    Exit.setSize(Vector2f(550, 150));

    //options button

    Texture options;
    options.loadFromFile("textures/options_button.png");
    RectangleShape Options;
    Options.setTexture(&options);
    Options.setPosition(650, 700);
    Options.setSize(Vector2f(550, 150));



    //score


    font.loadFromFile("textures/maginors-maginors-400.otf");

    Text scoretex;
    string scorestring = to_string(score);
    scoretex.setFont(font);
    scoretex.setString(to_string(score));

    scoretex.setScale(1.2, 1.2);
    scoretex.setPosition(190, 1030);
    scoretex.setFillColor(Color::Cyan);

    //health

    Text healthtex;
    string healthstring = to_string(health);
    healthtex.setFont(font);
    healthtex.setString(healthstring);
    healthtex.setScale(1.2, 1.2);
    healthtex.setPosition(70, 1030);
    healthtex.setFillColor(Color::Cyan);

    //werkcounter

    Text werktex;
    string werkstring = to_string(werkcounter);
    werktex.setFont(font);
    werktex.setString(werkstring);
    werktex.setScale(1.2, 1.2);
    werktex.setPosition(395, 1030);
    werktex.setFillColor(Color::Cyan);

    //faten win
    Texture FatenWin;
    FatenWin.loadFromFile("textures/faten win.png");
    RectangleShape fatenwin;
    fatenwin.setTexture(&FatenWin);
    fatenwin.setPosition(305, 1600);
    fatenwin.setSize(Vector2f(1260, 1040));


    //faten ending screen
     
    Texture FatenEnd;
    FatenEnd.loadFromFile("textures/faten ending.png");
    RectangleShape fatenend;
    fatenend.setTexture(&FatenEnd);
    fatenend.setPosition(305, 1600);
    fatenend.setSize(Vector2f(1260, 1040));


    //credentials

    Texture Credentials;
    Credentials.loadFromFile("textures/crew members.png");
    RectangleShape credentials;
    credentials.setTexture(&Credentials);
    credentials.setPosition (0, 2300);
    credentials.setSize(Vector2f(1920, 1080));


    //faten gameover
    Texture FatenGameover;
    FatenGameover.loadFromFile("textures/faten gameover.png");
    RectangleShape fatengameover;
    fatengameover.setTexture(&FatenGameover);
    fatengameover.setPosition(305, 1600);
    fatengameover.setSize(Vector2f(1260, 1040));


    Texture NextButtonGG;
    NextButtonGG.loadFromFile("textures/next.png");
    RectangleShape nextbuttongg;
    nextbuttongg.setTexture(&NextButtonGG);
    nextbuttongg.setPosition(905, 1600);
    nextbuttongg.setSize(Vector2f(552, 203));

    //game bar  
    Sprite gamebar;
    Texture GameBar;
    GameBar.loadFromFile("textures/game bar.png");

    gamebar.setTexture(GameBar);
    gamebar.setPosition(-4, 980);

    //sounds
       //sound laser
    SoundBuffer laserbuffer;
    laserbuffer.loadFromFile("textures/neutronGun.wav");
    Sound lasersound;
    lasersound.setBuffer(laserbuffer);

    //***********************************************************
//sound blue bullets
    SoundBuffer bluebuffer;
    bluebuffer.loadFromFile("textures/ionBlaster.wav");
    Sound bluesound;
    bluesound.setBuffer(bluebuffer);
    //********************************************************
    //sound green bullets
    SoundBuffer greenbuffer;
    greenbuffer.loadFromFile("textures/hypergun.wav");
    Sound greensound;
    greensound.setBuffer(greenbuffer);
    //************************************************************

    //sound chicken
    SoundBuffer chickenbuffer;
    chickenbuffer.loadFromFile("textures/ChickenHit.wav");
    Sound chickensound;
    chickensound.setBuffer(chickenbuffer);


    //eating
    SoundBuffer eatingbuffer;
    eatingbuffer.loadFromFile("textures/eat.wav");
    Sound eatingsound;
    eatingsound.setBuffer(eatingbuffer);


    //explosion
    SoundBuffer explobuffer;
    explobuffer.loadFromFile("textures/explosion.wav");
    Sound explosound;
    explosound.setBuffer(explobuffer);


    //click
    SoundBuffer clickbuffer;
    clickbuffer.loadFromFile("textures/click.wav");
    Sound clicksound;
    clicksound.setBuffer(clickbuffer);




    while (window.isOpen()) {

        DeltaTime = GameClock.restart().asSeconds();


        //  cout<<DeltaTime<<endl;

        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {

                window.close();

            }

        }

        eggclock += DeltaTime;
        eggclock2 += DeltaTime;
        eggclock3 += DeltaTime;
        eggclock4 += DeltaTime;


        for (int i = 0; i < 2; i++)
        {
            Menu[i].move(Vector2f(0, -0.6));
        }
        if (Menu[0].getPosition().y <= -1080 - 1) {
            Menu[0].setPosition(Vector2f(0, 1080 - 1));

        }
        else if (Menu[1].getPosition().y <= -1080 - 1) {
            Menu[1].setPosition(Vector2f(0, 1080 - 1));
        }


        if (count == 0)
        {
            music2.stop();

            if (music.getStatus() != sf::Music::Playing) {
                music.play();
            }
        }
       

       if (count == 5)
        {
            music.stop();

            if (music2.getStatus() != sf::Music::Playing) {
                music2.play();
            }
        }

        //faten win

        if (fatencounter == 40) {

            if (count == 2)
            {

                fatenwin.move(0, -1000.0f * DeltaTime);
                nextbuttonl1.move(0, -1000.0f * DeltaTime);
            }
            if (fatenwin.getPosition().y < 50)
            {
                fatenwin.setPosition(fatenwin.getPosition().x, 50);
            }

            if (nextbuttonl1.getPosition().y < 700)
            {
                nextbuttonl1.setPosition(nextbuttonl1.getPosition().x, 700);

            }
        }


        if (fatencounter == 40) {

            if (count == 3)
            {

                fatenwin.move(0, -1000.0f * DeltaTime);
                nextbuttonl2.move(0, -1000.0f * DeltaTime);
            }
            if (fatenwin.getPosition().y < 50)
            {
                fatenwin.setPosition(fatenwin.getPosition().x, 50);
            }

            if (nextbuttonl2.getPosition().y < 700)
            {
                nextbuttonl2.setPosition(nextbuttonl2.getPosition().x, 700);

            }

        }



        if (fatencounter == 0)
        {
            fatenwin.setPosition(305, 1600);
            fatengameover.setPosition(305, 1600);
        }



        if (fatencounter == 40 ) {

            //cout << "hena" << endl;
            if (count == 4)
            {

                fatenend.move(0, -1000.0f * DeltaTime);
                nextbuttone.move(0, -1000.0f * DeltaTime);
            }
            if (fatenend.getPosition().y < 50)
            {
                fatenend.setPosition(fatenend.getPosition().x, 50);
            }

            if (nextbuttone.getPosition().y < 700)
            {
                nextbuttone.setPosition(nextbuttone.getPosition().x, 700);

            }

        }

        if (count == 5)
        {
            //cout << "hereeeeeeeeeeeeeee" << endl;
            credentials.move(0, -90.0f * DeltaTime);
            
        }

        

        //score
        string healthstring = to_string(health);
        healthtex.setString(healthstring);
        string scorestring = to_string(score);
        scoretex.setString(to_string(score));
        string werkstring = to_string(werkcounter);
        werktex.setString(werkstring);

        //
        if (health == 0)
        {
            if (count == 2)
            {

                fatengameover.move(0, -1000.0f * DeltaTime);
                nextbuttongg.move(0, -1000.0f * DeltaTime);
            }
            if (fatengameover.getPosition().y < 50)
            {
                fatengameover.setPosition(fatengameover.getPosition().x, 50);
            }

            if (nextbuttongg.getPosition().y < 700)
            {
                nextbuttongg.setPosition(nextbuttongg.getPosition().x, 700);

            }
        }


        if (health == 0)
        {
            if (count == 3)
            {

                fatengameover.move(0, -1000.0f * DeltaTime);
                nextbuttongg.move(0, -1000.0f * DeltaTime);
            }
            if (fatengameover.getPosition().y < 50)
            {
                fatengameover.setPosition(fatengameover.getPosition().x, 50);
            }

            if (nextbuttongg.getPosition().y < 700)
            {
                nextbuttongg.setPosition(nextbuttongg.getPosition().x, 700);

            }
        }


        if (health == 0)
        {
            if (count == 4)
            {

                fatengameover.move(0, -1000.0f * DeltaTime);
                nextbuttongg.move(0, -1000.0f * DeltaTime);
            }
            if (fatengameover.getPosition().y < 50)
            {
                fatengameover.setPosition(fatengameover.getPosition().x, 50);
            }

            if (nextbuttongg.getPosition().y < 700)
            {
                nextbuttongg.setPosition(nextbuttongg.getPosition().x, 700);

            }
        }

        //if (BossStruct.HpBoss == 0)
        //{
        //    score += 500;
        //    BossStruct.HpBoss = -1;
        //}


        if (count == 1)
        {
            fatenwelcome.move(0, -1000.0f * DeltaTime);
            nextbutton.move(0, -1000.0f * DeltaTime);

        }


        if (fatenwelcome.getPosition().y < 50)
        {
            fatenwelcome.setPosition(fatenwelcome.getPosition().x, 50);

        }
        if (nextbutton.getPosition().y < 700)
        {
            nextbutton.setPosition(nextbutton.getPosition().x, 700);

        }



        // cout << redrockTimer << endl;

         //bullets update
        if (levelcount == 1)
        {


            for (int i = 0; i < 8; i++)
            {
                chickenSprites3[i].setScale(scaleX, scaleY);
                chickenSprites3[i].setPosition(200 + i * 200, 100);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites2[i].setPosition(200 + i * 200, 235);
                chickenSprites2[i].setScale(scaleX, scaleY);
            }

            for (int i = 0; i < 8; i++)
            {
                chickenSprites[i].setScale(scaleX, scaleY);
                chickenSprites[i].setPosition(200 + i * 200, 350);
            }

            for (int i = 0; i < 8; i++)
            {
                chickenSprites5[i].setPosition(200 + i * 200, 550);
                chickenSprites5[i].setScale(scaleX, scaleY);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites4[i].setPosition(200 + i * 200, 450);
                chickenSprites4[i].setScale(scaleX, scaleY);
            }
            //cout << levelcount << endl;




            for (int i = 0; i < 8; i++) {
                collisionchicken[i] = false;
            }



            for (int i = 0; i < 8; i++) {
                collisionchicken2[i] = false;
            }


            for (int i = 0; i < 8; i++) {
                collisionchicken3[i] = false;
            }




            for (int i = 0; i < 8; i++) {
                collisionchicken4[i] = false;
                for (int i = 0; i < 8; i++) {
                    collisionchicken5[i] = false;
                }

            }

            moveChickens(window, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, NUM_CHICKENS, CHICKEN_WIDTH, moveLeft1, moveLeft2, moveLeft3, moveLeft4, moveLeft5, isShot, bullets, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, chickensound,ship, Explosion.explo);
            updateEgg(window, egg1, egg2, egg3, egg4, egg5, ship, bomb, c_egg, c_egg2, c_egg3, c_egg4, c_egg5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, NUM_CHICKENS, Explosion.explotimer, Explosion.explo, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer, f_rand, s_rand, t_rand, forth_rand, fifth_rand, eggclock, eggclock2, eggclock3, eggclock4);

            move_werk(window, ship, werk, werk2, werk3, werk4, werk5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, eatingsound);
            levelcount = 0;
        }

        if (levelcount == 2)
        {
            for (int i = 0; i < 8; i++)
            {
                chickenSprites3[i].setScale(scaleX, scaleY);
                chickenSprites3[i].setPosition(200 + i * 200, 100);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites2[i].setPosition(200 + i * 200, 235);
                chickenSprites2[i].setScale(scaleX, scaleY);
            }

            for (int i = 0; i < 8; i++)
            {
                chickenSprites[i].setScale(scaleX, scaleY);
                chickenSprites[i].setPosition(200 + i * 200, 350);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites5[i].setPosition(200 + i * 200, 550);
                chickenSprites5[i].setScale(scaleX, scaleY);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites4[i].setPosition(200 + i * 200, 450);
                chickenSprites4[i].setScale(scaleX, scaleY);
            }

            //  cout << levelcount << endl;




            for (int i = 0; i < 8; i++) {
                collisionchicken[i] = false;
            }



            for (int i = 0; i < 8; i++) {
                collisionchicken2[i] = false;
            }


            for (int i = 0; i < 8; i++) {
                collisionchicken3[i] = false;
            }




            for (int i = 0; i < 8; i++) {
                collisionchicken4[i] = false;
            }
            for (int i = 0; i < 8; i++) {
                collisionchicken5[i] = false;
            }


            moveChickens(window, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, NUM_CHICKENS, CHICKEN_WIDTH, moveLeft1, moveLeft2, moveLeft3, moveLeft4, moveLeft5, isShot, bullets, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, chickensound, ship, Explosion.explo);
            move_werk(window, ship, werk, werk2, werk3, werk4, werk5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, eatingsound);
            updateEgg(window, egg1, egg2, egg3, egg4, egg5, ship, bomb, c_egg, c_egg2, c_egg3, c_egg4, c_egg5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, NUM_CHICKENS, Explosion.explotimer, Explosion.explo, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer, f_rand, s_rand, t_rand, forth_rand, fifth_rand, eggclock, eggclock2, eggclock3, eggclock4);


            levelcount = 0;
        }



        if (levelcount == 3)
        {


            for (int i = 0; i < 8; i++)
            {
                chickenSprites3[i].setScale(scaleX, scaleY);
                chickenSprites3[i].setPosition(200 + i * 200, 100);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites2[i].setPosition(200 + i * 200, 235);
                chickenSprites2[i].setScale(scaleX, scaleY);
            }

            for (int i = 0; i < 8; i++)
            {
                chickenSprites[i].setScale(scaleX, scaleY);
                chickenSprites[i].setPosition(200 + i * 200, 350);
            }

            for (int i = 0; i < 8; i++)
            {
                chickenSprites5[i].setPosition(200 + i * 200, 550);
                chickenSprites5[i].setScale(scaleX, scaleY);
            }
            for (int i = 0; i < 8; i++)
            {
                chickenSprites4[i].setPosition(200 + i * 200, 450);
                chickenSprites4[i].setScale(scaleX, scaleY);
            }
            // cout << levelcount << endl;




            for (int i = 0; i < 8; i++) {
                collisionchicken[i] = false;
            }



            for (int i = 0; i < 8; i++) {
                collisionchicken2[i] = false;
            }


            for (int i = 0; i < 8; i++) {
                collisionchicken3[i] = false;
            }




            for (int i = 0; i < 8; i++) {
                collisionchicken4[i] = false;
                for (int i = 0; i < 8; i++) {
                    collisionchicken5[i] = false;
                }

            }

            moveChickens(window, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, NUM_CHICKENS, CHICKEN_WIDTH, moveLeft1, moveLeft2, moveLeft3, moveLeft4, moveLeft5, isShot, bullets, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, chickensound, ship, Explosion.explo);
            updateEgg(window, egg1, egg2, egg3, egg4, egg5, ship, bomb, c_egg, c_egg2, c_egg3, c_egg4, c_egg5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, NUM_CHICKENS, Explosion.explotimer, Explosion.explo, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer, f_rand, s_rand, t_rand, forth_rand, fifth_rand, eggclock, eggclock2, eggclock3, eggclock4);

            BossAnimation(BossStruct.boss, BossStruct.randx, BossStruct.randy, ship, Explosion.explo, isShielded, bomb, Explosion.explotimer, shield, bullets, Explosion.BossExplo, BULLets.chBull, Explosion.chickenBomb, BossStruct.BossAppeartimer);
            BossAnimation2(BossStruct.boss2, BossStruct.randx2, BossStruct.randy2, ship, Explosion.explo, isShielded, bomb, Explosion.explotimer, shield, bullets, Explosion.Boss2Explo, BULLets.chBull, Explosion.chickenBomb2, BossStruct.Boss2Appeartimer);

            exp(BossStruct.boss2);
            Bossexplo(BossStruct.boss);
            move_werk(window, ship, werk, werk2, werk3, werk4, werk5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, eatingsound);
            levelcount = 0;
        }






        // new function for eggs



        //ship move
        explosion(Explosion.explo, ship, bomb, Explosion.explotimer, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer,explosound);

        exp(BossStruct.boss2);
        Bossexplo(BossStruct.boss);
        //mouse in

        counterr(window, count, levelcount, volcount, clicktimer, SoundBar, SoundBar2, SoundBar3, SoundBar4, SoundBar5, soundbar, clicktimer2, clicked, fatenwelcome, yPos, nextbutton, menuoption, fatenwin, nextbuttonl1, nextbuttonl2, fatengameover, nextbuttongg, clicksound,music,credentials);

        //rocks
//cout<<menuoption<<endl;

        //draw
       // cout << countercounter << endl;
        //cout << fatencounter << endl;
     //   cout << levelcount << endl;
        window.clear();
        drawObjects(window, count, Option, Back, Menu, Button, Logo, Exit, Options, Levelback, Earth, Planet, Planet2, Level1back, Level2back, Level3back, ship, chickenSprites, chickenSprites2, chickenSprites3, star, gift, bullets, Explosion.explo, redrocks, greyrocks, bomb, shield, isShielded, BossStruct.boss, Explosion.chickenBomb, Explosion.BossExplo, greenbutton, redbutton, soundbar, mutebutton, volumetext, fatenwelcome, nextbutton, werk, werk2, werk3, BossStruct.boss2, Setting, menuoption, Optionstart, Optionexit, Emptymenu, chickenSprites4, chickenSprites5, egg1, egg2, egg3, egg4, c_egg, c_egg2, c_egg3, c_egg4, N_bomb, werk4, werk5, scoretex, healthtex, fatenwin, gamebar, werktex, nextbuttonl1, nextbuttonl2, fatengameover, nextbuttongg, fatenend, nextbuttone, gameEndingback, credentials);
        fork.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        hover(window, Button, mouse, Earth, Planet, Planet2, Exit, Options, greenbutton, redbutton, mutebutton, nextbutton,  nextbuttonl1,  nextbuttonl2, nextbuttongg, nextbuttone, Optionexit, Optionstart, Emptymenu, Setting,Back);

        if (countercounter == 0)
        {
            shipmove(ship, Explosion.explo, shield, shieldTimer, isShielded);
            updateEgg(window, egg1, egg2, egg3, egg4, egg5, ship, bomb, c_egg, c_egg2, c_egg3, c_egg4, c_egg5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, NUM_CHICKENS, Explosion.explotimer, Explosion.explo, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer, f_rand, s_rand, t_rand, forth_rand, fifth_rand, eggclock, eggclock2, eggclock3, eggclock4);
            Bullets(bullets, ship, fireTimer, isShot, BULLets.ctrBull, BULLets.chBull, RedBullettex1, RedBullettex2, RedBullettex3, GreenBullettex1, GreenBullettex2, GreenBullettex3, BlueBullettex1, BlueBullettex2, BlueBullettex3, lasersound,greensound,bluesound);
            starMovemnt(star, ship, StarGift.startimer, BULLets.ctrBull);
            move_werk(window, ship, werk, werk2, werk3, werk4, werk5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, eatingsound);
            moveChickens(window, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, NUM_CHICKENS, CHICKEN_WIDTH, moveLeft1, moveLeft2, moveLeft3, moveLeft4, moveLeft5, isShot, bullets, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, chickensound, ship, Explosion.explo);
        }


        else   if (countercounter == 1)
        {
            shipmove(ship, Explosion.explo, shield, shieldTimer, isShielded);
            Bullets(bullets, ship, fireTimer, isShot, BULLets.ctrBull, BULLets.chBull, RedBullettex1, RedBullettex2, RedBullettex3, GreenBullettex1, GreenBullettex2, GreenBullettex3, BlueBullettex1, BlueBullettex2, BlueBullettex3, lasersound, greensound, bluesound);
            RedRockMovement(redrocks, ship, BULLets.ctrBull, Rocks.redrockTimer, bomb, Explosion.explo, Explosion.explotimer, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer);
            GreyRockMovement(greyrocks, ship, BULLets.ctrBull, Rocks.greyRockTimer, Explosion.explo, bomb, Explosion.explotimer, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer);
            GiftMovement(gift, ship, BULLets.chBull, StarGift.gifttimer);
            moveChickens(window, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, NUM_CHICKENS, CHICKEN_WIDTH, moveLeft1, moveLeft2, moveLeft3, moveLeft4, moveLeft5, isShot, bullets, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, chickensound, ship, Explosion.explo);
            updateEgg(window, egg1, egg2, egg3, egg4, egg5, ship, bomb, c_egg, c_egg2, c_egg3, c_egg4, c_egg5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, NUM_CHICKENS, Explosion.explotimer, Explosion.explo, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer, f_rand, s_rand, t_rand, forth_rand, fifth_rand, eggclock, eggclock2, eggclock3, eggclock4);

            starMovemnt(star, ship, StarGift.startimer, BULLets.ctrBull);
            move_werk(window, ship, werk, werk2, werk3, werk4, werk5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, eatingsound);

        }
        else if (countercounter == 2)
        {
            shipmove(ship, Explosion.explo, shield, shieldTimer, isShielded);
            updateEgg(window, egg1, egg2, egg3, egg4, egg5, ship, bomb, c_egg, c_egg2, c_egg3, c_egg4, c_egg5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, NUM_CHICKENS, Explosion.explotimer, Explosion.explo, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer, f_rand, s_rand, t_rand, forth_rand, fifth_rand, eggclock, eggclock2, eggclock3, eggclock4);
            moveChickens(window, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, NUM_CHICKENS, CHICKEN_WIDTH, moveLeft1, moveLeft2, moveLeft3, moveLeft4, moveLeft5, isShot, bullets, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, chickensound, ship, Explosion.explo);
            move_werk(window, ship, werk, werk2, werk3, werk4, werk5, chickenSprites, chickenSprites2, chickenSprites3, chickenSprites4, chickenSprites5, collisionchicken, collisionchicken2, collisionchicken3, collisionchicken4, collisionchicken5, eatingsound);
            RedRockMovement(redrocks, ship, BULLets.ctrBull, Rocks.redrockTimer, bomb, Explosion.explo, Explosion.explotimer, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer);
            GreyRockMovement(greyrocks, ship, BULLets.ctrBull, Rocks.greyRockTimer, Explosion.explo, bomb, Explosion.explotimer, shield, isShielded, Explosion.BossExplo, BossStruct.boss, Explosion.chickenBomb, BossStruct.BossAppeartimer);

            Bullets(bullets, ship, fireTimer, isShot, BULLets.ctrBull, BULLets.chBull, RedBullettex1, RedBullettex2, RedBullettex3, GreenBullettex1, GreenBullettex2, GreenBullettex3, BlueBullettex1, BlueBullettex2, BlueBullettex3, lasersound, greensound, bluesound);
            BossAnimation(BossStruct.boss, BossStruct.randx, BossStruct.randy, ship, Explosion.explo, isShielded, bomb, Explosion.explotimer, shield, bullets, Explosion.BossExplo, BULLets.chBull, Explosion.chickenBomb, BossStruct.BossAppeartimer);
            BossAnimation2(BossStruct.boss2, BossStruct.randx2, BossStruct.randy2, ship, Explosion.explo, isShielded, bomb, Explosion.explotimer, shield, bullets, Explosion.Boss2Explo, BULLets.chBull, Explosion.chickenBomb2, BossStruct.Boss2Appeartimer);
            Bossexplo(BossStruct.boss);
            exp(BossStruct.boss2);
            GiftMovement(gift, ship, BULLets.chBull, StarGift.gifttimer);
            starMovemnt(star, ship, StarGift.startimer, BULLets.ctrBull);



        }


        window.setMouseCursorVisible(false);

        window.draw(fork);

        window.display();

    }

    return 0;

}
