#include "carte_collision.h"
#include "constante.h"
#include <iostream>
//#include <../SFML-2.4.2/include/Graphics/Colors.hpp>

carte_collision::carte_collision()
{
    //ctor
}

carte_collision::~carte_collision()
{
    //dtor
}
void carte_collision::load_all_image()
{
    if (!collision.loadFromFile("IMG/hyrule_city_collision.png")) //chargement de la texture depuis le disque (dossiers IMG dans le dossier projet)
    {
        std::cout << "Erreur du chargement" << std::endl; //affichage message d'erreur si le chargement échoue
    }
}

bool carte_collision::get_collision(int x,int y,int direction)
{
    bool ret=true;
    //sf::Vector2f buff_vect(s_fonds->getPosition());
    switch(direction)
    {
    case DIRECTION_HAUT:
        /*if(collision.getPixel(x,y)==sf::Color::White)
        {
            ret=false;
        }*/
        for (int i=x+DEPLACEMENT; i<x+TAILLE_PERSONNAGE-DEPLACEMENT; i++)
        {
            if(collision.getPixel(i,y)==sf::Color::White)
            {
                ret=false;

            }
        }
        std::cout << "COLLISION" << std::endl;
        break;
    case DIRECTION_BAS:
        for (int i=x+DEPLACEMENT; i<x+TAILLE_PERSONNAGE-DEPLACEMENT; i++)
        {
            if(collision.getPixel(i,y+TAILLE_PERSONNAGE)==sf::Color::White)
            {
                ret=false;

            }
        }
        std::cout << "COLLISION" << std::endl;
        break;
    case DIRECTION_DROITE:
        for (int i=y+DEPLACEMENT; i<y+TAILLE_PERSONNAGE-DEPLACEMENT; i++)
        {
            if(collision.getPixel(x+TAILLE_PERSONNAGE,i)==sf::Color::White)
            {
                ret=false;

            }
        }
        std::cout << "COLLISION" << std::endl;
        break;
    case DIRECTION_GAUCHE:
        for (int i=y+DEPLACEMENT; i<y+TAILLE_PERSONNAGE-DEPLACEMENT; i++)
        {
            if(collision.getPixel(x,i)==sf::Color::White)
            {
                ret=false;

            }

        }
        std::cout << "COLLISION" << std::endl;
        break;
    }
    return ret;
}

