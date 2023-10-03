/**
   *\file jeu.cpp
   *le fichier jeu.cpp
*/

#include"jeux.h"
#include<math.h>
#include"initialisation.cpp"


//*************appliquer le masque sur les images****************
CImg<float> NO_opacite(CImg<unsigned char> imag)
{
    CImg<float> opacite(imag.width(), imag.height(), 1, 1, 0);
    for(int x=0; x<opacite.width(); ++x)
        for(int y=0; y<opacite.height(); ++y)
            if (imag(x,y,0)==255 && imag(x,y,1)==255 && imag(x,y,2)==255)
                opacite(x,y)=0;
            else
                opacite(x,y)=1;
    return opacite;
}

//**********ajouter une plante dans le jardin******************
void plante::ajouter(int ind,int x,int y,jardin *T,string fold,int nbgr)
{
    int n;
    n=temp_pousse/4;    //la durée entre deux etapes de pousse
    grain gr0;
    if(ind==1 || ind==2 || ind==3)  //si c'est un type fleur
    {
        fleur flr0;
        flr0.position[0]=x;
        flr0.position[1]=y;
        flr0.indice_plante=ind;
        T->ft.push_back(flr0);      //l'ajout du fleur dans le tableau fleur
    }
    else if(ind==4 || ind==5 || ind==6)
    {
        legume leg0;
        leg0.position[0]=x;
        leg0.position[1]=y;
        leg0.indice_plante=ind;
        T->lt.push_back(leg0);      //l'ajout de legume dans le tableau legume
    }

    //************l'ajout du grain dans le tableau grain********
    gr0.position[0]=x-40;
    gr0.position[1]=y;
    gr0.indice_plante=ind;
    gr0.nbre=nbgr;
    T->gt.push_back(gr0);

    //*************les images des quatres etapes de pousse
    CImg<unsigned char> etape1((fold+"etape1.pnm").c_str());
    CImg<unsigned char> etape2((fold+"etape2.pnm").c_str());;
    CImg<unsigned char> etape3((fold+"etape3.pnm").c_str());;
    CImg<unsigned char> etape4((fold+"etape4.pnm").c_str());;
    CImg<unsigned char> etape5((fold+"etape5.pnm").c_str());;
    //***********la redimensionnement des images**********
    etape1.resize(40,40);
    etape2.resize(30,30);
    etape3.resize(40,40);
    etape4.resize(40,40);
    etape5.resize(50,50);
    //***********premier etape de pousse***********
    img.draw_image(x-40,y,0,0,etape1,NO_opacite(etape1));
    dsp.display(img);
    dsp.wait(n);
    //***********deuxieme etape de pousse***********
    //img.draw_rectangle(x,y,x+30,y+30,color);
    img.draw_image(x+4,y,0,0,etape2,NO_opacite(etape2));
    dsp.display(img);
    dsp.wait(n);
    //***********troisieme etape de pousse*********
    //img.draw_rectangle(x,y,x+40,y+40,color);
    img.draw_image(x+4,y,0,0,etape3,NO_opacite(etape3));
    dsp.display(img);
    dsp.wait(n);
    //***********quatrieme etape de pousse********
    //img.draw_rectangle(x+4,y,x+40,y+40,color);
    img.draw_image(x+4,y,0,0,etape4,NO_opacite(etape4));
    dsp.display(img);
    dsp.wait(n);
    //***********cinquieme etape de pousse********
    //img.draw_rectangle(x,y,x+50,y+50,color);//supprimer l'objet
    img.draw_image(x,y,0,0,etape5,NO_opacite(etape5));
    dsp.display(img);
}

//**********ajouter un jardinier dans le jardin*****************
void joueur::ajouter_jardinier(int x,int y,jardin *T)
{
    jardinier jard0;
    time_t begine = time(NULL);
    jard0.position[0]=x;
    jard0.position[1]=y;
    jard0.position_tache[0]=x;
    jard0.position_tache[1]=y;
    jard0.last_hour=begine;
    jard0.moral="content";
    T->jt.push_back(jard0);     //ajouter le jardinier dans le tableau des jardiniers
    img.draw_image(x,y,0,0,jardbas1,NO_opacite(jardbas1));
    int n=T->jt.size();
    img.draw_rectangle(868,430+(n-1)*50+10,tail_aff_long-10,(430+(n-1)*50)+50,color4);
    img.draw_text(868,430+(n-1)*50+10,"je suis content",color3,0,1,23);   //le comportement de jardinier: content au debut
    dsp.display(img);
}

