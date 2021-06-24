#include "../include/animatie.h"
#include <iostream>
animatie::animatie()
{
    //ctor
}

void animatie::setup(sf::Texture* texture,sf::Vector2u image_coun,float switch_tim)
{
    this->image_count=image_coun;
    this->switch_time=switch_tim;
    total_time=0;
    curent_image.x=0;

    uv_rect.width=texture->getSize().x/(float)image_count.x;
    uv_rect.height=texture->getSize().y/(float)image_count.y;
}

void animatie::update(int &row,float delta_time,bool dreapta,int stay)
{
    if (row!=curent_image.y&&row!=3)
        curent_image.x=0;
    curent_image.y=row;
    total_time+=delta_time;

    if (total_time>=switch_time)
    {
        total_time-=switch_time;
        if (stay==0)
        curent_image.x++;

        if (curent_image.x>=image_count.x)
        {
            curent_image.x=0;
            if (row==2)
                row=1,curent_image.y=row;
        }
    }

    uv_rect.top=curent_image.y*uv_rect.height;
    if (dreapta)
    {
        uv_rect.left=curent_image.x*uv_rect.width;
        uv_rect.width=abs(uv_rect.width);
    }
    else
    {
        uv_rect.left=(curent_image.x+1)*abs(uv_rect.width);
        uv_rect.width=-abs(uv_rect.width);
    }
}
