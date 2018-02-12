//---------- Interface de l'espace de nom <Console> (fichier Console.h) ----------------
#ifndef TP_POO2_CONSOLE_H
#define TP_POO2_CONSOLE_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <limits>
#include <istream>
#include <string>
#include <stdlib.h>

//------------------------------------------------------------- Constantes
#define RESET "\x1B[00m"
#define GRAS "\x1B[01m"
#define GRIS "\x1B[02m"
#define GRIS_F "\x1B[30m"
#define ITALIQUE "\x1B[03m"
#define SOULIGNE "\x1B[04m"
#define RGE "\x1B[31m"
#define VRT "\x1B[32m"
#define JAU "\x1B[33m"
#define BLE "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define BLC "\x1B[37m"
#define FOND_BLC "\x1B[07m"
#define FOND_RGE "\x1B[41m"
#define FOND_VRT "\x1B[42m"
#define FOND_JAU "\x1B[43m"
#define FOND_BLE "\x1B[44m"
#define FOND_MAG "\x1B[45m"
#define FOND_CYN "\x1B[46m"
#define FOND_GRIS "\x1B[47m"
#define FOND_GRIS_F "\x1B[40m"

//------------------------------------------------------------------------
// Rôle de l'espace de nom <Console>
//
//   -> Ces fonctions permettent d'effectuer des opération complexes
//      ou courantes dans la console.
//
//------------------------------------------------------------------------

namespace Console
{
//----------------------------------------------------- Méthodes publiques
    void Vider();
    // Mode d'emploi :
    //   -> Permet de vider la console. Est équivalent à un appel à "clear"
    //      (Unix) / "cls" (Windows), mais sans appel système.
    //   -> Si MAP est définie, ne vide plus la console mais affiche un
    //      séparateur.
    //
    // Contrat : aucun

    void DemanderLigne(std::istream &flux, std::string &ligne);
    // Mode d'emploi :
    //   -> Cette fonction fonctionne comme std::getline(flux, ligne), mais
    //      enlève les espaces en début et fin de chaîne, et interdit la
    //      saisie de ligne vide.
    //
    // Paramètres :
    //   -> flux = flux dans lequel réaliser la saisie
    //   -> ligne = chaîne de caractères où est enregistré le résultat
    //
    // Contrat : aucun

    unsigned int SaisieStrictementPositif();
    // Mode d'emploi :
    //   -> Cette fonction effectue la saisie d'un entier strictement positif.
    //   -> Affiche un message d'erreur quand la saisie est incorrecte, et
    //      réalise une nouvelle saisie tant qu'un nombre valide n'est pas saisi.
    //   -> Le nombre maximal géré par cette fonction est MAX_INT, pas MAX_UINT.
    //
    // Retour :
    //   -> un entier strictement positif
    //
    // Contrat : aucun
};

//----------------------------------------------------- Macros

// Cette macro permet de réaliser des cin sécurisés, c'est-à-dire qu'elle
// s'assure qu'une valeur est récupérée, et permet aux std::cin de cohabiter
// avec les getline.
#define SAFE_CIN(input) while (!(input)) \
    { \
        std::cin.clear(); \
        std::cout << RGE "Entrée invalide, veuillez réessayer : " RESET; \
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); \
    } \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

#endif //TP_POO2_CONSOLE_H
