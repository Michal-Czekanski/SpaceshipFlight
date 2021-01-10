// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

Ship* ship = NULL;
AttachableCamera* camera = NULL;
Planet* planet = NULL;
Star* star = NULL;

Planet* helperShipDirectionLine = NULL;
float helperShipDirectionLineLength;
Planet* helperShipLightConeEndPoint = NULL;
Planet* helperShipLightConeRadius = NULL;


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case'\x1b':
			glutLeaveMainLoop();
			break;
		case 'w': 
			ship->moveForward();
			break;
		case 's': 
			ship->moveBackwards();
			break;
		case'b':
			debugHelpersOn = !debugHelpersOn;
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
		drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, renderableObject->getModelMatrix(), glm::vec3(0.6f));
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

	// Render planets
	for (int i = 0; i < planetsCount; i++)
	{
		Planet* planet = planets[i];
		planet->update();
		obj::Model model = planet->getModel();
		drawPlanetColor(programAsteroidColor, planet, &model, perspectiveMatrix, cameraMatrix, glm::vec3(0.3f, 0.0f, 0.0f), stars);
	}

	// Render stars
	for (int i = 0; i < starsCount; i++)
	{
		Star* star= stars[i];
		star->update();
		obj::Model model = star->getModel();
		drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, star->getModelMatrix(), glm::vec3(0.980f, 0.450f, 0.0f));
	}

	if (debugHelpersOn)
	{
		renderDebugHelpers(perspectiveMatrix, cameraMatrix);
	}


	glutSwapBuffers();
}

void renderDebugHelpers(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	helperShipDirectionLine->setPosition(ship->getPosition());
	helperShipDirectionLine->setRottaionQuat(ship->getRotationQuat());
	helperShipDirectionLine->update();
	obj::Model model = helperShipDirectionLine->getModel();
	drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, helperShipDirectionLine->getModelMatrix(), glm::vec3(0, 1, 0));

	helperShipLightConeEndPoint->setPosition(ship->getPosition() + ship->getVectorForward() * helperShipDirectionLineLength);
	helperShipLightConeEndPoint->setRottaionQuat(ship->getRotationQuat());
	helperShipLightConeEndPoint->update();
	drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, helperShipLightConeEndPoint->getModelMatrix(), glm::vec3(0, 1, 0));

	helperShipLightConeRadius->setPosition(helperShipLightConeEndPoint->getPosition() + ship->getLightConeBaseRadius() * ship->getVectorTop());
	helperShipLightConeRadius->update();
	drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, helperShipLightConeRadius->getModelMatrix(), glm::vec3(1, 1, 0));
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
	programAsteroidColor = shaderLoader.CreateProgram((char*)"shaders/shader_planet.vert", (char*)"shaders/shader_planet.frag");

	obj::Model shipModel = obj::loadModelFromFile("models/mock_spaceship.obj");
	obj::Model sphereModel = obj::loadModelFromFile("models/sphere.obj");
	obj::Model asteroidModel1 = obj::loadModelFromFile("models/asteroid1.obj");

	initScene(shipModel, sphereModel, asteroidModel1, ship, camera, renderableObjects, renderableObjectsCount, asteroidFields, planets, planetsCount, stars, starsCount);

	initDebugHelpers(sphereModel);

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

	glm::mat4 modelMatrix = asteroid->getModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(asteroidProgram, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	glm::mat4 modelViewProjectionMatrix = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(asteroidProgram, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&modelViewProjectionMatrix);


	glm::vec3 shipPosition = ship->getPosition();
	glUniform3f(glGetUniformLocation(asteroidProgram, "shipPos"), shipPosition.x, shipPosition.y, shipPosition.z);
	glm::vec3 shipDirection = ship->getVectorForward();
	glUniform3f(glGetUniformLocation(asteroidProgram, "shipDirection"), shipDirection.x, shipDirection.y, shipDirection.z);
	glUniform1f(glGetUniformLocation(asteroidProgram, "shipLightConeHeight"), ship->getLightConeHeight());
	glUniform1f(glGetUniformLocation(asteroidProgram, "shipLightConeRadius"), ship->getLightConeBaseRadius());
	glUniform3f(glGetUniformLocation(asteroidProgram, "shipLightColor"), ship->getLightColor().x, ship->getLightColor().y, ship->getLightColor().z);
	glUniform3f(glGetUniformLocation(asteroidProgram, "objectColor"), color.x, color.y, color.z);

	glm::vec3 camPos = camera->getCamPos();
	glUniform3f(glGetUniformLocation(asteroidProgram, "cameraPos"), camPos.x, camPos.y, camPos.z);

	Core::DrawModel(asteroidModel);

	glUseProgram(0);
}

