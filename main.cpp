#include <../SFML-2.4.2/include/SFML/Graphics.hpp>
#include <iostream>
#include "main_menu.h"
#include "constante.h"

/**< Point de d�part */
int main()
{
    // cr�ation de la fen�tre
    sf::RenderWindow window(sf::VideoMode(TAILLE_Y,TAILLE_X),"Unknow_Dungeon");/**< classe g�rant la fen�tre */
    window.setVerticalSyncEnabled(true); /**< On active la synchro verticale (le jeu �tant assez l�ger les performances demand� par une v-sync seront faibles */
    window.setJoystickThreshold(5);/**< On fixe un pas de 5 (valeur allant de 0 � 100) pour la d�tection du mouvement du joystick */

    /**< D�claration de l'entit� menu de la class Main_menu qui g�rera tout le d�roulement du jeu  */
    Main_menu menu;
    menu.wake_up(); /**< On appel la fonction d'initialisation de Main_menu */

    if(!menu.intro_jeu(&window))window.close(); /**< On appel la fonction de l'intro et l'on test son retour */
    // on fait tourner le programme tant que la fen�tre n'a pas �t� ferm�e
    while (window.isOpen())
    {
        window.clear(sf::Color::Black); // On efface le buffer d'affichage
        //menu.draw_all_sprite(&window); /**< reliquat d'un ancien bout du code, conserver ici en tant que pense-b�te/backup */

        // on traite tous les �v�nements de la fen�tre qui ont �t� g�n�r�s depuis la derni�re it�ration de la boucle
        sf::Event event; /**< classe de SFML g�rant les �v�nement */
        while (window.pollEvent(event)) /**< Boucle de gestion des �v�nement */
        {
            // fermeture de la fen�tre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed) //Correspond � l'appuie sur la croix rouge
                window.close(); //fermeture de la fen�tre

            if (event.type == sf::Event::JoystickButtonPressed) /**< Correspond � l'appuie apr�s relachement sur un bouton */
            {
                if (sf::Joystick::isButtonPressed(0, 1)) // On v�rifie que le bouton "B" est appuy�
                {
                    menu.Setcol(-menu.Getcol()); /**< On active/d�sactive l'affichage de la carte de collision */
                    std::cout << "inversion map" << std::endl; /**< Affichage de l'inversion dans la console */
                }
            }

        }
        // On consid�re que le joystick est pouss� � partir d'une valeur re�ue de 30
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)<-30)menu.scrolling(DIRECTION_HAUT); /**< Si le joystick est pouss� vers le haut on appel le d�placement vers le haut */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)>30)menu.scrolling(DIRECTION_BAS);   /**< Si le joystick est pouss� vers le bas on appel le d�placement vers le bas */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X)>30)menu.scrolling(DIRECTION_DROITE);  /**< Si le joystick est pouss� vers la droite on appel le d�placement vers la droite */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X)<-30)menu.scrolling(DIRECTION_GAUCHE); /**< Si le joystick est pouss� vers la gauche on appel le d�placement vers la gauche */
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X)<30  /**< Long test pour v�rifier si le joystick est au repos */
                &&sf::Joystick::getAxisPosition(0, sf::Joystick::X)>-30
                &&sf::Joystick::getAxisPosition(0, sf::Joystick::Y)<30
                &&sf::Joystick::getAxisPosition(0, sf::Joystick::Y)>-30)menu.reset_anim_perso();
        if (sf::Joystick::isButtonPressed(0, 6)) /**< Si le bouton "SELECT" est appuy� on quitte le programme et la fen�tre*/
        {
            window.close(); // fermeture de la fen�tre
        }
        if (sf::Joystick::isButtonPressed(0, 7))
        {
            if(!menu.pause_game(&window))window.close();
        }
        // c'est ici qu'on dessine tout
        menu.draw_all_sprite(&window);

        // fin de la frame courante, affichage de tout ce qu'on a dessin�
        window.display();
    }

    return 0;
}
/** END_OF_MAIN **/