//************animer un jardinier***************
void jardin::animer_jardinier(jardin *T)
{
    int ind;
    int* gh=new int;
    int puo[2];
    int indice[5];
    int indicejard[5];    //un tableau qui contient les indices des jardiniers en etat active
    int m=0;
    int n=0;
    int total_grain=0;
    //************la phase d'affectement des taches pour chaque jardinier********
    string morale;
    for(int i=0; i<(T->jt.size()); i++)
    {
        if (T->jt[i].moral=="content")
        {
            ind=3;  //l'indice de grain
            morale="content";
        }
        else if (T->jt[i].moral=="normal")
        {
            ind=1;  //l'indice de legume
            morale="content";
            indice[n]=i;
            n++;

        }

        else if (T->jt[i].moral=="mecontent")
        {
            ind=2;  //l'indice de fleur
            morale="content";
            indice[n]=i;
            n++;
        }
        puo[0]=T->jt[i].position[0];
        puo[1]=T->jt[i].position[1];
        gh=T->distance_minimal( puo[0], puo[1],T,ind);   //chercher la distance minimal entre le jardinier et la tache
        T->jt[i].position_tache[0]=gh[0];
        T->jt[i].position_tache[1]=gh[1];

        if(puo[0]!=gh[0] || puo[1]!=gh[1])
        {
            if(ind==3)
            {
                for(int i=0; i<(T->gt.size()); i++)
                {
                    if(T->gt[i].position[0]==gh[0] && T->gt[i].position[1]==gh[1])
                        {total_grain=total_grain+T->gt[i].nbre;
                            break;
                        }

                }
            }
            T->supprimer_plante(T,gh[0],gh[1],ind);     //supprimer la plante
            T->jt[i].moral=morale;                  //rafraichir le moral de jardinier
            indicejard[m]=i;
            m++;
        }
    }

    //***************la phase de mouvement des jardiniers************

    ind=1;
    while(ind==1)  //tantque qu'il y a un jardinier qui n'a pas terminer sa mission
    {
        ind=0;
        for(int i=0; i<(T->jt.size()); i++)
        {
            //faire boujer plusieur jardinier au meme temps
            int b=T->jt[i].boujer(T->jt[i].position[0],T->jt[i].position[1],T->jt[i].position_tache[0],T->jt[i].position_tache[1],T,i);
            if(b==1)
                ind=1;
            T->refraichissement(T,indicejard,m);           //rafraichir les elements du jardin
        }
        dsp.display(img);
        T->jou.acheter_pltjard(T);  //verifier si l'utilisateur veut ajouter une plante dans le jardin
    }

    //la mise a jour du temps de chagement de comportement pour les jardiniers qui ont manger ou detruire une fleur
    for(int i=0; i<n; i++)
    {
        time_t begine = time(NULL);
        T->jt[indice[i]].last_hour=begine;
    }
T->somme_grain=T->somme_grain+total_grain;
    //***********afficher le stock de grain************
    affich_grain="le stocke de grain est:"+to_string(T->somme_grain);
    img.draw_rectangle(810,375,tail_aff_long-10,395,color4);
    img.draw_text(810,375,affich_grain.c_str(),color3,0,1,23);
    T->comport_jard(T);     //renitialiser le comportement
    delete gh; //liberer l'espace
}

