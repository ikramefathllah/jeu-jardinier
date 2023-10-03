/**
   *\file jeux.h
   *le fichier header du jeu
*/

#ifndef jeux
#define jeux
#include<iostream>
#include<vector>
#include <ctime> //pour souvenir de l'heur de changement de comportement

using namespace std;

class jardin;  //le prototypage de classe jardin
/**
*@class plante
*la classe mère des plantes : fleur, grain et legume
*/
class plante
{
public:
    /**
    *@var position
    *un tableau 2D qui stock la position en x et en y de plant dans le jardin
    */
    int* position=new int[2];
    /**
    *@var indice_plante
    *un indice qui permet de differencier entre les differents types de plantes c'est comme un ID plante
    */
    int indice_plante;
public:
    /**
    *@brief ajouter une fleur, une legume ou bien un grain
    *@fn void ajouter(int ind,int x,int y,jardin *T,string fold,int nbgr)
    *@param x cordonnnée x du plant à ajouter
    *@param y cordonnnée y du plant à ajouter
    *@param ind un indice qui permet de differencier le type de plant
    *@param fold c'est le dossier qui contient l'image du palnt à ajouter
    *@param nbgr le nombre de grain qui caracterise le plant à ajouter
    */
    void ajouter(int ind,int x,int y,jardin *T,string fold,int nbgr);
};

/**
*@class fleur
*la classe fleur, elle herite de la classe plante toute les caracteristiques
*/
class fleur: public plante
{
};

/**
*@class legume
*la classe legume, elle herite de la classe plante toute les caracteristiques
*/
class legume: public plante
{};

/**
*@class grain
*la classe grain: sont les plantes a grain
*/
class grain: public plante
{
public:
    /**
    *@var nbre
    *le nombre de grain qui caracterise chaque type de plante
    */
    int nbre;
};

/**
*@class jardinier
*la classe jardinier: c'est l'employe du jardin, il va faire la recolte des grains
*/
class jardinier
{
public:
    /**
    *@var position
    *un tableau 2D qui stock la position en x et en y de jardinier dans le jardin
    */
    int position[2];
    /**
    *@var position_tache
    *un tableau 2D qui stock la position en x et en y de la plante à recolté par ce jardinier c'est comme ca mission
    */
    int position_tache[2];
    /**
    *@var last_hour
    *indique la dernier moment ou le jardinier a changer de comportement
    */
    float last_hour; //en secondes
    /**
    *@var last_hour
    *le moral de jardinier:
    @retval "content" si il a bien manger des legumes
    @retval "normal" si il est au debut de sa fain
    @retval "mecontent" si il est n'a pas trouvé de legumes à manger dans ce cas il cherche a detruire une fleur
    */
    string moral;  //={"normal","content","mecontent"};
    /**
    *@fn int boujer(int x1,int y1,int x2,int y2,jardin *T,int i);
    *@brief boujer le jardinier sur le jardin afin de recolter les grains
    *@param x1 le cordonnée en x de jardinier qui s'occupe de cette mission
    *@param y1 le cordonnée en y de jardinier qui s'occupe de cette mission
    *@param x2 le cordonnée en x de plante a recolté par le jardinier de cordonnée(x1,y1)
    *@param y2 le cordonnée en y de plante a recolté par le jardinier de cordonnée(x1,y1)
    *@return un entier qui nous indique si le jardinier a arrivé de recolté la plante ou pas encore
    */
    int boujer(int x1,int y1,int x2,int y2,jardin *T,int i);

};

