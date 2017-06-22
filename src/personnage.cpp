#include "../include/personnage.h"
#include "constante.h"
#include <iostream>

personnage::personnage():pos_x((TAILLE_Y/2)-MILIEU_PERSONNAGE),pos_y((TAILLE_X/2)-MILIEU_PERSONNAGE),taille_x(60),taille_y(60),type(1),Nb_anim(1)
{

}

personnage::~personnage()
{
    //dtor
}

void personnage::deplacement(sf::Sprite* s_fonds, int direction,sf::Vector2f* pos_ecran)
{
    //sf::Vector2f buff_vect(s_fonds->getPosition());
    switch(direction)
    {
    case DIRECTION_HAUT:
        if(validation_scrolling(DIRECTION_HAUT,pos_ecran))
        {
            s_fonds->setTextureRect(sf::IntRect((pos_ecran->x),((pos_ecran->y)-DEPLACEMENT),pos_ecran->x+TAILLE_Y,(pos_ecran->y)-DEPLACEMENT+TAILLE_X));
            pos_ecran->y-=DEPLACEMENT;
            pos_perso.y-=DEPLACEMENT;
        }
        else if(validation_mouvement(direction))
        {
            pos_y-=DEPLACEMENT;
            pos_perso.y-=DEPLACEMENT;
        }

        std::cout << "scrolling_vers_le_haut" <<std::endl;
        break;
    case DIRECTION_BAS:
        if(validation_scrolling(DIRECTION_BAS,pos_ecran))
        {
            s_fonds->setTextureRect(sf::IntRect((pos_ecran->x),((pos_ecran->y)+DEPLACEMENT),pos_ecran->x+TAILLE_Y,(pos_ecran->y)+DEPLACEMENT+TAILLE_X));
            pos_ecran->y+=DEPLACEMENT;
            pos_perso.y+=DEPLACEMENT;
        }
        else if(validation_mouvement(direction))
        {
            pos_y+=DEPLACEMENT;
            pos_perso.y+=DEPLACEMENT;
        }
        std::cout << "scrolling_vers_le_bas" <<std::endl;
        break;
    case DIRECTION_DROITE:
        if(validation_scrolling(DIRECTION_DROITE,pos_ecran))
        {
            s_fonds->setTextureRect(sf::IntRect((pos_ecran->x)+DEPLACEMENT,(pos_ecran->y),pos_ecran->x+TAILLE_Y+DEPLACEMENT,(pos_ecran->y)+TAILLE_X));
            pos_ecran->x+=DEPLACEMENT;
            pos_perso.x+=DEPLACEMENT;
        }
        else if(validation_mouvement(direction))
        {
            pos_x+=DEPLACEMENT;
            pos_perso.x+=DEPLACEMENT;
        }

        std::cout << "scrolling_vers_la_droite" <<std::endl;
        break;
    case DIRECTION_GAUCHE:
        if(validation_scrolling(DIRECTION_GAUCHE,pos_ecran))
        {
            s_fonds->setTextureRect(sf::IntRect((pos_ecran->x)-DEPLACEMENT,(pos_ecran->y),pos_ecran->x+TAILLE_Y-DEPLACEMENT,(pos_ecran->y)+TAILLE_X));
            pos_ecran->x-=DEPLACEMENT;
            pos_perso.x-=DEPLACEMENT;
        }
        else if(validation_mouvement(direction))
        {
            pos_x-=DEPLACEMENT;
            pos_perso.x-=DEPLACEMENT;
        }

        std::cout << "scrolling_vers_la_gauche" <<std::endl;
        break;
    }
    s_sprite_joueur.setPosition(pos_x,pos_y);
    //update_sprite(direction);
    std::cout << "pos_x:" << pos_perso.x <<std::endl << "pos_y" << pos_perso.y << std::endl;
}
void personnage::load_all_sprite()
{
    s_sprite_joueur.setTexture(sprite_joueur); // on relie le sprite et la texture
    //s_fonds.setTextureRect(sf::IntRect(560,560,560+TAILLE_X,560+TAILLE_Y)); //définition du rectangle de sprite du fonds (servi
    s_sprite_joueur.setPosition((TAILLE_Y/2)-MILIEU_PERSONNAGE,(TAILLE_X/2)-MILIEU_PERSONNAGE);
    s_sprite_joueur.setTextureRect(sf::IntRect(0,0,TAILLE_PERSONNAGE,TAILLE_PERSONNAGE));
    s_sprite_joueur.scale(1.4,1.4);
}

void personnage::load_all_texture()
{
    if (!sprite_joueur.loadFromFile(cible_load)) //chargement de la texture depuis le disque (dossiers IMG dans le dossier projet)
    {
        std::cout << "Erreur du chargement" << std::endl; //affichage message d'erreur si le chargement échoue
    }
}

void personnage::wake_up(int x,int y,std::string sprite_cible)
{
    load_all_sprite();
    pos_perso.x=pos_x+x;
    pos_perso.y=pos_y+y;
    cible_load=sprite_cible;
    load_all_texture();
}

