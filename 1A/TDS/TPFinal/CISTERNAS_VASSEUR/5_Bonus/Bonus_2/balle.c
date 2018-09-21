#include "balle.h"
#include "vecteur.h"

Balle chargerBalle(char* chemin)
{
    
    Balle info; 
    FILE *fichier = fopen(chemin,"r"); // Lecture des donnees du fichier balle.txt
    if (fichier != NULL ) // On verifie que l'on puisse bien lire le fichier
    { 
            fscanf(fichier,"masse %f\nfCoef %f\nposition %f %f\nvitesse %f %f\nattenuation %f", 
            &info.masse, &info.coeffriction, &info.position.x, &info.position.y, &info.vitesse.x, &info.vitesse.y, &info.attenuation); // Remplissage de la structure
            fclose(fichier);
    }
        
    info.ballePrecedente=NULL; // On initialise la balle precedente a nulle
    info.balleSuivante=NULL; // On initialise la balle suivante a nulle
    return info; 
    
}

int majPosition(Balle * balle, AttracteurList *pAttList, float dt)
{
    
    if (balle == NULL)
    {
        return -1; //securite
    }
    
    Vecteur attracteurs = creerVect(0,0); // Creation du vecteur somme des forces a l'etat initial 
    
    for (int i=0; pAttList->utiliseMoi[i]!=0; i++) // Boucle pour chaque attracteurs
    { 
        
        Vecteur position = subVect(balle->position , pAttList->positionAttracteurs[i]); // Calcule de difference des positions de la balle et de l'astre i 
        float distance = pow(normVect(position), 2); // Calcule du carre de la distance qui intervient dans la formule de la force 
        
        float magnitude = (-0.1) / distance; // Calcul de la partie flottante de la formule de la force
        if (magnitude<-1) // Test sur la magnitude
        {    
            magnitude = -0.5; // Gere une vitesse trop elevee 
        }
        Vecteur u12 = normaliseVect(position); // Calcule du vecteur U12 (normalise) 
        
        Vecteur force = multScalVect(magnitude , u12); // Calcul de la force 
        Vecteur coefficient = multScalVect(pAttList->utiliseMoi[i], force); // Application du coefficient utiliseMoi[i] a la force (0 ou 1) si un astre a ete place, utiliseMoi[i] vaut 1
        
        attracteurs = addVect(attracteurs, coefficient); // Addition successive des forces s'appliquant a la balle 
        
    }
    
    
    float k = 200, l_p=0, l_s=0, lo = 0.02; // Coefficient estimes
    
    Vecteur rappel_p = creerVect(0,0); // On initialise les forces de rappel a 0
    Vecteur rappel_s = creerVect(0,0);
    
    if (balle->ballePrecedente!=NULL) // Si il existe une balle precedente, on calcule la force de rappel entre la balle precedente et la balle actuelle
    {
        Vecteur distance_p = subVect(balle->position, balle->ballePrecedente->position);
        l_p = normVect(distance_p);
        rappel_p = multScalVect(-k*(l_p-lo), normaliseVect(distance_p)); // Application de la formule de la force
    }
    
    if (balle->balleSuivante!=NULL) // Si il existe une balle precedente, on calcule la force de rappel entre la balle actuelle et la suivante
    {
        Vecteur distance_s = subVect(balle->position, balle->balleSuivante->position );
        l_s = normVect(distance_s);
        rappel_s = multScalVect(-k*(l_s-lo), normaliseVect(distance_s)); // Application de la formule de la force
    }
    
    Vecteur somme = addVect(addVect(attracteurs, rappel_p), rappel_s); // Sommes des forces 
    
    Vecteur acceleration = multScalVect((float)(1/balle->masse), somme); // Calcul de l'acceleration
 
    balle->vitesse = addVect(balle->vitesse, multScalVect(dt, acceleration)); // Mise a jour de la vitesse de la balle
    balle->position = addVect(balle->position, multScalVect(dt, balle->vitesse)); // Mise a jour de la position de la balle 
    
    return 0;
}

void initAttracteurList(AttracteurList * pAttrList) // Initialise le tableau utiliseMoi a 0
{
    for (int i=0; i<NB_ATTRACTEURS; i++)
    {
        pAttrList->utiliseMoi[i]=0;
    }
}
