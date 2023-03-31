
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;


/*
 * Exemple de definition de fonction permettant la creation du Mesh de votre Objet.
 */
//void ViewerEtudiant::init_votreObjet()
//{
//}
void ViewerEtudiant::init_cube()
{
    // 8 sommets 0 1 2 3 4 5 6 7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    // 6 faces 0 1 2 3 4 5
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    // les 6 normales pour chacune des faces
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    // Choix des primitives OpenGL employées
    m_cube = Mesh(GL_TRIANGLE_STRIP);

    for (int i = 0; i < 6; i++) // i = numéro de la face
    {
        //couleur du cube
        //m_cube.color(0, 1, 0)
        // La normale à la face
        m_cube.normal(n[i][0], n[i][1], n[i][2]);
        // Les 4 sommets de la face
        m_cube.color(0, 1, 0);
        m_cube.vertex(pt[f[i][0]][0], pt[f[i][0]][1], pt[f[i][0]][2]);
        m_cube.color(1, 0, 0);
        m_cube.vertex(pt[f[i][1]][0], pt[f[i][1]][1], pt[f[i][1]][2]);
        m_cube.color(0, 0, 1);
        m_cube.vertex(pt[f[i][3]][0], pt[f[i][3]][1], pt[f[i][3]][2]);
        m_cube.color(1, 0, 1);
        m_cube.vertex(pt[f[i][2]][0], pt[f[i][2]][1], pt[f[i][2]][2]);
        m_cube.restart_strip(); // Demande un nouveau strip
    }
}

void ViewerEtudiant::init_cylindre()
{
    // Variation de l’angle de 0 à 2!
    const int div = 25;
    float alpha;
    float step = 2.0 * M_PI / (div);
    // Choix primitive OpenGL
    m_cylindre = Mesh(GL_TRIANGLE_STRIP);
    m_cylindre.color(1, 1, 1);
    for (int i = 0; i <= div; ++i)
    {
        // Variation de l’angle de 0 à 2!
        alpha = i * step;
        m_cylindre.normal(Vector(cos(alpha), 0, sin(alpha)));
        m_cylindre.texcoord(i / div, 1);
        m_cylindre.vertex(Point(cos(alpha), -1, sin(alpha)));
        m_cylindre.normal(Vector(cos(alpha), 0, sin(alpha)));
        m_cylindre.texcoord(i / div, 0);
        m_cylindre.vertex(Point(cos(alpha), 1, sin(alpha)));
    }
}//void

void ViewerEtudiant::init_cone()
{
    // Variation de l’angle de 0 à 2!
    const int div = 25;
    float alpha;
    float step = 2.0 * M_PI / (div);
    // Choix de la primitive OpenGL
    m_cone = Mesh(GL_TRIANGLE_STRIP);
    for (int i = 0;i <= div;++i)
    {
        alpha = i * step; // Angle varie de 0 à 2!
        m_cone.normal(
            Vector(cos(alpha) / sqrtf(2.f),
                1.f / sqrtf(2.f),
                sin(alpha) / sqrtf(2.f)));
        m_cone.vertex(Point(cos(alpha), 0, sin(alpha)));
        m_cone.normal(
            Vector(cos(alpha) / sqrtf(2.f),
                1.f / sqrtf(2.f),
                sin(alpha) / sqrtf(2.f)));
        m_cone.vertex(Point(0, 1, 0));
    }
}

