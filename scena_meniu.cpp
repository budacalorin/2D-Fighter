#include "scena_meniu.h"
#include <cstring>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "init.h"


void scena_meniu::adaugare_optiune(const char *s)
{
    strcpy(optiuni[++numar_optiuni],s);
}

void scena_meniu::input_tastatura()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type==sf::Event::KeyReleased)
        {
            if (event.key.code==sf::Keyboard::Up)
            {
                up=1;
                down=0;
            }

            if (event.key.code==sf::Keyboard::Down)
            {
                up=0;
                down=1;
            }

            if (event.key.code==sf::Keyboard::Enter)
            {
                enter=1;
            }
            if (event.key.code==sf::Keyboard::Left)
            {
                left=1;
                right=0;
            }
            if (event.key.code==sf::Keyboard::Right)
            {
                right=1;
                left=0;
            }

        }

        if (event.type==sf::Event::Closed)
        {
            game_on=0;
        }
    }
}

void scena_meniu::deplasare()
{
    if (up==1)
    {
        optiune_curenta--;
        if(optiune_curenta==0)
            optiune_curenta=1;
        up=0;
    }
    if (down==1)
    {
        optiune_curenta++;
        if (optiune_curenta==numar_optiuni+1)
            optiune_curenta=numar_optiuni;
        down=0;
    }
    if (enter==1)
    {
        actiune();
        enter=0;
    }
    if (right)
    {
        numar_playeri++;
        if (numar_playeri>4)
            numar_playeri=4;
        right=0;
    }
    if (left)
    {
        numar_playeri--;
        if (numar_playeri<2)
            numar_playeri=2;
        left=0;
    }
}

void scena_meniu::draw()
{
    window.clear();
    window.draw(background);
    afisare_optiuni();
    window.display();
}

void scena_meniu::afisare_optiuni()
{
    int x_optiuni=200;
    int y_optiuni=hight-numar_optiuni*110;
    for (int i=1; i<=numar_optiuni; i++)
    {
        sf::Text text;
        text.setString(optiuni[i]);
        text.setCharacterSize (80);
        text.setPosition(sf::Vector2f(x_optiuni,y_optiuni));
        y_optiuni+=90;
        text.setFillColor(sf::Color::Black);
        if (optiune_curenta==i)
        {
            text.setFillColor(sf::Color::White);

            text.setStyle(sf::Text::Underlined);
        }
        sf::Font arial;
        arial.loadFromFile ("arial.ttf");
        text.setFont (arial);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        window.draw(text);
    }
}

void scena_meniu::update()
{
    input_tastatura();
    deplasare();
    draw();
}

void scena_meniu::actiune()
{
    if (strstr(optiuni[optiune_curenta],"PLAY"))
    {
        scena_curenta=3;
    }
    if (strstr(optiuni[optiune_curenta],"EXIT"))
    {
        game_on=0;
    }

}

