//
// main.cpp for  in /home/vagrant/shared_data/Bedel2K17
// 
// Made by Vagrant Default User
// Login   <adrien.bedel@epitech.eu>
// 
// Started on  Mon Mar 27 16:54:35 2017 Vagrant Default User
// Last update Mon Mar 27 16:55:53 2017 Vagrant Default User
//


//#include "encapsulation/Input.hpp"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
//#include "encapsulation/L_OpenGL.hpp"
#include <iostream>
#include <vector>
#include "Triangle.hpp"
//#include "engine/ObjParser.hpp"
//#include "Light.hpp"

#include "map/Diamond.hpp"

/*void Reshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int x = 640;
    int y = 490;
    //glViewport(0, 0, x, y);
    gluPerspective(60, (float)x / (float)y, 1.f, 1000.f);
    glEnable(GL_DEPTH_TEST);
}*/

std::vector<game::Triangle<float>> triangles;
/*void Draw()
{
    //glClearColor(0.3f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,-10,0,0,0,0,1,0);

    glRotatef(0.0f, 1.0, 0.0, 0.0);
    glRotatef(0.0f, 0.0, 1.0, 0.0);

    glTranslatef(0.f, -5.f, -3.f);

    Light _light;
    _light.setPos(31.0, 35.0, 73.0, 1.0);
    _light.setDiffuse(0.0, 0.0, 1.0, 1.0);
    _light.setAmbient(0.0, 0.0, 0.0, 1.0);
    _light.setSpecular(1.0, 1.0, 1.0, 1.0);
	//gl.initRendering();
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);

    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);

    //glLightfv(GL_LIGHT0, GL_POSITION, _light._pos);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, _light._diffuse);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, _light._ambient);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, _light._specular);

	GLfloat tete[9];
    std::cout << triangles[0].vertices[0].x << " ";
    std::cout << triangles[0].vertices[1].x << " ";
    std::cout << triangles[0].vertices[2].x << std::endl;
    glBegin(GL_TRIANGLES);
	for (size_t k = 0; k < triangles.size(); k++)
	{
		tete[0] = triangles[k].vertices[0].x;
		tete[1] = triangles[k].vertices[0].y;
		tete[2] = triangles[k].vertices[0].z;

		tete[3] = triangles[k].vertices[1].x;
		tete[4] = triangles[k].vertices[1].y;
		tete[5] = triangles[k].vertices[1].z;

		tete[6] = triangles[k].vertices[2].x;
		tete[7] = triangles[k].vertices[2].y;
		tete[8] = triangles[k].vertices[2].z;

        glNormal3f(triangles[k].normal.x, triangles[k].normal.y, triangles[k].normal.z);
        glVertexPointer(3, GL_FLOAT, 0, tete);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(0,1);
    glVertex2i(-1,0);
    glVertex2i(1,0);

    glEnd();
	//gl.finishRendering();

    //glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);

    //glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);

    glutSwapBuffers();
    glutPostRedisplay();
    //glFlush();
}

int main(int argc,char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Ma première fenêtre OpenGL !");

	//sf::RenderWindow window(sf::VideoMode(960, 540), "Cube!", sf::Style::Default);
	Camera *camera = new Camera();
	L_OpenGL gl(camera);
	Input input(camera);

	Diamond diams(0.75f, 65);
	diams.fillMap();
	diams.updateVertices(5, 250);
	diams.updateTriangles();
	//window.setVerticalSyncEnabled(true);
	//window.setActive(true);
	//window.resetGLStates();
	//game::Parser parser("../ressources/obj/hazelnut.obj");
	//diams.printMap();
	std::vector<game::Triangle<float>>	terrain;
	//gl.init();

	//gl.initReshape(window);
    triangles = diams._triangles;
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutMainLoop();
	bool running = true;
	while (running)
	{
		while (window.pollEvent(input._event))
		{
			input.KeyManager(running);
		}
		input.KeyManager(running);

		gl.clear();

		gl.updateCamera();

		//draw(parser.triangles, gl);
		draw(diams._triangles, gl);
		window.display();
	}
	gl.resetReshap();
	return 0;
}*/


namespace Cube {

    const int NUM_VERTICES = 8;
    const int NUM_FACES = 6;