void ViewerEtudiant::init_sphere()
{
    // Variation des angles alpha et beta
    const int divBeta = 16;
    const int divAlpha = divBeta / 2;
    float beta, alpha, alpha2;
    // Choix de la primitive OpenGL
    m_sphere = Mesh(GL_TRIANGLE_STRIP);
    // Variation des angles alpha et beta
    for (int i = 0; i < divAlpha; ++i)
    {
        alpha = -0.5f * M_PI + float(i) * M_PI / divAlpha;
        alpha2 = -0.5f * M_PI + float(i + 1) * M_PI / divAlpha;
        for (int j = 0; j <= divBeta; ++j)
        {
            beta = float(j) * 2.f * M_PI / (divBeta);
            m_sphere.normal(Vector(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)));
            m_sphere.texcoord(beta / (M_PI * 2.0), 0.5 + alpha / M_PI);
            m_sphere.vertex(Point(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)));
            m_sphere.normal(Vector(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));
            m_sphere.texcoord(beta / (M_PI * 2.0), 0.5 + alpha2 / M_PI);
            m_sphere.vertex(Point(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));
        } // boucle sur les j, angle beta, dessin des sommets d’un cercle
        m_sphere.restart_strip(); // Demande un nouveau strip
    } // boucle sur les i, angle alpha, sphère = superposition de cercles
}

void ViewerEtudiant::init_carre() {

    // Choix de la primitive OpenGL
    m_carre = Mesh(GL_TRIANGLE_STRIP);

    // Vecteur normal a la face
    m_carre.normal(0, 0, -1);

    m_carre.texcoord(0, 0);
    m_carre.vertex(-1, -1, 0);
    m_carre.texcoord(1,0);
    m_carre.vertex( 1, -1, 0);
    m_carre.texcoord(0, 1);
    m_carre.vertex(-1,1, 0);  
    m_carre.texcoord(1, 1);
    m_carre.vertex( 1,1, 0);
}

void ViewerEtudiant::init_disque() {
    const int div = 25;
    float alpha;
    float step = 2.0 * M_PI / div;

    
    m_disque = Mesh(GL_TRIANGLE_FAN);
    m_disque.normal(Vector(0, 0, 1));
    m_disque.vertex(Point(0, 0, 0));


    for(int i=0;i<=div;i++){
        alpha = i * step;
        m_disque.color(0, 0, 0);
        m_disque.normal(Vector(0, 0, 1));
        m_disque.vertex(Point(sin(alpha), cos(alpha), 0));
    }

}
void ViewerEtudiant::init_posArbre(const Image& im) {
    srand((unsigned int)time(NULL));
    for (int w = 0; w < 10; w++)
    {
        TabPosition[w][0] = rand() % (im.width() - 2);
        TabPosition[w][2] = rand() % (im.height() - 1);
        TabPosition[w][1] = 25.f * im(TabPosition[w][0], TabPosition[w][2]).r +10; // Y 

    }
}


//code pour le terrain
Vector TerrainNormal(const Image& im, const int i, const int j) {
    //Calcul de la normale au point(i,j) de l'image
    int ip = i - 1;
    int in = i + 1;
    int jp = j - 1;
    int jn = j + 1;

    Vector a(ip, im(ip, j).r, j);
    Vector b(in, im(in, j).r, j);
    Vector c(i, im(i, jp).r, jp);
    Vector d(i, im(i, jn).r, jn);

    Vector ab = normalize(b - a);
    Vector cd = normalize(d - c);

    Vector n = cross(cd , ab);

    return n;
}


void ViewerEtudiant::init_terrain(Mesh& m_terrain, const Image& im) {
    m_terrain = Mesh(GL_TRIANGLE_STRIP); //Choix primitive OpenGL

    for (int i = 1;i < im.width() - 2;++i) {
        for (int j = 1;j < im.height() - 1;++j) {
            m_terrain.normal(TerrainNormal(im, i + 1, j));
            m_terrain.texcoord((float)i / (im.width() - 2), (float)j / (im.height() - 1));
            m_terrain.vertex(Point(i + 1, 25.f * im(i + 1, j).r, j));

            
            m_terrain.normal(TerrainNormal(im, i , j));
            m_terrain.texcoord((float)i / (im.width() - 2),(float) j / (im.height() - 1));
            m_terrain.vertex(Point(i , 25.f * im(i , j).r, j));
        }
        m_terrain.restart_strip();//Affichage en triangle_strip par bande
    }
}