//**********acheter des plantes et recruter des nouvels jardiniers************
void joueur::acheter_pltjard(jardin *T)
{
    int n;
    string folder;
    //***********ajouter jardinier********
    if(dsp.is_keyJ())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y()); //verifier que cette position est libre
        if(T->somme_grain>=8 && n==0)   //pour recruter un jardinier on a besoin de 8 grains
        {
            T->jou.ajouter_jardinier(dsp.mouse_x(),dsp.mouse_y(),T);
            T->somme_grain-=8;
        }
    }

    //**********ajouter legume************
    if(dsp.is_keyD())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y());
        if(T->somme_grain>=3 && n==0)   //pour ajouter un legume on a besoin de 3 grain
        {
            folder="elements_champs/legume1/";
            T->l.ajouter(4,dsp.mouse_x(),dsp.mouse_y(),T,folder,3);
            T->somme_grain-=3;
        }
    }
    if(dsp.is_keyE())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y());
        if(T->somme_grain>=6 && n==0)   //pour ajouter un legume on a besoin de 6 grain
        {
            folder="elements_champs/legume2/";
            T->l.ajouter(5,dsp.mouse_x(),dsp.mouse_y(),T,folder,6);
            T->somme_grain-=6;
        }
    }
    if(dsp.is_keyF())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y());
        if(T->somme_grain>=8 && n==0)   //pour ajouter un legume on a besoin de 8 grain
        {
            folder="elements_champs/legume3/";
            T->l.ajouter(6,dsp.mouse_x(),dsp.mouse_y(),T,folder,8);
            T->somme_grain-=8;
        }
    }

    //*****************ajouter fleur***************
    if(dsp.is_keyA())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y());
        if(T->somme_grain>=3 && n==0)   //pour ajouter un fleur on a besoin de 3 grain
        {
            folder="elements_champs/fleur1/";
            T->f.ajouter(1,dsp.mouse_x(),dsp.mouse_y(),T,folder,3);
            T->somme_grain-=3;
        }
    }
    if(dsp.is_keyB())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y());
        if(T->somme_grain>=2 && n==0)   //pour ajouter un fleur on a besoin de 2 grain
        {
            folder="elements_champs/fleur2/";
            T->f.ajouter(2,dsp.mouse_x(),dsp.mouse_y(),T,folder,2);
            T->somme_grain-=2;
        }
    }
    if(dsp.is_keyC())
    {
        n=T->position_unique(T,dsp.mouse_x(),dsp.mouse_y());
        if(T->somme_grain>=4 && n==0)   //pour ajouter un fleur on a besoin de 4 grain
        {
            folder="elements_champs/fleur3/";
            T->f.ajouter(3,dsp.mouse_x(),dsp.mouse_y(),T,folder,4);
            T->somme_grain-=4;
        }
    }

    //**********l'affichage de somme de grain************
    affich_grain="le stocke de grain est:"+to_string(T->somme_grain);
    img.draw_rectangle(810,375,tail_aff_long-10,395,color4);
    img.draw_text(810,375,affich_grain.c_str(),color3,0,1,23);
}

//************rechercher la distance minimal entre le jardinier et le plante*************
int* jardin::distance_minimal(int x,int y,jardin* T,int ind)
{
    int dist;
    int pos[2];
    int *val=new int;
    int min=800;   //on prend comme valeur maximal la taille de l'affichage

    legume legu;
    fleur flor;
    grain gran;
    switch (ind)
    {
    case 1:
        if(T->lt.size()==0)   //si il n'existe pas des legumes dans le jardin
        {
            val[0]=x;
            val[1]=y;

        }
        else
            for(auto&  legu:(T->lt))  //parcourir le tableau legume
            {
                pos[0]=legu.position[0];
                pos[1]=legu.position[1];

                dist=sqrt(pow((x-pos[0]),2)+pow((y-pos[1]),2));

                if(dist<min)
                {
                    min=dist;
                    val[0]=pos[0];
                    val[1]=pos[1];

                }
            }
        break;
    case 2:
        if(T->ft.size()==0)         //si il n'existe pas des fleurs dans le jardin
        {
            val[0]=x;
            val[1]=y;

        }
        else
            for(auto&  flor:(T->ft))//parcourir le tableau des fleur
            {
                pos[0]=flor.position[0];
                pos[1]=flor.position[1];

                dist=sqrt(pow((x-pos[0]),2)+pow((y-pos[1]),2));

                if(dist<min)
                {
                    min=dist;
                    val[0]=pos[0];
                    val[1]=pos[1];

                }
            }
        break;
    case 3:
        if(T->gt.size()==0)     //si il n'existe pas des grains sur le jardin
        {
            val[0]=x;
            val[1]=y;

        }
        else
        {
            int i=-1;
            int ind;
            for(auto&  gran:(T->gt))//parcourir le tableau des grains
            {
                i++;
                pos[0]=gran.position[0];
                pos[1]=gran.position[1];

                dist=sqrt(pow((x-pos[0]),2)+pow((y-pos[1]),2));

                if(dist<min)
                {
                    ind=i;
                    min=dist;
                    val[0]=pos[0];
                    val[1]=pos[1];

                }
            }
           // T->somme_grain+=T->gt[ind].nbre;
        }
        break;
    }
    return val;
}

