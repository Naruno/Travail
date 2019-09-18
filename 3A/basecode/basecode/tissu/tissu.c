#include "tissu.h"
#include <stdlib.h>
#include <math.h>

//#include "vld.h"

/*! normals to draw the fabric */
vec3 * g_normals = NULL;
/*! positions to draw the fabric */
vec3 * g_positions = NULL;
/*! texture coordinates to draw the fabric with a texture applied on it */
vec3 * g_texcoords = NULL;
/*! list of indices to specify the faces of the fabric */
unsigned int * g_faces = NULL;
/*! Texture ID */
GLuint g_texID = 0;

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
void initializeArrayOfParticles(particle ** p_array, float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles)
{
	// create the particles
	// TODO		
	int i, j, n = 1;
	vec3 pos, vitesse;
	for (i = 0; i < p_nbPartW; i++) {	
		for (j = 0; j < p_nbPartL; j++) {
			pos = set3(p_width / p_nbPartW * i, 1, p_length / p_nbPartL * j);
			vitesse = set3(0, 0, 0);
			p_array[i][j] = createParticle(n, DEFAULT_MASS, DEFAULT_SIZE, FALSE, pos , vitesse, FRICTION);			
			n++;
		}
	}	
	// create the links between particles
	// TODO
	for (i = 0; i < p_nbPartW; i++) {	
		for (j = 0; j < p_nbPartL; j++) {
			p_array[i][j].m_voisinage = (voisins*)calloc(1, sizeof(voisins));
			// Adjacents.
			if (UP >= 0) p_array[i][j].m_voisinage->adjacents[HAUT] = &(p_array[UP][j]);				
			if (DOWN < p_nbPartW) p_array[i][j].m_voisinage->adjacents[BAS] = &(p_array[DOWN][j]);						
			if (LEFT >= 0) p_array[i][j].m_voisinage->adjacents[GAUCHE] = &(p_array[i][LEFT]);							
			if (RIGHT < p_nbPartL) p_array[i][j].m_voisinage->adjacents[DROITE] = &(p_array[i][RIGHT]);					
			// Diagonaux.
			if (UP >= 0 && LEFT >= 0) p_array[i][j].m_voisinage->diagonaux[HAUT] = &(p_array[UP][LEFT]);							
			if (UP >= 0 && RIGHT < p_nbPartL) p_array[i][j].m_voisinage->diagonaux[DROITE] = &(p_array[UP][RIGHT]);						
			if (DOWN < p_nbPartW && RIGHT < p_nbPartL) p_array[i][j].m_voisinage->diagonaux[BAS] = &(p_array[DOWN][RIGHT]);							
			if (DOWN < p_nbPartW && LEFT >= 0) p_array[i][j].m_voisinage->diagonaux[GAUCHE] = &(p_array[DOWN][LEFT]);
			// Loins.		
			if (UP - 1 >= 0) p_array[i][j].m_voisinage->loins[HAUT] = &(p_array[UP - 1][j]);						
			if (DOWN + 1 < p_nbPartW) p_array[i][j].m_voisinage->loins[BAS] = &(p_array[DOWN + 1][j]);							
			if (LEFT - 1 >= 0) p_array[i][j].m_voisinage->loins[GAUCHE] = &(p_array[i][LEFT - 1]);					
			if (RIGHT + 1 < p_nbPartL) p_array[i][j].m_voisinage->loins[DROITE] = &(p_array[i][RIGHT + 1]);							
		}
	}
	// initialize the obstacles 
	
	// TODO	
	for (i = 0; i < p_nbObstacles; i++) {
		p_obstacles[i].m_friction = RANDOM_0_1;
		p_obstacles[i].m_position = set3(RANDOM_0_1, RANDOM_0_1, RANDOM_0_1);
		p_obstacles[i].m_size = 120 * DEFAULT_SIZE;
	}		
}

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
particle ** createFabric(float p_width, float p_length, int p_nbPartW, int p_nbPartL, obstacle * p_obstacles, int p_nbObstacles)
{
	int i;
	particle ** array = NULL;

	if( p_width<=0.0f || p_length<=0.0f || p_nbPartW<=1 || p_nbPartL<=1 ) return NULL;

	// allocate the particles' array
	// TODO
	array = (particle **)calloc(p_nbPartW, sizeof(particle*));
	if (!array) return NULL;
	
	for (i = 0; i < p_nbPartW; i++) {
		array[i] = (particle*)calloc(p_nbPartL, sizeof(particle));
	}	
	// initialize the particles' array
	initializeArrayOfParticles(array, p_width, p_length, p_nbPartW, p_nbPartL, p_obstacles, p_nbObstacles);

	return array;
}