/**
*@class joueur
*la classe joueur: c'est l'utilisateur de ce jeu, il peut recruter des jardiniers ainsi qu'ajouter des legumes et des fleures
*/
class joueur
{
public:
    /**
    *@fn void ajouter_jardinier(int x, int y,jardin *T)
    *@brief ajouter une jardinier dans le jardin afin de reculter des grains
    *@param x le cordonnée en x de jardinier
    *@param y le cordonnée en y de jardinier
    *@param T c'est un pointeur sur le jardin en question
    */
    void ajouter_jardinier(int x, int y,jardin *T);
    /**
    *@fn void acheter_pltjard(jardin *T)
    *@brief permet au joueur d'acheter des legumes et des fleures ainsi que des jardiniers solon le solde en grain
    *@param T c'est un pointeur sur le jardin en question
    */
    void acheter_pltjard(jardin *T);
};
/**
*@class jardin
*la classe jardin: c'est le champs du jeu il englobe tous les elements: jardiniers, plantes
*/
class jardin
{
public:
    /**
    *@var p une plante
    */
    plante p;
    /**
    *@var f une fleur
    */
    fleur f;
    /**
    *@var l une legume
    */
    legume l;
    /**
    *@var g une grain
    */
    grain g;
    /**
    *@var j un jardinier
    */
    jardinier j;
    /**
    *@var jou un joueur
    */
    joueur jou;
    /**
    *@var pt un tableau des plantes qui existe sur le jardin
    */
    vector <plante> pt;
    /**
    *@var ft un tableau des fleures qui existe sur le jardin
    */
    vector <fleur> ft;
    /**
    *@var lt un tableau des legumes qui existe sur le jardin
    */
    vector <legume> lt;
    /**
    *@var pt un tableau des grains qui existe sur le jardin
    */
    vector <grain> gt;
    /**
    *@var pt un tableau des jardiniers qui existe sur le jardin
    */
    vector <jardinier> jt;
    /**
    *@var somme_grain la somme des grains récoltés par les jardiniers: c'est le score du jeu
    */
    int somme_grain;
    /**
    *@fn int* distance_minimal(int x,int y,jardin *T,int ind)
    *@brief cherche la plante la plus proche au jardinier de cordonnées(x,y)
    *@param ind selon le comportement de jardinier cet indice change
    *@retval 1 si le jardinier est normal et veut manger de legume
    *@retval 2 si le jardinier est mecontent et veut detruire de fleur
    *@retval 3 si le jardinier est content et veut recolté de grain
    *@return un tableau d'entier qui retourne les cordonnées de la plante la plus proche au jardinier(x,y)
    */
    int* distance_minimal(int x,int y,jardin *T,int ind);
    /**
    *@fn void animer_jardinier(jardin *T)
    *@brief permet de faire l'affectation des taches des jardiniers, ainsi que le deplacements de plusieurs jardiniers au meme temsp
    */
    void animer_jardinier(jardin *T);
    /**
    *@fn void supprimer_plante(jardin*T,int x,int y,int ind)
    *@brief permet de supprimer une plante qui est manger ou bien recolté par un jardinier afin qu'il n'apparaitre plus sur le jardin
    *@param x le cordonnée en x de plante ou bien de jardinier à supprimer
    *@param y le cordonnée en y de plante ou bien de jardinier à supprimer
    *@param ind c'est l'ID de type plante a supprimer
    */
    void supprimer_plante(jardin*T,int x,int y,int ind);
    /**
    *@fn void refraichissement(jardin* T,int *indicejard,int m)
    *@brief permet de faire la mise a jour de jardin et de verifier a chaque fois les nouvels plantes et jardiniers a ajouter ou bien a supprimer
    *@param indicejard est un tableau d'entiers qui contient les cordonnées des jardiers qui sont en mode active
    */
    void refraichissement(jardin* T,int *indicejard,int m);
    /**
    *@fn void comport_jard(jardin* T)
    *@brief cette fonction permet de verifier le comportement de jardinier
    */
    void comport_jard(jardin* T);
    /**
    *@fn int position_unique(jardin *T,int x,int y)
    *@brief permet de verifier que la position ou le joueur veut ajouter la plante n'est pas deja rempli
    */
    int position_unique(jardin *T,int x,int y);
};

#endif