//**********supprimer un plante de la table******************
void jardin::supprimer_plante(jardin*T,int x,int y,int ind)
{
    legume legu;
    fleur fl;
    grain gr;
    int indice=0;
    int compt=0;
    int pos[2];

    switch (ind)
    {
    case 1: //legume
        for(auto&  legu:(T->lt))
        {
            pos[0]=legu.position[0];
            pos[1]=legu.position[1];
            if(pos[0]==x && pos[1]==y)
                indice=compt;
            compt++;
        }
        T->lt.erase(T->lt.begin()+indice);
        break;
    case 2://pour les fleures
        for(auto&  fl:(T->ft))
        {
            pos[0]=fl.position[0];
            pos[1]=fl.position[1];
            if(pos[0]==x && pos[1]==y)
                indice=compt;
            compt++;
        }
        T->ft.erase(T->ft.begin()+indice);
        break;
    case 3:  //grain
        for(auto&  gr:(T->gt))
        {
            pos[0]=gr.position[0];
            pos[1]=gr.position[1];
            if(pos[0]==x && pos[1]==y)
                indice=compt;
            compt++;
        }
        T->gt.erase(T->gt.begin()+indice);
        break;
    }
}

//*************la mise a jour des elements de jardin*****************
void jardin::refraichissement(jardin *T,int *indicejard,int m)
{
    int pos[2];
    grain gra;
    legume legu;
    fleur fl;
    jardinier jard;
    //mise a jour des jardiniers
    for(int i=0; i<(T->jt.size()); i++)
    {
        int ind=0;
        for(int j=0; j<m; j++)
        {
            if(indicejard[j]==i)  //les jardiniers qui sont active
            {
                ind=1;
                break;
            }
        }
        if(ind==0)
        {
            pos[0]=T->jt[i].position[0];
            pos[1]=T->jt[i].position[1];
            img.draw_rectangle(pos[0],pos[1],pos[0]+50,pos[1]+50,color);
            img.draw_image(pos[0],pos[1],0,0,jardbas1,NO_opacite(jardbas1));
        }
    }

    //la mise a jour des grains
    for(auto&  gra:(T->gt))
    {
        pos[0]=gra.position[0];
        pos[1]=gra.position[1];
        if(gra.indice_plante==1)//grain fleur1
            img.draw_image(pos[0],pos[1],0,0,fleur1e1,NO_opacite(fleur1e1));
        else if(gra.indice_plante==2)//grain fleur2
            img.draw_image(pos[0],pos[1],0,0,fleur2e1,NO_opacite(fleur2e1));
        else if(gra.indice_plante==3)//grain fleur3
            img.draw_image(pos[0],pos[1],0,0,fleur3e1,NO_opacite(fleur3e1));
        else if(gra.indice_plante==4)//grain legume1
            img.draw_image(pos[0],pos[1],0,0,legume1e1,NO_opacite(legume1e1));
        else if(gra.indice_plante==5)//grain legume2
            img.draw_image(pos[0],pos[1],0,0,legume2e1,NO_opacite(legume2e1));
        else if(gra.indice_plante==6)//grain legume3
            img.draw_image(pos[0],pos[1],0,0,legume3e1,NO_opacite(legume3e1));
    }

    //la mise a jour des legumes
    for(auto&  legu:(T->lt))
    {
        pos[0]=legu.position[0];
        pos[1]=legu.position[1];
        if(legu.indice_plante==4)
            img.draw_image(pos[0],pos[1],0,0,legume1e5,NO_opacite(legume1e5));
        else if(legu.indice_plante==5)
            img.draw_image(pos[0],pos[1],0,0,legume2e5,NO_opacite(legume2e5));
        else if(legu.indice_plante==6)
            img.draw_image(pos[0],pos[1],0,0,legume3e5,NO_opacite(legume3e5));
    }
    //la mise a jour des les fleures
    for(auto&  fl:(T->ft))
    {
        pos[0]=fl.position[0];
        pos[1]=fl.position[1];
        if(fl.indice_plante==1)
            img.draw_image(pos[0],pos[1],0,0,fleur1e5,NO_opacite(fleur1e5));
        else if(fl.indice_plante==2)
            img.draw_image(pos[0],pos[1],0,0,fleur2e5,NO_opacite(fleur2e5));
        else if(fl.indice_plante==3)
            img.draw_image(pos[0],pos[1],0,0,fleur3e5,NO_opacite(fleur3e5));
    }
    dsp.display(img);
}

