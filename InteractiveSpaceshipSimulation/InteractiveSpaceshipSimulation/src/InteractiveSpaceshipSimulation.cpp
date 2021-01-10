// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

std::vector<RenderableObject*> renderableObjects;
int renderableObjectsCount = 0;


Ship* ship = NULL;
AttachableCamera* camera = NULL;
Planet* planet = NULL;
Star* star = NULL;

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
	Time::update();
	glm::mat4 cameraMatrix = camera->updateCameraMatrix();
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix(0.1, 7000.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	// Render renderable objects
	for (int i = 0; i < renderableObjectsCount; i++)
	{
		RenderableObject* renderableObject = renderableObjects[i];
		renderableObject->update();
		obj::Model model = renderableObject->getModel();
		if (typeid(renderableObject) != typeid(Asteroid*))
		{
			drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, renderableObject->getModelMatrix(), glm::vec3(0.6f));
		}
		else 
		{
			drawAsteroidColor(programAsteroidColor, (Asteroid*)renderableObject, &model, perspectiveMatrix, cameraMatrix, glm::vec3(0.3f));
		}
		
	}

	// Render asteroid fields
	for (int i = 0; i < asteroidFields.size(); i++)
	{
		AsteroidField* asteroidField = asteroidFields[i];
		std::vector<Asteroid*> asteroids = asteroidField->getAsteroids();
		for (int j = 0; j < asteroids.size(); j++)
		{
			asteroids[j]->update();
			obj::Model model = asteroids[j]->getModel();
			drawAsteroidColor(programAsteroidColor, asteroids[j], &model, perspectiveMatrix, cameraMatrix, glm::vec3(0.3f));
		}
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
	programAsteroidColor = shaderLoader.CreateProgram((char*)"shaders/shader_asteroid.vert", (char*)"shaders/shader_asteroid.frag");
	
	obj::Model shipModel = obj::loadModelFromFile("models/mock_spaceship.obj");
	obj::Model sphereModel = obj::loadModelFromFile("models/sphere.obj");
	obj::Model asteroidModel1 = obj::loadModelFromFile("models/asteroid1.obj");

	

	initScene(shipModel, sphereModel, asteroidModel1, ship, camera, renderableObjects, renderableObjectsCount, asteroidFields);
	Time::start();
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

void drawAsteroidColor(GLuint asteroidProgram, Asteroid* asteroid, obj::Model* asteroidModel, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::vec3 color)
{
	glUseProgram(asteroidProgram);

	glUniform3f(glGetUniformLocation(asteroidProgram, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(asteroidProgram, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glUniformMatrix4fv(glGetUniformLocation(asteroidProgram, "perspectiveMatrix"), 1, GL_FALSE, (float*)&perspectiveMatrix);
	glUniformMatrix4fv(glGetUniformLocation(asteroidProgram, "cameraMatrix"), 1, GL_FALSE, (float*)&cameraMatrix);
	glm::mat4 modelMatrix = asteroid->getModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(asteroidProgram, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(asteroidModel);

	glUseProgram(0);
}
