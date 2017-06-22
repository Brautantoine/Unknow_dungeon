#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <../SFML-2.4.2/include/SFML/Graphics.hpp>

/** ***                                                         *** **/
/** *** CLASS DE GESTION DU PERSONNAGE                          *** **/
/** *** VERSION : 1.4.3                                         *** **/
/** *** DERNIERE MODIF : 22 JUIN 2017                           *** **/
/** *** TO DO: AJOUTER COLLISION ENTRE PERSO                    *** **/
/** *** CONSTR TYPE: LISTE                                      *** **/
/** *** DESTRUCTEUR: VIRTUEL                                    *** **/
/** ***                                                         *** **/
class personnage
{
public:
    personnage();//constructeur
    virtual ~personnage();//destructeur

    int Getpos_x()//"getter" de pos_x
    {
        return pos_x;
    }
    void Setpos_x(int val)//"setter" de pos_x
    {
        pos_x = val;
    }
    int Getpos_y()//"getter" de pos_y
    {
        return pos_y;
    }
    void Setpos_y(int val)//"setter" de pos_y
    {
        pos_y = val;
    }
    int Gettaille_x()//"getter" de taille_x
    {
        return taille_x;
    }
    void Settaille_x(int val)//"setter" de taille_x
    {
        taille_x = val;
    }
    int Gettaille_y()//"getter" de taille_y
    {
        return taille_y;
    }
    void Settaille_y(int val)//"setter" de taille_y
    {
        taille_y = val;
    }
    int Gettype()//"getter" de type
    {
        return type;
    }
    void Settype(int val)//"setter" de type
    {
        type = val;
    }
    int GetNb_anim()//"getter" de Nb_anim
    {
        return Nb_anim;
    }
    void SetNb_anim(int val)//"setter" de Nb_anim
    {
        Nb_anim = val;
    }
    void deplacement(sf::Sprite* s_fonds, int direction,sf::Vector2f* pos_ecran);//deplacement du personnage
    void load_all_sprite();//chargement des srpites
    void load_all_texture();//chargement des textures
    void wake_up(int x,int y,std::string sprite_cible);//initialisation (complémentaire au constructeur)
    void draw_all_sprite(sf::RenderWindow* p_window);//mise en mémoire tampon des sprite avant affichage
    bool validation_scrolling(int direction,sf::Vector2f* pos_ecran);//verification du scrolling
    bool validation_mouvement(int direction);//verification du mouvement
    int get_localisation_x()//"getter" de la composante en x de pos_perso
    {
        return pos_perso.x;
    }
    int get_localisation_y()//"getter" de la composante en y de pos_perso
    {
        return pos_perso.y;
    }
    void update_sprite(int);//mise à jour du sprite à afficher

protected:

private:
    /** position par raport à l'écran **/
    int pos_x;
    int pos_y;
    /** position du joueur (de base égale à la macro TAILLE_PERSONNAGE mais a la possibilité d'être modifier **/
    int taille_x;
    int taille_y;
    /** type du personnage (inutilisé pour l'instant) **/
    int type;
    /** numéro de l'animation actuelle **/
    int Nb_anim;
    /** position du personnage sur la carte **/
    sf::Vector2f pos_perso;
    /** texture du personnage **/
    sf::Texture sprite_joueur;
    /** sprite du personnage **/
    sf::Sprite s_sprite_joueur;
    /** timer de l'animation **/
    sf::Clock temp_animation;
    sf::Time elapsed_time;
    /** buffer de l'adresse de la texture **/
    std::string cible_load;

};


#endif // PERSONNAGE_H
