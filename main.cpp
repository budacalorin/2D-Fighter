#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "bloc.h"
#include "init.h"
#include "scena_joc.h"
#include "scena_meniu.h"
using namespace std;


bool game_on=1;
int hight=768;
int width=1366;
int scena_curenta=1;
float coeficient_frecare=0.90;
float gravitatie=0.7;
int cooldown_puteri=500000;
int viata_proiectile=500000;
float viteza_proiectile=7;
int damage_paricula_la_busire_perete=3;
float viteza_player=3.5;
int putere_saritura=15;
int inaltime_healthbar=30;
float coeficient_healthbar=2.5;
int damage_proiectil_player=10;
int inaltime_ground=498;
int hp_player=200;
int dimensiune_proiectile_x=100;
int dimensiune_proiectile_y=100;


scena_meniu meniu_principal;
scena_joc joc_principal;
sf::RectangleShape border;
sf::RectangleShape viata_1;
sf::RectangleShape viata_2;
sf::Texture background_texture;
sf::Texture *p_background_texture;
sf::RectangleShape background;
sf::RectangleShape viata_1_border;
sf::RectangleShape viata_2_border;sf::Texture textura_1;
sf::Texture *p_textura_1;
sf::Texture *p_textura_2;
sf::Texture textura_2;
sf::Texture player_1_tag;
sf::Texture player_2_tag;
sf::Texture texturi_fireball[29];



sf::Texture p1_p2_np3_p4_p5_p6;
sf::Texture np5;
sf::Texture np1_p2_np3_p4_p5_p6;
sf::Texture np1_p2_p3_p4_p5_p6;
sf::Texture p1_p2_p3_p4_p5_p6;
sf::Texture p4_p5_p6;
sf::Texture p4_p5_np6;
sf::Texture np4_p5_p6;
sf::Texture np2_np4_p5_np6;
sf::Texture p2_np4_p5_np6;
sf::Texture p2_np4_p5_p6;
sf::Texture p2_p4_p5_np6;
sf::Texture p2_p4_p5_p6_np8;
sf::Texture np2_p4_p5_p6_np8;

sf::Texture p2_p4_p5_np6_np8;
sf::Texture p2_np4_p5_p6_np8;

sf::Texture *p_np2_np4_p5_np6_np8;
sf::Texture np2_np4_p5_np6_np8;

sf::Texture *p_p1_p2_np3_p4_p5_p6;
sf::Texture *p_np5;
sf::Texture *p_np1_p2_np3_p4_p5_p6;
sf::Texture *p_np1_p2_p3_p4_p5_p6;
sf::Texture *p_p1_p2_p3_p4_p5_p6;
sf::Texture *p_p4_p5_p6;
sf::Texture *p_p4_p5_np6;
sf::Texture *p_np4_p5_p6;
sf::Texture *p_np2_np4_p5_np6;
sf::Texture *p_p2_np4_p5_np6;
sf::Texture *p_p2_np4_p5_p6;
sf::Texture *p_p2_p4_p5_np6;
sf::Texture *p_p2_p4_p5_p6_np8;
sf::Texture *p_np2_p4_p5_p6_np8;

sf::Texture *p_p2_p4_p5_np6_np8;
sf::Texture *p_p2_np4_p5_p6_np8;

sf::Texture np2_np4_p5_p6_np8;
sf::Texture *p_np2_np4_p5_p6_np8;
sf::Texture np2_p4_p5_np6_np8;
sf::Texture *p_np2_p4_p5_np6_np8;
sf::Texture p2_np4_p5_np6_np8;
sf::Texture *p_p2_np4_p5_np6_np8;


void init_fireball();
/////////////////////////////////////////////////////////////

sf::RenderWindow window(sf::VideoMode(width,hight),"",sf::Style::Fullscreen);
sf::Clock ceas_general;

