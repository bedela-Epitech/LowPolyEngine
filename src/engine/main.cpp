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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
//#include "encapsulation/L_OpenGL.hpp"
#include <iostream>
#include <vector>
#include "Triangle.hpp"
//#include "engine/ObjParser.hpp"
//#include "Light.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
}

std::vector<game::Triangle<float>> triangles;
void Draw()
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

#define GLSL(src) "#version 130\n" #src

// Vertex shader
const char* ff = GLSL(
                                      precision highp float;
                                      in  vec3 ex_Color;
                                      out vec4 out_Color;
                                      void main(void)
                                      {
                                          out_Color = vec4(ex_Color,1.0);
                                      }
                              );

// Fragment shader
const char* vv = GLSL(

                         attribute vec3 vPos;
                         uniform mat4 MVP;
                         in  vec3 in_Color;
                         out  vec3 ex_Color;
                         void main()
                         {
                             ex_Color = in_Color;
                             gl_Position = MVP * vec4(vPos, 1);
                         }
                 );


/*#ifdef __APPLE__
#define SHADING_LANG_VERS "140"
#else
#define SHADING_LANG_VERS "130"
#endif
// load shaders
const char *vv = "#version "SHADING_LANG_VERS"\n\
  in  vec3 in_Position;\
  in  vec3 in_Color;\
  out vec3 ex_Color;\
  void main(void)\
  {\
    ex_Color = in_Color;\
    gl_Position = vec4(in_Position, 1.0);\
  }";

const char *ff = "#version "SHADING_LANG_VERS"\n\
  precision highp float;\
  in  vec3 ex_Color;\
  out vec4 out_Color;\
  void main(void)\
  {\
    out_Color = vec4(ex_Color,1.0);\
  }";*/


const char *vertexShaderSource ="#version 330 core\n"
                                "layout (location = 2) in vec3 vertexColor;\n"
                                "out vec3 fragmentColor;"
                                "void main()\n"
                                "{\n"
                                "   fragmentColor = vertexColor;\n"
                                "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 fragmentColor;\n"
                                   "out vec3 color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   color = fragmentColor;\n"
                                   "}\n\0";

GLuint colorbuffer;
GLuint shaderProgram;
GLuint vertexbuffer;
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
        std::vector<GLfloat> verts;
        /*for (const auto & tri : triangles)
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
        }*/
        verts.push_back(0.0);
        verts.push_back(0.0);
        verts.push_back(0.0);

        verts.push_back(0.0);
        verts.push_back(1.0);
        verts.push_back(0.0);

        verts.push_back(0.0);
        verts.push_back(0.0);
        verts.push_back(1.0);
        GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts.size(), verts.data(), GL_STATIC_DRAW);




        //glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

// The following commands will talk about our 'vertexbuffer' buffer

        //glUseProgram(shaderProgram);

        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Draw the triangle !
        glDrawArrays( GL_TRIANGLES, 0, 12 * 3 );
        glDisableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glDisableVertexAttribArray(2);


        //glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
        //glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

    }
}

float angle = 20.f;
float translation = 0.1f;
GLfloat vertices[] = {	-1.0f,0.0f,0.9f,
                          0.0f,1.0f,0.9f,
                          0.0f,0.0f,0.9f };
GLfloat colours[] = {	1.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 1.0f };
GLfloat vertices2[] = {	0.0f,0.0f,0.0f,
                           0.0f,-1.0f,0.0f,
                           1.0f,0.0f,0.0f };

GLuint p, f, v;
// two vertex array objects, one for each object drawn
unsigned int vertexArrayObjID[2];
// three vertex buffer objects in this example
unsigned int vertexBufferObjID[3];

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().

void printShaderInfoLog(GLint shader)
{
    int infoLogLen = 0;
    GLchar *infoLog;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0)
    {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        glGetShaderInfoLog(shader,infoLogLen, NULL, infoLog);
        fprintf(stderr, "InfoLog:\n%s\n", infoLog);
        delete [] infoLog;
    }
}
void initShaders(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v, 1, &vv,NULL);
    glShaderSource(f, 1, &ff,NULL);

    GLint compiled;

    glCompileShader(v);
    glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        fprintf(stderr, "Vertex shader not compiled.\n");
        printShaderInfoLog(v);
    }

    glCompileShader(f);
    glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        fprintf(stderr, "Fragment shader not compiled.\n");
        printShaderInfoLog(f);
    }

    p = glCreateProgram();

    glAttachShader(p,v);
    glAttachShader(p,f);
    glBindAttribLocation(p,0, "vPos");
    glBindAttribLocation(p,1, "in_Color");
    glBindAttribLocation(p, 2, "MVP");

    glLinkProgram(p);
    glGetProgramiv(p, GL_LINK_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLchar *infoLog; GLint length;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &length);
        infoLog = new GLchar[length];
        glGetProgramInfoLog(p, length, NULL, infoLog);
        fprintf(stderr, "Link log=%s\n", infoLog);
        delete[] infoLog;
    }
    glUseProgram(p);

}

