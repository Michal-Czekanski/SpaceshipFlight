// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

GLuint programColor;

Core::Shader_Loader shaderLoader;

obj::Model shipModel;
glm::vec3 shipPosition = glm::vec3(0, 0, 0);
glm::vec3 shipDirection = glm::vec3(0, 0, 1);
float shipSpeed = 0.5f;

glm::vec3 lightDir = glm::normalize(glm::vec3(0, 0, -1));



void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': 
			shipPosition += shipDirection * shipSpeed;
			break;
		case 's': 
			shipPosition -= shipDirection * shipSpeed;
			break;
	}
}

void drawObjectColor(GLuint program, obj::Model* model, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::mat4 modelMatrix, glm::vec3 color)
{
	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}

glm::mat4 createCameraMatrix()
{
	return Core::createViewMatrix(glm::vec3(0, 0, 5), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

void idle()
{
	glutPostRedisplay();
}

void renderScene() 
{
	glm::mat4 cameraMatrix = createCameraMatrix();
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	glm::mat4 shipModelMatrix = glm::translate(shipPosition);
	drawObjectColor(programColor, &shipModel, perspectiveMatrix, cameraMatrix, shipModelMatrix, glm::vec3(0.6f));

	glutSwapBuffers();
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);

}

void init()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram((char*)"shaders/shader_color.vert", (char*)"shaders/shader_color.frag");
	shipModel = obj::loadModelFromFile("models/mock_spaceship.obj");


}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Spaceship Simulation");
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
}
