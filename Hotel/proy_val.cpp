//#include <gl/gl.h>     // The GL Header File
//#include <windows.h>	//Solo para Windows
//#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
//#include <stdlib.h>		// Descomentar para Linux
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>		// Solo para Windows

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include <time.h>
#include "cmodel/CModel.h" 

CFiguras fig3;
CModel kit;
CModel llanta;
float posX =0, posY = 2.5, posZ =-3.5;
#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	

	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=5;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,_time,timebase=0;
char s[30];


//Animación del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitY = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotKitX = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;

int timer = 0;

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
CCamera objCamera; 

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



GLUquadricObj *quadratic;				// Storage For Our Quadratic Objects ( NEW )


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture tex;
CTexture vent;
CTexture muro;
CTexture p1;//puertas
CTexture E1;
CTexture p2;
CTexture audit;
CTexture techo;
CTexture elevador;
CTexture negro;
CTexture cristal;
CTexture pasto;
CTexture mampara;
CTexture escaleras;

//variables de estación de trabajo
CTexture madera;//mesa y silla
CTexture teclado;
CTexture cubierta;
CTexture pant1;
CTexture pant2;
CTexture pant3;
int contadorPantalla=0;

CFiguras fig1;
CFiguras fig2;

/*
Inicio variables para el proyecto
*/
float entrepiso = 2;
double movelevador=4.000000;
double poselevador=4.000000;
//bool g_fanimacion = false;