int main()
{
    window.setFramerateLimit(60);
    init_fireball();
    meniu_principal.adaugare_optiune("PLAY");
    meniu_principal.adaugare_optiune("EXIT");
    border.setPosition(sf::Vector2f(width/10*10,0));
    border.setSize(sf::Vector2f(width-width/10*10,hight));
    border.setFillColor(sf::Color::Black);
    viata_1.setPosition(sf::Vector2f(100,100));
    viata_1.setFillColor(sf::Color::Red);
    viata_2.setFillColor(sf::Color::Red);
    viata_2.setPosition(sf::Vector2f(width-100,100+inaltime_healthbar));
    viata_2.setRotation(180);
    viata_1_border.setPosition(sf::Vector2f(100,100));
    viata_1_border.setFillColor(sf::Color::Transparent);
    viata_2_border.setFillColor(sf::Color::Transparent);
    viata_2_border.setPosition(sf::Vector2f(width-100,100+inaltime_healthbar));
    viata_2_border.setRotation(180);
    viata_1_border.setOutlineColor(sf::Color(91,110,225));
    viata_1_border.setOutlineThickness(5);
    viata_2_border.setOutlineColor(sf::Color(64,64,64));
    viata_2_border.setOutlineThickness(5);
    viata_1_border.setSize(sf::Vector2f(hp_player*coeficient_healthbar,inaltime_healthbar));
    viata_2_border.setSize(sf::Vector2f(hp_player*coeficient_healthbar,inaltime_healthbar));

    textura_1.loadFromFile("img/player-spritemap-v9.png");
    //textura_1.setSmooth(1);
    p_textura_1=&textura_1;
   textura_2.loadFromFile("img/player-spritemap-v9_player_2.png");
    //textura_1.setSmooth(1);
    p_textura_2=&textura_2;


    player_1_tag.loadFromFile("img/player_1_tag.png");
    player_2_tag.loadFromFile("img/player_2_tag.png");

    background_texture.loadFromFile("img/background_1_1.png");
    //background.setFillColor(sf::Color::Black);
    p_background_texture=&background_texture;
    background.setTexture(p_background_texture);
    background.setSize(sf::Vector2f(width,hight));


    np5.loadFromFile("img/np5.png");
    p_np5=&np5;
    p1_p2_np3_p4_p5_p6.loadFromFile("img/p1_p2_np3_p4_p5_p6.png");
    p_p1_p2_np3_p4_p5_p6=&p1_p2_np3_p4_p5_p6;
    np1_p2_np3_p4_p5_p6.loadFromFile("img/np1_p2_np3_p4_p5_p6.png");
    p_np1_p2_np3_p4_p5_p6=&np1_p2_np3_p4_p5_p6;
    np1_p2_p3_p4_p5_p6.loadFromFile("img/np1_p2_p3_p4_p5_p6.png");
    p_np1_p2_p3_p4_p5_p6=&np1_p2_p3_p4_p5_p6;
    p1_p2_p3_p4_p5_p6.loadFromFile("img/p1_p2_p3_p4_p5_p6.png");
    p_p1_p2_p3_p4_p5_p6=&p1_p2_p3_p4_p5_p6;
    p4_p5_p6.loadFromFile("img/p4_p5_p6.png");
    p_p4_p5_p6=&p4_p5_p6;
    p4_p5_np6.loadFromFile("img/p4_p5_np6.png");
    p_p4_p5_np6=&p4_p5_np6;
    np4_p5_p6.loadFromFile("img/np4_p5_p6.png");
    p_np4_p5_p6=&np4_p5_p6;
    np2_np4_p5_np6.loadFromFile("img/np2_np4_p5_np6.png");
    p_np2_np4_p5_np6=&np2_np4_p5_np6;
    p2_np4_p5_np6.loadFromFile("img/p2_np4_p5_np6.png");
    p_p2_np4_p5_np6=&p2_np4_p5_np6;
    p2_np4_p5_p6.loadFromFile("img/p2_np4_p5_p6.png");
    p_p2_np4_p5_p6=&p2_np4_p5_p6;
    p2_p4_p5_np6.loadFromFile("img/p2_p4_p5_np6.png");
    p_p2_p4_p5_np6=&p2_p4_p5_np6;
    p2_p4_p5_p6_np8.loadFromFile("img/p2_p4_p5_p6_np8.png");;
    p_p2_p4_p5_p6_np8=&p2_p4_p5_p6_np8;
    np2_p4_p5_p6_np8.loadFromFile("img/np2_p4_p5_p6_np8.png");
    p_np2_p4_p5_p6_np8=&np2_p4_p5_p6_np8;
    p2_p4_p5_np6_np8.loadFromFile("img/p2_p4_p5_np6_np8.png");
    p_p2_p4_p5_np6_np8=&p2_p4_p5_np6_np8;
    p2_np4_p5_p6_np8.loadFromFile("img/p2_np4_p5_p6_np8.png");
    p_p2_np4_p5_p6_np8=&p2_np4_p5_p6_np8;

    np2_np4_p5_p6_np8.loadFromFile("img/np2_np4_p5_p6_np8.png");
    p_np2_np4_p5_p6_np8=&np2_np4_p5_p6_np8;
    np2_p4_p5_np6_np8.loadFromFile("img/np2_p4_p5_np6_np8.png");
    p_np2_p4_p5_np6_np8=&np2_p4_p5_np6_np8;
    p2_np4_p5_np6_np8.loadFromFile("img/p2_np4_p5_np6_np8.png");
    p_p2_np4_p5_np6_np8=&p2_np4_p5_np6_np8;

    np2_np4_p5_np6_np8.loadFromFile("img/np2_np4_p5_np6_np8.png");
    p_np2_np4_p5_np6_np8=&np2_np4_p5_np6_np8;

    sf::Clock ceas;
    sf::Clock c;
    int fps=0;
    int timp_per_frame=1000000/60;
    while (game_on)
    {
        fps++;
        if (c.getElapsedTime().asSeconds()>=1)
        {
            c.restart();
            cout << fps << endl;
            fps=0;
        }
        int timp=ceas.getElapsedTime().asMicroseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)==1)
            game_on=0;
        if (scena_curenta==1)
        {
            meniu_principal.update();
        }
        if (scena_curenta==3)
        {
            joc_principal.reset(meniu_principal.numar_playeri);
            scena_curenta=2;
        }
        if (scena_curenta==2)
        {
            joc_principal.update();
        }


        if (ceas.getElapsedTime().asMicroseconds()-timp<timp_per_frame)
            sf::sleep(sf::microseconds(timp_per_frame-(ceas.getElapsedTime().asMicroseconds()-timp)));
    }

    return 0;
}
