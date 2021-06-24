#include <SFML/Graphics.hpp>
#include "player.h"
#include "proiectil.h"
#include "particula.h"
#include "init.h"
#include <cmath>
#include <cstring>
#include <iostream>

bool coliziune_player(sf::RectangleShape forma,bloc blocuri[],int numar_blocuri)
{
    for (int i=1;i<=numar_blocuri;i++)
    if (forma.getGlobalBounds().intersects(blocuri[i].forma.getGlobalBounds())&&blocuri[i].alive)
        return 1;
    return 0;
}
void adaugare_proiectil(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,proiectil proiectile[],int &numar_proiectile,int indice_proprietar)
{
    //std::cout <<numar_proiectile <<std::endl;
    for (int i=1;i<=numar_proiectile;i++)
    {

        if (proiectile[i].alive()==0)
        {
            //std::cout << "da\n\n\n\n\n";
            proiectile[i].setup(x,y,viteza_x,viteza_y,unghi,countdown,indice_proprietar);
            proiectile[i].hp=50;
            return;
        }
    }
    //std::cout << "dA\n";

    proiectile[++numar_proiectile].setup(x,y,viteza_x,viteza_y,unghi,countdown,indice_proprietar);
    proiectile[numar_proiectile].hp=50;
}
void adaugare_particula(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,particula particule[],int &numar_particule,int indice_proprietar)
{
    //std::cout <<numar_proiectile <<std::endl;
    for (int i=1;i<=numar_particule;i++)
    {

        if (particule[i].alive()==0)
        {
            //std::cout << "da\n\n\n\n\n";
            particule[i].setup(x,y,viteza_x,viteza_y,unghi,countdown,indice_proprietar);
            particule[i].hp=50;
            return;
        }
    }
    //std::cout << "dA\n";

    particule[++numar_particule].setup(x,y,viteza_x,viteza_y,unghi,countdown,indice_proprietar);
    particule[numar_particule].hp=50;
}

void coliziune_orizontala(sf::RectangleShape &forma,bloc blocuri[],int numar_blocuri,float &viteza_x)
{
    int ok=1;
    while (coliziune_player(forma,blocuri,numar_blocuri))
    {
        if (ok)
        {
            ok=0;
            forma.move(sf::Vector2f(-(forma.getPosition().x-(int)forma.getPosition().x),0));
        }
        else
        {
            forma.move(sf::Vector2f(-viteza_x/abs(viteza_x),0));
        }
    }
    if (ok==0)
    {
        viteza_x=0;
    }
}

void coliziune_verticala(sf::RectangleShape &forma,bloc blocuri[],int numar_blocuri,float &viteza_y)
{
    int ok=1;
    while (coliziune_player(forma,blocuri,numar_blocuri))
    {
        if (ok)
        {
            ok=0;
            forma.move(sf::Vector2f(0,-(forma.getPosition().y-(int)forma.getPosition().y)));
        }
        else
        {
            forma.move(sf::Vector2f(0,-viteza_y/abs(viteza_y)));
        }
    }
    if (ok==0)
        viteza_y=0;
}

void init_fireball()
{
    for (int i=1;i<=28;i++)
    {
        char s[40]={0};
        strcpy(s,"img/fireball/Effects_Fire_0_");
        char v[5]={0};
        if (i<10)
            v[0]='0';
        else
            v[0]=i/10+'0';
        v[1]=i%10+'0';
        v[2]=NULL;
        strcat(s,v);
        strcat(s,".png");
        texturi_fireball[i].loadFromFile(s);
    }
}
