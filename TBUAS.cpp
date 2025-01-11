#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

using namespace std;

float lightPos[] = {10.0f, 10.0f, 10.0f, 1.0f};
float tableHeight = -5.0f; 
bool isMoving = true;
bool showCartesian = false; 

//Variabel Tranlasi untuk Dadu
float dicePosX = 0.0;

// Variabel Scale untuk Dadu
float diceScale = 1.0;

struct Movement
{
    float rotate;
    
} dice;

void init3D();
void display();
void drawRoom();
void drawTable();
void drawDice();
void drawCartesianLines();
void createMenu();
void update(int value);
void processMenu(int option);
void myKeyboard(unsigned char key, int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TUGAS BESAR PRAKTIKUM GRAFKOM KELOMPOK4");

    init3D();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    createMenu();
    glutTimerFunc(1000 / 60, update, 0);
    glutMainLoop();
    return 0;
}

void init3D()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1.0, 100.0);
    gluLookAt(40.0, 30.0, 60.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.9, 0.9, 0.9, 1.0); 
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    drawRoom(); // Menggambar Background Ruangan
    drawTable(); // Menggambar Meja

    if (showCartesian)
    {
        drawCartesianLines(); // Garis kartesius
    }

    drawDice(); // Menggambar Dadu

    glutSwapBuffers();
}

void drawRoom()
{
    // Lantai pada ruangan
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); 
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, tableHeight - 10, -50.0f); 
    glVertex3f(50.0f, tableHeight - 10, -50.0f);
    glVertex3f(50.0f, tableHeight - 10, 50.0f);
    glVertex3f(-50.0f, tableHeight - 10, 50.0f);
    glEnd();
    glPopMatrix();
}

void drawTable()
{
    glPushMatrix();
    glColor3ub(139, 69, 19); 
    glTranslated(0.0, tableHeight, 0.0);

    // Bagian Permukaan (Atas) Meja
    glPushMatrix();
    glScalef(30.0, 1.0, 20.0); // Ukuran Meja
    glutSolidCube(1.0);
    glPopMatrix();

    // Bagian Kaki (Bawah) Meja
    float legOffsetX = 14.5f;
    float legOffsetZ = 9.5f;

    glPushMatrix();
    glTranslated(legOffsetX, -5.0, legOffsetZ);
    glScalef(1.0, 10.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-legOffsetX, -5.0, legOffsetZ);
    glScalef(1.0, 10.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(legOffsetX, -5.0, -legOffsetZ);
    glScalef(1.0, 10.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-legOffsetX, -5.0, -legOffsetZ);
    glScalef(1.0, 10.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void drawDice()
{
    glPushMatrix();
    glTranslated(dicePosX, tableHeight + 3.0, 0.0); //untuk Tranlasi pada Dadu
    glRotated(dice.rotate, 1.0, 1.0, 0.0);
    glScalef(diceScale, diceScale, diceScale);
    glColor3ub(255, 255, 255); 
    glutSolidCube(4.0);
    
 	glColor3ub(0, 0, 0);
 	
    // Titik  Satu (Bagian Depan Dadu)
    glPushMatrix();
    glTranslated(0.0, 0.0, 2.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();

	// Titik  Dua (Bagian Belakang Dadu)
    glPushMatrix();
    glTranslated(-1.0, -1.0, -2.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.0, 1.0, -2.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    // Titik  Tiga (Bagian Kanan Dadu)
    glPushMatrix();
    glTranslated(2.0, -1.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(2.0, 0.0, 0.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(2.0, 1.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    // Titik  Empat (Bagian Kiri Dadu)
    glPushMatrix();
    glTranslated(-2.0, 1.0, 1.0);
    glutSolidSphere(0.3, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-2.0, -1.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-2.0, 1.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-2.0, -1.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    // Titik  Lima (Bagian Atas Dadu)
    glPushMatrix();
    glTranslated(-1.0, 2.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.0, 2.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 2.0, 0.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-1.0, 2.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.0, 2.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    // Titik  Enam (Bagian Bawah Dadu)
    glPushMatrix();
    glTranslated(-1.0, -2.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.0, -2.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, -2.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-1.0, -2.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.0, -2.0, 1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, -2.0, -1.0);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
    
    glPopMatrix();
}

void drawCartesianLines()
{
    glPushMatrix();
    glLineWidth(2.0);
    glColor3f(0.8f, 0.6f, 1.0f); 
    glBegin(GL_LINES);
    glVertex3f(-50.0f, tableHeight, 0.0f);
    glVertex3f(50.0f, tableHeight, 0.0f);
    glEnd();

    glColor3f(0.8f, 0.6f, 1.0f); 
    glBegin(GL_LINES);
    glVertex3f(0.0f, tableHeight - 50.0f, 0.0f);
    glVertex3f(0.0f, tableHeight + 50.0f, 0.0f);
    glEnd();

  	glColor3f(0.8f, 0.6f, 1.0f);  
    glBegin(GL_LINES);
    glVertex3f(0.0f, tableHeight, -50.0f);
    glVertex3f(0.0f, tableHeight, 50.0f);
    glEnd();
    glPopMatrix();
}

void createMenu()
{
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Start/Stop Rotation", 1);
    glutAddMenuEntry("Tampilkan/Sembunyikan Garis Kartesius", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenu(int option)
{
    switch (option)
    {
    case 1:
        isMoving = !isMoving;
        break;
    case 2:
        showCartesian = !showCartesian;
        break;
    case 3:
        exit(0);
    }
    glutPostRedisplay();
}

void update(int value)
{
    if (isMoving)
    {
        dice.rotate += 1.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
}
void myKeyboard(unsigned char key, int x, int y)
{

//Batas minumum dan maksimum posisi dadu pada translasi	
const float Min_X = -12.0;
const float Max_X = 13.0;
const float Min_Scale = 0.5;
const float Max_Scale = 2.0;
switch (key)
{
    case 's': // Tombol 's' untuk bergerak ke Kanan
        if (!isMoving && dicePosX + 0.1 <= Max_X) // Bergerak saat Rotasi Berhenti
            dicePosX += 0.1;
        break;

    case 'r': // Tombol 'r' untuk bergerak ke Kiri
        if (!isMoving && dicePosX - 0.1 >= Min_X) // Bergerak saat Rotasi Berhenti
            dicePosX -= 0.1;
        break;

    case 'n': // Tombol 'n' untuk Memperkecil Dadu
        if (!isMoving && diceScale - 0.1 >= Min_Scale) // Bergerak saat Rotasi Berhenti
            diceScale -= 0.1;
        break;

    case 'a': // Tombol 'a' untuk Memperbesar Dadu
        if (!isMoving && diceScale + 0.1 <= Max_Scale) // Bergerak saat Rotasi Berhenti
            diceScale += 0.1;
        break;

    default:
        break;
}
    glutPostRedisplay();
	
}