void drawPlanetColor(GLuint programPlanet, Planet* planet, obj::Model* planetModel, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::vec3 color,
	std::vector<Star*> &stars)
{
	glUseProgram(programPlanet);

	glm::mat4 modelMatrix = planet->getModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(programPlanet, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	glm::mat4 modelViewProjectionMatrix = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(programPlanet, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&modelViewProjectionMatrix);
	glm::vec3 shipPosition = ship->getPosition();
	glUniform3f(glGetUniformLocation(programPlanet, "shipPos"), shipPosition.x, shipPosition.y, shipPosition.z);
	glm::vec3 shipDirection = ship->getVectorForward();
	glUniform3f(glGetUniformLocation(programPlanet, "shipDirection"), shipDirection.x, shipDirection.y, shipDirection.z);
	glUniform1f(glGetUniformLocation(programPlanet, "shipLightConeHeight"), ship->getLightConeHeight());
	glUniform1f(glGetUniformLocation(programPlanet, "shipLightConeRadius"), ship->getLightConeBaseRadius());
	glUniform3f(glGetUniformLocation(programPlanet, "shipLightColor"), ship->getLightColor().x, ship->getLightColor().y, ship->getLightColor().z);
	glUniform3f(glGetUniformLocation(programPlanet, "objectColor"), color.x, color.y, color.z);
	glm::vec3 camPos = camera->getCamPos();
	glUniform3f(glGetUniformLocation(programPlanet, "cameraPos"), camPos.x, camPos.y, camPos.z);

	
	std::vector<glm::vec3> starsPos;
	for (int i = 0; i < stars.size(); i++)
	{
		starsPos.push_back(stars[i]->getPosition());
	}
	glUniform3fv(glGetUniformLocation(programPlanet, "starsPos"), stars.size(), reinterpret_cast<GLfloat*>(starsPos.data()));

	std::vector<float> starsLightStr;
	for (int i = 0; i < stars.size(); i++)
	{
		starsLightStr.push_back(stars[i]->getLightStrength());
	}
	glUniform1fv(glGetUniformLocation(programPlanet, "starsLightStr"), stars.size(), reinterpret_cast<GLfloat*>(starsLightStr.data()));
	
	std::vector<glm::vec3> starsLightCol;
	for (int i = 0; i < stars.size(); i++)
	{
		starsLightCol.push_back(stars[i]->getLightColor());
	}
	glUniform3fv(glGetUniformLocation(programPlanet, "starsLightCol"), stars.size(), reinterpret_cast<GLfloat*>(starsLightCol.data()));

	Core::DrawModel(planetModel);
	glUseProgram(0);
}

void initDebugHelpers(obj::Model sphereModel)
{
	helperShipDirectionLineLength = ship->getLightConeHeight();
	helperShipDirectionLine = new Planet(ship->getPosition(), ship->getRotationQuat(), ship->getVectorForward(), ship->getVectorTop(), sphereModel, glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 1), glm::vec3(0.1f, 0.1f, helperShipDirectionLineLength * 2));

	helperShipLightConeEndPoint = new Planet(ship->getPosition() + ship->getVectorForward() * helperShipDirectionLineLength,
		ship->getRotationQuat(), ship->getVectorForward(), ship->getVectorTop(), sphereModel, glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 1), glm::vec3(1.0f, 1.0f, 1.0f));

	helperShipLightConeRadius = new Planet(helperShipLightConeEndPoint->getPosition() + ship->getLightConeBaseRadius() * ship->getVectorTop(),
		ship->getRotationQuat(), ship->getVectorForward(), ship->getVectorTop(), sphereModel, glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 1), glm::vec3(1.0f, 1.0f, 1.0f));
}
