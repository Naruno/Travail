#ifndef _LIB_H_
#define _LIB_H_


#ifdef _LIB_C_
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif




#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*! \file Vecteur3D.h
\brief En-tete de la dll sur les primitives de vecteurs 3D
 fichier contenant l'addition (add3), la soustraction(sub3), la multiplication(mul3), la division(div3), l'initialisation(set3), la reflexion vis a vis d'un objet (reflect3), le calcule de la norme(norm3), la normalisation (normalize3), le produit vectoriel(cross3), le produit scalaire(dot3), la distance entre 2 vecteurs et la copie de vecteur 3D (distance3).
*/

/*! \brief Union vec3 d'une structure de vecteurs 3D et d'un champ data
 la structure contient 3 float x, y, z et le champ data permet d'acceder au 3 float via un tableau.
*/
typedef union vec3_u
{
	float data[3];/*!< Tableau equivalent au 3 champs x, y, z. */
	struct
	{
		float x;/*!< Composante x */
		float y;/*!< Composante y */
		float z;/*!< Composante z */
	};
	
}vec3;

/*! \brief Fonction sommant les deux vecteurs, pas de passage par adresse.
\param[in] Vect1 de type vec3  
\param[in] Vect2 de type vec3
\return renvoie la somme des vecteurs
*/
LIB_API vec3 add3(vec3 Vect1, vec3 Vect2);

/*! \brief fonction soustrayant  les deux vecteurs, pas de passage par adresse
on effectue la soustraction de Vect1 par Vect2
V1-V2
\param[in] Vect1 de type vec3
\param[in] Vect2 de type vec3
\return renvoie la soustraction des vecteurs
*/
LIB_API vec3 sub3(vec3 Vect1, vec3 Vect2);

/*! \brief fonction multiplication d'un vecteur par un float, pas de passage par adresse
\param[in] Vect1 de type vec3  
\param[in] Vect2 de type float
\return renvoie la multipication du vecteur par le float
*/
LIB_API vec3 mul3(vec3 Vect1, float Vect2);

/*! \brief fonction division d'un vecteur par un float, pas de passage par adresse
gere l'exception de la division par 0
on divise Vect1 par Vect2 
V1/V2
\param[in] Vect1 de type vec3  
\param[in] Vect2 de type float
\return renvoie la division du vecteur par le float
*/
LIB_API vec3  div3(vec3 Vect1, float Vect2);

/*! \brief fonction calculant la norme d'un vecteur 3D
\param[in] Vect1 de type vec3

\return renvoie la valeur de la norme du vecteur
*/
LIB_API float norm3(vec3 Vect1);

/*! \brief fonction renvoyant une copie normalisee d'un vecteur passer en parametre
Details.
\param[in] Vect1 de type vec3
\return renvoie la description de la valeur
*/
LIB_API vec3 normalize3(vec3 Vect1);

/*! \brief fonction de copie d'un vecteur passe en parametre
Details.
\param[in] Vect1 de type vec3
\return renvoie la copie du vecteur
*/
LIB_API vec3 copy3(vec3 Vect1);

/*! \brief fonction calculant le produit scalaire entre 2 vecteurs.
NB : rappel de la formule du produit scalaire
 vect1 = (a)     vect2 = (d)
		 (b)			 (e)
		 (c)			 (f)
produit scalaire = a*d + b*e + c*f
\param[in] Vect1  de type vec3
\param[in] Vect2 de type vec3
\return renvoie un float contenant le resultat du produit scalaire
*/
LIB_API float dot3(vec3 Vect1, vec3 Vect2);

/*! \brief fonction calculant le produit vectoriel entre 2 vecteurs.
Attention non commutatif
NB : rappel de la formule du produit vectoriel
 vect1 = (a)     vect2 = (d)
		 (b)			 (e)
		 (c)			 (f)
produit vectoriel = (b*f - c*e)
					(c*d - a*f)
					(a*e - b*d)
\param[in] Vect1  de type vec3
\param[in] Vect2 de type vec3
\return renvoie le vecteur contenant le resultat du produit vectoriel
*/
LIB_API vec3 cross3(vec3 Vect1, vec3 Vect2);

/*! \brief initialise un vecteur a partir des composantes donnees par l'utilisateur.

\param[in] x de type float renvoie a la composante sur l'axe des absisses
\param[in] y float renvoie a la composante sur l'axe des ordonees
\param[in] z float renvoie a la composante sur l'axe de l'altitude
\return renvoie le vecteur initialise au composantes donnees en parametre
*/
LIB_API vec3 set3(float x, float y, float z);

/*! \brief renvoie la reflexion d'un vecteur par rapport a un second normee
le vecteur incident est considere comme ayant son origine sur la surface et allant vers l'exterieur
le vecteur i par rapport a la surface
<------|
\param[in] Vect1 de type vec3 le vecteur incident
\param[in] Vect2 de type vec3 doit etre norme : on prends le vecteur normale
\return renvoie le vecteur reflechis
*/
LIB_API vec3 reflect3(vec3 Vect1, vec3 Vect2);

/*! \brief renvoie la distance d'un vecteur par rapport a un autre vecteur
la distance entre le vecteur 1 et le vecteur 2 etant la norme de la difference entre le vecteur 1 et le vecteur 2
|| Vect1-Vect2||
\param[in] Vect1 de type vec3 le vecteur 1.
\param[in] Vect2 de type vec3 le vecteur 2.
\return renvoie la distance entre les deux vecteurs
*/

LIB_API float distance3(vec3 Vect1, vec3 Vect2);

#endif