void ViewerEtudiant::init_cubemap()
{
    // 8 sommets 0 1 2 3 4 5 6 7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    // 6 faces 0 1 2 3 4 5
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    // les 6 normales pour chacune des faces
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {1,0,0}, {0,0,1}, {0,0,-1} };
    //les coordonées de la texture par rapport a chaque point de chaque face
    static float tc[6][4][2] = {
        {{0.25,0},         {0.5 ,0},         {0.5,1 / 3.f},        {0.25,1 / 3.f}},//premier face
        {{0.5 ,1},         {0.25,1},         {0.25,2 / 3.f},       {0.5,2 / 3.f}},
        {{0.5,1 / 3.f},    {0.75,1 / 3.f},   {0.75,2 / 3.f},       {0.5,2 / 3.f}},
        {{0,1 / 3.f},      {0.25,1 / 3.f},   {0.25,2 / 3.f},       {0,2 / 3.f}},
        {{0.25,1 / 3.f},   {0.5,1 / 3.f},    {0.5,2 / 3.f},        {0.25,2 / 3.f}},
        {{0.75,1 / 3.f},   {1,1 / 3.f},      {1,2 / 3.f},          {0.75,2 / 3.f}}//dernière face

    };
    // Choix des primitives OpenGL employées 
    m_cubemap = Mesh(GL_TRIANGLE_STRIP);

    for (int i = 0; i < 6; i++) // i = numéro de la face
    {
        //couleur du cube
        // La normale à la face
        m_cubemap.normal(-n[i][0], -n[i][1], -n[i][2]);
        // Les 4 sommets de la face
        m_cubemap.texcoord(tc[i][0][0], tc[i][0][1]);
        m_cubemap.vertex(pt[f[i][0]][2], pt[f[i][0]][1], pt[f[i][0]][0]);

        m_cubemap.texcoord(tc[i][1][0], tc[i][1][1]);
        m_cubemap.vertex(pt[f[i][1]][2], pt[f[i][1]][1], pt[f[i][1]][0]);

        m_cubemap.texcoord(tc[i][3][0], tc[i][3][1]);
        m_cubemap.vertex(pt[f[i][3]][2], pt[f[i][3]][1], pt[f[i][3]][0]);

        m_cubemap.texcoord(tc[i][2][0], tc[i][2][1]);
        m_cubemap.vertex(pt[f[i][2]][2], pt[f[i][2]][1], pt[f[i][2]][0]);
        m_cubemap.restart_strip(); // Demande un nouveau strip
    }
}

//création d'une texture animé
void ViewerEtudiant::init_textanime() {

    // Choix de la primitive OpenGL
    m_textanime = Mesh(GL_TRIANGLE_STRIP);

    // Vecteur normal a la face
    m_textanime.normal(0, 0, -1);

    m_textanime.texcoord(0 ,0);
    m_textanime.vertex(-1, -1, 0);
    m_textanime.texcoord(1.0/10.0, 0);
    m_textanime.vertex(1, -1, 0);
    m_textanime.texcoord(0, 1);
    m_textanime.vertex(-1, 1, 0);
    m_textanime.texcoord(1.0 / 10.0, 1);
    m_textanime.vertex(1, 1, 0);
      
 }

