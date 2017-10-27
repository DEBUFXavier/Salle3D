#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif                     
#include<math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "tga.h"
#define D_ANGLE 0.015708
#define SCA 1.0
#define COTE 0.5
GLuint texture[10];
GLuint le_cube;
GLuint le_pied;
GLuint le_plateau;
GLuint les_4pieds;
GLuint la_table;
GLuint la_rangee;
GLuint la_salle;
GLuint la_tour;
GLuint le_socle_H;
GLuint le_socle_V;
GLuint le_ecran;
GLuint le_clavier;
GLuint le_siege;
GLuint le_pied_chaise;
GLuint le_dossier;
GLuint la_chaise;
GLuint les_4pied_Chaise;
GLuint le_mur1;
GLuint le_mur2;
GLuint le_mur3;
GLuint la_porte;
GLuint le_tableau;





//GLuint le_pc;

//GLuint la_tour;
enum mouvement{RIEN,GAUCHE,MILIEU,DROIT} mouv;

//GLuint la_croix, le_repere, ancien_x, ancien_y, le_cube, fixe=-1;

GLdouble angle=0.4*M_PI, tetha=0.00005*M_PI, hauteur=0.50, distance=1035.0, rayon=0.25;
/*GLdouble angle=M_PI, tetha=M_PI;*/
struct point{double x,y,z;};         /* definition d'un point */
typedef struct point point;

struct vecteur{double x,y,z;};       /* definition d'un vecteur */
typedef struct vecteur vecteur;

vecteur co,cote={1,2,2},cote2={2,1,-2},cote3;

//point centre={1.5,3.5,1.5},observateur={10.5,6,8.5};
point centre={10,75.,0.},observateur={10.,10.,5.};
int ancien_x, ancien_y;float alpha=0.0;
long	timeout=20;
float eclat[]={119.0};
float position[]={2,5,2,1.};
GLfloat XPied=5.0;YPied=72.0;ZPied=5.0;
GLfloat XPlateau=160.0;YPlateau=3.0;ZPlateau=80.0;
GLfloat ecartTable=76.;GLfloat ecart=240.;
GLfloat largeurSalle=610.;hauteurSalle=275.;longueurSalle=980.;
 GLfloat XPosPl;
 GLfloat YPosPl;
 GLfloat ZPosPl;
 GLfloat XPi;
 GLfloat YPi;
 GLfloat ZPi;
 point sommet[6][4]={{{+COTE,-COTE,+COTE},{+COTE,-COTE,-COTE},{+COTE,+COTE,-COTE},{+COTE,+COTE,+COTE}},   /* face 0 */
                    {{+COTE,-COTE,-COTE},{-COTE,-COTE,-COTE},{-COTE,+COTE,-COTE},{+COTE,+COTE,-COTE}},   /* face 1 */
                    {{-COTE,-COTE,-COTE},{-COTE,-COTE,+COTE},{-COTE,+COTE,+COTE},{-COTE,+COTE,-COTE}},   /* face 2 */
                    {{-COTE,-COTE,+COTE},{+COTE,-COTE,+COTE},{+COTE,+COTE,+COTE},{-COTE,+COTE,+COTE}},   /* face 3 */
                    {{-COTE,+COTE,+COTE},{+COTE,+COTE,+COTE},{+COTE,+COTE,-COTE},{-COTE,+COTE,-COTE}},   /* face 4 */
                    {{-COTE,-COTE,-COTE},{+COTE,-COTE,-COTE},{+COTE,-COTE,+COTE},{-COTE,-COTE,+COTE}}};
point normale[6]={{1.,0.,0.},{0.,0.,-1.},{-1.,0.,0.},{0.,0.,1.},{0.,1.,0.},{0.,-1.,0.}};
char* image[]={"./texture/clavier.tga","./texture/tour.tga","./texture/TextureEcran.tga","./texture/texture_citrouille.tga","./texture/textureTable.tga","./texture/tableau.tga","./texture/TexturePied.tga","./texture/porte.tga","./texture/mur2.tga","./texture/sol5.tga"};

