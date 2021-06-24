#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "bloc.h"
#include "include/animatie.h"

using namespace std;


class player
{
public:
    sf::RectangleShape forma;
    sf::Sprite sprite;
    float viteza_x,viteza_y;
    float cooldown_putere_1;
    float pixel_miscare;
    int hp=200;
    sf::Texture *textura;
    sf::RectangleShape tag;
    sf::Keyboard::Key sus,jos,stanga,dreapta,action;
    sf::Keyboard::Key aim_sus,aim_jos,aim_stanga,aim_dreapta;
    bool declansare_putere_1;
    bool a_sus,a_jos,a_st,a_dr;
    bool alive;
    bool directie_dreapta;
    animatie animatia;
    int row=1;

    void set_positioin(int x,int y);

    void set_texture(sf::Texture *texture);

    void setTaste (sf::Keyboard::Key su,sf::Keyboard::Key jo,sf::Keyboard::Key st,sf::Keyboard::Key dr,sf::Keyboard::Key act,sf::Keyboard::Key aim_su,sf::Keyboard::Key aim_jo,sf::Keyboard::Key aim_st,sf::Keyboard::Key aim_dr);

    void set_size(int x,int y);

    void miscare(bloc blocuri[],int numar_blocuri);

    void deplasare(bloc blocuri[],int numar_blocuri);

    void actualizare_textura(int timp_trecut);

    void init_animatie(sf::Vector2u vector2u,float switch_time);

    void set_tag_texture(sf::Texture *texture);
};

#endif