/*!<	
 *	\brief	function to delete the fabric particles created before
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 */
void deleteFabric(particle ** p_array, int p_nbPartW, int p_nbPartL)
{
	int i,j;

	if(!p_array) return;
	
	// delete particles array
	// TODO
	for (i = 0; i < p_nbPartW; i++) {
		for (j = 0; j < p_nbPartL; j++) {
			free(p_array[i][j].m_voisinage);
		}
		free(p_array[i]);
	}
	free(p_array);

	if(g_faces)
		free(g_faces);

	if(g_positions)
		free(g_positions);

	if(g_normals)
		free(g_normals);

	if(g_texcoords)
		free(g_texcoords);
}


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
particle createParticle(int p_num, float p_mass, float p_size, bool p_static, vec3 p_pos, vec3 p_speed, float p_friction)
{	
	particle p;
	
	p.m_num    = p_num;
	p.m_mass   = p_mass;
	p.m_size   = p_size;
	p.m_static = p_static;
	p.m_position[CURRENT]	= copy3(p_pos);
	p.m_position[NEXT]		= copy3(p_pos);	
	p.m_speed[CURRENT]		= copy3(p_speed);		
	p.m_speed[NEXT]			= copy3(p_speed);	
	p.m_friction = p_friction;
	return p;
}

/*!<	
 *	\brief	function to update all the fabric particles 
 *
 *	\param	p_array		the particles
 *	\param	p_nbPartW	number of particles on width axis
 *	\param	p_nbPartL	number of particles on length axis
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for each particle
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateFabric(particle ** p_array, int p_nbPartW, int p_nbPartL, float p_dt, obstacle * p_obstacles, int p_nbObstacles)
{
	static float lastingDt = 0.0f;
	int i,j;

	if(!p_array) return;

	// count the lasting dt frame previous frame
	p_dt += lastingDt;

	// loop to integrate always using the integration step defined
	while(p_dt>INTEGRATION_STEP)
	{
		// update the particles position & speed
		// TODO
		for (i = 0; i < p_nbPartW; i++) {
			for (j = 0; j < p_nbPartL; j++) {
				updateParticle(&(p_array[i][j]), INTEGRATION_STEP, p_obstacles, p_nbObstacles);				
			}
		}
		for (i = 0; i < p_nbPartW; i++) {
			for (j = 0; j < p_nbPartL; j++) {	
				finalizeParticle(&(p_array[i][j]));
			}
		}
		p_dt-=INTEGRATION_STEP;
	}
	// store the lasting dt for next frame
	lastingDt = p_dt;
}

/*!<	
 *	\brief	function to update a particle
 *
 *	\param	p_particle	the particle
 *	\param	p_dt		the elapsed time to integrate the acceleration to calculate speed & position for the particle
 *	\param	p_obstacles	the obstacles to take into account in the simulation (array of obstacle structures)
 *	\param	p_nbObstacles	the number of obstacles stored in the array "p_obstacles"
 */