//extrusion vase
void ViewerEtudiant::create_vertex_normal_vase() {
    // Nombre de points de la silhouette 2D
    vase_NBPT = 10; // déclaré dans la class ViewerEtudiant
    /// Points de la silhouette 2D
    vase_p[0] = Point(0.3, 0, 0);
    vase_p[1] = Point(0.2, 0.2, 0);
    vase_p[2] = Point(0.4, 0.4, 0);
    vase_p[3] = Point(0.5, 0.6, 0);
    vase_p[4] = Point(0.6, 0.8, 0);
    vase_p[5] = Point(0.7, 1.0, 0);
    vase_p[6] = Point(0.8, 1.2, 0);
    vase_p[7] = Point(0.8, 1.4, 0);
    vase_p[8] = Point(0.8, 1.6, 0);
    vase_p[9] = Point(0.5, 1.8, 0);

    // Nombre de rotations pour créer le vase par rotation
    vase_NBROT = 20; // déclaré dans la class ViewerEtudiant

    for (int i = 0; i < vase_NBROT; i++) {
        //i indice rotation (angle : 2 pi * i / nbrot)
        // Angle qui varie de 0 à 2 pi
        float teta = 2 * M_PI * i / vase_NBROT;
        // Matrice de rotation de l’angle theta autour axe des y
        // en coordonnées homogènes : 4 x 4
        float mat[16] = {
        cos(teta), 0, -sin(teta), 0,
        0, 1, 0, 0,
        sin(teta), 0, cos(teta), 0,
        0, 0, 0, 1 };
        // Calcul des coordonnées des sommets
        for (int j = 0; j < vase_NBPT; j++) {
            // j indice du point de la silhouette
            // Application de ma matrice de rotation au point j qui subit la rotation (2 pi * i / nbrot)
            vase_v[i][j].x = mat[0] * vase_p[j].x + mat[1] * vase_p[j].y + mat[2] * vase_p[j].z + mat[3] * 1;
            vase_v[i][j].y = mat[4] * vase_p[j].x + mat[5] * vase_p[j].y + mat[6] * vase_p[j].z + mat[7] * 1;
            vase_v[i][j].z = mat[8] * vase_p[j].x + mat[9] * vase_p[j].y + mat[10] * vase_p[j].z + mat[11] * 1;
        }//for_j
    }//for_i

    // Initialise à 0 les normales
    for (int i = 0; i < vase_NBROT; i++)
        for (int j = 0; j < vase_NBPT; j++)
            vase_vn[i][j] = Vector(0, 0, 0);

    for (int i = 0; i < vase_NBROT; i++) {
        for (int j = 0; j < vase_NBPT - 1; j++) {
            Vector a, b, vntmp;
            a = normalize(vase_v[i][j] - vase_v[i][j + 1]);
            b = normalize(vase_v[i][j] - vase_v[(i + 1) % vase_NBROT][j]);
            vntmp = cross(a, b); // Produit vectoriel =
            // On répercute cette normale sur les 4 sommets de la face
            // (accumulation des normales)
            vase_vn[i][j] = vntmp + vase_vn[i][j];
            vase_vn[(i + 1) % vase_NBROT][j] = vntmp + vase_vn[(i + 1) % vase_NBROT][j];
            vase_vn[(i + 1) % vase_NBROT][j + 1] = vntmp + vase_vn[(i + 1) % vase_NBROT][j + 1];
            vase_vn[i][j + 1] = vntmp + vase_vn[i][j + 1];
        }
    }

    // Normale à un sommet = moyenne de la normale des 4 sommets de la face
    for (int i = 0; i < vase_NBROT; i++) {
        for (int j = 0; j < vase_NBPT; j++) {
            float q = 4.0f;
            if (j == vase_NBPT - 1) // Points du bord
                q = 2.0f;
            vase_vn[i][j] = vase_vn[i][j] / q;
        }//for_i
    }//for_j
}//void_create_vertex_normal_vase