//************la mise a jour du comportement jardinier*************
void jardin::comport_jard(jardin* T)
{
    time_t ende= time(NULL);
    for(int i=0; i<T->jt.size(); i++)
    {
        float secondes =ende-(T->jt[i].last_hour);
        string comp=T->jt[i].moral;
        string compf="je suis "+comp;

        img.draw_rectangle(868,430+i*50+10,tail_aff_long-10,(430+i*50)+50,color4);
        img.draw_text(868,430+i*50+10,compf.c_str(),color3,0,1,23);

        if(secondes>12)  //la durée de changement de comportement
        {
            if(T->jt[i].moral=="content")
            {
                T->jt[i].last_hour=ende;
                T->jt[i].moral="normal";

                img.draw_rectangle(868,430+i*50+10,tail_aff_long-10,(430+i*50)+50,color4);
                img.draw_text(868,430+i*50+10,"je suis normal",color3,0,1,23);
            }
            else if(T->jt[i].moral=="normal")
            {
                T->jt[i].last_hour=ende;
                T->jt[i].moral="mecontent";

                img.draw_rectangle(868,430+i*50+10,tail_aff_long-10,(430+i*50)+50,color4);
                img.draw_text(868,430+i*50+10,"je suis mecontent",color3,0,1,23);
            }
        }
    }
    dsp.display(img);
}

//*************faire boujer les jardiniers vers leurs taches***********
int jardinier::boujer(int x1,int y1,int x2,int y2,jardin *T,int i)
{
    if(x1<x2)   //bouger vers la droite
    {
        dsp.wait(40);
        img.draw_rectangle(x1,y1,x1+50,y1+50,color);//supprimer l'objet
        x1=x1+1;
        T->jt[i].position[0]=x1;
        img.draw_image(x1,y1,0,0,jarddroit1,NO_opacite(jarddroit1));
        return 1;
    }
    else if (x1>x2)     //bouger vers la gauche
    {
        dsp.wait(40);
        img.draw_rectangle(x1,y1,x1+50,y1+50,color);//supprimer l'objet
        x1=x1-1;
        T->jt[i].position[0]=x1;
        img.draw_image(x1,y1,0,0,jardgauche1,NO_opacite(jardgauche1));

        return 1;
    }
    else if(y1<y2)      //bouger vers le bas
    {
        dsp.wait(40);
        img.draw_rectangle(x1,y1,x1+50,y1+50,color);//supprimer l'objet
        y1=y1+1;
        T->jt[i].position[1]=y1;
        img.draw_image(x1,y1,0,0,jardbas1,NO_opacite(jardbas1));

        return 1;

    }
    else if(y1>y2)      //bouger vers le haut
    {
        dsp.wait(40);
        img.draw_rectangle(x1,y1,x1+50,y1+50,color);//supprimer l'objet
        y1=y1-1;
        T->jt[i].position[1]=y1;
        img.draw_image(x1,y1,0,0,jardhaut1,NO_opacite(jardhaut1));

        return 1;
    }
    return 0;

}

//*******verifier que l'emplacement dont on veut ajouter le plant est libre************
int jardin::position_unique(jardin *T,int x,int y)
{
    int indice=0;
    //pour les jardiniers
    for(int i=0; i<T->jt.size(); i++)
    {
        if (x>=T->jt[i].position[0] && x<(T->jt[i].position[0]+50) && y>=T->jt[i].position[1] && y<(T->jt[i].position[1]+50))
        {
            indice=1;
            break;
        }
    }
    //pour les fleures
    for(int i=0; i<T->ft.size(); i++)
    {
        if (x>=T->ft[i].position[0] && x<(T->ft[i].position[0]+50) && y>=T->ft[i].position[1] && y<(T->ft[i].position[1]+50))
        {
            indice=1;
            break;
        }
    }
    //pour les legumes
    for(int i=0; i<T->lt.size(); i++)
    {
        if (x>=T->lt[i].position[0] && x<(T->lt[i].position[0]+50) && y>=T->lt[i].position[1] && y<(T->lt[i].position[1]+50))
        {
            indice=1;
            break;
        }
    }
    //pour les grains
    for(int i=0; i<T->gt.size(); i++)
    {
        if (x>=T->gt[i].position[0] && x<(T->gt[i].position[0]+40) && y>=T->gt[i].position[1] && y<(T->gt[i].position[1]+40))
        {
            indice=1;
            break;
        }
    }
    if(x>70 && x<(tail_champ_long+50) && y>70 && y<(tail_champ_larg+120) && indice==0)
        return 0;
    return 1;
}
