/**
   *\file initialisation.cpp
   *englobe tous les initialisations des parametres du jardin
*/
#include"CImg.h"
#include<string>
using namespace cimg_library;
using namespace std;

//*************l'initialisation des parametres du jardin*****************
int tail_champ_long=700;
int tail_champ_larg=500;
int temp_pousse=4000;
int nbr_jard=0;
int cout_grain=1;
int tail_aff_long=1200;
int tail_aff_larg=700;

CImg<unsigned char> img(tail_aff_long,tail_aff_larg,1,3,0);
CImgDisplay dsp(img,"jeu jardinier");
unsigned char color[3] {0,255,0};   //vert
unsigned char color2[3] {255,100,50};  //rouge
unsigned char color3[3] {0,0,0};    //noir
unsigned char color4[3] {255,255,255};//blanc

//********les images pour des plantes*********
//3 types des fleurs
CImg<unsigned char> fleur1e1("elements_champs/fleur1/etape1.pnm");
CImg<unsigned char> fleur1e5("elements_champs/fleur1/etape5.pnm");
CImg<unsigned char> fleur2e1("elements_champs/fleur2/etape1.pnm");
CImg<unsigned char> fleur2e5("elements_champs/fleur2/etape5.pnm");
CImg<unsigned char> fleur3e1("elements_champs/fleur3/etape1.pnm");
CImg<unsigned char> fleur3e5("elements_champs/fleur3/etape5.pnm");



//les 3 types des legumes
CImg<unsigned char> legume1e1("elements_champs/legume1/etape1.pnm");
CImg<unsigned char> legume1e5("elements_champs/legume1/etape5.pnm");
CImg<unsigned char> legume2e1("elements_champs/legume2/etape1.pnm");
CImg<unsigned char> legume2e5("elements_champs/legume2/etape5.pnm");
CImg<unsigned char> legume3e1("elements_champs/legume3/etape1.pnm");
CImg<unsigned char> legume3e5("elements_champs/legume3/etape5.pnm");

//jardinier bas
CImg<unsigned char> jardbas1("elements_champs/jard1/bas1.pnm");
//jardinier haut
CImg<unsigned char> jardhaut1("elements_champs/jard1/haut1.pnm");
//jardinier gauche
CImg<unsigned char> jardgauche1("elements_champs/jard1/gauche1.pnm");
//jardinier droite
CImg<unsigned char> jarddroit1("elements_champs/jard1/droite1.pnm");

string affich_grain="le stocke de grain est:  "+to_string(0);
