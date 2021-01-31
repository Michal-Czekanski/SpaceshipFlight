// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"

#include <cmath>


using namespace std;



Ship* ship = NULL;
AttachableCamera* camera = NULL;

GLuint skyboxVAO, skyboxVBO;
unsigned int cubemapTexture;

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


		case 'e':
			bloom->setExposure(bloom->getExposure() + 0.01f);
			std::cout << "Exposure: " << bloom->getExposure() << std::endl;
			break;
		case 'r':
			bloom->setExposure(bloom->getExposure() - 0.01f);
			std::cout << "Exposure: " << bloom->getExposure() << std::endl;
			break;

		case 'y':
			DiscreteLOD::enabled = !DiscreteLOD::enabled;
			std::cout << "Discrete Level Of Detail: " << DiscreteLOD::enabled << std::endl;
			break;



	}
}

void idle()
{
	glutPostRedisplay();
}

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	unsigned long width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		std::ifstream input(faces[i], std::ios::binary);
		std::vector<char> buffer((
			std::istreambuf_iterator<char>(input)),
			(std::istreambuf_iterator<char>()));

		std::vector<unsigned char> decoded;
		decodePNG(decoded, width, height, (unsigned char*)&buffer[0], buffer.size(), true);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &decoded[0]);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

vector<std::string> faces
{
		"textures/skybox/right.png",
		"textures/skybox/left.png",
		"textures/skybox/top.png",
		"textures/skybox/bottom.png",
		"textures/skybox/front.png",
		"textures/skybox/back.png"
};