void updateParticle(particle * p_particle, float p_dt, obstacle * p_obstacles, int p_nbObstacles)
{
	// TODO 
	float tau = -p_particle->m_friction / p_particle->m_mass;
	float Lo_a = SIZE_W/ WIDTH;
	float Lo_l = Lo_a * 2;
	float Lo_d = Lo_a * sqrt(2);
	float k1, rayon = p_obstacles->m_size / 2;
	int i;
	vec3 forces_voisins = set3(0, 0, 0);
	vec3 OP, OP_N, obs, part = p_particle->m_position[NEXT];
	
	vec3 v_cur = p_particle->m_speed[CURRENT];
	vec3 g = set3(0, GRAVITY, 0);
	vec3 f = mul3(p_particle->m_speed[CURRENT], tau);

	// Calcul des forces
	for (i = 0; i < 4; i++) {

		if (p_particle->m_voisinage->adjacents[i] == NULL) continue;

		OP = sub3(p_particle->m_voisinage->adjacents[i]->m_position[CURRENT], p_particle->m_position[CURRENT]); // Soustraction entre le centre de la particule et le centre de son voisin i.
		OP_N = normalize3(OP);
		k1 = KA * (norm3(OP) - Lo_a) / p_particle->m_mass;

		forces_voisins = add3(forces_voisins, mul3(OP_N, k1));
	}

	for (i = 0; i < 4; i++) {

		if (p_particle->m_voisinage->diagonaux[i] == NULL) continue;

		OP = sub3(p_particle->m_voisinage->diagonaux[i]->m_position[CURRENT], p_particle->m_position[CURRENT]);
		OP_N = normalize3(OP);
		k1 = KD * (norm3(OP) - Lo_d) / p_particle->m_mass;

		forces_voisins = add3(forces_voisins, mul3(OP_N, k1));
	}
	for (i = 0; i < 4; i++) {

		if (p_particle->m_voisinage->loins[i] == NULL) continue;

		OP = sub3(p_particle->m_voisinage->loins[i]->m_position[CURRENT], p_particle->m_position[CURRENT]);
		OP_N = normalize3(OP);
		k1 = KL * (norm3(OP) - Lo_l) / p_particle->m_mass;

		forces_voisins = add3(forces_voisins, mul3(OP_N, k1));
	}	
	p_particle->m_speed[NEXT] = add3(v_cur, mul3(add3(add3(g, f), forces_voisins), p_dt));
	p_particle->m_position[NEXT] = add3(p_particle->m_position[CURRENT], mul3(v_cur, p_dt));

	// Collision au sol
	if (p_particle->m_position[NEXT].y < 0)
	{ 
		p_particle->m_position[NEXT].y = 0;
		p_particle->m_speed[NEXT].y = 0;
	}
	
	// Collision obstacles
	for (i = 0; i < p_nbObstacles; i++)
	{		
		obs = p_obstacles[i].m_position;		

		if (pow(part.x - obs.x, 2) + pow(part.y - obs.y, 2) + pow(part.z - obs.z, 2) < pow(rayon, 2) + DEFAULT_SIZE *2) 
		{			
			p_particle->m_speed[NEXT] = mul3(reflect3(v_cur, mul3(normalize3(sub3(p_particle->m_position[NEXT], obs)), (0.01) * (p_obstacles->m_size + p_particle->m_size))), p_obstacles->m_friction);
			p_particle->m_position[NEXT] = add3(p_particle->m_position[NEXT], mul3(sub3(p_particle->m_position[NEXT], obs), (0.01) * (p_obstacles->m_size + p_particle->m_size)) );
		}	
	}
}

/*!<	
 *	\brief	function to finalize the particle update. 
 *
 *	The position & speed calculated in m_position[NEXT] & m_speed[NEXT] are copied into m_position[CURRENT] & m_speed[CURRENT] so the particle can be rendered with its new position.
 *
 *	\param	p_particle	the particle
 */
void finalizeParticle(particle * p_particle)
{	
	p_particle->m_speed[CURRENT] = p_particle->m_speed[NEXT];	
	p_particle->m_position[CURRENT] = p_particle->m_position[NEXT];
	
}



/*! 
 *	\brief	to draw the fabric using GL primitives (GL_TRIANGLES / GL_LINE_LOOP)
 *
 *	\param	p_particles	the particles' array to define the position of each particle of the fabric 
 *	\param	p_width		number of particles on the width axis
 *	\param	p_length	number of particles on the length axis
 *	\param	p_obstacles	array of obstacles
 *	\param	p_nbObstacles	number of obstacles in the list
 */