void ViewerEtudiant::init_vase()
{
    m_vase = Mesh(GL_TRIANGLES); // Primitive OpenGL
    m_vase.color(1.0, 1.0, 1.0); // Couleur du Mesh
    for (int i = 0; i < vase_NBROT; i++) {
        for (int j = 0; j < vase_NBPT - 1; j++) { // Attention boucle de 0 à vase_NBPT-2 car (j+1)
        // Premier triangle
        m_vase.texcoord(0, 0);
        m_vase.normal(vase_vn[i][j]);
        m_vase.vertex(vase_v[i][j]);

        m_vase.texcoord(1, 1);
        m_vase.normal(vase_vn[(i + 1) % vase_NBROT][j + 1]);
        m_vase.vertex(vase_v[(i + 1) % vase_NBROT][j + 1]);

        m_vase.texcoord(1, 0);
        m_vase.normal(vase_vn[(i + 1) % vase_NBROT][j]);
        m_vase.vertex(vase_v[(i + 1) % vase_NBROT][j]);

        // Second triangle
        m_vase.texcoord(0, 0);
        m_vase.normal(vase_vn[i][j]);
        m_vase.vertex(vase_v[i][j]);

        m_vase.texcoord(0, 1);
        m_vase.normal(vase_vn[i][j + 1]);
        m_vase.vertex(vase_v[i][j + 1]);

        m_vase.texcoord(1, 1);
        m_vase.normal(vase_vn[(i + 1) % vase_NBROT][j + 1]);
        m_vase.vertex(vase_v[(i + 1) % vase_NBROT][j + 1]);
        }//for_j
    }//for_i
}//void



/*
 * Fonction dans laquelle les initialisations sont faites.
 */
int ViewerEtudiant::init()
{
    Viewer::init();
    
    //chargement de l'image servant de carte de hauteur
    const Image m_terrainAlti = read_image("data/terrain/mapheight.png");

    m_camera.lookat( Point(0,0,0), 150 );
    gl.light(Point(-100, 100, -100), White());

    //Création du Mesh du terrain
    init_terrain(m_terrain, m_terrainAlti);
    
    /// Appel des fonctions init_votreObjet pour creer les Mesh
    init_cube();
    init_cylindre();
    init_cone();
    init_sphere();
    init_carre();
    init_disque();
    init_cubemap();
    init_textanime();
    init_posArbre(m_terrainAlti);

    // Calcul des coordonnées des sommets et des normales
    create_vertex_normal_vase();
    // Création du Mesh à partir des coordonnées calculées
    init_vase();

    //textures
    terrain_tex = read_texture(0, "data/terrain/mapvertv2.png");
    cubemap_texture = read_texture(0, "data/cubemap/cubevertv2.jpg");
    pneu_texture = read_texture(0, "data/kart/pneu.jpg");
    casque_texture = read_texture(0, "data/kart/casque.png");
    metal_texture = read_texture(0, "data/kart/metal.jpg");
    tree_texture = read_texture(0, "data/billboard/arbre2.png");
    oiseau_texture = read_texture(0, "data/divers/oiseau.png");
    or_texture = read_texture(0, "data/divers/or.jpg");

    //animation de la voiture
    //m_anim.init(smart_path("data/animation/anim1.ani"));

    return 0;
}


/*
 * Exemple de definition de fonction permettant l affichage
 * de 'votreObjet' subissant la Transform T
 */
//void ViewerEtudiant::draw_votreObjet(const Transform& T)
//{
//void
// gl.texture(....);
// gl.model( T );
// gl.draw( m_votreObjet );
//}

void ViewerEtudiant::draw_cube(const Transform& T)
{
    gl.model(T);
    gl.draw(m_cube);
}

void ViewerEtudiant::draw_cylindre(const Transform& T)
{
    gl.texture(or_texture);
    gl.model(T);
    gl.draw(m_cylindre);
}

void ViewerEtudiant::draw_cone(const Transform& T)
{
    gl.model(T);
    gl.draw(m_cone);
}

void ViewerEtudiant::draw_sphere(const Transform& T)
{
    gl.model(T);
    gl.draw(m_sphere);
}

void ViewerEtudiant::draw_carre(const Transform& T) {
    gl.model(T);
    gl.draw(m_carre);
}

void ViewerEtudiant::draw_disque(const Transform& T) {
    gl.model(T);
    gl.draw(m_disque);
}