void personnage::draw_all_sprite(sf::RenderWindow* p_window)
{
    p_window->draw(s_sprite_joueur);
}

bool personnage::validation_scrolling(int direction,sf::Vector2f* pos_ecran)
{
    bool ret;
    //sf::Vector2f buff_vect(s_fonds->getPosition());
    switch(direction)
    {
    case DIRECTION_HAUT:
        if((pos_ecran->y)-DEPLACEMENT>0&&pos_y<=(TAILLE_X/2)-MILIEU_PERSONNAGE)
        {
            ret=true;
        }
        else ret=false;
        break;
    case DIRECTION_BAS:
        if((pos_ecran->y)+TAILLE_Y+DEPLACEMENT<TAILLE_VILLE&&pos_y>=(TAILLE_X/2)-MILIEU_PERSONNAGE)
        {
            ret=true;
        }
        else ret=false;
        break;
    case DIRECTION_DROITE:
        if((pos_ecran->x)+TAILLE_Y+DEPLACEMENT<TAILLE_VILLE&&pos_x>=(TAILLE_Y/2)-MILIEU_PERSONNAGE)
        {
            ret=true;
        }
        else ret=false;
        break;
    case DIRECTION_GAUCHE:
        if((pos_ecran->x)-DEPLACEMENT>0&&pos_x<=(TAILLE_Y/2)-MILIEU_PERSONNAGE)
        {
            ret=true;
        }
        else ret=false;
        break;
    }
    return ret;
}

bool personnage::validation_mouvement(int direction)
{
    bool ret;
    //sf::Vector2f buff_vect(s_fonds->getPosition());
    switch(direction)
    {
    case DIRECTION_HAUT:
        if(pos_y-DEPLACEMENT>0)
        {
            ret=true;
        }
        else ret=false;
        break;
    case DIRECTION_BAS:
        if(pos_y+DEPLACEMENT+TAILLE_PERSONNAGE<TAILLE_X)
        {
            ret=true;
        }
        else ret=false;
        break;
    case DIRECTION_DROITE:
        if(pos_x+DEPLACEMENT-TAILLE_PERSONNAGE<TAILLE_X)
        {
            ret=true;
        }
        else ret=false;
        break;
    case DIRECTION_GAUCHE:
        if(pos_x-DEPLACEMENT>0)
        {
            ret=true;
        }
        else ret=false;
        break;
    }
    return ret;
}

void personnage::update_sprite(int direction)
{
    static int direction_1=DIRECTION_STOP;
    bool anim(true);
    //if(direction!=direction_1)Nb_anim=1;
    if(direction==DIRECTION_STOP)
    {
        direction=direction_1;
        anim=false;
    }
    switch (direction)
    {
    case DIRECTION_HAUT:
         elapsed_time=temp_animation.getElapsedTime();
        if(elapsed_time.asMilliseconds()>91&&anim)
        {
            Nb_anim++;
            temp_animation.restart();
        }
        if(Nb_anim>4)Nb_anim=1;
        s_sprite_joueur.setTextureRect(sf::IntRect(60*(Nb_anim-1),60+60,TAILLE_PERSONNAGE,TAILLE_PERSONNAGE));
        break;
    case DIRECTION_BAS:
        elapsed_time=temp_animation.getElapsedTime();
        if(elapsed_time.asMilliseconds()>91&&anim)
        {
            Nb_anim++;
            temp_animation.restart();
        }
        if(Nb_anim>5)Nb_anim=1;
        s_sprite_joueur.setTextureRect(sf::IntRect(60*(Nb_anim-1),0,TAILLE_PERSONNAGE,TAILLE_PERSONNAGE));
        break;
    case DIRECTION_DROITE:
        elapsed_time=temp_animation.getElapsedTime();
        if(elapsed_time.asMilliseconds()>91&&anim)
        {
            Nb_anim++;
            temp_animation.restart();
        }
        if(Nb_anim>5)Nb_anim=1;
        s_sprite_joueur.setTextureRect(sf::IntRect(60*(Nb_anim-1),60+5,TAILLE_PERSONNAGE,TAILLE_PERSONNAGE));
        break;
    case DIRECTION_GAUCHE:
        elapsed_time=temp_animation.getElapsedTime();
        if(elapsed_time.asMilliseconds()>91&&anim)
        {
            Nb_anim++;
            temp_animation.restart();
        }
        if(Nb_anim>5)Nb_anim=1;
        s_sprite_joueur.setTextureRect(sf::IntRect(60*(Nb_anim-1)+TAILLE_PERSONNAGE,60+5,-TAILLE_PERSONNAGE,TAILLE_PERSONNAGE));
        //s_sprite_joueur.flipVerticaly();
        break;
        /*case DIRECTION_STOP:
            s_sprite_joueur.setTextureRect(sf::IntRect(60*(Nb_anim-1),0,TAILLE_PERSONNAGE,TAILLE_PERSONNAGE));
            std::cout << "reset" << std::endl;
            break;*/
    }
    direction_1=direction;
}
