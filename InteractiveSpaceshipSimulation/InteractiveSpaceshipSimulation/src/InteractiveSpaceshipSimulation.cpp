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

void printPerformanceMeasures()
{
	std::cout << PerformanceMeasure::getMsPerFrame() << " ms/frame | ";
	std::cout << PerformanceMeasure::getFPS() << " FPS" << std::endl;
}

void rotateShip()
{
	float windowW = glutGet(GLUT_WINDOW_WIDTH);	float windowH = glutGet(GLUT_WINDOW_HEIGHT);
	glm::vec2 windowCenter = glm::vec2(windowW / 2, windowH / 2);
	float pitch = (windowCenter.y - Mouse::y) / (windowH / 2);
	float roll = -(windowCenter.x - Mouse::x) / (windowW / 2);
	ship->rotateShip(pitch, 0.0f, roll);
}
void mouse(int x, int y)
{
	Mouse::x = x;
	Mouse::y = y;
}

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

		case 'd': // right
			ship->rotateShip(0.0f, 1.0f, 0.0f);
			break;
		case 'a': // left
			ship->rotateShip(0.0f, -1.0f, 0.0f);
			break;
	}
}

void drawObjectColor(GLuint program, obj::Model* model, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::mat4 modelMatrix, glm::vec3 color)
{
	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), testLightDir.x, testLightDir.y, testLightDir.z);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Render ship
	rotateShip();
	ship->update();
	obj::Model shipModel = ship->getModel();
	ship->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(), starsLights);

	// Render asteroid fields
	for (int i = 0; i < asteroidFields.size(); i++)
	{
		AsteroidField* asteroidField = asteroidFields[i];
		std::vector<Asteroid*> asteroids = asteroidField->getAsteroids();
		for (int j = 0; j < asteroids.size(); j++)
		{
			asteroids[j]->update();
			asteroids[j]->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(),
				starsLights);
		}
	}

	// Render renderable objects
	for (int i = 0; i < renderableObjectsCount; i++)
	{
		RenderableObject* renderableObject = renderableObjects[i];
		renderableObject->update();
		obj::Model model = renderableObject->getModel();
		renderableObject->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(),
			starsLights);
	}
	
	if (debugHelpersOn)
	{
		renderDebugHelpers(perspectiveMatrix, cameraMatrix);
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
	programColor2 = shaderLoader.CreateProgram((char*)"shaders/shader_color2.vert", (char*)"shaders/shader_color2.frag");
	programStar = shaderLoader.CreateProgram((char*)"shaders/shader_star.vert", (char*)"shaders/shader_star.frag");

	obj::Model shipModel = obj::loadModelFromFile("models/mock_spaceship.obj");
	ModelData shipModelData = ModelData(shipModel, glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

	obj::Model sphereModel = obj::loadModelFromFile("models/sphere.obj");
	obj::Model sphereModelSimplified = obj::loadModelFromFile("models/sphere-simpl.obj");
	ModelData sphereModelData = ModelData(sphereModel, sphereModelSimplified,
		glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

	obj::Model asteroid1Model = obj::loadModelFromFile("models/asteroid1.obj");
	obj::Model asteroid1ModelSimplified = obj::loadModelFromFile("models/asteroid1-simpl.obj");
	ModelData asteroid1ModelData = ModelData(asteroid1Model, asteroid1ModelSimplified,
		glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));



	initScene(shipModelData, sphereModelData, asteroid1ModelData, ship, camera, renderableObjects,
		renderableObjectsCount, asteroidFields, planets, planetsCount, stars, starsCount,
		moons, moonsCount, starsLights, programColor2, programStar);

	initDebugHelpers(sphereModelData);

	Time::start();
	PerformanceMeasure::addMeasuresTakenListener(printPerformanceMeasures);
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
	glutPassiveMotionFunc(mouse);
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
	ShipLight shipLight = ship->getShipLight();
	glUniform1f(glGetUniformLocation(asteroidProgram, "shipLightConeHeight"), shipLight.getLightConeHeight());
	glUniform1f(glGetUniformLocation(asteroidProgram, "shipLightConeRadius"), shipLight.getLightConeBaseRadius());
	glUniform3f(glGetUniformLocation(asteroidProgram, "shipLightColor"), 
		shipLight.getLightColor().x, shipLight.getLightColor().y, shipLight.getLightColor().z);
	glUniform3f(glGetUniformLocation(asteroidProgram, "objectColor"), color.x, color.y, color.z);

	glm::vec3 camPos = camera->getCamPos();
	glUniform3f(glGetUniformLocation(asteroidProgram, "cameraPos"), camPos.x, camPos.y, camPos.z);

	Core::DrawModel(asteroidModel);

	glUseProgram(0);
}

void drawObjectColor(GLuint program, RenderableObject* object, obj::Model* model, glm::mat4 perspectiveMatrix, 
	glm::mat4 cameraMatrix, glm::vec3 color, std::vector<Star*>& stars)
{
	glUseProgram(program);

	glm::mat4 modelMatrix = object->getModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	glm::mat4 modelViewProjectionMatrix = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&modelViewProjectionMatrix);
	glm::vec3 shipPosition = ship->getPosition();
	glUniform3f(glGetUniformLocation(program, "shipPos"), shipPosition.x, shipPosition.y, shipPosition.z);
	glm::vec3 shipDirection = ship->getVectorForward();
	glUniform3f(glGetUniformLocation(program, "shipDirection"), shipDirection.x, shipDirection.y, shipDirection.z);
	ShipLight shipLight = ship->getShipLight();
	glUniform1f(glGetUniformLocation(program, "shipLightConeHeight"), shipLight.getLightConeHeight());
	glUniform1f(glGetUniformLocation(program, "shipLightConeRadius"), shipLight.getLightConeBaseRadius());
	glUniform3f(glGetUniformLocation(program, "shipLightColor"),
		shipLight.getLightColor().x, shipLight.getLightColor().y, shipLight.getLightColor().z);
	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glm::vec3 camPos = camera->getCamPos();
	glUniform3f(glGetUniformLocation(program, "cameraPos"), camPos.x, camPos.y, camPos.z);


	std::vector<glm::vec3> starsPos;
	for (int i = 0; i < stars.size(); i++)
	{
		starsPos.push_back(stars[i]->getPosition());
	}
	glUniform3fv(glGetUniformLocation(program, "starsPos"), stars.size(), reinterpret_cast<GLfloat*>(starsPos.data()));

	std::vector<float> starsLightStr;
	for (int i = 0; i < stars.size(); i++)
	{
		starsLightStr.push_back(stars[i]->getLight()->getStrength());
	}
	glUniform1fv(glGetUniformLocation(program, "starsLightStr"), stars.size(), reinterpret_cast<GLfloat*>(starsLightStr.data()));

	std::vector<glm::vec3> starsLightCol;
	for (int i = 0; i < stars.size(); i++)
	{
		starsLightCol.push_back(stars[i]->getLight()->getColor());
	}
	glUniform3fv(glGetUniformLocation(program, "starsLightCol"), stars.size(), reinterpret_cast<GLfloat*>(starsLightCol.data()));

	Core::DrawModel(model);
	glUseProgram(0);
}


