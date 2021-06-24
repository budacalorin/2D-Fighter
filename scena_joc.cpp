#include "scena_joc.h"
#include "init.h"
#include "time.h"
#include <iostream>
void adaugare_proiectil(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,proiectil proiectile[],int &numar_proiectile,int indice_proprietar);
void adaugare_particula(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,particula particule[],int &numar_particule,int indice_proprietar);

void scena_joc::update()
{
    int x;
    x=update_cooldown();
    update_playeri();
    update_events();
    update_particule();
    update_proiectile();
    coliziune_player_proiectil();
    distrugere_blocuri();
    update_vieti();
    draw();
    actualizare_animatii(x);
    verificare_final();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        cout << "coord 1: "<<playeri[1].forma.getPosition().x << " " <<playeri[1].forma.getPosition().y <<"\n\n";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        cout << "coord 2: "<<playeri[2].forma.getPosition().x << " " <<playeri[2].forma.getPosition().y <<"\n\n";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        update_texturi_blocuri();
}

void scena_joc::draw()
{
    window.clear();

    window.draw(background);

    draw_blocuri();
    draw_playeri();
    draw_proiectile();
    draw_particule();
    draw_vieti();
    //draw_taguri();
    //window.draw(border);

    window.display();
}

void scena_joc::draw_playeri()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].alive==1)
        {
            window.draw(playeri[i].sprite);
        }

    }
}
void scena_joc::draw_blocuri()
{

    for (int i=1; i<=numar_blocuri; i++)
    {
        if (blocuri[i].alive==1)
        {
            window.draw(blocuri[i].forma);
            }
    }

}

void scena_joc::update_playeri()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].alive==1)
        {

            playeri[i].deplasare(blocuri,numar_blocuri);
            playeri[i].miscare(blocuri,numar_blocuri);
            if (playeri[i].declansare_putere_1==1&&playeri[i].cooldown_putere_1<=0)
            {
                playeri[i].declansare_putere_1=0;
                playeri[i].cooldown_putere_1=cooldown_puteri;

                float x=playeri[i].forma.getPosition().x+playeri[i].forma.getSize().x/2;
                float y=playeri[i].forma.getPosition().y+playeri[i].forma.getSize().y/2;
                int ok=0;
                if (sf::Keyboard::isKeyPressed(playeri[i].aim_sus))
                    y-=10,ok=1;
                if (sf::Keyboard::isKeyPressed(playeri[i].aim_jos))
                    y+=10,ok=1;
                if (sf::Keyboard::isKeyPressed(playeri[i].aim_stanga))
                    x-=10,ok=1,playeri[i].directie_dreapta=0;
                if (sf::Keyboard::isKeyPressed(playeri[i].aim_dreapta))
                    x+=10,ok=1,playeri[i].directie_dreapta=1;

                if (ok==0)
                {
                    if (playeri[i].a_jos)
                        y+=10;
                    if (playeri[i].a_sus)
                        y-=10;
                    if (playeri[i].a_st)
                        x-=10,playeri[i].directie_dreapta=0;
                    if (playeri[i].a_dr)
                        x+=10,playeri[i].directie_dreapta=1;
                }

                float dif_x=x-playeri[i].forma.getPosition().x-playeri[i].forma.getSize().x/2;
                float dif_y=y-playeri[i].forma.getPosition().y-playeri[i].forma.getSize().y/2;
                float pi=3.14;
                int unghi=-atan2(dif_y,dif_x)*180/pi;
                if (unghi<0)
                    unghi=360+unghi;

                x-=playeri[i].forma.getPosition().x+playeri[i].forma.getSize().x/2;
                y-=playeri[i].forma.getPosition().y+playeri[i].forma.getSize().y/2;
                x/=10;
                y/=10;
                //cout << unghi <<endl;

                adaugare_proiectil(playeri[i].forma.getPosition().x+x*playeri[i].forma.getSize().x+playeri[i].forma.getSize().x/2,playeri[i].forma.getPosition().y+playeri[i].forma.getSize().y/2-5+y*playeri[i].forma.getSize().y,viteza_proiectile,viteza_proiectile,unghi,viata_proiectile,proiectile,numar_proiectile,i);

            }
            playeri[i].tag.setPosition(sf::Vector2f(playeri[i].forma.getPosition().x,playeri[i].forma.getPosition().y-30));
        }
    }
}

void scena_joc::verificare_final()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].hp<=0)
        {
            scena_curenta=1;
            sf::sleep(sf::seconds(1));
        sf::Event event;
        while (window.pollEvent(event));
        }
    }
}