void ViewerEtudiant::draw_kart(const Transform& T) {
    //partie principale du kart
    gl.texture(casque_texture);
    gl.model(T*Translation(0,-0.25,0) * Scale(6,1,1.5));
    gl.draw(m_sphere);

    //cardan 1 et 2
    gl.texture(metal_texture);
    gl.model(T * Translation(3, -0.5, 0) * Scale(0.25, 0.25, 3.25) * RotationX(90));
    gl.draw(m_cylindre);
    gl.model(T * Translation(-3, -0.5, 0) * Scale(0.25, 0.25, 3.25) * RotationX(90));
    gl.draw(m_cylindre);

    //première roue
    gl.texture(pneu_texture);
    gl.model(T * Translation(3, -0.5, 3.5) * Scale(1.5, 1.5, 0.5) * RotationX(90));
    gl.draw(m_cylindre);
    gl.model(T * Translation(3, -0.5, 3.5) * Scale(1.5 ,1.5 , 0.5) * RotationX(180));
    gl.draw(m_disque);
    gl.model(T * Translation(3, -0.5, 3) * Scale(1.5, 1.5, 0.5) );
    gl.draw(m_disque);

    //deuxieme
    gl.texture(pneu_texture);
    gl.model(T * Translation(-3, -0.5, 3.5) * Scale(1.5, 1.5, 0.5) * RotationX(90));
    gl.draw(m_cylindre);
    gl.model(T * Translation(-3, -0.5, 3.5) * Scale(1.5, 1.5, 0.5) * RotationX(180));
    gl.draw(m_disque);
    gl.model(T * Translation(-3, -0.5, 3) * Scale(1.5, 1.5, 0.5) );
    gl.draw(m_disque);

    //troisieme
    gl.texture(pneu_texture);
    gl.model(T * Translation(3, -0.5, -3.5) * Scale(1.5, 1.5, 0.5) * RotationX(90));
    gl.draw(m_cylindre);
    gl.model(T * Translation(3, -0.5, -3.5) * Scale(1.5, 1.5, 0.5) );
    gl.draw(m_disque);
    gl.model(T * Translation(3, -0.5, -3) * Scale(1.5, 1.5, 0.5) * RotationX(180));
    gl.draw(m_disque);

    //quatrieme roue
    gl.texture(pneu_texture);
    gl.model(T * Translation(-3, -0.5, -3.5) * Scale(1.5, 1.5, 0.5) * RotationX(90));
    gl.draw(m_cylindre);
    gl.model(T * Translation(-3, -0.5, -3.5) * Scale(1.5, 1.5, 0.5));
    gl.draw(m_disque);
    gl.model(T * Translation(-3, -0.5, -3) * Scale(1.5, 1.5, 0.5)* RotationX(180));
    gl.draw(m_disque);

    //conducteur
    gl.texture(casque_texture);
    gl.model(T * Translation(1, 0.5, 0) * Scale(0.5, 1.25, 0.5));
    gl.draw(m_sphere);
    gl.model(T * Translation(1, 1.5, 0) * Scale(0.75, 0.5, 0.75));
    gl.draw(m_sphere);

    //vollant
    gl.model(T * Translation(0, 1, 0) * Scale(0.1, 0.5, 0.5));
    gl.draw(m_sphere);

}

void ViewerEtudiant::draw_terrain(const Transform& T){
    
    gl.texture(terrain_tex);
    gl.model(T);
    gl.draw(m_terrain);
}

void ViewerEtudiant::draw_arbre(const Transform& T){
    int rotation = 0; //initialise la variable rotation a 0

    for (int w = 0; w < 10; w++){
         Transform Tc = T * Translation(TabPosition[w][0], TabPosition[w][1], TabPosition[w][2]) ; ;
         for (int rotation = 0; rotation <= 375; rotation += 25) // boucle pour faire la rotation qui change de 25 degre a chaque iteration
         {  
            gl.texture(tree_texture); //applique la texture sur le quad
            gl.model(Tc  * RotationY(rotation)  * Scale(10, 10, 10) ); // applique la rotation a chaque iteration
            gl.draw(m_carre); // affichage
         }
    }

}

