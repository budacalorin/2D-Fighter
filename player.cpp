#include "player.h"
#include "init.h"
#include <iostream>
void coliziune_verticala(sf::RectangleShape &forma,bloc blocuri[],int numar_blocuri,float &viteza_y);
void coliziune_orizontala(sf::RectangleShape &forma,bloc blocuri[],int numar_blocuri,float &viteza_x);


void player::set_positioin(int x,int y)
{
    forma.setPosition(sf::Vector2f(x,y));
    sprite.setScale(sf::Vector2f(2,2));
    forma.setFillColor(sf::Color::Black);
    sprite.setOrigin(sf::Vector2f(46/2,50/2));

}

void player::set_texture(sf::Texture *texture)
{
    textura=texture;
}

void player::set_size(int x,int y)
{
    forma.setSize(sf::Vector2f(x,y));
}

void player::miscare(bloc blocuri[],int numar_blocuri)
{
    viteza_x*=coeficient_frecare;
    viteza_y+=gravitatie;
    if (viteza_y>15)
        viteza_y=15;
    //viteza_y*=coeficient_frecare;
    if (viteza_x<0.01&&viteza_x>-0.01)
        viteza_x=0;
    if (viteza_y<0.01&&viteza_y>-0.01)
        viteza_y=0;

    forma.move(sf::Vector2f(viteza_x,0));
    coliziune_orizontala(forma,blocuri,numar_blocuri,viteza_x);

    forma.move(sf::Vector2f(0,viteza_y));
    coliziune_verticala(forma,blocuri,numar_blocuri,viteza_y);

    int y=forma.getPosition().y;
    if (forma.getPosition().y>=hight)
        forma.setPosition(sf::Vector2f(forma.getPosition().x,0-forma.getSize().y));
    if (forma.getPosition().y<-forma.getSize().y-1)
        forma.setPosition(sf::Vector2f(forma.getPosition().x,hight));

    for (int i=1; i<=numar_blocuri; i++)
    {
        if (blocuri[i].alive==1)
            if (forma.getGlobalBounds().intersects(blocuri[i].forma.getGlobalBounds()))
            {
                forma.setPosition(forma.getPosition().x,y);
            }
    }
    int x=forma.getPosition().x;
    if (forma.getPosition().x>width)
        forma.setPosition(sf::Vector2f(0-forma.getSize().x,forma.getPosition().y));
    if (forma.getPosition().x<-forma.getSize().x)
        forma.setPosition(sf::Vector2f(width,forma.getPosition().y));
    for (int i=1; i<=numar_blocuri; i++)
    {
        if (blocuri[i].alive==1)
            if (forma.getGlobalBounds().intersects(blocuri[i].forma.getGlobalBounds()))
            {
                forma.setPosition(x,forma.getPosition().y);

            }
    }

}

void player::setTaste (sf::Keyboard::Key su,sf::Keyboard::Key jo,sf::Keyboard::Key st,sf::Keyboard::Key dr,sf::Keyboard::Key act,sf::Keyboard::Key aim_su,sf::Keyboard::Key aim_jo,sf::Keyboard::Key aim_st,sf::Keyboard::Key aim_dr)
{
    action=act;
    sus=su;
    jos=jo;
    stanga=st;
    dreapta=dr;
    aim_sus=aim_su;
    aim_jos=aim_jo;
    aim_stanga=aim_st;
    aim_dreapta=aim_dr;
}

void player::deplasare(bloc blocuri[],int numar_blocuri)
{
    if (sf::Keyboard::isKeyPressed(sus))
    {
        int ok=1;
        forma.move(0,1);
        for (int i=1; i<=numar_blocuri; i++)
        {
            if (forma.getGlobalBounds().intersects(blocuri[i].forma.getGlobalBounds())&&blocuri[i].alive)
            {
                ok=0;
                break;
            }
        }
        forma.move(0,-1);
        if (ok==0)
            viteza_y=-putere_saritura;
    }
    if (sf::Keyboard::isKeyPressed(jos))
    {
        if (viteza_y<pixel_miscare)
            viteza_y=pixel_miscare;
    }
    if (sf::Keyboard::isKeyPressed(stanga))
    {
        viteza_x=-pixel_miscare;
    }
    if (sf::Keyboard::isKeyPressed(dreapta))
    {
        viteza_x=pixel_miscare;
    }
    if (sf::Keyboard::isKeyPressed(action)&&cooldown_putere_1<=0)
    {
        declansare_putere_1=1;
    }
    if (sf::Keyboard::isKeyPressed(aim_sus))
    {
        a_sus=1;
        a_jos=a_st=a_dr=0;
    }

    if (sf::Keyboard::isKeyPressed(aim_jos))
    {
        a_jos=1;
        a_sus=a_st=a_dr=0;
    }

    if (sf::Keyboard::isKeyPressed(aim_stanga))
    {
        directie_dreapta=0;
        a_st=1;
        a_jos=a_sus=a_dr=0;
    }

    if (sf::Keyboard::isKeyPressed(aim_dreapta))
    {
        directie_dreapta=1;
        a_dr=1;
        a_jos=a_st=a_sus=0;
    }



}
void player::init_animatie(sf::Vector2u vector2u,float switch_time)
{
    animatia.setup(textura,vector2u,switch_time);
}

void player::actualizare_textura(int timp_trecut)
{
    int stay=0;
    if (viteza_x>0.5||viteza_x<-0.5)
    {
        row=3;
        animatia.image_count.x=8;
        animatia.switch_time=70000;
        if (viteza_x<0)
            directie_dreapta=0;
        else
            directie_dreapta=1;
    }
    if (!(viteza_x>0.5||viteza_x<-0.5))
    {
        if (row!=2)
        {
            row=1;
            animatia.image_count.x=3;
            animatia.switch_time=100000;
        }
    }
    if (sf::Keyboard::isKeyPressed(action)&&cooldown_putere_1==0||cooldown_putere_1==cooldown_puteri)
    {
        stay=0;
        animatia.curent_image.x=0;
        row=2;
        animatia.image_count.x=3;
        animatia.switch_time=150000;
    }
    else
    {
        stay=0;
    }
    if (viteza_y!=0)
    {
        if (viteza_y<0)
            animatia.curent_image.x=6;
        else
            animatia.curent_image.x=7;

        row=0;
        animatia.image_count.x=8;
        animatia.switch_time=100000;
        stay=1;
    }
    animatia.update(row,(float)timp_trecut,directie_dreapta,stay);

    sprite.setTextureRect(animatia.uv_rect);
    forma.setTextureRect(animatia.uv_rect);
    sprite.setPosition(sf::Vector2f(forma.getPosition().x+forma.getSize().x/2,forma.getPosition().y+forma.getSize().y/2));
}

void player::set_tag_texture(sf::Texture *texture)
{
    tag.setTexture(texture);
    tag.setSize(sf::Vector2f(50,16.5));
}
