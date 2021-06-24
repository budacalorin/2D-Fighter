#ifndef PARTICULA
#define PARTICULA

#include <SFML/Graphics.hpp>

class particula{
public:
    sf::RectangleShape forma;
    float viteza_x,viteza_y;
    int countdown;
    float hp=50;
    int unghi;
    int indice_proprietar;
    int victime[5];
    int numar_victime;

    particula();

    void setup(int x,int y,float viteza_Y,float viteza_X,int UNGHI, int COUNTDOWN,int indice_proprietaR);

    void miscare();

    void test_colizune();

    bool alive();

    void adaugare_victime(int x);

    bool verificare_victima(int x);
};

#endif // PARTICULA