void ViewerEtudiant::draw_cubemap(const Transform& T) {
    gl.texture(cubemap_texture);
    gl.model(T * Translation(0,20,0)* Scale(125, 125, 125));
    gl.draw(m_cubemap);

}

void ViewerEtudiant::draw_oiseau(const Transform& T) {
    gl.texture(oiseau_texture);
    gl.model(T * Translation(10, 10, 0)*Scale(5,5,5));
    gl.draw(m_textanime);
}

void ViewerEtudiant::draw_vase(const Transform& T) {
    gl.texture(or_texture);
    gl.model(T);
    gl.draw(m_vase);
}
/*
 * Fonction dans laquelle les appels pour les affichages sont effectues.
 */
int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manageCameraLight();

    gl.camera(m_camera);

    gl.alpha(0.5f);
    
    
    /// Appel de la fonction render() de la class Viewer
    /// pour que vous voyez apparaitre un premier objet
    /// a supprimer ensuite
    //Viewer::render();
    
    
    /// Appel des fonctions du type 'draw_votreObjet'
    Transform T_cube = RotationX(45)*Translation(20,20,0)* Scale(2, 1, 1);
    draw_cube(T_cube);

    Transform T_cy = Translation(16, 20, 0);
    draw_cylindre(T_cy);

    Transform T_co = Translation(16, 21, 0);
    draw_cone(T_co);

    Transform T_sp = Translation(20, 20, 0);
    draw_sphere(T_sp);

    
    draw_kart(Tkart * Translation(-20, -6, 10) * RotationY(-90));

    Transform T_carre = Translation(0, 1, 0) ;
    //draw_carre(T_carre);

    Transform T_terrain = Translation(-120, 3, -120) * Scale(0.4, 0.4, 0.4);
    draw_terrain(T_terrain);

    draw_arbre(T_terrain);

    draw_cubemap(Identity());
    
    Transform T_oiseau = Translation(0, 20, -80);
    draw_oiseau(T_oiseau);

    Transform t_vase = Translation(0, 5, 0)* Scale(5,5,5);
    draw_vase(t_vase);

    return 1;
    
}


/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    
    float temps1 = time / 150;
    int temps2 = int(temps1);

    //pour faire une texture animé
    compteurTps = temps2; // on crée un compteur pour l'utiliser pour la texture animée;

    int nt = compteurTps % 10;

    m_textanime.texcoord(0, nt * (1.0 / 10.0) , 0 );
    m_textanime.texcoord(1, nt * (1.0 / 10.0)+ (1.0/10.0),0);
    m_textanime.texcoord(2, nt * (1.0 / 10.0) , 1);
    m_textanime.texcoord(3, nt * (1.0 / 10.0) + (1.0 / 10.0), 1);

    
    // animation du Kart
    float ts = time / 300.0;

    

    int te = int(ts);
    int ite = te % m_anim.nb_points();
    int ite_suiv = (te + 1) % m_anim.nb_points();
    int ite_suiv_suiv = (ite_suiv + 1) % m_anim.nb_points();

    Point p0 = m_anim[ite];
    Point p1 = m_anim[ite_suiv];
    Point p2 = m_anim[ite_suiv_suiv];

    float poids = ts - te;

    Vector pos = Vector(p0) + (Vector(p1) - Vector(p0)) * poids;
    Vector pos_suiv = Vector(p1) + (Vector(p2) - Vector(p1)) * poids;

    Vector dir = normalize(pos_suiv - pos);
    Vector up = Vector(0, 1, 0);
    Vector codir = cross(dir, up);


    Tkart = Transform(dir, up, codir, pos);
    
    return 0;
}


/*
 * Constructeur.
 */

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
}


/*
 * Programme principal.
 */
int main( int argc, char **argv )
{
    ViewerEtudiant v;
    v.run();
    return 0;
}
