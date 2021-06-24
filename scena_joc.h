#ifndef SCENA_JOC
#define SCENA_JOC

#include "player.h"
#include "proiectil.h"
#include "particula.h"

class scena_joc{
public:
    player playeri[4];
    bloc blocuri[10000];
    proiectil proiectile[200];
    particula particule[5000];
    int numar_particule;
    int numar_proiectile=0;
    int numar_playeri;
    int numar_blocuri;
    long long timp_precedent;


    void update_playeri();

    void draw();

    void draw_blocuri();

    void draw_playeri();

    void verificare_final();

    void update();

    void reset(int x);

    void adaugare_player(int indice,int x,int y,int size_x,int size_y,sf::Texture *texture,sf::Keyboard::Key su,sf::Keyboard::Key jo,sf::Keyboard::Key st,sf::Keyboard::Key dr,sf::Keyboard::Key act,sf::Keyboard::Key aim_su,sf::Keyboard::Key aim_jo,sf::Keyboard::Key aim_st,sf::Keyboard::Key aim_dr,sf::Texture *tag);

    void update_events();

    void adaugare_bloc(int x,int y,int size_x,int size_y,sf::Color culoare);

    void init_ground();

    void draw_proiectile();

    void update_proiectile();

    void draw_particule();

    void update_particule();

    int update_cooldown();

    void distrugere_blocuri();

    void coliziune_player_proiectil();

    void continuitate(bloc blocul);

    void update_vieti();

    void draw_vieti();

    void actualizare_animatii(int timp_trecut);

    void draw_taguri();

    void update_texturi_blocuri();

    void reset_colt_fill();
};


#endif
