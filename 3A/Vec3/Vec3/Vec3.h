#ifndef _VEC3_H_
#define _VEC3_H_


/*! \file Vec3.h
		  \brief Fichier de manipulation de vecteur 3D
*/

#include <stdio.h>
#include <math.h>

#ifdef _VEC3_C_
#define LIB_API __declspec(dllimport)
#else
#define LIB_API __declspec(dllexport)
#endif


typedef union {

	struct {
		float x;
		float y;
		float z;
	};

	float data[3];
}vec3;

LIB_API void afficheVec3(vec3 p_vec);

/*! \brief Additionne deux vecteurs.

		  \param[in] p_vect1 premier vecteur.
		  \param[in] p_vect2 deuxieme vecteur.

		  \return vec3 somme de p_vect1 et p_vect2.
*/
LIB_API vec3 add3(vec3 p_vect1, vec3 p_vect2);


/*! \brief Soustrait deux vecteurs.

		  \param[in] p_vect1 premier vecteur.
		  \param[in] p_vect2 deuxieme vecteur.

		  \return vec3 soustraction de p_vect1 et p_vect2.
*/
LIB_API vec3 sub3(vec3 p_vect1, vec3 p_vect2);

/*! \brief Initialise un vecteur.

		  \param[in] p_x coordonnée en x.
		  \param[in] p_y coordonnée en y.
		  \param[in] p_z coordonnée en z.

		  \return un vec3 initialisé.
*/
LIB_API vec3 set3(float p_x, float p_y, float p_z);

/*! \brief calcul la distance euclidienne entre deux vecteurs.

		  \param[in] p_vect1, un vecteur.
		  \param[in] p_vect2, un vecteur.

		  \return la distance en float.
*/

LIB_API float distance3(vec3 p_vect1, vec3 p_vect2);

/*! \brief produit scalaire de deux vecteurs.

		  \param[in] p_vect1, un vecteur.
		  \param[in] p_vect2, un vecteur.

		  \return le produit scalaire en float.
*/

LIB_API float dot3(vec3 p_vect1, vec3 p_vect2);

/*! \brief copie un vecteur dans un autre.

		  \param[in] p_vec, le vecteur à copier.

		  \return un vec3, le vecteur copié.
*/

LIB_API vec3 copy3(vec3 p_vect);

/*! \brief multiplie un vecteur par un scalaire.

		  \param[in] p_vec le vecteur à multiplier.
		  \param[in] p_nombre, un scalaire.

		  \return un vec3, le vecteur multiplié.
*/

LIB_API vec3 mul3(vec3 p_vec, float p_nombre);

/*! \brief divise un vecteur.

		  \param[in] p_vec, le vecteur à diviser.
		  \param[in] p_nombre, un scalaire par lequel diviser.

		  \return un vec3, le vecteur divisé .
*/

LIB_API vec3 div3(vec3 p_vec, float p_nombre);

/*! \brief calcul la norme d'un vecteur.

		  \param[in] p_vec, le vecteur à utiliser .


		  \return la distance en float.
*/

LIB_API float norm3(vec3 p_vec);

/*! \brief normalise un vecteur.

		  \param[in] p_vec, le vecteur à normaliser.

		  \return un vec3, le vecteur normalisé.
*/
LIB_API vec3 normalize3(vec3 p_vec);

/*! \brief effectue le produit vectoriel de deux vecteurs.

		  \param[in] p_vect1, le premier vecteur.
		  \param[in] p_vect2, le deuxieme vecteur.

		  \return un vec3, le resultat du produit vectoriel.
*/
LIB_API vec3 cross3(vec3 p_vect1, vec3 p_vect2);

/*! \brief calcul de la reflection d'un vecteur /!\ QUEL SENS POUR I ?.

		  \param[in] p_vect1, le vecteur à reflechir (sens positif).
		  \param[in] p_vect2, le vecteur normal.

		  \return un vec3, le vecteur reflechi .
*/

LIB_API vec3 reflect3(vec3 p_vect1, vec3 p_vect2);

#endif // !_VEC3_H_