void drawFabric(particle ** p_particles, int p_width, int p_length, obstacle * p_obstacles, int p_nbObstacles)
{
	int i,j;

	GLfloat diff[4] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat spec[4] = {1.0f,1.0f,1.0f,1.0f};

	if(!g_faces)
	{
		g_normals = (vec3*)calloc(sizeof(vec3),2*p_width*p_length);
		g_positions= (vec3*)calloc(sizeof(vec3),2*p_width*p_length);
		g_texcoords = (vec3*)calloc(sizeof(vec3),2*p_width*p_length);
		g_faces = (unsigned int *)calloc(sizeof(unsigned int),12*(p_width-1)*(p_length-1));

		for(i=0; i < (p_width-1)*(p_length-1); i++)
		{
			g_faces[12*i+0+0]	= i/(p_width-1)*p_width + i%(p_width-1);
			g_faces[12*i+0+1]	= i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+0+2]	= i/(p_width-1)*p_width + i%(p_width-1) + p_width;

			g_faces[12*i+3+0]	= i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+3+1]	= i/(p_width-1)*p_width + i%(p_width-1) + p_width +1;
			g_faces[12*i+3+2]	= i/(p_width-1)*p_width + i%(p_width-1) + p_width;			
			
			g_faces[12*i+6+0]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+6+1]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1);
			g_faces[12*i+6+2]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + p_width;

			g_faces[12*i+9+0]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + 1;
			g_faces[12*i+9+1]	= p_width*p_length +i/(p_width-1)*p_width + i%(p_width-1) + p_width;
			g_faces[12*i+9+2]	= p_width*p_length + i/(p_width-1)*p_width + i%(p_width-1) + p_width + 1;
		}
		for(i=0; i < p_width*p_length; i++)
		{
			g_texcoords[i] = set3( (i/p_width)/(float)(p_length-1) , (i%p_width)/(float)(p_width-1) , 0.0f );
			g_texcoords[p_width*p_length+i] = set3( (i/p_width)/(float)(p_length-1) , (i%p_width)/(float)(p_width-1) , 0.0f );
		}

		if(!g_texID)
		{
			g_texID = loadTexture("./tex.BMP");
		}
	}

	
	for(i=0; i < p_width*p_length; i++)
	{
		g_positions[i] = copy3(p_particles[i%p_width][p_length-1-i/p_width].m_position[CURRENT]);
		g_positions[p_width*p_length+i] = copy3(p_particles[i%p_width][p_length-1-i/p_width].m_position[CURRENT]);
	}
	for(i=0; i < p_width*p_length; i++)
	{
		vec3 n;
		bool valide[4]= {FALSE,FALSE,FALSE,FALSE };


		vec3 v[4];
		if(i%p_width>0)
		{
			v[0] = normalize3(sub3(g_positions[i],g_positions[i-1]));
			valide[0] = TRUE;
		}
		if(i/p_width>0)
		{
			v[1] = normalize3(sub3(g_positions[i],g_positions[i-p_width]));
			valide[1] = TRUE;
		}
		if(i%p_width<p_width-1)
		{
			v[2] = normalize3(sub3(g_positions[i],g_positions[i+1]));
			valide[2] = TRUE;
		}
		if(i/p_width<p_length-1)
		{
			v[3] = normalize3(sub3(g_positions[i],g_positions[i+p_width]));
			valide[3] = TRUE;
		}
		

		n = set3(0.0f,0.0f,0.0f);
		if(valide[0] && valide[1])
			n = add3(n,cross3(v[0],v[1]));
		if(valide[1] && valide[2])
			n = add3(n,cross3(v[1],v[2]));
		if(valide[2] && valide[3])
			n = add3(n,cross3(v[2],v[3]));
		if(valide[3] && valide[0])
			n = add3(n,cross3(v[3],v[0]));

		g_normals[i] = normalize3(n);
		g_normals[p_width*p_length + i] = mul3(g_normals[i],-1.0f);
	}



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3,GL_FLOAT,0,g_positions);
	glNormalPointer(GL_FLOAT,0,g_normals);
	glTexCoordPointer(3,GL_FLOAT,0,g_texcoords);
	glColorPointer(3,GL_FLOAT,0,g_normals);

	if(g_texID)
	{
		glColor3f(1.0f,1.0f,1.0f);
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}
	
	glDrawElements(GL_TRIANGLES,12*(p_width-1)*(p_length-1),GL_UNSIGNED_INT,g_faces);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

#ifdef _DEBUG
	for(i=0;i<p_width; i++)
	{
		for(j=0;j<p_length;j++)
		{
			drawSphere(p_particles[i][j].m_position[CURRENT],0.01f,set3(0.5f,0.5f,0.5f));
		}
	}
#endif

	for(i=0;i<p_nbObstacles; i++)
	{	
		drawSphere(p_obstacles[i].m_position,p_obstacles[i].m_size,set3(p_obstacles[i].m_friction/2.0f,0.0f,(1.0f-p_obstacles[i].m_friction)/2.0f));
	}
}