void scena_joc::adaugare_player(int indice,int x,int y,int size_x,int size_y,sf::Texture *textura,sf::Keyboard::Key su,sf::Keyboard::Key jo,sf::Keyboard::Key st,sf::Keyboard::Key dr,sf::Keyboard::Key act,sf::Keyboard::Key aim_su,sf::Keyboard::Key aim_jo,sf::Keyboard::Key aim_st,sf::Keyboard::Key aim_dr,sf::Texture *tag)
{
    playeri[indice].set_positioin(x,y);
    playeri[indice].set_size(size_x,size_y);
    playeri[indice].set_texture(textura);
    //playeri[indice].forma.setFillColor(sf::Color::White);
    playeri[indice].setTaste(su,jo,st,dr,act,aim_su,aim_jo,aim_st,aim_dr);
    playeri[indice].alive=1;
    playeri[indice].pixel_miscare=viteza_player;
    playeri[indice].hp=hp_player;
    playeri[indice].init_animatie(sf::Vector2u(8,4),100000);
    playeri[indice].forma.setTexture(textura);
    if (indice==1)
    playeri[indice].sprite.setTexture(textura_1);
    if (indice==2)
    playeri[indice].sprite.setTexture(textura_2);
    playeri[indice].set_tag_texture(tag);
}
void scena_joc::reset(int x)
{
    numar_playeri=x;
    numar_blocuri=0;
    numar_proiectile=0;
    numar_particule=0;

    //adaugare_player(1,100,450,30,100,p_textura_1,sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D,sf::Keyboard::Space,sf::Keyboard::I,sf::Keyboard::K,sf::Keyboard::J,sf::Keyboard::L,player_1_tag);
    adaugare_player(1,100,inaltime_ground-200,30,100,p_textura_1,sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D,sf::Keyboard::Space,sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D,&player_1_tag);
    playeri[1].directie_dreapta=playeri[1].a_dr=1;
    //adaugare_player(2,width-100-30,500,30,100,p_textura_1,sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right,sf::Keyboard::Enter,sf::Keyboard::Numpad8,sf::Keyboard::Numpad5,sf::Keyboard::Numpad4,sf::Keyboard::Numpad6,player_2_tag);
    adaugare_player(2,width-100-30,inaltime_ground-200,30,100,p_textura_2,sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right,sf::Keyboard::Enter,sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right,&player_2_tag);
    playeri[2].directie_dreapta=0;
    playeri[2].a_st=1;

    init_ground();
    timp_precedent=ceas_general.getElapsedTime().asMicroseconds();


    update_texturi_blocuri();
}

void scena_joc::update_events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type==sf::Event::Closed)
            game_on=0;

    }
}

void scena_joc::adaugare_bloc(int x,int y,int size_x,int size_y,sf::Color culoare)
{
    blocuri[++numar_blocuri].forma.setPosition(sf::Vector2f(x,y));
    blocuri[numar_blocuri].forma.setSize(sf::Vector2f(size_x,size_y));
    blocuri[numar_blocuri].forma.setFillColor(culoare);
    blocuri[numar_blocuri].alive=1;
}

void scena_joc::init_ground()
{
    srand(time(0));
    int x=rand()%3%10;
    for (int i=-30; i<=width+30; i+=30)
    {
        if (i%60==0)
            x=rand()%3*30;
        if (i<=0||i>=width/30*30)
            x=0;
        for (int j=inaltime_ground-x; j<hight; j+=30)
        {
            adaugare_bloc(i,j,30,30,sf::Color::White);
        }
    }
}

void scena_joc::draw_proiectile()
{
    for (int i=1; i<=numar_proiectile; i++)
        if (proiectile[i].viteza_x!=0||proiectile[i].viteza_y!=0)
        {
            //window.draw(proiectile[i].forma);
            window.draw(proiectile[i].sprite);
        }
}

void scena_joc::draw_particule()
{
    for (int i=1; i<=numar_particule; i++)
        if (particule[i].viteza_x!=0||particule[i].viteza_y!=0)
        {
            window.draw(particule[i].forma);
        }
}

void scena_joc::update_proiectile()
{
    for (int i=1; i<=numar_proiectile; i++)
    {
        if (proiectile[i].viteza_x!=0||proiectile[i].viteza_y!=0)
        {
            proiectile[i].miscare();
            proiectile[i].test_colizune();
            proiectile[i].update_sprite();
        }
    }
}

void scena_joc::update_particule()
{
    for (int i=1; i<=numar_particule; i++)
    {
        if (particule[i].viteza_x!=0||particule[i].viteza_y!=0)
        {
            particule[i].miscare();
            particule[i].test_colizune();

        }
    }
}

