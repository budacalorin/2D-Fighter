#include "bloc.h"
#include "init.h"
#include <iostream>
using namespace std;
void bloc::update_texture(int matrice[100][100])
{
    int i=forma.getPosition().y/forma.getSize().y;
    int j=forma.getPosition().x/forma.getSize().x;
    //cout << i << " " << j <<endl;
    bool p1,p2,p3,p4,p5,p6;
    bool p7,p8,p9;
    p1=p2=p3=p4=p5=p6=false;
    p6=p7=p8=p9=false;
    p1=matrice[i-1][j-1];
    p2=matrice[i-1][j];
    p3=matrice[i-1][j+1];
    p4=matrice[i][j-1];
    p5=matrice[i][j];
    p6=matrice[i][j+1];
    p7=matrice[i+1][j-1];
    p8=matrice[i+1][j];
    p9=matrice[i+1][j+1];

    if (p5==0)
        {forma.setTexture(p_np5);return;}
    if (p5&&!p2&&!p4&&!p6&&!p8)
    {
        forma.setTexture(p_np2_np4_p5_np6_np8);
        return;
    }
    if (p2&&p4&&p5&&p6&&!p8)
    {
        forma.setTexture(p_p2_p4_p5_p6_np8);
        return;
    }

    if (!p1&&p2&&!p3&&p4&&p5&&p6)
        {forma.setTexture(p_np1_p2_np3_p4_p5_p6);return;}

    if (!p1&&p2&&p3&&p4&&p5&&p6)
        {forma.setTexture(p_np1_p2_p3_p4_p5_p6);return;}

    if (p1&&p2&&!p3&&p4&&p5&&p6)
        {forma.setTexture(p_p1_p2_np3_p4_p5_p6);return;}

    if (p1&&p2&&p3&&p4&&p5&&p6)
        {forma.setTexture(p_p1_p2_p3_p4_p5_p6);return;}

    if (p2&&p4&&p5&&!p6&&!p8)
    {
        forma.setTexture(p_p2_p4_p5_np6_np8);
        return;
    }

    if (p2&&!p4&&p5&&p6&&p8)
    {
        forma.setTexture(p_p2_np4_p5_p6);
        return;
    }

    if (!p2&&p4&&p5&&p6&&p8)
        {forma.setTexture(p_p4_p5_p6);return;}

    if (!p2&&p4&&p5&&p6&&!p8)
    {
        forma.setTexture(p_np2_p4_p5_p6_np8);
        return;
    }



    if (!p2&&p4&&p5&&!p6&&!p8)
    {
        forma.setTexture(p_np2_p4_p5_np6_np8);
        return;
    }
    if (!p2&&!p4&&p5&&p6&&!p8)
    {
        forma.setTexture(p_np2_np4_p5_p6_np8);
        return;

    }




    if (p2&&!p4&&p6&&!p8)
    {
        forma.setTexture(p_p2_np4_p5_p6_np8);
        return;
    }

    if (p1&&p2&&p4&&p5&&!p6)
        {forma.setTexture(p_p2_p4_p5_np6);return;}

    if (!p2&&p4&&p5&&!p6)
        {forma.setTexture(p_p4_p5_np6);return;}









        if (p2&&!p4&&p5&&!p6&&!p8)
    {
        forma.setTexture(p_p2_np4_p5_np6_np8);
        return;
    }





    if (p5&&p6)
    {
        if (p2)
        {
            forma.setTexture(p_p2_np4_p5_p6);
        }
        else
            forma.setTexture(p_np4_p5_p6);
        return;
    }
    if (p5&&!p2&&!p4&&!p6)
    {
        forma.setTexture(p_np2_np4_p5_np6);
        return;
    }
    if (p5&&!p4&&!p6&&p2)
    {
        forma.setTexture(p_p2_np4_p5_np6);
        return;
    }
    if (p5&&p2&&!p4&&p6)
    {
        forma.setTexture(p_p2_np4_p5_p6);
        return;
    }
    if (p2&&p4&&p5&&!p6)
    {
        forma.setTexture(p_p2_p4_p5_np6);
        return;
    }



    cout << " nu\n";

}
