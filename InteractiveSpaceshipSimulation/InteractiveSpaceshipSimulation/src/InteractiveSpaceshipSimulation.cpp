// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

Ship* ship;
AttachableCamera* camera;
Planet* planet;
Star* star;


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


void renderScene() 
{
	glm::mat4 cameraMatrix = camera->updateCameraMatrix();
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	for (int i = 0; i < renderableObjectsCount; i++)
	{
		RenderableObject* renderableObject = renderableObjects[i];
		renderableObject->update();
		obj::Model model = renderableObject->getModel();
		drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, renderableObject->getModelMatrix(), glm::vec3(0.6f));
	}

	glutSwapBuffers();
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	delete(ship);
	delete(camera);
}

void init()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram((char*)"shaders/shader_color.vert", (char*)"shaders/shader_color.frag");
	
	obj::Model shipModel = obj::loadModelFromFile("models/mock_spaceship.obj");
	obj::Model sphereModel = obj::loadModelFromFile("models/sphere.obj");

	ship = new Ship(initialShipPosition, initialShipDirection, initialShipTop, shipSpeed, shipRotationSpeed, 
		shipModel, initialShipRotation, shipTopInModelSpace, shipDirectionInModelSpace, shipScale);
	camera = new AttachableCamera(camOffsetMultiplier, camUpOffsetMultiplier, (CameraAttachable*)ship);
	planet = new Planet(glm::vec3(0, 0, 5), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(3.0f));
	star = new Star(glm::vec3(50, -10.0f, 125), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(75));

	renderableObjects.push_back((RenderableObject*)ship); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)planet); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)star); renderableObjectsCount++;

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