int scena_joc::update_cooldown()
{
    int timp=ceas_general.getElapsedTime().asMicroseconds();
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].alive)
        {
            playeri[i].cooldown_putere_1-=timp-timp_precedent;
            if (playeri[i].cooldown_putere_1<=0)
                playeri[i].cooldown_putere_1=0;
        }
    }
    for (int i=1; i<=numar_proiectile; i++)
    {
        if (proiectile[i].viteza_x!=0||proiectile[i].viteza_y!=0)
        {
            proiectile[i].countdown-=timp-timp_precedent;
            if (proiectile[i].countdown<=0)
                proiectile[i].countdown=0;
        }
    }

    for (int i=1; i<=numar_particule; i++)
    {
        if (particule[i].viteza_x!=0||particule[i].viteza_y!=0)
        {
            particule[i].countdown-=timp-timp_precedent;
            if (particule[i].countdown<=0)
                particule[i].countdown=0;
        }
    }
    int aux=timp_precedent;
    timp_precedent=timp;
    return timp-aux;
}

void scena_joc::distrugere_blocuri()
{
    for (int i=1; i<=numar_proiectile; i++)
    {
        if (proiectile[i].viteza_x!=0||proiectile[i].viteza_y!=0)
        {
            for (int j=1; j<=numar_blocuri; j++)
            {
                if (proiectile[i].forma.getGlobalBounds().intersects(blocuri[j].forma.getGlobalBounds())&&blocuri[j].alive==1)
                {
                    blocuri[j].alive=0;
                    if (blocuri[j].forma.getPosition().x<0||blocuri[j].forma.getPosition().x>=
                            width/10*10)
                        continuitate(blocuri[j]);
                    proiectile[i].hp-=damage_paricula_la_busire_perete;

                    update_texturi_blocuri();
                }
            }
        }
    }
}

void scena_joc::coliziune_player_proiectil()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].alive)
        {
            for (int j=1; j<=numar_proiectile; j++)
            {
                if (proiectile[j].alive()==1)
                {
                    if (playeri[i].forma.getGlobalBounds().intersects(proiectile[j].forma.getGlobalBounds())&&proiectile[j].indice_proprietar!=i)
                    {
                        if (proiectile[j].verificare_victima(i)==0)
                        {
                            proiectile[j].adaugare_victime(i);
                            playeri[i].hp-=damage_proiectil_player;
                            proiectile[j].hp=0;
                            for (int k=1;k<=30;k++)
                            {
                                float x=proiectile[j].forma.getPosition().x;
                                float y=proiectile[j].forma.getPosition().y;
                                x=(playeri[i].forma.getPosition().x+playeri[i].forma.getSize().x/2+x)/2;
                                y=(playeri[i].forma.getPosition().y+playeri[i].forma.getSize().y/2+y)/2;

                                adaugare_particula(x,y,(float)(rand()%300)/100,(float)(rand()%300)/100,rand()%360,100000,particule,numar_particule,i);
                            }
                        }

                    }

                }
            }
        }
    }
}

void scena_joc::continuitate(bloc blocul)
{
    int x=0-blocul.forma.getPosition().x;
    int y=blocul.forma.getPosition().y;
    if (x>0)
        x=width+blocul.forma.getSize().x*4-x;
    if (x<0)
        x=0-(width/10*10+blocul.forma.getSize().x*3-blocul.forma.getPosition().x);
    x/=10;
    x*=10;
    for (int i=1; i<=numar_blocuri; i++)
        if (blocuri[i].alive==1)
            if (blocuri[i].forma.getPosition().x==x&&blocuri[i].forma.getPosition().y==y)
            {
                blocuri[i].alive=0;

                break;
            }
}

void scena_joc::update_vieti()
{
    viata_1.setSize(sf::Vector2f(playeri[1].hp*coeficient_healthbar,inaltime_healthbar));
    viata_2.setSize(sf::Vector2f(playeri[2].hp*coeficient_healthbar,inaltime_healthbar));
}

void scena_joc::draw_vieti()
{
    window.draw(viata_1);
    window.draw(viata_2);
    window.draw(viata_1_border);
    window.draw(viata_2_border);
}

void scena_joc::actualizare_animatii(int timp_trecut)
{
    for (int i=1;i<=numar_playeri;i++)
    {
        if (playeri[i].alive==1)
        {
            playeri[i].actualizare_textura(timp_trecut);
        }
    }
}

void scena_joc::draw_taguri()
{
    for (int i=1;i<=numar_playeri;i++)
    {
        if (playeri[i].alive==1)
            window.draw(playeri[i].tag);
    }
}

void scena_joc::update_texturi_blocuri()
{
    int matrice[100][100]={0};

    for (int i=1;i<=numar_blocuri;i++)
    {

        int x=(int)blocuri[i].forma.getPosition().x/blocuri[i].forma.getSize().x;
        int y=(int)blocuri[i].forma.getPosition().y/blocuri[i].forma.getSize().y;
        //cout << x <<  " " << y << endl;
        if (blocuri[i].alive==1)
            matrice[y][x]=1;
    }
    for (int i=1;i<=numar_blocuri;i++)
        if (blocuri[i].alive==1)
            blocuri[i].update_texture(matrice);

}

void scena_joc::reset_colt_fill()
{}