float nubesAr[8][3];
float incremento=0;
bool inicio_prog = true;
float largo_sky=300;
float profundo_sky = 400;
/*
Fin variables para el proyecto
*/

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	
	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
    
    text1.LoadBMP("Texturas/01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	tex.LoadTGA("Texturas/f6.tga");
	tex.BuildGLTexture();
	tex.ReleaseImage();
	
	vent.LoadTGA("Texturas/v1.tga");
	vent.BuildGLTexture();
	vent.ReleaseImage();

	muro.LoadTGA("Texturas/m2.tga");
	muro.BuildGLTexture();
	muro.ReleaseImage();

	p1.LoadTGA("Texturas/p1.tga");
	p1.BuildGLTexture();
	p1.ReleaseImage();


	p2.LoadTGA("Texturas/p3.tga");
	p2.BuildGLTexture();
	p2.ReleaseImage();

	E1.LoadTGA("Texturas/E5.tga");
	E1.BuildGLTexture();
	E1.ReleaseImage();

	audit.LoadTGA("Texturas/a2.tga");
	audit.BuildGLTexture();
	audit.ReleaseImage();

	techo.LoadTGA("Texturas/t1.tga");
	techo.BuildGLTexture();
	techo.ReleaseImage();

	elevador.LoadTGA("Texturas/acero.tga");
	elevador.BuildGLTexture();
	elevador.ReleaseImage();

	negro.LoadTGA("Texturas/negro.tga");
	negro.BuildGLTexture();
	negro.ReleaseImage();

	cristal.LoadTGA("Texturas/azul.tga");
	cristal.BuildGLTexture();
	cristal.ReleaseImage();

	///texturas de la estación de trabajo
	madera.LoadTGA("Texturas/madera.tga");
	madera.BuildGLTexture();
	madera.ReleaseImage();

	teclado.LoadTGA("Texturas/teclado.tga");
	teclado.BuildGLTexture();
	teclado.ReleaseImage();

	cubierta.LoadTGA("Texturas/cubierta.tga");
	cubierta.BuildGLTexture();
	cubierta.ReleaseImage();

	pant1.LoadTGA("Texturas/pant1.tga");
	pant1.BuildGLTexture();
	pant1.ReleaseImage();

	pant2.LoadTGA("Texturas/pant2.tga");
	pant2.BuildGLTexture();
	pant2.ReleaseImage();

	pant3.LoadTGA("Texturas/pant3.tga");
	pant3.BuildGLTexture();
	pant3.ReleaseImage();

	pasto.LoadTGA("Texturas/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	mampara.LoadTGA("Texturas/mampara.tga");
	mampara.BuildGLTexture();
	mampara.ReleaseImage();

	escaleras.LoadTGA("Texturas/escalera.tga");
	escaleras.BuildGLTexture();
	escaleras.ReleaseImage();

	objCamera.Position_Camera(0,2.5f,7, 0,2.5f,0, 0, 1, 0);
	//objCamera.Position_Camera(0,10,10, 0,2.5f,0, 0, 1, 0);

	kit._3dsLoad("kitt.3ds");	
llanta._3dsLoad("k_rueda.3ds");


	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;

	KeyFrame[1].posX = 20;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;


	KeyFrame[2].posX = 20;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 4.0;


	KeyFrame[3].posX = 20;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 4.0;


	KeyFrame[4].posX = 20;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 4.0;

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}
/*
Función para dibujar una laptop, recibe las medidas del contenedor de la laptop
y los elementos de ella se escalan. 
Se debe mandar a llamar desde el centro del lado inferior del contenedor de la laptop.
*/
void laptop(float largo, float profundidad, float altura)
{
	float _largo = largo/6;
	float _profundo = profundidad/6;
	float _alto = altura/6;

	contadorPantalla ++;

	glPushMatrix();
		glTranslatef(0,_alto/2,0);
		fig2.laptopT(_alto,largo,profundidad,cubierta.GLindex,teclado.GLindex);
		glTranslatef(0,altura/2,(profundidad/2)-(_profundo/2));
		if(contadorPantalla<1000){
			fig2.laptopP(altura,largo,_profundo,cubierta.GLindex,pant1.GLindex);
		}else if(contadorPantalla < 2000){
			fig2.laptopP(altura,largo,_profundo,cubierta.GLindex,pant2.GLindex);
		}else if(contadorPantalla < 3000){
			fig2.laptopP(altura,largo,_profundo,cubierta.GLindex,pant3.GLindex);
		}else {
			contadorPantalla = 0;
			fig2.laptopP(altura,largo,_profundo,cubierta.GLindex,pant1.GLindex);
		}
	glPopMatrix();
}
/*
Función para dibujar una mesa, recibe las medidas del contenedor de la mesa
y los elementos de ella se escalan. 
Se debe mandar a llamar desde el centro del lado inferior del contenedor de la mesa.
*/
void mesa(float largo, float profundidad, float altura)
{
	float _largo = largo/14;
	float _profundo = profundidad/4;
	float _alto = altura/8;

	glPushMatrix();
		glTranslatef(0,_alto/2,0);//sube a la mitad de la base
		glPushMatrix();//soporte y pata izq
			glTranslatef(-(largo/2)+(1.5*_largo),0,0);//
			fig2.prisma(_alto,_largo,2*_profundo,madera.GLindex);
			glTranslatef(0,(altura/2)-(_alto/2),0);
			fig2.prisma(altura-(2*_alto),_largo,_profundo,madera.GLindex);
		glPopMatrix();
		glPushMatrix();//soporte y pata der
			glTranslatef((largo/2)-(1.5*_largo),0,0);//
			fig2.prisma(_alto,_largo,2*_profundo,madera.GLindex);
			glTranslatef(0,(altura/2)-(_alto/2),0);
			fig2.prisma(altura-(2*_alto),_largo,_profundo,madera.GLindex);
		glPopMatrix();
		glTranslatef(0,altura - _alto,0);
		fig2.prisma(_alto,largo,profundidad,madera.GLindex);
	glPopMatrix();
}
void pastizal(){
	fig2.cesped(2,300,400,pasto.GLindex);
}
/*
Función para dibujar una silla, recibe las medidas del contenedor de la silla
y los elementos de ella se escalan. 
Se debe mandar a llamar desde el centro del lado inferior del contenedor de la silla.
*/
void silla(float largo, float profundidad, float altura)
{
	float _largo = largo/9;
	float _profundo = profundidad/9;
	float _alto = altura/15;

	glPushMatrix();
		glTranslatef(0,(altura/5),0);//sube a los palos laterales
		glPushMatrix();//lateral izquierdo y pata-frente-izq
			glTranslatef(-(largo/2)+(_largo/2),_alto/2,0);
			fig2.prisma(_alto,_largo,profundidad-(2*_profundo),madera.GLindex);//lateral
			glTranslatef(0,-_alto/2,(profundidad/2)-(_profundo/2));
			fig2.prisma(2*(altura/5),_largo,_profundo,madera.GLindex);
		glPopMatrix();
		glPushMatrix();//lateral derecho y pata-frente-der
			glTranslatef((largo/2)-(_largo/2),_alto/2,0);
			fig2.prisma(_alto,_largo,profundidad-(2*_profundo),madera.GLindex);//lateral
			glTranslatef(0,-_alto/2,(profundidad/2)-(_profundo/2));
			fig2.prisma(2*(altura/5)+_alto,_largo,_profundo,madera.GLindex);
		glPopMatrix();
		glPushMatrix();//asiento
			glTranslatef(0,(altura/5)+(_alto/2),0);
			fig2.prisma(_alto,largo,profundidad,madera.GLindex);
		glPopMatrix();
		
		glTranslatef(0,0.3*altura,-(profundidad/2)+(_profundo/2));//sube a la mitad y atras

		glPushMatrix();//pata atras izquierda
			glTranslatef(-(largo/2)+(_largo/2),0,0);
			fig2.prisma(altura,_largo,_profundo,madera.GLindex);
		glPopMatrix();
		glPushMatrix();//pata atras derecha
			glTranslatef((largo/2)-(_largo/2),0,0);
			fig2.prisma(altura,_largo,_profundo,madera.GLindex);
		glPopMatrix();

		glTranslatef(0,0.35*altura,0);//sube respaldo
		fig2.prisma(0.3*altura,largo,_profundo,madera.GLindex);
	glPopMatrix();
}
/*
Función para delimitar el contenedor de una estación de trabajo.
Dibujara la mesa, silla y laptop.
*/
void estTrab(float largo, float profundidad, float altura)
{
	float _largo = largo/7;
	float _profundo = profundidad/6;
	float _alto = altura/5;

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,(profundidad/2)-(2*_profundo));//centro de la mesa
		mesa(7*_largo,4*_profundo,5*_alto);//dibuja mesa
		glTranslatef(0,5*_alto,0);//sube a la mesa 
		laptop(2*_largo,2*_profundo,2*_alto);//dibuja laptop
		glTranslatef(0,-5*_alto,-(2.5*_profundo));//baja al suelo y va al centro de la silla
		silla(3*_largo,3*_profundo,7*_alto);//dibuja silla
	glPopMatrix();
}
void nube(int x,int z,float r) 
{
	glPushMatrix();
		glTranslatef(x,0,z);
		glColor3f(1,1,1);
		for (float i = 0; i < 360; i=i+60)
		{
			glPushMatrix();
			glRotatef(i,1,0,0);
			for (float j = 0; j < 180; j=j+30)
			{
				glPushMatrix();
					glRotatef(-j+60,0,1,0);
					glTranslatef(0,0,((4*r)/3)+(j/60));
					fig2.esfera(r,5,5,0);
				glPopMatrix();
			}
			glPopMatrix();
		}
	glPopMatrix();
}
void nubes()
{
	if(inicio_prog){
		srand(time(NULL));
		for (int i = 0; i < 8; i++)
		{
			nubesAr[i][0]=-130+rand()%271;
			nubesAr[i][1]=-200+rand()%401;
			nubesAr[i][2]=2+(rand()%6);
		}
		inicio_prog = false;
	}
	
	for (int i = 0; i < 8; i++)
	{
		nube(nubesAr[i][0],nubesAr[i][1],nubesAr[i][2]);
	}
	for (int i = 0; i < 8; i++)
	{
		nubesAr[i][0]++;
		nubesAr[i][1]++;
	}
	for (int i = 0; i < 8; i++)
	{
		if(nubesAr[i][0] > largo_sky/2)
			nubesAr[i][0]=-largo_sky/2;
		if(nubesAr[i][1] > profundo_sky/2)
			nubesAr[i][1]=-profundo_sky/2;
	}
}
/*
Esta funcion crea un modulo con 4 estaciones de trabajo divididas con 2 mamparas atravesadas
*/
void modulo(){
	glPushMatrix();
		glTranslatef(0,2.5,0);
		fig2.prisma(5,0.5,10,mampara.GLindex);
		fig2.prisma(5,10,0.5,mampara.GLindex);
		glTranslatef(-2.5,-2.5,2.5);
		glRotatef(180,0,1,0);
		estTrab(3,3,3);
		glTranslatef(-5,0,0);
		estTrab(3,3,3);
		glTranslatef(0,0,5);
		glRotatef(180,0,1,0);
		estTrab(3,3,3);
		glTranslatef(-5,0,0);
		estTrab(3,3,3);
	glPopMatrix();
}
/*
Esta funcion dibuj las oficinas del quinto piso
*/
void oficinas(){
	glPushMatrix();//aquí se acomodan las estaciones de trabajo
		glTranslatef(-36,50,-68);
		glPushMatrix();//estciones de trabajo
			for (int i = 0; i < 57; i=i+8)
			{
				glPushMatrix();
					glTranslatef(0,0,i);
					glRotatef(90,0,1,0);
					estTrab(3,3,3);//estación de trabajo i
				glPopMatrix();
			}
		glPopMatrix();
		glTranslatef(72,0,0);
		glPushMatrix();
			for (int i = 0; i < 57; i=i+8)
			{
				glPushMatrix();
					glTranslatef(0,0,i);
					glRotatef(-90,0,1,0);
					estTrab(3,3,3);//estación de trabajo i
				glPopMatrix();
			}
		glPopMatrix();
		glTranslatef(-1.5,4,-2);//cubículos parte 1
		glPushMatrix();
			for (int i = 0; i < 57; i=i+8)
			{
				glPushMatrix();
					glTranslatef(0,0,i);
					fig2.prisma(8,8,0.5,mampara.GLindex);//cubículo i
				glPopMatrix();
			}
			glTranslatef(0,0,64);
			fig2.prisma(8,8,.5,mampara.GLindex);
		glPopMatrix();
		glTranslatef(-69,0,0);
		glPushMatrix();
			for (int i = 0; i < 57; i=i+8)
			{
				glPushMatrix();
					glTranslatef(0,0,i);
					fig2.prisma(8,8,0.5,mampara.GLindex);//cubículo i
				glPopMatrix();
			}
			glTranslatef(0,0,64);
			fig2.prisma(8,8,.5,mampara.GLindex);
		glPopMatrix();
		glTranslatef(3.75,-1,6.75);//cubiculos parte 2
		glPushMatrix();
			for (int i = 0; i < 57; i=i+8)
			{
				glPushMatrix();
					glTranslatef(0,0,i);
					fig2.prisma(6,.5,2,p2.GLindex);//cubículo i
					glTranslatef(0,4,0);
					fig2.prisma(2,.5,2,cristal.GLindex);//cubículo i
					glTranslatef(0,-3,-3.75);
					fig2.prisma(8,0.5,5.5,cristal.GLindex);//cubículo i
				glPopMatrix();
			}
		glPopMatrix();
		glTranslatef(61.5,0,0);//cubiculos parte 2
		glPushMatrix();
			for (int i = 0; i < 57; i=i+8)
			{
				glPushMatrix();
					glTranslatef(0,0,i);
					fig2.prisma(6,.5,2,p2.GLindex);//cubículo i
					glTranslatef(0,4,0);
					fig2.prisma(2,.5,2,cristal.GLindex);//cubículo i
					glTranslatef(0,-3,-3.75);
					fig2.prisma(8,0.5,5.5,cristal.GLindex);//cubículo i
				glPopMatrix();
			}
		glPopMatrix();

	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,50,-96);
		glPushMatrix();
			glTranslatef(-22.5,0,-15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-7.5,0,-15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(7.5,0,-15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(22.5,0,-15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-22.5,0,0);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-7.5,0,0);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(7.5,0,0);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(22.5,0,0);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(22.5,0,15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(7.5,0,15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-7.5,0,15);
			modulo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-22.5,0,15);
			modulo();
		glPopMatrix();
	glPopMatrix();
}