void skybox(glm::mat4 view, glm::mat4 projection, unsigned int id) {
	glDepthFunc(GL_LEQUAL);
	glUseProgram(programSkybox);
	view = glm::mat4(glm::mat3(view));
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(programSkybox, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}


void renderScene() 
{
	Time::update();
	glm::mat4 cameraMatrix = camera->updateCameraMatrix();
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix(0.1, 7000.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glm::vec3 campos = camera->getCamPos();
	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraDirection = (campos - cameraTarget);
	//glLoadIdentity();
	//gluLookAt(
	//	0, 0, 0,
	//	cameraDirection.x, 0, 0,
	//	0, 1, 0);


	bloom->beforeRendering();

	// Render ship
	rotateShip();
	ship->update();
	obj::Model shipModel = ship->getModel();
	ship->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(), starsLights);


	// Render asteroid fields
	for (int i = 0; i < asteroidFields.size(); i++)
	{
		AsteroidField* asteroidField = asteroidFields[i];
		asteroidField->update();
		asteroidField->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(), starsLights);
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

	skybox(cameraMatrix, perspectiveMatrix, cubemapTexture);

	if (debugHelpersOn)
	{
		renderDebugHelpers(perspectiveMatrix, cameraMatrix);
	}

	bloom->afterRendering();

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
	programSkybox = shaderLoader.CreateProgram((char*)"shaders/skybox.vert", (char*)"shaders/skybox.frag");
	programColor = shaderLoader.CreateProgram((char*)"shaders/shader_color.vert", (char*)"shaders/shader_color.frag");
	programColor2 = shaderLoader.CreateProgram((char*)"shaders/shader_color2.vert", (char*)"shaders/shader_color2.frag");
	programStar = shaderLoader.CreateProgram((char*)"shaders/shader_star.vert", (char*)"shaders/shader_star.frag");
	programInstanceColor = shaderLoader.CreateProgram(
		(char*)"shaders/shader_color_instancing.vert", (char*)"shaders/shader_color_instancing.frag");
	programInstanceTexture = shaderLoader.CreateProgram(
		(char*)"shaders/shader_texture_instancing.vert", (char*)"shaders/shader_texture_instancing.frag");
	programStarTexture = shaderLoader.CreateProgram(
		(char*)"shaders/shader_star_tex.vert", (char*)"shaders/shader_star_tex.frag");
	
	GLuint programBlur = shaderLoader.CreateProgram(
		(char*)"shaders/bloom/shader_gaussian_blur.vert", (char*)"shaders/bloom/shader_gaussian_blur.frag");
	GLuint programBloomFinalBlend = shaderLoader.CreateProgram(
		(char*)"shaders/bloom/shader_bloom_final_blend.vert", (char*)"shaders/bloom/shader_bloom_final_blend.frag");

	obj::Model shipModel = obj::loadModelFromFile("models/spaceship_model.obj");
	ModelData shipModelData = ModelData(shipModel, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	obj::Model sphereModel = obj::loadModelFromFile("models/sphere.obj");
	obj::Model sphereModelSimplified = obj::loadModelFromFile("models/sphere-simpl.obj");
	ModelData sphereModelData = ModelData(sphereModel, sphereModelSimplified,
		glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

	obj::Model asteroid1Model = obj::loadModelFromFile("models/asteroid1.obj");
	obj::Model asteroid1ModelSimplified = obj::loadModelFromFile("models/asteroid1-simpl.obj");
	ModelData asteroid1ModelData = ModelData(asteroid1Model, asteroid1ModelSimplified,
		glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));


	shipTexture = Core::LoadTexture("textures/spaceship/spaceship_model_texture.png");
	shipNormalTexture = Core::LoadTexture("textures/spaceship/spaceship_model_normal.png");

	starTextures[0] = Core::LoadTexture("textures/star1.png");
	starTextures[1] = Core::LoadTexture("textures/star2.png");
	starTextures[2] = Core::LoadTexture("textures/star3.png");
	asteroidTextures.push_back(Core::LoadTexture("textures/asteroid.png"));
	asteroidNormalTextures.push_back(Core::LoadTexture("textures/asteroid_normal.png"));
	asteroidTextures.push_back(Core::LoadTexture("textures/asteroid_texture.png"));
	asteroidNormalTextures.push_back(Core::LoadTexture("textures/asteroid_texture_normal.png"));

	planetTextures.push_back(Core::LoadTexture("textures/planet10_texture.png"));
	planetNormals.push_back(Core::LoadTexture("textures/planet10_texture_normal.png"));


	_skybox[0] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[1] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[2] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[3] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[4] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[5] = Core::LoadTexture("textures/kosmos3.png");

	cubemapTexture = loadCubemap(faces);
	

	initScene(shipModelData, sphereModelData, asteroid1ModelData, ship, camera, renderableObjects,
		renderableObjectsCount, asteroidFields,
		starsLights, programColor2, programStar, programInstanceTexture,
		programStarTexture, starTextures, asteroidTextures, asteroidNormalTextures,
		planetTextures, planetNormals,
		shipTexture, shipNormalTexture);

	initDebugHelpers(sphereModelData);


	bloom = new Bloom(WINDOW_WIDTH, WINDOW_HEIGHT, programBlur, programBloomFinalBlend);

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
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
}

void initDebugHelpers(ModelData &sphereModelData)
{
	ShipLight shipLight = ship->getShipLight();
	helperShipDirectionLineLength = shipLight.getLightConeHeight();
	glm::vec3 lineScale = glm::vec3(0.1f, 0.1f, helperShipDirectionLineLength * 2);

	helperShipDirectionLine = new Planet(ship->getPosition(), sphereModelData, lineScale, programColor, 0, 0);
	helperShipDirectionLine->rotate(ship->getRotationQuat());
	
	glm::vec3 helper2Pos = ship->getPosition() + ship->getVectorForward() * helperShipDirectionLineLength;
	helperShipLightConeEndPoint = new Planet(helper2Pos, sphereModelData, glm::vec3(1, 1, 1), programColor, 0, 0);
	helperShipLightConeEndPoint->rotate(ship->getRotationQuat());

	glm::vec3 helper3Pos = helper2Pos + shipLight.getLightConeBaseRadius() * ship->getVectorTop();
	helperShipLightConeRadius = new Planet(helper3Pos, sphereModelData, glm::vec3(1, 1, 1), programColor, 0, 0);
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






