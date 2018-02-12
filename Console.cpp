//---------- Réalisation de l'espace de nom <Console> (fichier Console.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <limits>

//------------------------------------------------------ Include personnel
#include "Console.h"
#include "OutilsDeDebug.h"

//------------------------------------------------------------- Constantes
const unsigned int NOMBRE_SAUTS_VIDER_CONSOLE = 150U;

//----------------------------------------------------- Méthodes publiques
void Console::Vider()
{
    IF_MAP_DECLARER_DEBUT;

#if !defined(MAP)
    for (unsigned int i = 0; i < NOMBRE_SAUTS_VIDER_CONSOLE; ++i)
    {
        std::cout << "\n";
    }

    const int xPos = 0;
    const int yPos = 0;
    std::cout << "\033[" << yPos + 1 << ";" << xPos + 1 << "H";
#else
    std::cout << std::endl << "-----------" << std::endl;
#endif

    IF_MAP_DECLARER_FIN;
} // Fin de Vider()

void Console::DemanderLigne(std::istream &flux, std::string &ligne)
{
    IF_MAP_DECLARER_DEBUT_EXTRA;

    bool valide;
    do
    {
        std::getline(flux, ligne);
        valide = true;

        // Enlève les espaces en début de ligne
        size_t debut{0U};
        for (; debut < ligne.size() && ligne[debut] == ' '; ++debut)
        {} // bloc vide
        if (debut == ligne.size())
        {
            valide = false;
        }

        // Enlève les espaces en fin de ligne
        size_t fin{ligne.size() - 1U};
        for (; fin > debut && ligne[fin] == ' ' && valide; --fin)
        {} // bloc vide

        // Affiche un message d'erreur si la chaîne n'est pas valide
        if (!valide)
        {
            std::cout << RGE "Entrée invalide, veuillez réessayer." RESET << std::endl;
        }

        // Sinon, si elle est valide, tronque les espaces
        if (valide)
        {
            ligne = ligne.substr(debut, fin - debut + 1);
        }

    } while (!valide);

    IF_MAP_DECLARER_FIN_EXTRA;
} // Fin de DemanderLigne()

unsigned int Console::SaisieStrictementPositif()
{
    IF_MAP_DECLARER_DEBUT_EXTRA;

    int entree;
    do
    {
        SAFE_CIN(std::cin >> entree);

        if (entree <= 0) {
            std::cout << RGE "Veuillez saisir un nombre strictement positif : " RESET;
        }

    } while(entree <= 0);

    IF_MAP_DECLARER_FIN_EXTRA;
    return static_cast<unsigned int>(entree);
} // Fin de SaisieStrictementPositif()