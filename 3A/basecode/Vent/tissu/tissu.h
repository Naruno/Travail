#ifndef _TISSU_
#define _TISSU_

#include "./vec3/include/vec3.h"
#include "utils.h"

/*! To define the index of the current value (position/speed of the particle) */
#define CURRENT	0
/*! to define the index of the calculated value (next value for position & speed of the particle) */
#define NEXT	1

/*! Coefficient for friction (for the particle) */
#define FRICTION	13.0f
/*! Coefficient to. tweak the spring reactions easily */
#define KA		400.0f
#define KD		200.0f
#define KL		100.0f

#define K 20.0f

/*! Gravity value (to be applied on Y axis) */
#define GRAVITY		-9.81f
/*! integration step to have same behaviour on different machines */
#define INTEGRATION_STEP	0.005f


/*! Default size */
#define DEFAULT_SIZE	0.005f
/*! Default mass */
#define DEFAULT_MASS	1.0f

#define PI 3.14159
#define UP i-1
#define DOWN i+1
#define LEFT j-1
#define RIGHT j+1

#define WIDTH	10
#define LENGTH	10

#define SIZE_W	1.0f
#define SIZE_L	1.0f


#define RAND(min, max) rand() % (max - min + 1) + min

enum voisins_pos { HAUT = 0, BAS = 1, GAUCHE = 2, DROITE = 3 };

typedef struct sVoisins voisins;
typedef struct sParticle particle;

struct sVoisins {

	particle* adjacents[4];
	particle* diagonaux[4];
	particle* loins[4];
};


/*! Definition of a particle properties */
struct sParticle{

	int		m_num;
	float	m_friction;
	float   m_mass;
	float	m_size;			/*! size of the particle (diameter) */
	vec3	m_position[2];	/*! position of the particle (CURRENT & NEXT), m_position[CURRENT] is used for rendering, m_position[NEXT] is used for calculation */
	vec3	m_speed[2];		/*! speed of the particle (CURRENT & NEXT) */
	vec3	m_force;
	voisins* m_voisinage;
	bool	m_static;
};

/*! definition of the type to store a sphere/obstacle configuration */
typedef struct sObstacle {
	vec3	m_position;
	float	m_size;
	float	m_friction;
}obstacle;



/*!<	
 *	\brief	function to initialize all the particles properties (but the springs)
 *
 *	\param	p_array		the array of particles
 *	\param	p_width		the width in meter
 *	\param	p_length	the length in meter
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_obstacles	the array of obstacles
 *	\param	p_nbObstacles	the number of obstacles
 */
void initializeArrayOfParticles(particle ** p_array, float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles);


/*!<	
 *	\brief	function to generate all the particles to be used to do the simulation 
 *
 *	\param	p_width		the width in meter
 *	\param	p_length	the length in meter
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_obstacles	the array of obstacles
 *	\param	p_nbObstacles	the number of obstacles
 *
 *	\return	an array of particles initialised so the size of the fabric is the one wished, NULL if an error occurred
 */
particle ** createFabric(float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles);

/*!<	
 *	\brief	function to delete the fabric particles created before
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 */
void deleteFabric(particle ** p_array, int p_nbPartW, int p_nbPartL);


/*!
 *	\brief to create a particle with the parameters given 
 *
 *	\param	p_num		the ID of the particle
 *	\param	p_mass		the mass of the particle
 *	\param	p_size		the size of the particle
 *	\param	p_static	does the particle can move or not ?
 *	\param	p_pos		the initial position of the particle
 *	\param	p_speed		the initial speed of the particle
 *	\param	p_friction	the friction coefficient to apply to the particle
 */
particle createParticle(int p_num, float p_mass, float p_size, bool p_static, vec3 p_pos, vec3 p_speed, float p_friction);

/*!<	
 *	\brief	function to update all the fabric particles 
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for each particle*
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateFabric(particle ** p_array, int p_nbPartW, int p_nbPartL, float p_dt, obstacle * p_obstacles, int p_nbObstacles);

/*!<	
 *	\brief	function to update a particle
 *
 *	\param	p_particle	the particle
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for the particle
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateParticle(particle * p_particle, float p_dt, obstacle * p_obstacles, int p_nbObstacles);



/*!<	
 *	\brief	function to finalize the particle update. 
 *
 *	The position & speed calculated in m_position[NEXT] & m_speed[NEXT] are copied into m_position[CURRENT] & m_speed[CURRENT] so the particle can be rendered with its new position.
 *
 *	\param	p_particle	the particle
 */
void finalizeParticle(particle * p_particle);


/*! 
 *	\brief	to draw the fabric using GL primitives (GL_TRIANGLES / GL_LINE_LOOP)
 *
 *	\param	p_particles	the particles' array to define the position of each particle of the fabric 
 *	\param	p_width		number of particles on the width axis
 *	\param	p_length	number of particles on the length axis
 *	\param	p_obstacles	array of obstacles
 *	\param	p_nbObstacles	number of obstacles in the list
 */
void drawFabric(particle ** p_particles, int p_width, int p_length, obstacle * p_obstacles, int p_nbObstacles);






#endif