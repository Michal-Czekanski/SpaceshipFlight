// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

GLuint programColor;

Core::Shader_Loader shaderLoader;

obj::Model shipModel;

const glm::vec3 initialShipPosition = glm::vec3(0, 0, 0);
/// <summary>
/// Ship position in world space.
/// </summary>
glm::vec3 shipPosition = initialShipPosition;

const glm::vec3 initialShipDirection = glm::vec3(0, 0, 1);
/// <summary>
/// Ship looking direction vector.
/// </summary>
glm::vec3 shipDirection = initialShipDirection;

/// <summary>
/// Ship rotation quaternion.
/// </summary>
glm::quat shipRotation = glm::quat(1, 0, 0, 0);

const glm::vec3 initialShipTop = glm::vec3(0, 1, 0);
/// <summary>
/// Ship top vector.
/// </summary>
glm::vec3 shipTop = initialShipTop;
float shipSpeed = 0.5f;

float shipRotationSpeed = 0.25f;
/// <summary>
/// Ship rotation angle along y-z axis.
/// </summary>
float shipRotationAngleX = 0;

/// <summary>
/// Ship rotation angle along x-z axis.
/// </summary>
float shipRotationAngleY = 0;

/// <summary>
/// Ship rotation angle along x-y plane.
/// </summary>
float shipRotationAngleZ = 0;

glm::vec3 lightDir = glm::normalize(glm::vec3(1, -1, 1));



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

		// test rotation, later should be with mouse
		case 'a':
			shipRotationAngleY = shipRotationSpeed;
			break;
		case 'd':
			shipRotationAngleY = -shipRotationSpeed;
			break;

		// test light dir
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


glm::quat calculateRotationQuat(glm::quat initRotationQuat, float rotationAngleX, float rotationAngleY, float rotationAngleZ)
{
	glm::quat quatX = glm::angleAxis(rotationAngleX, glm::vec3(1, 0, 0));
	glm::quat quatY = glm::angleAxis(rotationAngleY, glm::vec3(0, 1, 0));
	glm::quat quatZ = glm::angleAxis(rotationAngleZ, glm::vec3(0, 0, 1));

	glm::quat rotationChange = quatZ * quatY * quatX;

	return glm::normalize(rotationChange * initRotationQuat);
}

/// <summary>
/// Creates camera matrix. Camera is attached to the ship.
/// </summary>
/// <returns></returns>
glm::mat4 createCameraMatrix(glm::vec3 shipPosition, glm::vec3 shipDirection, glm::vec3 shipTop, glm::vec3 camOffset)
{
	glm::quat initCameraRotation = glm::quat(1, 0, 0, 0); // Camera should look at the ship initial direction at the start.
	initCameraRotation = calculateRotationQuat(initCameraRotation, 0, glm::radians(180.0f), 0);

	glm::vec3 cameraPos = shipPosition - camOffset;
	return Core::createViewMatrixQuat(cameraPos, initCameraRotation * glm::inverse(shipRotation));
}

void idle()
{
	glutPostRedisplay();
}

/// <summary>
/// Calculates camera offset. Camera should be behind ship.
/// </summary>
glm::vec3 calculateCameraOffset(glm::vec3 shipDirection, glm::vec3 shipTop)
{
	glm::vec3 camOffset = shipDirection * 2.0f;
	//camOffset = glm::vec3(0, 0, 0); // DELETE LATER
	camOffset += -shipTop * 0.5f;
	return camOffset;
}



glm::quat calculateShipRotation(glm::quat shipRotation, float &shipRotationAngleX, float &shipRotationAngleY, float &shipRotationAngleZ)
{
	shipRotation = calculateRotationQuat(shipRotation, shipRotationAngleX * shipRotationSpeed, shipRotationAngleY * shipRotationSpeed, shipRotationAngleZ * shipRotationSpeed);

	shipDirection = glm::normalize(shipRotation * glm::vec3(0, 0, 1)); // Ship direction is vector (0, 0, 1) in ship model space
	shipTop = glm::normalize(shipRotation * glm::vec3(0, 1, 0)); // Ship top is vector (0, 1, 0) in ship model space

	shipRotationAngleX = 0; shipRotationAngleY = 0; shipRotationAngleZ = 0; // reset angle inputs

	return shipRotation;
}

/// <summary>
/// Calculates ship model matrix.
/// </summary>
/// <param name="shipPosition">Position of ship in world space.</param>
/// <returns>Ship model matrix.</returns>
glm::mat4 calculateShipModelMatrix(glm::vec3 shipPosition)
{
	glm::mat4 shipModelMatrix;

	shipRotation = calculateShipRotation(shipRotation, shipRotationAngleX, shipRotationAngleY, shipRotationAngleZ);
	glm::mat4 shipRotationMatrix = glm::mat4_cast(shipRotation);

	shipModelMatrix = glm::translate(shipPosition) * shipRotationMatrix * glm::scale(glm::vec3(1));
	return shipModelMatrix;
}

void renderScene() 
{
	glm::mat4 shipModelMatrix = calculateShipModelMatrix(shipPosition);

	glm::vec3 camOffset = calculateCameraOffset(shipDirection, shipTop);
	glm::mat4 cameraMatrix = createCameraMatrix(shipPosition, shipDirection, shipTop, camOffset);
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

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