    GLint vertices[NUM_VERTICES][3] = {
            {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
            {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

    GLint faces[NUM_FACES][4] = {
            {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
            {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

    GLfloat vertexColors[NUM_VERTICES][3] = {
            {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
            {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

    void draw() {
        //GLfloat tete[9];
        /*std::cout << triangles[0].vertices[0].x << " ";
        std::cout << triangles[0].vertices[1].x << " ";
        std::cout << triangles[0].vertices[2].x << std::endl;
        std::vector<GLfloat> verts;
        for (const auto & tri : triangles)
        {
            verts.push_back(tri.vertices[0].x / 100.f);
            verts.push_back(tri.vertices[0].y / 100.f);
            verts.push_back(tri.vertices[0].z / 100.f);

            verts.push_back(tri.vertices[1].x / 100.f);
            verts.push_back(tri.vertices[1].y / 100.f);
            verts.push_back(tri.vertices[1].z / 100.f);

            verts.push_back(tri.vertices[2].x / 100.f);
            verts.push_back(tri.vertices[2].y / 100.f);
            verts.push_back(tri.vertices[2].z / 100.f);
        }
        verts.push_back(0.0);
        verts.push_back(0.0);
        verts.push_back(0.0);

        verts.push_back(0.0);
        verts.push_back(1.0);
        verts.push_back(0.0);

        verts.push_back(0.0);
        verts.push_back(0.0);
        verts.push_back(1.0);
            static const GLfloat tete[] = {
                    0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f,  0.0f, 1.0f,
            };
        GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts.size(), verts.data(), GL_STATIC_DRAW);

        //glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);*/



        struct MyVertex
        {
            float x, y, z;        // Vertex
            float nx, ny, nz;     // Normal
            float s0, t0;         // Texcoord0
        };

        MyVertex pvertex[3];
        // VERTEX 0
        pvertex[0].x = 0.0;
        pvertex[0].y = 0.0;
        pvertex[0].z = 0.0;
        pvertex[0].nx = 0.0;
        pvertex[0].ny = 0.0;
        pvertex[0].nz = 1.0;
        pvertex[0].s0 = 0.0;
        pvertex[0].t0 = 0.0;
        // VERTEX 1
        pvertex[1].x = 1.0;
        pvertex[1].y = 0.0;
        pvertex[1].z = 0.0;
        pvertex[1].nx = 0.0;
        pvertex[1].ny = 0.0;
        pvertex[1].nz = 1.0;
        pvertex[1].s0 = 1.0;
        pvertex[1].t0 = 0.0;
        // VERTEX 2
        pvertex[2].x = 0.0;
        pvertex[2].y = 1.0;
        pvertex[2].z = 0.0;
        pvertex[2].nx = 0.0;
        pvertex[2].ny = 0.0;
        pvertex[2].nz = 1.0;
        pvertex[2].s0 = 0.0;
        pvertex[2].t0 = 1.0;
        GLuint VertexVBOID;
        GLuint IndexVBOID;

        glGenBuffers(1, &VertexVBOID);
        glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex)*3, &pvertex[0].x, GL_STATIC_DRAW);

        ushort pindices[3];
        pindices[0] = 0;
        pindices[1] = 1;
        pindices[2] = 2;

        glGenBuffers(1, &IndexVBOID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort)*3, pindices, GL_STATIC_DRAW);

        // Define this somewhere in your header file

        glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
        glEnableVertexAttribArray(0);    // We like submitting vertices on stream 0 for no special reason
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(0));      // The starting point of the VBO, for the vertices
        glEnableVertexAttribArray(1);    // We like submitting normals on stream 1 for no special reason
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(12));     // The starting point of normals, 12 bytes away
        glEnableVertexAttribArray(2);    // We like submitting texcoords on stream 2 for no special reason
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(24));     // The starting point of texcoords, 24 bytes away

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
        // To render, we can either use glDrawElements or glDrawRangeElements
        // The is the number of indices. 3 indices needed to make a single triangle
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
        /*glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );*/
// Draw the triangle !
        //glDrawArrays(GL_TRIANGLES, 0, verts.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
        //glDisableVertexAttribArray(0);

        //glBegin(GL_TRIANGLES);
        /*glColor3f(0.25f, 0.25f, 0.25f);
        glVertex3f(0,0,0);
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex3f(0,1,0);
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex3f(0,0,1);
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex3f(0,1,1);
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex3f(1,0,0);
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex3f(1,0,1);*/

        //glNormal3f(triangles[k].normal.x, triangles[k].normal.y, triangles[k].normal.z);
        /*glNormal3f(0, 1, 0);
        glVertexPointer(3, GL_FLOAT, 0, tete);
        glDrawArrays(GL_TRIANGLES, 0, 3);*/
        /*for (size_t k = 0; k < triangles.size(); k++)
        {
            tete[0] = triangles[k].vertices[0].x;
            tete[1] = triangles[k].vertices[0].y;
            tete[2] = triangles[k].vertices[0].z;

            tete[3] = triangles[k].vertices[1].x;
            tete[4] = triangles[k].vertices[1].y;
            tete[5] = triangles[k].vertices[1].z;

            tete[6] = triangles[k].vertices[2].x;
            tete[7] = triangles[k].vertices[2].y;
            tete[8] = triangles[k].vertices[2].z;

            //glNormal3f(triangles[k].normal.x, triangles[k].normal.y, triangles[k].normal.z);
            glColor3f(0.25f, 0.25f, 0.25f);
            glVertex3f(triangles[k].vertices[0].x, triangles[k].vertices[0].y, triangles[k].vertices[0].z);
            glColor3f(0.25f, 0.25f, 0.25f);
            glVertex3f(triangles[k].vertices[1].x, triangles[k].vertices[1].y, triangles[k].vertices[1].z);
            glColor3f(0.25f, 0.25f, 0.25f);
            glVertex3f(triangles[k].vertices[2].x, triangles[k].vertices[2].y, triangles[k].vertices[2].z);
            //glVertexPointer(3, GL_FLOAT, 0, tete);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
        }*/
        //glEnd();
    }
}

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Cube::draw();
    glFlush();
    glutSwapBuffers();
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v) {
    static GLfloat u = 0.0;
    u += 0.01;
    glLoadIdentity();
    gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
    glutPostRedisplay();
    glutTimerFunc(1000/60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
    Diamond diams(0.75f, 65);
    diams.fillMap();
    diams.updateVertices(5, 250);
    diams.updateTriangles();
    triangles = diams._triangles;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("The RGB Color Cube");
    GLenum err = glewInit();
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}