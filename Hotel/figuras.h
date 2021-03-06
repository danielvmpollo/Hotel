//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	CFiguras();
	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Func�on creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Func�on creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Func�on creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Func�on creacion movimiento
	void laptopP (float altura, float largo, float profundidad, GLuint text1, GLuint text2);//Func�on creacion prisma
	void laptopT (float altura, float largo, float profundidad, GLuint text1, GLuint text2);//Func�on creacion prisma
	void prisma (float altura, float largo, float profundidad, GLuint text);//Func�on creacion prisma
	void prisma2 (GLuint text, GLuint text2);
	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	void cesped (float altura, float largo, float profundidad, GLuint text);//Func�on creacion prisma
	

	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

};
