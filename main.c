/*******************************************************************
BITMAP : Charger une image depuis un fichier .bmp vers une BITMAP
         et afficher cette BITMAP au milieu de l'écran

         L'image s'apppelle "bonhomme" et doit être mise
         au niveau du répertoire de projet (avec le main.c)
         à moins de modifier le chemin d'accès ci dessous...

         Appuyer sur espace pour afficher l'image à une position aléatoire
         Appuyer sur la flèche du haut pour faire monter l'image
         Appuyer sur la flèche du bas pour faire descendre l'image
         Appuyer sur la touche Entrée pour recentrer l'image
*******************************************************************/

#include <allegro.h>
#include <time.h>

void something() {
    printf("hello git");
}
void initialisation_allegro();
// Exo 1

/*int main()
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *image;
    int touche;
    int x,y;
    // Il y aura un peu de hasard...
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Chargement de l'image (l'allocation a lieu en même temps)
    image=load_bitmap("bonhomme.bmp",NULL);

    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    if (!image)
    {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Affichage de l'image sur l'écran au milieu
    blit(image,screen,0,0, (SCREEN_W-image->w)/2, (SCREEN_H-image->h)/2, image->w, image->h);
    x=(SCREEN_W-image->w)/2;
    y=(SCREEN_H-image->h)/2;
    int depy=5;
    // Boucle interactive
    while (!key[KEY_ESC]) {
        if(keypressed()){
            touche=readkey();
            touche=touche>>8;
            if (touche==KEY_SPACE){
                x=rand()%(SCREEN_W-image->w);
                y=rand()%(SCREEN_H-image->h);
            }
            if (touche==KEY_UP) {
                if (y-depy>0) y-=depy;
            }
            if (touche==KEY_DOWN) {
                if (y+image->h+depy<SCREEN_H) y+=depy;
            }
            if (touche==KEY_ENTER) {
                x=(SCREEN_W-image->w)/2;
                y=(SCREEN_H-image->h)/2;
            }
            if (touche==KEY_LEFT) {
                if (x-depy>0) x-=depy;
            }
            if (touche==KEY_RIGHT) {
                if (x+image->w+depy<SCREEN_W) x+=depy;
            }
            clear_bitmap(screen);
            blit(image,screen,0,0, x, y, image->w, image->h);
        }
    }
    //quand on a plus besoin de la bitmap, on la détruit
    destroy_bitmap(image);
    allegro_exit();
    return 0;
}
END_OF_MAIN();*/

void initialisation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici : identique à celle du bureau

    //sélection du mode graphique
    // avec choix d'un driver+mode+résolution de l'écran
    /// si échec, le programme s'arrête
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}


// Exo 2

/*int main() {
    BITMAP *image;
    BITMAP *masque;
    BITMAP *buffer;

    initialisation_allegro();
    set_color_depth(24);
    // Chargement de l'image (l'allocation a lieu en même temps)
    image = load_bitmap("galaxie-andromede.bmp", NULL);

    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    if (!image) {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    masque = create_bitmap(SCREEN_W, SCREEN_H);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(masque, makecol(0, 0, 0)); // remplir en noir

    int fenetre_w = 100, fenetre_h = 100; //  fenêtre de révélation

    while (!key[KEY_ESC]) {

        clear_bitmap(buffer);

        blit(image, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(buffer, masque, 0, 0); // masque sur l'image

        blit(image, buffer,
             mouse_x - fenetre_w / 2, mouse_y - fenetre_h / 2,
             mouse_x - fenetre_w / 2, mouse_y - fenetre_h / 2,
             fenetre_w, fenetre_h);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(40);
    }

    //quand on a plus besoin de la bitmap, on la détruit
    destroy_bitmap(image);
    destroy_bitmap(masque);
    destroy_bitmap(buffer);
    allegro_exit();
    return 0;
}
END_OF_MAIN();*/



