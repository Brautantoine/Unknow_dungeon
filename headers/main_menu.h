#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <../SFML-2.4.2/include/SFML/Graphics.hpp>
#include "../include/personnage.h"
#include "../include/carte_collision.h"
#include <../SFML-2.4.2/include/SFML/audio.hpp>


/** ***                                                         *** **/
/** *** CLASS DE GESTION DU JEU                                 *** **/
/** *** VERSION : 2.0.1                                         *** **/
/** *** DERNIERE MODIF : 22 JUIN 2017                           *** **/
/** *** TO DO: AJOUTER PNJ   reparer pause                      *** **/
/** *** CONSTR TYPE: SIMPLE                                     *** **/
/** *** DESTRUCTEUR: VIRTUEL                                    *** **/
/** ***                                                         *** **/
class Main_menu
{
public:
    Main_menu(); //constructeur
    virtual ~Main_menu(); //deconstructeur
    void load_all_texture(); //chargement des textures
    void load_all_sprite(); //chargement des sprites
    void load_all_font(); //chargements des polices d'écritures
    void open_all_music(); //ouverture de la musique
    void draw_all_sprite(sf::RenderWindow* p_window); //mise en mémoire tampon de la frame courante
    void wake_up(); //initialisation de la classe (en plus du constructeur)
    void scrolling(int direction); //méthodes de déplacement globalisées (actionne aussi les déplacements des personnages)
    void Setcol(int val) //"setter" de la variable col
    {
        col = val;
    }
    int Getcol()//"getter" de la variable col
    {
        return col;
    }
    void reset_anim_perso();//RAZ du numéro d'animation du sprite personnage
    void launch_music();//démarre la musique de fond
    bool pause_game(sf::RenderWindow* p_window);//lance le menu de pause /!\ FONCTION BLOQUANTE
    bool intro_jeu(sf::RenderWindow* p_window);//lance l'intro /!\ FONCTION BLOQUANTE

protected:

private:
    /** TEXTURE **/
    sf::Texture fonds; //carte du fonds
    sf::Texture col_map; //carte de collision
    sf::Texture sup; //partie supérieur de la carte
    /** SPRITE **/
    sf::Sprite s_fonds;
    sf::Sprite s_col_map;
    sf::Sprite s_sup;
    /** Relative au texte **/
    sf::Font font;
    sf::Text text;
    sf::Text text_intro;
    /** POINTEUR VERS L'ENTITE FENÊTRE **/
    sf::RenderWindow* p_window;
    /** CLASS DE GESTION DU PERSONNAGE_JOUEUR **/
    personnage player;
    /** POSITION  DU SCROLLING **/
    sf::Vector2f pos_ecran;
    /** CLASS DE GESTION DE LA CARTE DE COLLISION **/
    carte_collision collision;
    int col; // Variable de mémorisation de l'affichage de la carte de collision
    /** MUSIQUE **/
    sf::Music back_music;
    /** TIMER DES EFFETS DE SON **/
    sf::Clock temp_bump;
    sf::Time elapsed_time;
    /** EFFET DE SON **/
    sf::SoundBuffer bump_sound;
    sf::Sound sound_bump;
    /** TIMER DE L'INTRO **/
    sf::Clock timer_intro;
};

#endif // MAIN_MENU_H