/*
Esta función crea todos los techos de atras para adelante y de izquierda a derecha.
Cada techo esta encerrad en PUSH y POP porque me estoy regresando al origen (0,0,0) para mayor facilidad
al momento de hacer los techo del lado derecho.
Los que estan en el FOR son para la parte que quiere que se amueble el ultimo piso para el de teoría.
*/
void techos(){
	//techo1
	glPushMatrix();
		glColor3f(1,1,1);
		for (int i = 9; i < 60; i=i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);//sube al centro del entrepiso del 5 piso
				glPushMatrix();//parte grande
					glTranslatef(0,0,-96);//va al centro de la parte grande
					fig2.prisma(entrepiso,77.5,54,techo.GLindex);//dibuja el techo de la parte grande
					//fig2.prisma(5,10,5,madera.GLindex);
				glPopMatrix();//regresa al origen
				glPushMatrix();//escalera
					glTranslatef(0,0,-63.75);//va al centro del ducto de las escaleras
					glPushMatrix();
						glTranslatef(-8,0,0);
						fig2.prisma(entrepiso,4,9.5,techo.GLindex);//dibuja el techo de las escaleras parte 1
					glPopMatrix();//regresa al origen
					glPushMatrix();
						glTranslatef(8,0,0);
						fig2.prisma(entrepiso,4,9.5,techo.GLindex);//dibuja el techo de las escaleras parte 2
					glPopMatrix();//regresa al origen
					glPushMatrix();
						glTranslatef(0,0,-4.25);
						fig2.prisma(entrepiso,12,1,techo.GLindex);//dibuja el techo de las escaleras parte 3
					glPopMatrix();//regresa al origen
					glPushMatrix();
						glTranslatef(0,0,4.25);
						fig2.prisma(entrepiso,12,1,techo.GLindex);//dibuja el techo de las escaleras parte 4
					glPopMatrix();//regresa al origen
				glPopMatrix();//regresa al origen
				glPushMatrix();//izq-escalera
					glTranslatef(-24.75,0,-66.375);//va al centro del techo costado izquierdo de las escaleras
					fig2.prisma(entrepiso,28.25,5.25,techo.GLindex);//dibuja el techo del costado izquierdo de las escaleras
				glPopMatrix();//regresa al origen
				glPushMatrix();//der-escalera
					glTranslatef(24.75,0,-66.375);//va al centro del techo costado derecho de las escaleras
					fig2.prisma(entrepiso,28.25,5.25,techo.GLindex);//dibuja el techo del costado derecho de las escaleras				
				glPopMatrix();//regresa al origen
				glPushMatrix();//izq-largo
					glTranslatef(-28.5,0,-32.25);//va al centro del techo del largo izquierdo
					fig2.prisma(entrepiso,20,63.5,techo.GLindex);//dibuja el techo del largo izquierdo			
				glPopMatrix();//regresa al origen
				glPushMatrix();//der-largo
					glTranslatef(28.5,0,-32.25);//va al centro del techo del largo derecho
					fig2.prisma(entrepiso,20,63.5,techo.GLindex);//dibuja el techo del largo derecho	
				glPopMatrix();//regresa al origen
			glPopMatrix();
		}
		glPushMatrix();//escalera
			glTranslatef(0,69,-63.75);//va al centro del ducto de las escaleras
			fig2.prisma(entrepiso,20,9.5,techo.GLindex);//dibuja el techo de las escaleras
		glPopMatrix();//regresa al origen
		glPushMatrix();//ducto-izq
			glTranslatef(-14,69,-9.5);//va al centro del techo del ducto del lado izquierdo
			fig2.prisma(entrepiso,7,11.5,techo.GLindex);//dibuja el techo del ducto del lado izquierdo
		glPopMatrix();//regresa al origen
		glPushMatrix();//ducto-der
			glTranslatef(14,69,-9.5);//va al centro del techo del ducto del lado derecho
			fig2.prisma(entrepiso,7,11.5,techo.GLindex);//dibuja el techo del ducto del lado derecho
		glPopMatrix();//regresa al origen
		
		glPushMatrix();
			glTranslatef(-16,59,39.55);
			fig2.prisma(entrepiso,38,86,techo.GLindex);//dibuja el techo largo en la parte 2
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(19,59,18.5);
			fig2.prisma(entrepiso,32,44,techo.GLindex);//dibuja el techo mediando en la parte 2
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(12.5,59,52);
			glRotatef(-45,0,1.0,0);
			fig2.prisma(entrepiso,8,11.5,techo.GLindex);//dibuja el techo en diagonal
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(11.125,59,45.75);
			fig2.prisma(entrepiso,16.25,10.5,techo.GLindex);//dibuja el techo parte 1 deforme
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(7.25,59,55);
			fig2.prisma(entrepiso,8.5,8,techo.GLindex);//dibuja el techo parte 2 deforme
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(-0.375,31,79.125);
			fig2.prisma(entrepiso,9.25,9.75,techo.GLindex);//dibuja el piso del cuarto salido
			glTranslatef(0,28,0);
			fig2.prisma(entrepiso,9.25,9.75,techo.GLindex);//dibuja el techo del cuarto salido
		glPopMatrix();//regresa al origen
	glPopMatrix();
}