// Exo 3
int main()
{
    // BITMAP devant recevoir l'image
    BITMAP *image;
    BITMAP *buffer;

    // paramètres de l'élément 1 à animer (disque)
    int posx1,posy1;    // coordonnées
    int rayon1;          // taille (rayon du disque)
    int depx1,depy1;    // vecteur déplacement effectif en x et y

    // paramètres de l'élément 2 à animer (image)
    int posx2,posy2;    // coordonnées
    int tx2,ty2;        // taille (largeur et hauteur)
    int depx2,depy2;    // vecteur déplacement effectif en x et y


    // Lancer allegro et le mode graphique
    initialisation_allegro();
    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran

    // Chargement de l'image
    image=load_bitmap("earth.bmp",NULL);
    if (!image)  {
        allegro_message("pas pu trouver/charger earth.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }

    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    if (!buffer) {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Initialisation des paramètres de l'élément 1
    rayon1=40;
    posx1=rayon1;  posy1=rayon1;
    depx1=5;       depy1=9;

    // Initialisation des paramètres de l'élément 2
    tx2=image->w;            ty2=image->h;
    posx2=SCREEN_W/2-tx2/2;  posy2=SCREEN_H/2-ty2/2;
    depx2=9;                 depy2=5;

    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {
         //DETERMINER NOUVELLEs POSITIONs

        // contrôle des bords : ici on décide de rebondir sur les bords
        if ( (posx1-rayon1<0 && depx1<0) || (posx1+rayon1>SCREEN_W && depx1>0) )
            depx1=-depx1;
        if ( (posy1-rayon1<0 && depy1<0) || (posy1+rayon1>SCREEN_H && depy1>0) )
            depy1=-depy1;

        if ( (posx2<0 && depx2<0) || (posx2+tx2>SCREEN_W && depx2>0) )
            depx2=-depx2;
        if ( (posy2<0 && depy2<0) || (posy2+ty2>SCREEN_H && depy2>0) )
            depy2=-depy2;



        // calculer nouvelles positions
        // nouvelle position = position actuelle + deplacement
        posx1=posx1+depx1;
        posy1=posy1+depy1;

        posx2=posx2+depx2;
        posy2=posy2+depy2;

        // AFFICHAGE AUX NOUVELLES POSITIONS

        blit(image,buffer,0,0,posx2,posy2,tx2,ty2);
        circlefill(buffer,posx1,posy1,rayon1,makecol(200,255,200));
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H); // astuce : image en 1er...

        clear_bitmap(buffer);
        rest(10);
    }
    destroy_bitmap(image);
    destroy_bitmap(buffer);
    allegro_exit();
    return 0;
}END_OF_MAIN()

// Exo 4

/*int main() {
    BITMAP *image;
    BITMAP *buffer;
    BITMAP *masque;
    BITMAP *sprite;
    int rayon = 60;
    initialisation_allegro();
    image=load_bitmap("Galaxie.bmp",NULL);
    if(!image) {
        allegro_message("pas pu trouver/bitmap.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    if(!buffer) {
        allegro_message("pas pu trouver/bitmap.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    masque=create_bitmap(SCREEN_W,SCREEN_H);
    sprite=create_bitmap(SCREEN_W,SCREEN_H);
    while (!key[KEY_ESC]) {
        clear_to_color(masque, makecol(0,0,0));
        circlefill(masque, mouse_x, mouse_y, rayon, makecol(250,0,250));
        draw_sprite(sprite, image, 0, 0);
        draw_sprite(sprite, buffer, 0, 0);
        blit(sprite, buffer, 0,0,0,0, image->w, image->h);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        clear_bitmap(buffer);
        clear_bitmap(sprite);
        rest(10);
    }
    destroy_bitmap(buffer);
    destroy_bitmap(masque);
    destroy_bitmap(sprite);
    destroy_bitmap(image);
    allegro_exit();
    return 0;
} END_OF_MAIN();*/