void drawStarColor(GLuint program, Star* star, obj::Model* model, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::vec3 color)
{
	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glm::vec3 starPos = star->getPosition();
	glUniform3f(glGetUniformLocation(program, "starPos"), starPos.x, starPos.y, starPos.z);

	glm::mat4 modelMatrix = star->getModelMatrix();
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}

void initDebugHelpers(ModelData &sphereModelData)
{
	ShipLight shipLight = ship->getShipLight();
	helperShipDirectionLineLength = shipLight.getLightConeHeight();
	glm::vec3 lineScale = glm::vec3(0.1f, 0.1f, helperShipDirectionLineLength * 2);

	helperShipDirectionLine = new Planet(ship->getPosition(), sphereModelData, lineScale, programColor);
	helperShipDirectionLine->rotate(ship->getRotationQuat());
	
	glm::vec3 helper2Pos = ship->getPosition() + ship->getVectorForward() * helperShipDirectionLineLength;
	helperShipLightConeEndPoint = new Planet(helper2Pos, sphereModelData, glm::vec3(1, 1, 1), programColor);
	helperShipLightConeEndPoint->rotate(ship->getRotationQuat());

	glm::vec3 helper3Pos = helper2Pos + shipLight.getLightConeBaseRadius() * ship->getVectorTop();
	helperShipLightConeRadius = new Planet(helper3Pos, sphereModelData, glm::vec3(1, 1, 1), programColor);
	helperShipLightConeRadius->rotate(ship->getRotationQuat());
}

void renderDebugHelpers(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix)
{
	helperShipDirectionLine->setPosition(ship->getPosition());
	helperShipDirectionLine->rotate(ship->getRotationQuat());
	helperShipDirectionLine->update();
	obj::Model model = helperShipDirectionLine->getModel();
	drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, helperShipDirectionLine->getModelMatrix(), glm::vec3(0, 1, 0));

	helperShipLightConeEndPoint->setPosition(ship->getPosition() + ship->getVectorForward() * helperShipDirectionLineLength);
	helperShipLightConeEndPoint->rotate(ship->getRotationQuat());
	helperShipLightConeEndPoint->update();
	drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, helperShipLightConeEndPoint->getModelMatrix(), glm::vec3(0, 1, 0));

	helperShipLightConeRadius->setPosition(helperShipLightConeEndPoint->getPosition()
		+ ship->getShipLight().getLightConeBaseRadius() * ship->getVectorTop());
	helperShipLightConeRadius->update();
	drawObjectColor(programColor, &model, perspectiveMatrix, cameraMatrix, helperShipLightConeRadius->getModelMatrix(), glm::vec3(1, 1, 0));
}
