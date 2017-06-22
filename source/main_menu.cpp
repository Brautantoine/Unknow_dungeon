#include "main_menu.h"
#include <../SFML-2.4.2/include/SFML/Graphics.hpp>
#include <iostream>
#include "constante.h"
#include "../include/personnage.h"
#include <../SFML-2.4.2/include/SFML/audio.hpp>

/** \brief constructeur de la class Main_menu
 *
 * \param aucun
 * \param
 * \return aucun
 *
 */

Main_menu::Main_menu()
{
    //cercle_joueur.setRadius(30);
    //cercle_joueur.setPosition((TAILLE_Y/2)-30,(TAILLE_X/2)-30);
    col=-1;
}


/** \brief destructeur
 *
 * \param
 * \param
 * \return
 *
 */

Main_menu::~Main_menu()
{
    //dtor
}

/** \brief chargement des texture
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::load_all_texture()
{
    if (!fonds.loadFromFile("IMG/hyrule_city.png")) //chargement de la texture depuis le disque (dossiers IMG dans le dossier projet)
    {
        std::cout << "Erreur du chargement" << std::endl; //affichage message d'erreur si le chargement échoue
    }
    if (!col_map.loadFromFile("IMG/hyrule_city_collision.png")) //chargement de la texture depuis le disque (dossiers IMG dans le dossier projet)
    {
        std::cout << "Erreur du chargement" << std::endl; //affichage message d'erreur si le chargement échoue
    }
    if (!sup.loadFromFile("IMG/hyrule_city_sup.png")) //chargement de la texture depuis le disque (dossiers IMG dans le dossier projet)
    {
        std::cout << "Erreur du chargement" << std::endl; //affichage message d'erreur si le chargement échoue
    }
}

/** \brief chargement des sprites
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::load_all_sprite()
{
    s_fonds.setTexture(fonds); // on relie le sprite et la texture
    s_fonds.setTextureRect(sf::IntRect(DEMARRAGE_POS_PERSO_X,DEMARRAGE_POS_PERSO_Y,DEMARRAGE_POS_PERSO_X+TAILLE_X,DEMARRAGE_POS_PERSO_Y+TAILLE_Y)); //définition du rectangle de sprite du fonds (scrolling d'affichage)
    pos_ecran.x=DEMARRAGE_POS_PERSO_X; //position du scrolling en x
    pos_ecran.y=DEMARRAGE_POS_PERSO_Y; //position du scrolling en y
    s_col_map.setTexture(col_map); // on relie le sprite et la texture
    s_col_map.setTextureRect(sf::IntRect(DEMARRAGE_POS_PERSO_X,DEMARRAGE_POS_PERSO_Y,DEMARRAGE_POS_PERSO_X+TAILLE_X,DEMARRAGE_POS_PERSO_Y+TAILLE_Y));
    s_sup.setTexture(sup); // on relie le sprite et la texture
    s_sup.setTextureRect(sf::IntRect(DEMARRAGE_POS_PERSO_X,DEMARRAGE_POS_PERSO_Y,DEMARRAGE_POS_PERSO_X+TAILLE_X,DEMARRAGE_POS_PERSO_Y+TAILLE_Y));
}

/** \brief  affichage de tous les sprites
 *
 * \param pointeur vers la fenêtre
 * \param sf::RenderWindow*
 * \return void
 *
 */

void Main_menu::draw_all_sprite(sf::RenderWindow* p_window)
{
    s_col_map.setTextureRect(sf::IntRect(pos_ecran.x,pos_ecran.y,pos_ecran.x+TAILLE_Y,pos_ecran.y+TAILLE_X));//on actualise la position de l'écran
    s_sup.setTextureRect(sf::IntRect(pos_ecran.x,pos_ecran.y,pos_ecran.x+TAILLE_Y,pos_ecran.y+TAILLE_X));// on actualise la postion de l'écran
    if(col==-1)p_window->draw(s_fonds);//On affiche ou non la carte de collision
    if(col==1)p_window->draw(s_col_map); //on affiche ou non la carte de collision
    player.draw_all_sprite(p_window); //on affiche le personnage
    p_window->draw(s_sup); //on affiche les éléments de décor supérieur

}

/** \brief initialisation de la classe (complémentaire au constructeur)
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::wake_up()
{
    load_all_texture(); //chargement des textures
    load_all_sprite(); //chargement des sprites
    open_all_music(); //ouverture des musiques
    load_all_font(); //chargement des polices d'écritures
    player.wake_up(560,560,"IMG/anim_2.png"); //initialisation du joueur
    text.setFont(font); //on "ratache" la police au texte

    text.setCharacterSize(50);//taille de la police

    text.setFillColor(sf::Color::Black);//couleur du corps du texte

    text.setPosition(sf::Vector2f(90,100));//position du texte
    text.setOutlineColor(sf::Color::White);//couleur du contour du texte

    text.setOutlineThickness(5);//taille du contour du texte

    sound_bump.setBuffer(bump_sound);//chargement du son dans son buffer
    sound_bump.setVolume(20);//on fixe le volume du son
    collision.load_all_image();//chargement de la carte de collision
    launch_music(); //lancement de la musique
}

/** \brief fonction de scrolling et de déplacement généralisée
 *
 * \param direction du déplacement
 * \param int direction
 * \return void
 *
 */