void display() {
    //glClear(GL_COLOR_BUFFER_BIT);
    //Cube::draw();
    // clear the screen
    //glViewport( 0, 0, 500.f, 500.f ) ;

    auto projection = glm::perspective(glm::radians(60.0f), 500.f / 500.f, 0.5f, 400.f);
    //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, translation));
    auto view = glm::lookAt(glm::vec3(0.f, 0.f, -3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -translation));
    //std::cout << translation << std::endl;
    glm::mat4 MVP = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(p, "MVP"), 1, 0, &model[0][0]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vertexArrayObjID[0]);	// First VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);	// draw first object

    glBindVertexArray(vertexArrayObjID[1]);		// select second VAO
    glVertexAttrib3f((GLuint)1, 1.0, 0.0, 0.0); // set constant color attribute

    //model = glm::translate(model, glm::vec3(0.1,0.1, 0.1));







    glDrawArrays(GL_TRIANGLES, 0, 3);	// draw second object

    //gluLookAt(0.f, 0.f, -3.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
    //glFlush();
    glutSwapBuffers();
    angle += 1.f;
    translation += 1.f;
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v) {
    static GLfloat u = 0.0;
    u += 0.01;
    //gluLookAt(0.f, 0.f, -3.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
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
/*void init() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}*/



void init(void)
{
    // Would load objects from file here - but using globals in this example

    // Allocate Vertex Array Objects
    glGenVertexArrays(2, &vertexArrayObjID[0]);
    // Setup first Vertex Array Object
    glBindVertexArray(vertexArrayObjID[0]);
    glGenBuffers(2, vertexBufferObjID);

    // VBO for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[0]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // VBO for colour data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[1]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), colours, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // Setup second Vertex Array Object
    glBindVertexArray(vertexArrayObjID[1]);
    glGenBuffers(1, &vertexBufferObjID[2]);

    // VBO for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[2]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


// The usual main for a GLUT application.
/*int main(int argc, char** argv) {
    Diamond diams(0.75f, 65);
    diams.fillMap();
    diams.updateVertices(5, 250);
    diams.updateTriangles();
    //triangles = diams._triangles;


    glutInit(&argc, argv);



    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("The RGB Color Cube");
    GLenum err = glewInit();




    //glutReshapeFunc(reshape);

    glutTimerFunc(100, timer, 0);*/



    /*static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };
// Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
// Draw the triangle !
    glDrawArrays( GL_TRIANGLES, 0, 12 * 3 );

   static const GLfloat g_color_buffer_data[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };
    glGenBuffers(2, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    std::cout << "hello" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    std::cout << "hello" << std::endl;
    glVertexAttribPointer(
            2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );*/






    /*initShaders();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}*/

/*GLfloat vertices[] = {	-1.0f,0.0f,0.0f,
                          0.0f,1.0f,0.0f,
                          0.0f,0.0f,0.0f };
GLfloat colours[] = {	1.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 1.0f };
GLfloat vertices2[] = {	0.0f,0.0f,0.0f,
                           0.0f,-1.0f,0.0f,
                           1.0f,0.0f,0.0f };

// two vertex array objects, one for each object drawn
unsigned int vertexArrayObjID[2];
// three vertex buffer objects in this example
unsigned int vertexBufferObjID[3];


void printShaderInfoLog(GLint shader)
{
    int infoLogLen = 0;
    GLchar *infoLog;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0)
    {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        glGetShaderInfoLog(shader,infoLogLen, NULL, infoLog);
        fprintf(stderr, "InfoLog:\n%s\n", infoLog);
        delete [] infoLog;
    }
}


void init(void)
{
    // Would load objects from file here - but using globals in this example

    // Allocate Vertex Array Objects
    glGenVertexArrays(2, &vertexArrayObjID[0]);
    // Setup first Vertex Array Object
    glBindVertexArray(vertexArrayObjID[0]);
    glGenBuffers(2, vertexBufferObjID);

    // VBO for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[0]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // VBO for colour data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[1]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), colours, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // Setup second Vertex Array Object
    glBindVertexArray(vertexArrayObjID[1]);
    glGenBuffers(1, &vertexBufferObjID[2]);

    // VBO for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[2]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void initShaders(void)
{
    GLuint p, f, v;
    glClearColor (1.0, 1.0, 1.0, 0.0);

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

#ifdef __APPLE__
#define SHADING_LANG_VERS "140"
#else
#define SHADING_LANG_VERS "130"
#endif
    // load shaders
    const char *vv = "#version "SHADING_LANG_VERS"\n\
  in  vec3 in_Position;\
  in  vec3 in_Color;\
  out vec3 ex_Color;\
  void main(void)\
  {\
    ex_Color = in_Color;\
    gl_Position = vec4(in_Position, 1.0);\
  }";

    const char *ff = "#version "SHADING_LANG_VERS"\n\
  precision highp float;\
  in  vec3 ex_Color;\
  out vec4 out_Color;\
  void main(void)\
  {\
    out_Color = vec4(ex_Color,1.0);\
  }";

    glShaderSource(v, 1, &vv,NULL);
    glShaderSource(f, 1, &ff,NULL);

    GLint compiled;

    glCompileShader(v);
    glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        fprintf(stderr, "Vertex shader not compiled.\n");
        printShaderInfoLog(v);
    }

    glCompileShader(f);
    glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        fprintf(stderr, "Fragment shader not compiled.\n");
        printShaderInfoLog(f);
    }

    p = glCreateProgram();

    glAttachShader(p,v);
    glAttachShader(p,f);
    glBindAttribLocation(p,0, "in_Position");
    glBindAttribLocation(p,1, "in_Color");

    glLinkProgram(p);
    glGetProgramiv(p, GL_LINK_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLchar *infoLog; GLint length;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &length);
        infoLog = new GLchar[length];
        glGetProgramInfoLog(p, length, NULL, infoLog);
        fprintf(stderr, "Link log=%s\n", infoLog);
        delete[] infoLog;
    }
    glUseProgram(p);
}


void display(void)
{
    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vertexArrayObjID[0]);	// First VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);	// draw first object

    glBindVertexArray(vertexArrayObjID[1]);		// select second VAO
    glVertexAttrib3f((GLuint)1, 1.0, 0.0, 0.0); // set constant color attribute
    glDrawArrays(GL_TRIANGLES, 0, 3);	// draw second object
}


int main (int argc, char* argv[])
{
    Fl::use_high_res_GL(true);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | FL_OPENGL3);
    glutInitWindowSize(400,400);
    glutCreateWindow("Triangle Test");
#ifndef __APPLE__
    GLenum err = glewInit(); // defines pters to functions of OpenGL V 1.2 and above
    if (err) Fl::error("glewInit() failed returning %u", err);
    fprintf(stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
    int gl_version_major;
    const char *glv = (const char*)glGetString(GL_VERSION);
    fprintf(stderr, "OpenGL version %s supported\n", glv);
    sscanf(glv, "%d", &gl_version_major);
    if (gl_version_major < 3) {
        fprintf(stderr, "\nThis platform does not support OpenGL V3\n\n");
        exit(1);
    }
    initShaders();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}*/



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    initShaders();
    init();

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    auto projection = glm::perspective(glm::radians(60.0f), 500.f / 500.f, 0.5f, 400.f);
    auto view = glm::lookAt(glm::vec3(0.f, 0.f, -3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 model = glm::mat4(1.0f);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, translation));
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, translation));
        //std::cout << translation << std::endl;
        glm::mat4 MVP = projection * view * model;

        glUniformMatrix4fv(glGetUniformLocation(p, "MVP"), 1, 0, &model[0][0]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vertexArrayObjID[0]);	// First VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);	// draw first object

        glBindVertexArray(vertexArrayObjID[1]);		// select second VAO
        glVertexAttrib3f((GLuint)1, 1.0, 0.0, 0.0); // set constant color attribute

        //model = glm::translate(model, glm::vec3(0.1,0.1, 0.1));







        glDrawArrays(GL_TRIANGLES, 0, 3);	// draw second object
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}