void vTimer(int i)
{
	alpha=alpha+1.0;
	glutPostRedisplay();
	glutTimerFunc(timeout,vTimer,i);	// On choisit un timer de 50ms
}
void charger_image(int* id, const char* fichier)
{
    glGenTextures(1,id);
    glBindTexture(GL_TEXTURE_2D,*id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    gl_texture_t* tex = ReadTGAFile(fichier);
    glTexImage2D(GL_TEXTURE_2D,0,tex->internalFormat,tex->width,tex->height,0,tex->format,GL_UNSIGNED_BYTE,tex->texels);
    free(tex->texels);
    free(tex);
    glBindTexture(GL_TEXTURE_2D,0);
}
void construire_cube()
{
  int f;
  
  float mat_ambiante[]={.75,0.75,0.75,1.0};
  float mat_diffuse[]={.75,0.75,0.75,1.0};
  float mat_speculaire[]={1.,1.,1.,1.0};
  
 // cube[0]=glGenLists(1);
  le_cube=glGenLists(1);
  glNewList(le_cube,GL_COMPILE);

  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialf(GL_FRONT,GL_SHININESS,100.);
  
  for(f=0;f<6;f++){
  //glBindTexture(GL_TEXTURE_2D,texture[0]);
  //glBindTexture(GL_TEXTURE_2D,0);
  
      glBegin(GL_QUADS);
  
      // glNormal3f(normale[f].x,normale[f].y,normale[f].z); 
      glNormal3f(normale[0].x,normale[4].y,normale[1].z); 
      glTexCoord2f(0.,0.);
      glVertex3f(sommet[f][0].x,sommet[f][0].y,sommet[f][0].z);
      glTexCoord2f(1.,0.);
      glVertex3f(sommet[f][1].x,sommet[f][1].y,sommet[f][1].z);
      glTexCoord2f(1.,1.);
      glVertex3f(sommet[f][2].x,sommet[f][2].y,sommet[f][2].z);
      glTexCoord2f(0.,1.);
      glVertex3f(sommet[f][3].x,sommet[f][3].y,sommet[f][3].z);
    
    glEnd();

   // glBindTexture(GL_TEXTURE_2D,0);
    
    }

  glEndList(); 
  
   // glerror = glGetError();
  //if(glerror != GL_NO_ERROR) printf("==> Erreur OpenGL : %s \n",gluErrorString(glerror));
}
/*void construire_cube(){
float taille=1;
le_cube=glGenLists(1);
glNewList(le_cube,GL_COMPILE);
glutSolidCube(taille);
glEndList();
}*/
void construire_pied(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
XPi=0.;
YPi=YPied/2;
ZPi=0.;

  
le_pied=glGenLists(1);
glNewList(le_pied,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[6]);
glPushMatrix();

	glTranslatef(XPi,YPi,ZPi);
	glScalef(XPied,YPied,ZPied);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}

void construire_plateau(){
float mat_diffuse[]={1.,1.,1.,1.};
float mat_ambiante[]={0.1,0.1,0.1,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
XPosPl=0.;
YPosPl=YPied;
ZPosPl=0.;

  
le_plateau=glGenLists(1);
glNewList(le_plateau,GL_COMPILE);
 
  
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
  
  glBindTexture(GL_TEXTURE_2D,texture[4]);
  
glPushMatrix();
glTranslatef(XPosPl,YPosPl,ZPosPl);
	glScalef(XPlateau,YPlateau,ZPlateau);
	
	glCallList(le_cube);
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();

}
void construire_tour(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float XT=50.0;
float YT=95.;
float ZT=0.0;

  
la_tour=glGenLists(1);
glNewList(la_tour,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
glPushMatrix();

	glTranslatef(XT,YT,ZT);
	glScalef(20.0,40.0,45.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_socle_horizontal(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float XE=-10.0;
float YE=75.;
float ZE=-10.0;

  
le_socle_H=glGenLists(1);
glNewList(le_socle_H,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
glPushMatrix();

	glTranslatef(XE,YE,ZE);
	glScalef(18.,1.5,15.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_socle_vertical(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float XE=-10.0;
float YE=85.0+1.5;
float ZE=-10.0;

  
le_socle_V=glGenLists(1);
glNewList(le_socle_V,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
glPushMatrix();

	glTranslatef(XE,YE,ZE);
	glScalef(7.,27.,2.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_siege(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float XS=15.0;
float YS=40.;
float ZS=40.0;

  
le_siege=glGenLists(1);
glNewList(le_siege,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
glPushMatrix();

	glTranslatef(XS,YS,ZS);
	glScalef(40.0,2.0,40.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_le_pied_chaise(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float Xp=15.0;
float Yp=75.0+1.5;
float Zp=40.0;

  
le_pied_chaise=glGenLists(1);
glNewList(le_pied_chaise,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
glPushMatrix();

	glTranslatef(Xp,Yp,Zp);
	glScalef(2.,40.,2.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_dossier(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float Xd=15.0;
float Yd=60.0;
float Zd=60.0;

  
le_dossier=glGenLists(1);
glNewList(le_dossier,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
glPushMatrix();

	glTranslatef(Xd,Yd,Zd);
	glScalef(40.,40.,2.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_4Pied_chaise(){
GLfloat XPosPi=20.;
 GLfloat YPosPi=-55.0;
 GLfloat ZPosPi=20.0;
les_4pied_Chaise=glGenLists(1);
glNewList(les_4pied_Chaise,GL_COMPILE);
glPushMatrix();	
glPushMatrix();
		glTranslatef(XPosPi,YPosPi,ZPosPi);
		glCallList(le_pied_chaise);
glPopMatrix();
glPushMatrix();
		glTranslatef(XPosPi,YPosPi,-ZPosPi);
		glCallList(le_pied_chaise);
glPopMatrix();
glPushMatrix();
		glTranslatef(-XPosPi,YPosPi,ZPosPi);
		glCallList(le_pied_chaise);
glPopMatrix();
glPushMatrix();
		glTranslatef(-XPosPi,YPosPi,-ZPosPi);
		glCallList(le_pied_chaise);
glPopMatrix();
glPopMatrix();
glEndList();
}
void construire_chaise(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};


  
la_chaise=glGenLists(1);
glNewList(la_chaise,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
glPushMatrix();

	glCallList(le_siege);
	glCallList(les_4pied_Chaise);
	glCallList(le_dossier);
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}

void construire_ecran(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float XE=-10.0;
float YE=105.;
float ZE=-10.0;

  
le_ecran=glGenLists(1);
glNewList(le_ecran,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
glPushMatrix();

	glTranslatef(XE,YE,ZE);
	glScalef(45.,35.0,5.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_clavier(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
float XC=-10.0;
float YC=75.0+1.5;
float ZC=5.0;

  
le_clavier=glGenLists(1);
glNewList(le_clavier,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
glPushMatrix();

	glTranslatef(XC,YC,ZC);
	glScalef(50.0,2.0,25.0);
	glCallList(le_cube);
	
	
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void construire_4Pied(){
GLfloat XPosPi=XPlateau/2-5.0;
 GLfloat YPosPi=YPlateau-2.5;
 GLfloat ZPosPi=ZPlateau/2-5.0;
les_4pieds=glGenLists(1);
glNewList(les_4pieds,GL_COMPILE);
glPushMatrix();	
glPushMatrix();
		glTranslatef(XPosPi,YPosPi,ZPosPi);
		glCallList(le_pied);
glPopMatrix();
glPushMatrix();
		glTranslatef(XPosPi,YPosPi,-ZPosPi);
		glCallList(le_pied);
glPopMatrix();
glPushMatrix();
		glTranslatef(-XPosPi,YPosPi,ZPosPi);
		glCallList(le_pied);
glPopMatrix();
glPushMatrix();
		glTranslatef(-XPosPi,YPosPi,-ZPosPi);
		glCallList(le_pied);
glPopMatrix();
glPopMatrix();
glEndList();
}
void construire_table()
{
 la_table=glGenLists(1);
glNewList(la_table,GL_COMPILE);
glPushMatrix();	
		glCallList(le_plateau);
		glCallList(les_4pieds);
		glCallList(la_tour);
		glCallList(le_ecran);
		glCallList(le_socle_H);
		glCallList(le_socle_V);
		glCallList(le_clavier);
		glTranslatef(-50.0,0.0,0.0);
		glCallList(la_chaise);
		glTranslatef(50.0,0.0,0.0);
		glCallList(la_chaise);
glPopMatrix();
glEndList();
}
void construire_rangee(){
int i=0;

la_rangee=glGenLists(1);
glNewList(la_rangee,GL_COMPILE);
for(i=0;i<3;i++){
 XPosPl=XPosPl+XPlateau;
glPushMatrix();
	glTranslatef(XPosPl,0.,0.);
	glCallList(la_table);	
glPopMatrix();
}
glEndList();
}
void construire_salle(){
int i=0;
 GLfloat XPosT=0.;
 GLfloat YPosT=0.;
 GLfloat ZPosT=ZPlateau+240.;
la_salle=glGenLists(1);
glNewList(la_salle,GL_COMPILE);
float XposTable=610.0-3.0*160.0-160.0/2.0;
for(i=0;i<4;i++){
 
glPushMatrix();
	glTranslatef(XposTable,YPosT,ZPosT);
	glCallList(la_rangee);	
glPopMatrix();
 ZPosT=ZPosT+ZPlateau+76.;
}

glEndList();

}
void construire_la_porte(){
float mat_diffuse[]={0.95,0.95,0.95,1.};
float mat_ambiante[]={0.95,0.95,0.95,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
//glCallList(le_mur1);
//float largeur=largeurSalle-95./2;
float hauteur=hauteurSalle/2-30.;
la_porte=glGenLists(1);
glNewList(la_porte,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
  glBindTexture(GL_TEXTURE_2D,texture[7]);
 glPushMatrix();
 	glTranslatef(largeurSalle,hauteur,195.);
	glScalef(4.,205.,95.);
	glCallList(le_cube);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();

}void construire_tableau(){
float mat_diffuse[]={0.75,0.75,0.75,1.};
float mat_ambiante[]={0.75,0.75,0.75,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};

le_tableau=glGenLists(1);
glNewList(le_tableau,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
  glBindTexture(GL_TEXTURE_2D,texture[5]);
 glPushMatrix();
 	glTranslatef(largeurSalle/2,hauteurSalle/2,0.0);
	glScalef(400.,125,4.);
	glCallList(le_cube);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();

}

void construire_mur1(){
float mat_diffuse[]={0.85,0.85,0.85,1.};
float mat_ambiante[]={0.85,0.85,0.85,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};



le_mur1=glGenLists(1);
glNewList(le_mur1,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
  glBindTexture(GL_TEXTURE_2D,texture[8]);
 glPushMatrix();
 	glTranslatef(largeurSalle/2,hauteurSalle/2,0.0);
	glScalef(largeurSalle,hauteurSalle,0.5);
	glCallList(le_cube);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glCallList(le_tableau);
glEndList();
}
void construire_mur2(){
float mat_diffuse[]={0.3,0.75,0.5,1.};
float mat_ambiante[]={0.3,0.75,0.5,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
//glCallList(la_salle);
le_mur2=glGenLists(1);
glNewList(le_mur2,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
  glBindTexture(GL_TEXTURE_2D,texture[8]);
 glPushMatrix();
 	glTranslatef(largeurSalle,hauteurSalle/2,longueurSalle/2);
	glScalef(0.5,hauteurSalle,longueurSalle);
	glCallList(le_cube);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glCallList(la_porte);
glEndList();
}
void construire_mur3(){
float mat_diffuse[]={0.95,0.95,0.95,1.};
float mat_ambiante[]={0.95,0.95,0.95,1.};
float mat_speculaire[]={0.98,0.98,0.98,1.};
//glCallList(la_salle);
le_mur3=glGenLists(1);
glNewList(le_mur3,GL_COMPILE);
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,eclat);
  glBindTexture(GL_TEXTURE_2D,texture[9]);
 glPushMatrix();
 
 	glTranslatef(largeurSalle/2,0.0,longueurSalle/2);
	glScalef(largeurSalle,0.5,longueurSalle);
	glCallList(le_cube);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D,0);
glEndList();
}
void initialiser_lumieres()
{
  //float comp_ambiante[]={0.6,0.6,0.2,1.};   /* intensitÔøΩ ambiante de la lumiÔøΩre                */
 float comp_ambiante[]={.75,.75,.75,0.};   /* intensitÔøΩ ambiante de la lumiÔøΩre                */
 //float comp_diffuse[]={0.8,0.8,0.8,1.};    /* intensitÔøΩ diffuse de la lumiÔøΩre                 */
  float comp_diffuse[]={.75,.75,.75,0.};    /* intensitÔøΩ diffuse de la lumiÔøΩre                 */
  //float comp_speculaire[]={0.5,0.5,0.5,1.}; /* intensitÔøΩ spÔøΩculaire de la lumiere              */
float comp_speculaire[]={1.,1.,1.,0.}; /* intensitÔøΩ spÔøΩculaire de la lumiere              */

  glEnable(GL_LIGHT0);                             /* active la lumiÔøΩre 0 */
  glLightfv(GL_LIGHT0,GL_AMBIENT,comp_ambiante);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,comp_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,comp_speculaire);
}
/*======================================*/
/* fonctions de calcul sur les vecteurs */
/*======================================*/

vecteur le_vecteur(point A, point B)
{vecteur V;

 V.x=B.x-A.x;
 V.y=B.y-A.y;
 V.z=B.z-A.z;
 return(V);
}

vecteur vectoriel(vecteur X,vecteur Y)
{vecteur W;

 W.x=(X.y*Y.z)-(X.z*Y.y);
 W.y=(X.z*Y.x)-(X.x*Y.z);
 W.z=(X.x*Y.y)-(X.y*Y.x);
 return(W);
}

double scalaire(vecteur X,vecteur Y)
{
  return(X.x*Y.x+X.y*Y.y+X.z*Y.z);
}

double norme(vecteur X)
{
  return(sqrt(X.x*X.x+X.y*X.y+X.z*X.z));
}

vecteur normalise(vecteur X)
{double n;
 vecteur Y;

 n=norme(X);
 Y.x=X.x/n;
 Y.y=X.y/n;
 Y.z=X.z/n;
 return(Y);
}

void affiche_vecteur(vecteur X)
{
  printf("%lf, %lf, %lf\n",X.x,X.y,X.z);
}

void affiche_point(point X)
{
  printf("%lf, %lf, %lf\n",X.x,X.y,X.z);
}

/*=================================*/
/* conversion d'angle rad <--> deg */
/*=================================*/

float deg(float angle)
{
  return (angle/M_PI)*180.;
}

float rad(float angle)
{
  return (angle/180.)*M_PI;
}

void initialiser()
{int i;
 co.x=observateur.x-centre.x;
 co.y=observateur.y-centre.y;
 co.z=observateur.z-centre.z; 
}

/*===============================================================================================*/
/* cette fonction realise la phase de VISUALISATION de la scene : mise en place de l'observateur */
/*===============================================================================================*/

void affichage()
{
  GLfloat Ox,Oy,Oz;
  //GLfloat Cx=largeurSalle/2.,Cy=hauteurSalle/2.,Cz=longueurSalle/2.;
  GLfloat Cx=350.,Cy=150.,Cz=0.;
  //GLfloat Cx=0.,Cy=0.,Cz=0.;
  GLfloat Ix=0.,Iy=1.,Iz=0.;

  GLfloat pos_lum1[]={0.5,250.,150.,1.};
  GLfloat pos_lum2[]={150.,200.,150.,1.};

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  rayon=distance*cos(tetha);
  Ox=rayon*cos(angle);                
  Oz=rayon*sin(angle);
  Oy=Cy+distance*sin(tetha);
//souris((int)Ox,(int)Oy);
  gluLookAt(Ox,Oy,Oz, Cx,Cy,Cz, Ix,Iy,Iz);   

  glLightfv(GL_LIGHT1,GL_POSITION,pos_lum1);
   glLightfv(GL_LIGHT1,GL_POSITION,pos_lum2);
 glCallList(le_mur1);
 glCallList(le_mur2);
 glCallList(le_mur3);
 
	glCallList(la_salle);
	
  glutSwapBuffers();  

}

/*=======================================================================================*/
/* cette fonction realise la phase de PROJECTION de la vue : definition du volume de vue */
/*=======================================================================================*/

void la_vue(int l, int h)
{

  GLfloat gauche=-.5,droite=.5;                       /* plans lateraux     */
  GLfloat bas=-.5,haut=.5;                            /* plans horizontaux  */
  GLfloat devant=1.,derriere=9800.;                     /* plans de facade    */

  if(l<h) h=l; else l=h;                              /* on conserve les proportions lar./hau. */
  glViewport(0.,0.,(GLsizei) l,(GLsizei) h);          /* definition de la fenetre logique      */

  glMatrixMode(GL_PROJECTION);                        /* selection de la matrice de projection */
  glLoadIdentity();
  glFrustum(gauche,droite,bas,haut,devant,derriere);  /* definition du volume de vue           */

}
void click_souris(int bouton,int etat,int x,int y)
{
  if(etat==GLUT_DOWN){
    ancien_x=x;
    ancien_y=y;
      switch(bouton)
	{
	case GLUT_LEFT_BUTTON :
	  mouv=GAUCHE;
	break;
	case GLUT_MIDDLE_BUTTON :
	  mouv=MILIEU;
	break;
	case GLUT_RIGHT_BUTTON :
	  mouv=DROIT;
	break;
	default :
	break;
     }
  }
  else if(etat==GLUT_UP) mouv=RIEN;
}

void souris(int x,int y)
{int dx,dy;

 dx=x-ancien_x;
 dy=y-ancien_y;

  switch(mouv){
  case GAUCHE :                                                /* depl. du global autour de la vue globale */
    if(dx<0) angle=angle-D_ANGLE;
    else if(dx>0) angle=angle+D_ANGLE;
    if(dy>0 && tetha<=M_PI/2.1) tetha=tetha+D_ANGLE;
    else if(dy<0 && tetha>=-M_PI/2.1) tetha=tetha-D_ANGLE;
    break;
  case DROIT :
    break;
  case MILIEU :                                                /* deplacement du global en avant ou en arriere */
    if (dy<0 && distance>2.) distance=distance-0.1;
    else if (dy>0 && distance<20.) distance=distance+0.1;
    break;
  }
 
 ancien_x=x;
 ancien_y=y;
 glutPostRedisplay();
}
void definir_lumiere()
{
  GLfloat lumiere1_ambiante[]={0.1,0.1,0.1,1.};      /* comp. ambiante : lumiere multidirectionnelle                         */
  GLfloat lumiere1_diffuse[]={0.8,0.8,0.8,1.};       /* comp. diffuse  : lumiere unidirect. reflechie ds ttes les dir.       */
  GLfloat lumiere1_speculaire[]={0.8,0.8,0.8,1.};    /* comp. speculaire : lumiere unidirect. reflechie ds une dir. (=eclat) */

  GLfloat lumiere2_ambiante[]={0.1,0.1,0.1,1.};
  GLfloat lumiere2_diffuse[]={0.9,0.9,0.9,1.};
  GLfloat lumiere2_speculaire[]={0.9,0.9,0.9,1.};

  glLightfv(GL_LIGHT1,GL_DIFFUSE,lumiere1_diffuse);    /* la lumiere1 simule une lumiere provenant d'une ampoule */
  glLightfv(GL_LIGHT1,GL_SPECULAR,lumiere1_speculaire);
  glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,.1);      /* Kc coef. cst, independant de la distance obj./lum.                     */
  glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,.1);        /* Kl agit de facon lineaire par rapport a la distance obj./lum.          */
  glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,.05);    /* Kq agit sur le carre de la distance obj./lum.                          */
                                                       /* K=1/Kc+Kl.d+Kq.d.d, + K est faible + la lum. s'attenuee sur la dist. d */

  glLightfv(GL_LIGHT2,GL_AMBIENT,lumiere2_ambiante);   /* la lumiere2 simule une lumiere provenant d'une fenetre */
  glLightfv(GL_LIGHT2,GL_DIFFUSE,lumiere2_diffuse);
  glLightfv(GL_LIGHT2,GL_SPECULAR,lumiere2_speculaire);

  glEnable(GL_LIGHT1);                                 /* allume la lumiere 1 */
  glEnable(GL_LIGHT2);                                 /* allume la lumiere 2 */
}
void clavier(unsigned char touche, int x, int y)
{
  switch(touche){
  case 27:
    exit(0);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}
void touches_speciales(int touche, int x, int y)
{
  switch(touche){
    /* rotation autour de O(0,0,0) */
  case GLUT_KEY_LEFT:
    angle=angle-M_PI/100.;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    angle=angle+M_PI/100.;
    glutPostRedisplay();
    break;
  case GLUT_KEY_UP:
    /*hauteur=hauteur-0.05;
    if(hauteur<-5.) hauteur=-5.;*/
    distance=distance-10;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    /*hauteur=hauteur+0.05;
    if(hauteur>5.) hauteur=5.;*/
    distance=distance+10;
    glutPostRedisplay();
    break;
    /* sortie ! */
  case GLUT_KEY_END:   
    exit(0);
    break;
  default: break;
  }
  }
main(int argc, char **argv)
{
 system("clear");

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
  
  /* initialisation de la fenetre principale */

  glutInitWindowSize(600, 600);
  glutInitWindowPosition(10,10);
  glutCreateWindow("Salle de classe Xavier DEBUF");
  int i;
  for(i=0;i<10;i++) charger_image(&texture[i],image[i]);
  /* phase de modelisation : appel des fonctions de construction des objets */
  construire_cube();
  construire_pied();
  construire_tour();
  construire_ecran();
  construire_socle_horizontal();
  construire_socle_vertical();
  construire_siege();
  construire_dossier();
  construire_le_pied_chaise();
  construire_4Pied_chaise();
  construire_chaise();
  construire_clavier();
  construire_plateau();
  construire_4Pied();
  construire_table();
  construire_rangee();
  construire_salle();
  construire_la_porte();
  construire_tableau();
  construire_mur1();
  construire_mur2();
  construire_mur3();
//glShadeModel(GL_SMOOTH);  

  /* mise en place du Z-buffer */
glEnable(GL_LIGHTING);   /* active l'Èclairage */

  initialiser_lumieres();

  glutKeyboardFunc(&clavier);
  glutSpecialFunc(&touches_speciales);
  glutDisplayFunc(&affichage);
  glutMotionFunc(&souris);
  glutMouseFunc(&click_souris);
  glutReshapeFunc(&la_vue);
	definir_lumiere();
  glEnable(GL_LIGHTING);
 glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
 

  glEnable(GL_DEPTH_TEST);                           /* mise en place du Z-buffer */
  glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);  /* correction de perspective sur les textures */
  glEnable(GL_NORMALIZE);
  glEnable(GL_RESCALE_NORMAL);
  glEnable(GL_TEXTURE_2D);
glShadeModel(GL_SMOOTH);
  /* phase de modelisation : appel des fonctions de construction des objets */
  //for(i=0;i<10;i++) charger_image(&texture[i],image[i]);
  initialiser();

  glutDisplayFunc(&affichage);
  glutReshapeFunc(&la_vue);
  glutMainLoop();

}
