#include <../SFML-2.4.2/include/SFML/Graphics.hpp>
#include <iostream>
#include "main_menu.h"
#include "constante.h"

/**< Point de départ */
int main()
{
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(TAILLE_Y,TAILLE_X),"Unknow_Dungeon");/**< classe gérant la fenêtre */
    window.setVerticalSyncEnabled(true); /**< On active la synchro verticale (le jeu étant assez léger les performances demandé par une v-sync seront faibles */
    window.setJoystickThreshold(5);/**< On fixe un pas de 5 (valeur allant de 0 à 100) pour la détection du mouvement du joystick */

    /**< Déclaration de l'entité menu de la class Main_menu qui gérera tout le déroulement du jeu  */
    Main_menu menu;
    menu.wake_up(); /**< On appel la fonction d'initialisation de Main_menu */

    if(!menu.intro_jeu(&window))window.close(); /**< On appel la fonction de l'intro et l'on test son retour */
    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        window.clear(sf::Color::Black); // On efface le buffer d'affichage
        //menu.draw_all_sprite(&window); /**< reliquat d'un ancien bout du code, conserver ici en tant que pense-bête/backup */

        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event; /**< classe de SFML gérant les évènement */
        while (window.pollEvent(event)) /**< Boucle de gestion des évènement */
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed) //Correspond à l'appuie sur la croix rouge
                window.close(); //fermeture de la fenêtre

            if (event.type == sf::Event::JoystickButtonPressed) /**< Correspond à l'appuie aprés relachement sur un bouton */
            {
                if (sf::Joystick::isButtonPressed(0, 1)) // On vérifie que le bouton "B" est appuyé
                {
                    menu.Setcol(-menu.Getcol()); /**< On active/désactive l'affichage de la carte de collision */
                    std::cout << "inversion map" << std::endl; /**< Affichage de l'inversion dans la console */
                }
            }

        }
        // On considére que le joystick est poussé à partir d'une valeur reçue de 30
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)<-30)menu.scrolling(DIRECTION_HAUT); /**< Si le joystick est poussé vers le haut on appel le déplacement vers le haut */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)>30)menu.scrolling(DIRECTION_BAS);   /**< Si le joystick est poussé vers le bas on appel le déplacement vers le bas */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X)>30)menu.scrolling(DIRECTION_DROITE);  /**< Si le joystick est poussé vers la droite on appel le déplacement vers la droite */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X)<-30)menu.scrolling(DIRECTION_GAUCHE); /**< Si le joystick est poussé vers la gauche on appel le déplacement vers la gauche */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X)<30  /**< Long test pour vérifier si le joystick est au repos */
                &&sf::Joystick::getAxisPosition(0, sf::Joystick::X)>-30
                &&sf::Joystick::getAxisPosition(0, sf::Joystick::Y)<30
                &&sf::Joystick::getAxisPosition(0, sf::Joystick::Y)>-30)menu.reset_anim_perso();
        if (sf::Joystick::isButtonPressed(0, 6)) /**< Si le bouton "SELECT" est appuyé on quitte le programme et la fenêtre*/
        {
            window.close(); // fermeture de la fenêtre
        }
        if (sf::Joystick::isButtonPressed(0, 7))
        {
            if(!menu.pause_game(&window))window.close();
        }
        // c'est ici qu'on dessine tout
        menu.draw_all_sprite(&window);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}
/** END_OF_MAIN **/
