
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"



class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int update( const float time, const float delta );
    int compteurTps;

protected:
    
    /* -----------------------------------------
     Pour creer un nouvel objet vous devez :
     
     1. declarer ici dans le fichier Viewer_etudiant.h
     le Mesh,
     la texture si besoin,
     une fonction 'init_votreObjet'
     une fonction 'draw_votreObjet(const Transform& T)'
     

     --- Rq : regarder comment cela est effectue dans le fichier Viewer.h
     
     
     2. Appeler la fonction 'init_votreObjet' dans la fonction 'init' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp
     
     
     3. Appeler la fonction 'draw_votreObjet' dans la fonction 'render' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp
     
      ----------------------------------------- */
    
    
    /// Declaration des Mesh
    // 1/2 :: Manipulation des formes de base et d'une forme complexe
    Mesh m_cube;            // Mesh d'une forme de base
    Mesh m_cylindre;
    Mesh m_cone;
    Mesh m_sphere;
    Mesh m_disque;

    GLuint pneu_texture; // texture du pneu
    GLuint casque_texture;// texture d'un casque
    GLuint metal_texture;// texture du metal


    void init_cube();       //fonction créant un cube
    void init_cylindre();   //fonction créant un cylindre
    void init_cone();       //fonction créant un cone
    void init_sphere();     //fonction créant une sphere
    void init_disque();     //fonction créant un disque

    void draw_cube(const Transform& T); // affichage de forme de base
    void draw_cylindre(const Transform& T);
    void draw_cone(const Transform& T);
    void draw_sphere(const Transform& T);
    void draw_disque(const Transform& T);

    void draw_kart(const Transform& T);// affichage d'un objet complexe : kart
    
    Transform Tkart;//animation

    //  3:: billboard(arbre) 
    Mesh m_carre;
    GLuint tree_texture;// texture arbre

    float TabPosition[10][3]; //création de plusieurs arbres 
    void init_posArbre(const Image& im);

    void init_carre();      //fonction créant un carré

    void draw_carre(const Transform& T); //affichage d'un carré
    void draw_arbre(const Transform& T); //affichage des arbres


    // 3 :: terrain 
    Mesh m_terrain;
    GLuint terrain_tex; // Texture du terrain

    void init_terrain(Mesh& m_terrain, const Image& im);    //fonction créant un terrain

    void draw_terrain(const Transform& T);                  //affichage du terrain

    // 3 :: Cubemap
    Mesh m_cubemap;
    GLuint cubemap_texture; // texture du cubemap

    void init_cubemap();    // fonction créant un cube visible del'interrieur

    void draw_cubemap(const Transform& T); //affichage du cubemap

    //4 :: création d'un objet par extrusion
    Mesh m_vase; // on déclare le mesh du vase

    int vase_NBPT; // les éléments nécessaire a la fabrication de la coupe
    Point vase_p[10];
    int vase_NBROT;
    Point vase_v[20][10];
    Vector vase_vn[20][10];

    GLuint or_texture;// texture de la coupe en or

    void create_vertex_normal_vase(); //fonction nécéssaire a la création d'un vase
    void init_vase();
    void draw_vase(const Transform& T);// affichage du vase

    
    // 5 :: Texture animée
    Mesh m_textanime;

    GLuint oiseau_texture;// texture de l'oiseau

    void init_textanime(); // création d'un quad avec une texture oiseau

    void draw_oiseau(const Transform& T);

    /// Declaration des fonctions draw_votreObjet(const Transform& T)
    
    
    
    
    
    
    
    
    

    

    
};



#endif
