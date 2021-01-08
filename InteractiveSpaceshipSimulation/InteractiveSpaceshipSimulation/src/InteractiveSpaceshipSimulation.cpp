// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

Ship* ship;


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': 
			ship->moveForward();
			break;
		case 's': 
			ship->moveBackwards();
			break;

		// test rotation, later should be with mouse
		case 'd': // right
			ship->rotateShip(false, false, true, false, false, false);
			break;
		case 'a': // left
			ship->rotateShip(false, false, false, true, false, false);
			break;
		case 'e': // roll right
			ship->rotateShip(false, false, false, false, true, false);
			break;
		case 'q': // roll left
			ship->rotateShip(false, false, false, false, false, true);
			break;
		case 'k': // pitch up
			ship->rotateShip(true, false, false, false, false, false);
			break; 
		case 'l': // pitch down
			ship->rotateShip(false, true, false, false, false, false);
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

void idle()
{
	glutPostRedisplay();
}

/// <summary>
/// Creates camera matrix. Camera is attached to the ship.
/// </summary>
/// <returns></returns>
glm::mat4 createCameraMatrix(glm::vec3 shipPosition, glm::quat shipRotationQuat, glm::vec3 camOffset)
{
	glm::quat initCameraRotation; // Camera should look at the ship initial direction at the start. Inital camera look direction is (0, 0, -1)
	initCameraRotation = calculateRotationQuat(initCameraRotation, 0, glm::radians(180.0f), 0);

	glm::vec3 cameraPos = shipPosition - camOffset;

	//return Core::createViewMatrixQuat(initialShipPosition - glm::vec3(0, -0.5f, 2), initCameraRotation); // TEST CAM POS WHICH IS FIXED AT (0, 0, 0) LOOKING AT THE INITIAL SHIP DIRECTION
	return Core::createViewMatrixQuat(cameraPos, initCameraRotation * glm::inverse(shipRotationQuat));
}

/// <summary>
/// Calculates camera offset. Camera should be behind ship.
/// </summary>
glm::vec3 calculateCameraOffset(glm::vec3 shipDirection, glm::vec3 shipTop)
{
	glm::vec3 camOffset = shipDirection * 2.0f;
	camOffset -= shipTop * 0.5f;
	return camOffset;
}


void renderScene() 
{
	glm::vec3 camOffset = calculateCameraOffset(ship->getShipDirection(), ship->getShipTop());
	glm::mat4 cameraMatrix = createCameraMatrix(ship->getShipPosition(), ship->getShipRotationQuat(), camOffset);
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	obj::Model shipModel = ship->getModel();
	drawObjectColor(programColor, &shipModel, perspectiveMatrix, cameraMatrix, ship->getModelMatrix(), glm::vec3(0.6f));

	glutSwapBuffers();
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	delete(ship);
}

void init()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram((char*)"shaders/shader_color.vert", (char*)"shaders/shader_color.frag");
	shipModel = obj::loadModelFromFile("models/mock_spaceship.obj");

	ship = new Ship(initialShipPosition, initialShipDirection, initialShipTop, shipSpeed, shipRotationSpeed, shipModel, initialShipRotation, shipTopInModelSpace, shipDirectionInModelSpace);
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