void Main_menu::scrolling(int direction)
{

    if(collision.get_collision(player.get_localisation_x(),player.get_localisation_y(),direction)) //on test la collision avec le décor
    {
        switch (direction) //on test la direction
        {
        case DIRECTION_HAUT:
            player.deplacement(&s_fonds,direction,&pos_ecran);//on déplace le personnage vers le haut
            break;
        case DIRECTION_BAS:
            player.deplacement(&s_fonds,direction,&pos_ecran);//on déplace le personnage vers le bas
            break;
        case DIRECTION_DROITE:
            player.deplacement(&s_fonds,direction,&pos_ecran);//on déplace le personnage vers la droite
            break;
        case DIRECTION_GAUCHE:
            player.deplacement(&s_fonds,direction,&pos_ecran);//on déplace le personnage vers la gauche
            break;
        }
    }
    else //en cas de collision
    {
        std::cout << "BUMP" << std::endl;//affichage de "debug"
        elapsed_time=temp_bump.getElapsedTime();//on lit le temps écoulé depuis la derniére collision
        if(elapsed_time.asMilliseconds()>900)//si le temps est supérieur à 900ms
        {
            if(!(sound_bump.getStatus()==sound_bump.Playing))sound_bump.play();//et si le son n'est pas en train d'être joué on le joue
            temp_bump.restart();//on relance le timer
        }
    }
    player.update_sprite(direction);//on met à jour le sprite du joueur
}

/** \brief RAZ l'animation du perso
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::reset_anim_perso()
{
    player.SetNb_anim(1);//on met le numéro d'animation du personnage à 1
    player.update_sprite(DIRECTION_STOP);//on remet à jour le sprite du personnage à l'arrêt
}

/** \brief ouverture des musique
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::open_all_music()
{
    if (!back_music.openFromFile("SONG/village.ogg"))//on test l'ouverture de la musique
    {
        std::cout << "ERREUR: impossible charge audio" << std::endl;//message d'erreur
    }
    if (!bump_sound.loadFromFile("SONG/bump.ogg"))//on test l'ouverture du son
    {
        std::cout << "ERREUR: impossible charge audio" << std::endl;//message d'erreur
    }
}

/** \brief Lancement de la musique
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::launch_music()
{
    back_music.setLoop(true);//on active la boucle sur la musique
    back_music.play();//on lance la musique
    back_music.setPlayingOffset(sf::seconds(2));//on fait commencer la musique à 2s
}

/** \brief Mise en pause du jeu
 *
 * \param pointeur vers la fenêtres
 * \param sf::RenderWindow
 * \return bool
 *
 */

bool Main_menu::pause_game(sf::RenderWindow* p_window)
{
    bool ret=true; //valeur de retour par défaut vrai)
    sf::Event event;//classe de détection des événements
    back_music.pause();//on met en pause la musique
    text.setString("&&& PAUSE &&&\n\n\nresume with \"B\"");//on charge le texte de mise en pause
    draw_all_sprite(p_window);//on redessine tous les sprite car l'on vient de passer par un clear
    p_window->draw(text);//on dessine le texte
    p_window->display();//on l'on affiche la frame
    while (!(sf::Joystick::isButtonPressed(0,1))&&!(event.type == sf::Event::Closed))//tant que l'on appuie pas sur "B" ou la croix rouge
    {
        while (p_window->pollEvent(event)) /**< Boucle de gestion des évènement */ //indispensable sinon la condition du while n'est jamais mise à jour
        {

            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed) //Correspond à l'appuie sur la croix rouge
                // p_window->close(); //fermeture de la fenêtre //impossible de fermer une fenêtre en dehors de là où elle est déclarée
                ret=false;//on revoie une valeur fausse pour fermer la fenêtre
        }
    }
    back_music.play();//on relance la musique aprés la pause
    return ret;
}

/** \brief chargement des polices
 *
 * \param aucun
 * \param
 * \return void
 *
 */

void Main_menu::load_all_font()
{
    if (!font.loadFromFile("FONT/petyka.ttf")) //chargement de la texture depuis le disque (dossiers IMG dans le dossier projet)
    {
        std::cout << "Erreur du chargement font" << std::endl; //affichage message d'erreur si le chargement échoue
    }
}
