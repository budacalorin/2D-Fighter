#include "particula.h"
#include "init.h"
#include <cmath>
#include <iostream>
particula::particula()
{
    forma.setSize(sf::Vector2f(2,2));
    forma.setFillColor(sf::Color::Red);
}

void particula::setup(int x,int y,float viteza_Y,float viteza_X,int UNGHI, int COUNTDOWN,int indice_proprietaR)
{
    viteza_x=viteza_X;
    viteza_y=viteza_Y;
    unghi=UNGHI;
    countdown=COUNTDOWN;
    forma.setPosition(sf::Vector2f(x,y));
    indice_proprietar=indice_proprietaR;
    numar_victime=0;

}

void particula::miscare()
{
    if (countdown)
    {
        float sin_unghi=-sin(unghi*3.14/180);
        float cos_unghi=cos(unghi*3.14/180);
        //std::cout << sin_unghi<< " " << cos_unghi <<std::endl;
        forma.move(sf::Vector2f(cos_unghi*viteza_x,sin_unghi*viteza_y));
    }
    if (forma.getPosition().x>width+forma.getSize().x+10)
        forma.setPosition(sf::Vector2f(0-forma.getSize().x/2,forma.getPosition().y));
    if (forma.getPosition().x<0-forma.getSize().x-10)
        forma.setPosition(sf::Vector2f(width+forma.getSize().x/2,forma.getPosition().y));
    if (forma.getPosition().y>hight+forma.getSize().y+10)
        forma.setPosition(sf::Vector2f(forma.getPosition().x,0-forma.getSize().y/2));
    if (forma.getPosition().y<0-forma.getSize().y-10)
        forma.setPosition(sf::Vector2f(forma.getPosition().x,hight+forma.getSize().y/2));

}

void particula::test_colizune()
{
    if (countdown<=0)
        viteza_x=viteza_y=0;
    if (hp<=0)
        viteza_x=viteza_y=0;

}

bool particula::alive()
{
    if (viteza_x!=0)
        return 1;
    if (viteza_y!=0)
        return 1;
    return 0;

}

void particula::adaugare_victime(int x)
{
    victime[++numar_victime]=x;
}

bool particula::verificare_victima(int x)
{
    for (int i=1;i<=numar_victime;i++)
        if (victime[i]==x)
            return 1;
    return 0;
}
