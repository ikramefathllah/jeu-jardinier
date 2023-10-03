/**
   *\file main.cpp
   *le fichier principal de main
*/
#include"CImg.h"
using namespace cimg_library;
#include"jeux.h"
#include"jeu.cpp"
#include <unistd.h>
#include<ctime>

int main()
{
//***************la redimensionnement des images******************
    fleur1e1.resize(40,40);
    fleur1e5.resize(50,50);
    fleur2e1.resize(40,40);
    fleur2e5.resize(50,50);
    fleur3e1.resize(40,40);
    fleur3e5.resize(50,50);
    legume1e1.resize(40,40);
    legume1e5.resize(50,50);
    legume2e1.resize(40,40);
    legume2e5.resize(50,50);
    legume3e1.resize(40,40);
    legume3e5.resize(50,50);
    jardbas1.resize(50,50);
    jardhaut1.resize(50,50);
    jardgauche1.resize(50,50);
    jarddroit1.resize(50,50);

    //**************l'affichage du champs*************************
    img.draw_rectangle(0,0,tail_aff_long,tail_aff_larg,color2);
    img.draw_rectangle(30,30,tail_champ_long+100,tail_champ_larg+170,color);
    img.draw_rectangle(802,30,tail_aff_long-10,tail_aff_larg-20,color4);

    //*****************la partie menu principale***************
    img.draw_text(815,30,"BIENVENUE DANS LE JEUX JARDINIER!!",color3,0,1,23);
    img.draw_rectangle(802,30,804,700,color2);//rectangle vertical
    img.draw_rectangle(810,60,1200-20,100,color2);//rectangle horizontal

    img.draw_text(880,70,"MENU PRINCIPAL",color3,0,1,23);
    img.draw_image(800,105,0,0,fleur1e5,NO_opacite(fleur1e5));
    img.draw_text(800+39,130,"3 grains//key A",color3,0,1,23);
    img.draw_image(800,160,0,0,fleur2e5,NO_opacite(fleur2e5));
    img.draw_text(800+39,185,"2 grains//key B",color3,0,1,23);
    img.draw_image(800,215,0,0,fleur3e5,NO_opacite(fleur3e5));
    img.draw_text(800+39,240,"4 grains//key C",color3,0,1,23);
    img.draw_image(1000,105,0,0,legume1e5,NO_opacite(legume1e5));
    img.draw_text(1000+45,130,"3 grains//key D",color3,0,1,23);
    img.draw_image(1000,160,0,0,legume2e5,NO_opacite(legume2e5));
    img.draw_text(1045,185,"6 grains//key E",color3,0,1,23);
    img.draw_image(1000,215,0,0,legume3e5,NO_opacite(legume3e5));
    img.draw_text(1045,240,"8 grains//key F",color3,0,1,23);
    img.draw_image(800,270,0,0,jardbas1,NO_opacite(jardbas1));
    img.draw_text(800+39,295,"8 grains//key J",color3,0,1,23);

    //***********************la partie resultat du jeu: score*******************
    img.draw_rectangle(810,330,1200-20,370,color2);
    img.draw_text(890,340,"SCORE FINAL",color3,0,1,23);
    img.draw_text(810,375,affich_grain.c_str(),color3,0,1,23);
    img.draw_text(810,400,"LE COMPORTEMENT DES JARDINIERS",color3,0,1,23);
    for (int i=430; i<=650; i+=50)
    {
        img.draw_image(808,i,0,0,jardbas1,NO_opacite(jardbas1));
        img.draw_text(868,i+10,"je suis hors service",color3,0,1,23);
    }


    //*****************un objet jardin***********************
    jardin *T=new jardin;

    //*************l'initialisation du jardin par des jardinier et des plants****************
    T->somme_grain=0;  //initialiser le nombre de grain recolté à 0
    T->f.ajouter(1,480,200,T,"elements_champs/fleur1/",3);
    T->l.ajouter(4,300,260,T,"elements_champs/legume1/",4);
    //T->l.ajouter(6,540,320,T,"elements_champs/legume3/",8);
    T->jou.ajouter_jardinier(250,100,T);
    T->jou.ajouter_jardinier(250,200,T);


    //***************commencer le jeu********************
    while(!dsp.is_closed())
    {
        dsp.wait(0);
        T->animer_jardinier(T);
    }
    getchar();
    //*********la liberation de la memoire*****************
    delete T;
}