/*
Función para crear muros de 6 pisos.
Cada piso tiene 8 de altura y 2 de techo.
Despues del ultimo piso le agrego 3 para la barda en la azotea
*/
void muros6P(float largo,float prof){
	fig2.prisma(73,largo,prof,muro.GLindex);
}
void elevator(){
	
	glPushMatrix();//techo y piso cabina elevador
		glTranslatef(0,3.75,0);
		fig2.prisma(0.5,12,8,elevador.GLindex);
		glTranslatef(0,-7.5,0);
		fig2.prisma(0.5,12,8,elevador.GLindex);
	glPopMatrix();
		
	glPushMatrix();//costados de las cabina
		glTranslatef(-5.75,0,0);
		fig2.prisma(7,0.5,8,elevador.GLindex);
		glTranslatef(11.5,0,0);
		fig2.prisma(7,0.5,8,elevador.GLindex);
	glPopMatrix();

	glPushMatrix();//animación de las puertas de la cabina
		if(movelevador==poselevador && movelevador==4){
	
		}else if(movelevador==poselevador && movelevador==14){
			glTranslatef(0,0,3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}else if(movelevador==poselevador && movelevador==24){
			glTranslatef(0,0,3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}else if(movelevador==poselevador && movelevador==34){
			glTranslatef(0,0,3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}else if(movelevador==poselevador && movelevador==44){
			glTranslatef(0,0,3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}else if(movelevador==poselevador && movelevador==54){
			glTranslatef(0,0,3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}else if(movelevador==poselevador && movelevador==64){
			glTranslatef(0,0,3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}else{
			glTranslatef(0,0,-3.75);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(-3,0,0);
			glTranslatef(0,0,7.5);
			fig2.prisma(7,1,0.5,negro.GLindex);
			glTranslatef(-3,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
			glTranslatef(6,0,0);
			fig2.prisma(7,5,0.5,elevador.GLindex);
		}
		
	glPopMatrix();

}
/*
Función para los muros de la parte 1, ya que aqui pongo 3 metros para la
azotea y en la parte 2 solo pongo 2 para que se vea como en la imagen.
Es llamada cuando esta en una posición (?,5,?) por lo que dibuja el muro de
10 que es lo de 1 piso y sube 10 para llegar al centro del otro piso.
Al final sube lo necesario para colocar la parte extra de la azotea.
*/
void muroPisoGr(float ancho,float prof){
	glPushMatrix();
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(10,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,56.5,0);
		fig2.prisma(3,ancho,prof,muro.GLindex);
	glPopMatrix();
}

/*
Función para los muros con ventanas de la parte 1, respeta que se agrega 3 a la azotea.
Es llamada desde (?,5,?) por lo que debe bajar hasta (?,1.6,?) para empezar a construir los muros:
- el primero de 3.2 que es la barda
- el segundo de 2.8 que es la ventana
- el tercero de 4, 2 para el resto del piso y 2 para el techo
- el cuarto saliendo del for sería el de la azotea de 3
*/
void ventanaPorPisoGr(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,59.9,0);
		fig2.prisma(3,ancho,prof,tex.GLindex);
	glPopMatrix();
}

/*
Función para los muros de la parte 2 que tienen la puerta chica.
Primero hace el muro donde se encuentra la puerta, luego sube a hacer los muros repetidos
del resto de los pisos y termina con la parte de la azotea
*/
void muroPisoChConPuerta(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,0,0.75);//avanza .75 para la pared larga de 10 
		fig2.prisma(10,ancho,1.5,muro.GLindex);//dibuja pared de 10
		glTranslatef(0,-1.5,2.25);//baja a 3.5 para puerta de 7
		glColor3f(1,1,1);//cambia color a cafe
		fig2.prisma(7,ancho,3,p2.GLindex);//dibuja puerta de 7 de alto y 3 de largo
		glTranslatef(0,5,0);//sube 5 y llegua a 8.5
		glColor3f(1,1,1);//cambia color del muro
		fig2.prisma(3,ancho,3,muro.GLindex);//dibuja muro sobre puerta de 3 x 3
		glTranslatef(0,-3.5,2.25);//regresa a 5 y avanza despues de la puerta
		fig2.prisma(10,ancho,1.5,muro.GLindex);//dibuja pared de 10
		glTranslatef(0,10,-2.25);//sube 10 para el segundo piso y regresa al centro
		for (int i = 0; i < 50; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(10,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,46,0);
		fig2.prisma(2,ancho,prof,muro.GLindex);
	glPopMatrix();
}

/*
Función para los muros de la parte 2 con solo 2 en la parte de la azotea.
Es llamada desde (?,5,?) por lo que empieza a construir los muros de 10
*/
void muroPisoCh(float ancho,float prof){
	glPushMatrix();
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(10,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,56,0);
		fig2.prisma(2,ancho,prof,muro.GLindex);
	glPopMatrix();
}

/*
Función para los muros con ventana de la parte 2, con 2 en la parte de la azotea.
Igual que en la función para la parte 1 baja a 1.6 y construye la barda, la ventana y 
el muro superior con el entrepiso.
*/
void ventanaPorPisoCh(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,59.4,0);
		fig2.prisma(2,ancho,prof,tex.GLindex);
	glPopMatrix();
}

/*
Función para los muros con ventana de los últimos 3 pisos.
*/
void ventana3pisos(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 30; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,29.4,0);
		fig2.prisma(2,ancho,prof,tex.GLindex);
	glPopMatrix();
}

/*
Función para dibujar el bloque de las puertas grandes que puede ser sustituida.
Yo la use para hacer el cambio de color, pero si se usan texturas directamente donde es llamada esta
función no habría problema.
Tener en cuenta que si se quita esta función colocar color en blanco antes de donde se mandaba a llamar para
que la textura no se vea afectada, también será necesario regresar al color o texturas de los muros despues
*/
void puerta(float ancho,float prof){
	glPushMatrix();
		glColor3f(1,1,1);
		fig2.prisma(10,ancho,prof,p1.GLindex);
		glColor3f(1,1,1);
	glPopMatrix();
}

/*
Función que dibuja la puerta grande y las ventanas de los pisos superiores.
Aquí es donde se puede omitir la llamada a la función "puerta" haciendo lo de los colores antes y despues de
la sustitución por fig2.prisma...
*/
void ventana3pisosConPuerta(float ancho,float prof){
	glPushMatrix();
		puerta(ancho,prof);
		glTranslatef(0,6.6,0);
		for (int i = 0; i < 20; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,muro.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,19.4,0);
		fig2.prisma(2,ancho,prof,muro.GLindex);
	glPopMatrix();
}
/*
Función para dibujar solo 2 ventanas correspondientes a la planta baja y primer piso.
*/
void ventana2pisos(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 20; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,39.4,0);
		fig2.prisma(42,ancho,prof,muro.GLindex);
	glPopMatrix();
}
/*
En esta funcion se dibujan todos los muros del edificio
*/
void muros(){
	glPushMatrix();
		glTranslatef(0,5,0);
		glColor3f(1,1,1);
		//////////////////////////////////////
		//muros atras parte 1
		//////////////////////////////////////
		glPushMatrix();
			glTranslatef(-38,0,-123.25);
			muroPisoGr(2,0.5);//muro 1
			glTranslatef(2.5,0,0);
			ventanaPorPisoGr(3,0.5);//ventana 1
			glTranslatef(4.25,0,0);
			muroPisoGr(5.5,0.5);//muro 2
			glTranslatef(6.5,0,0);
			ventanaPorPisoGr(7.5,0.5);//ventana 2
			glTranslatef(9.5,0,0);
			muroPisoGr(11.5,0.5);//muro 3
			glTranslatef(9.5,0,0);
			ventanaPorPisoGr(7.5,0.5);//ventana 3
			glTranslatef(5.75,0,0);
			muroPisoGr(4,0.5);//muro 4
			glTranslatef(5.75,0,0);
			ventanaPorPisoGr(7.5,0.5);//ventana 4
			glTranslatef(9.5,0,0);
			muroPisoGr(11.5,0.5);//muro 5
			glTranslatef(9.5,0,0);
			ventanaPorPisoGr(7.5,0.5);//ventana 5
			glTranslatef(6.5,0,0);
			muroPisoGr(5.5,0.5);//muro 6
			glTranslatef(4.25,0,0);
			ventanaPorPisoGr(3,0.5);//ventana 6
			glTranslatef(2.5,0,0);
			muroPisoGr(2,0.5);//muro 7
		glPopMatrix();
		//////////////////////////////////////
		//muros izquierda parte 1
		//////////////////////////////////////
		glPushMatrix();
			glTranslatef(-38.75,0,-111);
			muroPisoGr(0.5,25);//muro 1
			glTranslatef(0,0,16.5);
			ventanaPorPisoGr(0.5,8);//ventana 1
			glTranslatef(0,0,10.25);
			muroPisoGr(0.5,12.5);//muro 2
			glTranslatef(0,0,8.25);
			ventanaPorPisoGr(0.5,4);//ventana 2
			glTranslatef(0,0,3);
			muroPisoGr(0.5,2);//muro 3
			glTranslatef(0,0,2.5);
			ventanaPorPisoGr(0.5,3);//ventana 3
			glTranslatef(0,0,7.25);
			muroPisoGr(0.5,11.5);//muro 4
			glTranslatef(0,0,9.75);
			ventanaPorPisoGr(0.5,8);//ventana 4
			glTranslatef(0,0,9.75);
			muroPisoGr(0.5,11.5);//muro 5
			glTranslatef(0,0,9.75);
			ventanaPorPisoGr(0.5,8);//ventana 5
			glTranslatef(0,0,11.625);
			muroPisoGr(0.5,15.25);//muro 6
			glTranslatef(0,0,11.625);
			ventanaPorPisoGr(0.5,8);//ventana 6
			glTranslatef(0,0,7.375);
			muroPisoGr(0.5,6.75);//muro 7
		glPopMatrix();
		//////////////////////////////////////
		//muros derecha parte 1
		//////////////////////////////////////
		glPushMatrix();
			glTranslatef(38.75,0,-111);
			muroPisoGr(0.5,25);//muro 1
			glTranslatef(0,0,16.5);
			ventanaPorPisoGr(0.5,8);//ventana 1
			glTranslatef(0,0,10.25);
			muroPisoGr(0.5,12.5);//muro 2
			glTranslatef(0,0,8.25);
			ventanaPorPisoGr(0.5,4);//ventana 2
			glTranslatef(0,0,3);
			muroPisoGr(0.5,2);//muro 3
			glTranslatef(0,0,2.5);
			ventanaPorPisoGr(0.5,3);//ventana 3
			glTranslatef(0,0,7.25);
			muroPisoGr(0.5,11.5);//muro 4
			glTranslatef(0,0,9.75);
			ventanaPorPisoGr(0.5,8);//ventana 4
			glTranslatef(0,0,8.375);
			muroPisoGr(0.5,8.75);//muro 5
			glTranslatef(0,0,7.375);
			ventanaPorPisoGr(0.5,6);//ventana 5
			glTranslatef(0,0,5.25);
			muroPisoGr(0.5,4.5);//muro 6
			glTranslatef(0,0,5.25);
			ventanaPorPisoGr(0.5,6);//ventana 6
			glTranslatef(0,0,5.25);
			muroPisoGr(0.5,4.5);//muro 7
			glTranslatef(0,0,5.25);
			ventanaPorPisoGr(0.5,6);//ventana 7
			glTranslatef(0,0,5.25);
			muroPisoGr(0.5,4.5);//muro 8
			glTranslatef(0,0,5.25);
			ventanaPorPisoGr(0.5,6);//ventana 8
			glTranslatef(0,0,4.625);
			muroPisoGr(0.5,3.25);//muro 9
		glPopMatrix();
		//////////////////////////////////////
		//muros enfrente parte 1
		//////////////////////////////////////
		glPushMatrix();
			glPushMatrix();
				glTranslatef(-28.5,0,-0.25);
				muroPisoGr(20.875,0.5);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-18.25,0,-7.75);
				muroPisoGr(0.5,15.5);					
			glPopMatrix();
			glPushMatrix();
				glTranslatef(28.5,0,-0.25);
				muroPisoGr(20.875,0.5);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(18.25,0,-7.75);
				muroPisoGr(0.5,15.5);					
			glPopMatrix();
		glPopMatrix();
		//////////////////////////////////////
		//muros interiores parte 1
		//////////////////////////////////////
		glPushMatrix();
			glPushMatrix();//escaleras
				glTranslatef(0,31.5,-68.75);//el centro es 31.5 pero ya esta en 5
				glPushMatrix();
					glTranslatef(0,35,0);
					fig2.prisma(3,12,0.5,muro.GLindex);//dibuja muro atras parte 1
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,-32.5,0);
					glPushMatrix();
					/*animacion de abre y cierre de puertas*/
						if(movelevador==poselevador && movelevador==4){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
						glTranslatef(0,5,0);
						if(movelevador==poselevador && movelevador==14){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
						glTranslatef(0,5,0);
						if(movelevador==poselevador && movelevador==24){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
						glTranslatef(0,5,0);
						if(movelevador==poselevador && movelevador==34){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
						glTranslatef(0,5,0);
						if(movelevador==poselevador && movelevador==44){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
						glTranslatef(0,5,0);
						if(movelevador==poselevador && movelevador==54){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
						glTranslatef(0,5,0);
						if(movelevador==poselevador && movelevador==64){
							glTranslatef(0,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}else{
							fig2.prisma(8,1,0.5,negro.GLindex);
							glTranslatef(-3.25,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(6.5,0,0);
							fig2.prisma(8,5.5,0.5,elevador.GLindex);
							glTranslatef(-3.25,5,0);
							fig2.prisma(entrepiso,12,0.5,muro.GLindex);
						}
					glPopMatrix();
		
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-8,0,0);
					muros6P(4,0.5);//dibuja muro atras parte 5
					glTranslatef(16,0,0);
					muros6P(4,0.5);//dibuja muro atras parte 6
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-10.25,0,5);
					muros6P(0.5,10.5);//dibuja muro izquierdo
					glTranslatef(20.5,0,0);
					muros6P(0.5,10.5);//dibuja muro derecho
				glPopMatrix();

			glPopMatrix();
			glPushMatrix();
				glTranslatef(-14.5,0,-63.5);
				ventanaPorPisoGr(8,0.5);//vent izq escaleras
				glTranslatef(14.5*2,0,0);
				ventanaPorPisoGr(8,0.5);//vent der escaleras
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-18.25,0,-62.5);
				muroPisoGr(0.5,2);//col 1 izq
				glTranslatef(0,0,10);
				ventanaPorPisoGr(0.5,18);//vent 1 izq
				glTranslatef(0,0,10);
				muroPisoGr(0.5,2);//col 2 izq
				glTranslatef(0,0,10);
				ventanaPorPisoGr(0.5,18);//vent 2 izq
				glTranslatef(0,0,10);
				muroPisoGr(0.5,2);//col 3 izq
				glTranslatef(0,0,4);
				ventanaPorPisoGr(0.5,6);//vent 3 izq
			glPopMatrix();
			glPushMatrix();
				glTranslatef(18.25,0,-62.5);
				muroPisoGr(0.5,2);//col 1 der
				glTranslatef(0,0,10);
				ventanaPorPisoGr(0.5,18);//vent 1 der
				glTranslatef(0,0,10);
				muroPisoGr(0.5,2);//col 2 izq
				glTranslatef(0,0,10);
				ventanaPorPisoGr(0.5,18);//vent 2 der
				glTranslatef(0,0,10);
				muroPisoGr(0.5,2);//col 3 izq
				glTranslatef(0,0,4);
				ventanaPorPisoGr(0.5,6);//vent 3 der
			glPopMatrix();
			glPushMatrix();//Para los ductos
				glTranslatef(0,31.5,0);//el centro es 31.5 pero ya esta en 5
				glPushMatrix();//atras-ducto-izq
					glTranslatef(-14,0,-15.25);
					muros6P(8,0.5);					
				glPopMatrix();
				glPushMatrix();//izq-ducto-izq
					glTranslatef(-17.75,0,-9.5);
					muros6P(0.5,12);					
				glPopMatrix();
				glPushMatrix();//der-ducto-izq
					glTranslatef(-10.25,0,-9.5);
					muros6P(0.5,12);					
				glPopMatrix();
				glPushMatrix();//frente-ducto-izq
					glTranslatef(-14,0,-3.75);
					muros6P(8,0.5);						
				glPopMatrix();
				glPushMatrix();//atras-ducto-der
					glTranslatef(14,0,-15.25);
					muros6P(8,0.5);						
				glPopMatrix();
				glPushMatrix();//izq-ducto-der
					glTranslatef(17.75,0,-9.5);
					muros6P(0.5,12);				
				glPopMatrix();
				glPushMatrix();//der-ducto-der
					glTranslatef(10.25,0,-9.5);
					muros6P(0.5,12);						
				glPopMatrix();
				glPushMatrix();//frente-ducto-der
					glTranslatef(14,0,-3.75);
					muros6P(8,0.5);				
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0,-3.75);
				ventanaPorPisoGr(20.5,0.5);//ventanas entre ductos
			glPopMatrix();
		glPopMatrix();
		//////////////////////////////////////
		//muros izquierda parte 2
		//////////////////////////////////////
		glPushMatrix();
			glTranslatef(-35.25,0,0);
			muroPisoChConPuerta(0.5,6);//muro 1
			glTranslatef(0,0,8.5);
			ventanaPorPisoCh(0.5,5);//ventana 1
			glTranslatef(0,0,3.5);
			muroPisoCh(0.5,2);//muro 2
			glTranslatef(0,0,3);
			ventanaPorPisoCh(0.5,4);//ventana 2
			glTranslatef(0,0,7);
			muroPisoCh(0.5,10);//muro 3
			glTranslatef(0,0,7);
			ventanaPorPisoCh(0.5,4);//ventana 3
			glTranslatef(0,0,4);
			muroPisoCh(0.5,4);//muro 4
			glTranslatef(0,0,4);
			ventanaPorPisoCh(0.5,4);//ventana 4
			glTranslatef(0,0,7);
			muroPisoCh(0.5,10);//muro 5
			glTranslatef(0,0,7);
			ventanaPorPisoCh(0.5,4);//ventana 5
			glTranslatef(0,0,3);
			muroPisoCh(0.5,2);//muro 6
			glTranslatef(0,0,3);
			ventanaPorPisoCh(0.5,4);//ventana 6
			glTranslatef(0,0,4);
			muroPisoCh(0.5,4);//muro 7
			glTranslatef(0,0,4);
			ventanaPorPisoCh(0.5,4);//ventana 7
			glTranslatef(0,0,3);
			muroPisoCh(0.5,2);//muro 8
			glTranslatef(0,0,3);
			ventanaPorPisoCh(0.5,4);//ventana 8
			glTranslatef(0,0,4);
			muroPisoCh(0.5,4);//muro 9
			glTranslatef(0,0,4);
			ventanaPorPisoCh(0.5,4);//ventana 9
			glTranslatef(0,0,3);
			muroPisoCh(0.5,2);//muro 10
		glPopMatrix();
		//////////////////////////////////////
		//muros derecha parte 2
		//////////////////////////////////////
		glPushMatrix();
			glTranslatef(35.25,0,0);
			muroPisoChConPuerta(0.5,6);//muro 1
			glTranslatef(0,0,8.5);
			ventanaPorPisoCh(0.5,5);//ventana 1
			glTranslatef(0,0,3.5);
			muroPisoCh(0.5,2);//muro 2
			glTranslatef(0,0,3);
			ventanaPorPisoCh(0.5,4);//ventana 2
			glTranslatef(0,0,7);
			muroPisoCh(0.5,10);//muro 3
			glTranslatef(0,0,7);
			ventanaPorPisoCh(0.5,4);//ventana 3
			glTranslatef(0,0,4);
			muroPisoCh(0.5,4);//muro 4
			glTranslatef(0,0,4);
			ventanaPorPisoCh(0.5,4);//ventana 4
			glTranslatef(0,0,3);
			muroPisoCh(0.5,2);//muro 5
			glTranslatef(-8,0,0.75);
			muroPisoCh(16,0.5);
		glPopMatrix();

		//////////////////////////////////////
		//muros 3, 4 y 5 piso parte deforme
		//////////////////////////////////////
		glPushMatrix();
			glPushMatrix();
				glTranslatef(19.5,0,46);
				ventanaPorPisoCh(0.5,10);//vent vert
				/////////////////////////////////////////
		glTranslatef(-3.75, -9, 0);
		fig2.prisma(8, 31, 10.25, muro.GLindex); //ESCALERA
		glPopMatrix();
		glPushMatrix();
		glTranslatef(15.5, 30, 55);
		glRotatef(-45, 0, 1.0, 0);
		ventana3pisosConPuerta(0.5, 11.5);//vent incli
		glTranslatef(0, -30, 0);
		puerta(0.5, 11.5);
		//////////////////////////// escaleras
		glTranslatef(0, 0, 0);
		glTranslatef(-6, -12, -1);
		fig2.prisma(2, 27, 27, escaleras.GLindex);
		glTranslatef(0, 2, 0);
		fig2.prisma(2, 25, 25, escaleras.GLindex);
		glTranslatef(0, 2, 0);
		fig2.prisma(2, 23, 23, escaleras.GLindex);
		glTranslatef(0, 2, 0);
		fig2.prisma(2, 21, 21, escaleras.GLindex);

		glPopMatrix();
		glPushMatrix();
		glTranslatef(7.5, 0, 59);
		ventanaPorPisoCh(8.5, 0.5);//vent horizo
		////////////////////////////
		glTranslatef(-3.75, -9, 0);
		fig2.prisma(8, 20, 25, muro.GLindex);  //ESCALERA
			glPopMatrix();
			glPushMatrix();
				glTranslatef(3,0,66.25);
				muroPisoCh(0.5,15);//pared
			glPopMatrix();
			glPushMatrix();
				glTranslatef(3.75,30,74);
				ventana3pisos(2,0.5);//v1
				glTranslatef(0.75,0,5);
				ventana3pisos(0.5,10);//v2
				glTranslatef(-4.75,0,5.25);
				ventana3pisos(10,0.5);//v3
				glTranslatef(-5,0,-0.75);
				ventana3pisos(0.5,2);//v4
			glPopMatrix();
		glPopMatrix();

		//////////////////////////////////////
		//muros frente parte 2
		//////////////////////////////////////
		glPushMatrix();
			glTranslatef(-30.5,0,82.75);
			muroPisoCh(9,0.5);//muro 1
			glTranslatef(8.5,0,0);
			ventana2pisos(8,0.5);//vent 1
			glTranslatef(5,0,0);
			muroPisoCh(2,0.5);//muro 2
			glTranslatef(5,0,0);
			ventana2pisos(8,0.5);//vent 2
			glTranslatef(5.25,0,0);
			muroPisoCh(2.5,0.5);//muro 3
			glTranslatef(5.5,10,0);
			fig2.prisma(30,8.5,0.5,muro.GLindex);//muro 4
			glTranslatef(4.25,-13.4,-4.375);
			fig2.prisma(3.2,0.5,9.25,tex.GLindex);//muro bajo vent
			glTranslatef(0,16.4,0); //>---------------------------------------------------------------------------------------------------------------
			fig2.prisma(24,0.5,9.25,tex.GLindex);//muro sup vent
			glTranslatef(0,-13.4,3.125);
			fig2.prisma(2.8,0.5,3,tex.GLindex);//muro izq vent
			glTranslatef(0,0,-3);
			glColor3f(1,1,1);
			fig2.prisma(2.8,0.5,3,vent.GLindex);//ventana
			glColor3f(1,1,1);
			glTranslatef(0,0,-3.125);
			fig2.prisma(2.8,0.5,3.25,tex.GLindex);//muro der vent
		glPopMatrix();

		//////////////////////////////////////
		//muros piso 2 y 3
		//////////////////////////////////////
		glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(19.5,15,62);
			fig2.prisma(20,32,42,audit.GLindex);//auditorio
		glPopMatrix();
	
		glTranslatef(0,31.5,-68.75);//el centro es 31.5 pero ya esta en 5

		glPushMatrix();
			glTranslatef(8,0,10);
			fig2.prisma(73,4,0.5,cristal.GLindex);//dibuja muro enfrente parte 1
			glTranslatef(-8,0,0);
			glPushMatrix();
				glTranslatef(0,4,0);
				fig2.prisma(65,12,0.5,cristal.GLindex);//dibuja muro enfrente parte 2
				glTranslatef(0,-36.5,0);
				if(movelevador==poselevador && movelevador==4){
				
				}else{
					fig2.prisma(8,1,0.5,negro.GLindex);//dibuja muro enfrente parte 3
					glTranslatef(-3.25,0,0);
					fig2.prisma(8,5.5,0.5,elevador.GLindex);//dibuja muro enfrente parte 4
					glTranslatef(6.5,0,0);
					fig2.prisma(8,5.5,0.5,elevador.GLindex);//dibuja muro enfrente parte 5
				}
			glPopMatrix();
			glTranslatef(-8,0,0);
			fig2.prisma(73,4,0.5,cristal.GLindex);//dibuja muro enfrente parte 6
		glPopMatrix();
	glPopMatrix();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();

	glPushMatrix();	
	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glColor3f(1.0, 1.0, 1.0);
				glDisable(GL_LIGHTING);
				glTranslatef(0,150,0);
				fig1.skybox(largo_sky, 300.0, profundo_sky,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
				
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glLineWidth(2.0);
				glBegin(GL_LINES); //Ejes de Referencia
					glColor3f(1.0, 0.0, 0.0);
					glVertex3f(-80, 0.0, 0);
					glVertex3f(80.0, 0.0, 0);
					glColor3f(0.0, 1.0, 0.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 80.0, 0.0);
					glColor3f(0.0, 0.0, 1.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 85.0);
				glEnd();
				glEnable(GL_LIGHTING);
				
			glPopMatrix();
			/*
			Falta hacer la parte de las escaleras de la entrada para lo cual todo se tendría que levantar N unidades
			por eso lo pongo en el PUSH y POP para subirlo
			*/

			glColor3f(1,1,1);
			/////////////////////////
			glTranslatef(0,2,0);//subimos para que entre  el piso y el edificio esté el pasto
			glPushMatrix();
				glTranslatef(0,-1,0);
				pastizal();//pone el pasto
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,movelevador+8,-2);
				elevator();
			glPopMatrix();
			glPushMatrix();
				//glTranslatef(0, 2.5, 0);
				glTranslatef(0, 4, 0);
				//fig2.prisma(5, 78, 206.5, 0);
				fig2.prisma(8, 78, 123.5, muro.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 4, 82.25);
				fig2.prisma(8, 71, 41, muro.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-16.150, 4, 123.75);
				fig2.prisma(8, 38.75, 42, muro.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 0, 0);
				glTranslatef(-37.25, 0.5, 57.75);
				fig2.prisma(1, 3.25, 30, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 28,escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 26, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 24, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 22, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 20, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 18, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 16, escaleras.GLindex);
				glTranslatef(0, 0.5, 0);
				fig2.prisma(1, 3.25, 14, escaleras.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 0, 0);
				glTranslatef(37.25, 0.5, 57.75);
				fig2.prisma(1, 3.25, 30,escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 28, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 26, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 24, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 22, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 20, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 18, escaleras.GLindex);
				glTranslatef(0, 1, 0);
				fig2.prisma(1, 3.25, 16, escaleras.GLindex);
				glTranslatef(0, 0.5, 0);
				fig2.prisma(1, 3.25, 14, escaleras.GLindex);
			glPopMatrix();
			//codigo elevador
			//aqui podría continuar desde la base del escenario
			//codigo carro
			glColor3f(0,0,1);
			glPushMatrix();
				glRotatef(90, 0, 1, 0);
				glScalef(0.5, 0.5, 0.5);
				glTranslatef(190.25, 0, -120);
				glTranslatef(movKitX, movKitY+4, movKitZ);
				glRotatef(rotKit, 0, 1, 0);
				
				glRotatef(rotKitX, 1, 0, 0);
				

				kit.GLrender(NULL,_SHADED,1.0); //Dibujamos la carroceria
				//llanta.GLrender(NULL,_SHADED,1.0);

				//Colocar aquí las llantas
				glPushMatrix(); //llanta frontal der
					glTranslatef(-6,-1,7.5);
					glRotatef(-rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

				glPushMatrix(); //llanta frontal izq
					glTranslatef(6,-1,7.5);	
					glRotatef(180,0,1,0);
					glRotatef(rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();
				
				glPushMatrix(); //llanta trasera der
					glTranslatef(-6,-1,-9.5);	
					glRotatef(-rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

				glPushMatrix(); //llanta trasera izq
					glTranslatef(6,-1,-9.5);	
					glRotatef(180,0,1,0);
					glRotatef(rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

			glPopMatrix();
			glColor3f(1,1,1);
			//codigo nubes
			glPushMatrix();
				glTranslatef(0,200,0);
				nubes();
			glPopMatrix();
			glPushMatrix();
				//codigo edificio
				glTranslatef(0, 8, 61.75);
				techos();
				muros();
				oficinas();
			glPopMatrix();
			//aqui podría continuar desde la base del escenario
			

		glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glColor3f(1.0,0.0,0.0);
	pintaTexto(-0.25, 0.23,-0.25,(void *)font,"Proyecto Final Teoria");
	pintaTexto(-0.25, 0.21,-0.25,(void *)font,"Garcia Castro Hector");
	pintaTexto(-0.25, 0.19,-0.25,(void *)font,"Tobias Ramirez Diana Isadora");
	pintaTexto(-0.25, 0.17,-0.25,(void *)font,"Villar Ramirez Josafat Omar");
	pintaTexto(-0.25, 0.15,-0.25,(void *)font,"Villegas Moreno Zeuxis Daniel");
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}
void animacion()//Para que el elevador se mueva
{	
	if(g_fanimacion)
	{
		if (poselevador==movelevador){
			g_fanimacion=false;
		}else if(poselevador>movelevador){
				movelevador=movelevador+0.000001;
				movelevador=ceil(movelevador);
		}else if(poselevador<movelevador){
				movelevador-=0.000001;
				movelevador=floor(movelevador);
		}
	}
	fig3.text_izq-= 0.01;
	fig3.text_der-= 0.01;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	
		if(g_fanimacion)
	{
		if(g_avanza)
		{
			movKitZ +=1.0;
			rotTires -= 20;
			if(movKitZ>130)
				g_avanza = false;
		}
		else
		{
			movKitZ -=1.0;
			rotTires += 20;
			if(movKitZ<0)
				g_avanza = true;
		}
	}

	if(circuito)
	{
		if(recorrido1)
		{
			movKitZ=movKitZ+2;
			rotTires -= 20;
			if(movKitZ>240)
			{
				recorrido1 = false;
				recorrido2=true;
				
			}
		}

		if(recorrido2)
		{
			rotKit = -90;
			movKitX=movKitX-2;
			rotTires -= 20;
			if(movKitX <-500)
			{
				recorrido2 = false;
				recorrido3 = true;
				
			}
		}
		if(recorrido3)
		{
			rotKit = -180;
			movKitZ=movKitZ-2;
			rotTires -= 20;
			if(movKitZ< 0)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if(recorrido4)
		{
			rotKit = -270;
			movKitX=movKitX+2;
			rotTires -= 20;
			if(movKitX>0)
			{
				rotKit = 360;
				recorrido4 = false;
				recorrido1 = true;
			}
		}
		
	}
	
	frame++;
	_time=glutGet(GLUT_ELAPSED_TIME);
	if (_time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(_time-timebase));
		timebase = _time;		
		frame = 0;
	}

	glutPostRedisplay();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case ' ':		//Poner algo en movimiento
				circuito^= true; //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case '0':		//elevador se mueve a planta baja
				poselevador=4.000000;
				g_fanimacion=true;
			break;
		case '1':		//elevador se mueve a primer piso
			poselevador=14.000000;
			g_fanimacion=true;
			break;

		case '2':		//elevador se mueve a segundo piso
			poselevador=24.000000;
			g_fanimacion=true;
			break;

		case '3':		//elevador se mueve a tercer piso
			poselevador=34.000000;
			g_fanimacion=true;
			break;
		case '4':		//elevador se mueve a cuarto piso
			poselevador=44.000000;
			g_fanimacion=true;
			break;

		case '5':		//elevador se mueve a quinto piso
			poselevador=54.000000;
			g_fanimacion=true;
			break;

		case '6':		//elevador se mueve a sexto piso	
			poselevador=64.000000;
			g_fanimacion=true;
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }
	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{
	PlaySound(TEXT("Prelude.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (80, 80);	//Posicion de la Ventana
  glutCreateWindow    ("Figura Examen"); // Nombre de la Ventana

  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}


