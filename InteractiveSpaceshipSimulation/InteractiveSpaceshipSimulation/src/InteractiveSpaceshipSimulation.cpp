// InteractiveSpaceshipSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../headers/InteractiveSpaceshipSimulation.h"
#include "graphics_techniques/particles/ParticleGenerator.h"

#include <cmath>

float frustumScale = 1.1f;

using namespace std;



Ship* ship = NULL;
AttachableCamera* camera = NULL;

GLuint skyboxVAO, skyboxVBO;
unsigned int cubemapTexture;

Planet* helperShipDirectionLine = NULL;
float helperShipDirectionLineLength;
Planet* helperShipLightConeEndPoint = NULL;
Planet* helperShipLightConeRadius = NULL;

ParticleGenerator* smoke;

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

		case 'd': // right
			ship->rotateShip(0.0f, 1.0f, 0.0f);
			break;
		case 'a': // left
			ship->rotateShip(0.0f, -1.0f, 0.0f);
			break;

		case 'f':
			ship->slowDown();
			break;


		case 'u':
			camera->camOffsetMultiplier += 0.1f;
			break;
		case 'j':
			camera->camOffsetMultiplier -= 0.1f;
			break;

		case 'i':
			camera->upOffsetMultiplier += 0.1f;
			break;
		case 'k':
			camera->upOffsetMultiplier -= 0.1f;
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

	Physics::getInstance()->update(Time::getDeltaTimeSec());
	Game::updateNormalScene();
	glm::mat4 cameraMatrix = camera->updateCameraMatrix();
	glm::mat4 perspectiveMatrix = Core::createPerspectiveMatrix(0.1, 7000.0f, frustumScale);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	bloom->beforeRendering();

	// Render ship
	rotateShip();
	ship->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(), starsLights);


	// Render asteroid fields
	for (int i = 0; i < asteroidFields.size(); i++)
	{
		AsteroidField* asteroidField = asteroidFields[i];
		asteroidField->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(), starsLights);
	}

	// Render renderable objects
	for (int i = 0; i < renderableObjectsCount; i++)
	{
		RenderableObject* renderableObject = renderableObjects[i];
		renderableObject->draw(perspectiveMatrix, cameraMatrix, ship->getShipLight(), camera->getCamPos(),
			starsLights);
	}



	skybox(cameraMatrix, perspectiveMatrix, cubemapTexture);

	smoke->draw(ship->getPosition() + ship->getVectorForward(), ship->getRotationQuat(), *camera, perspectiveMatrix);

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
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	programSkybox = shaderLoader.CreateProgram((char*)"shaders/skybox.vert", (char*)"shaders/skybox.frag");
	programColor = shaderLoader.CreateProgram((char*)"shaders/shader_color.vert", (char*)"shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram((char*)"shaders/shader_texture.vert", (char*)"shaders/shader_texture.frag");
	programStar = shaderLoader.CreateProgram((char*)"shaders/shader_star.vert", (char*)"shaders/shader_star.frag");
	programInstanceColor = shaderLoader.CreateProgram(
		(char*)"shaders/shader_color_instancing.vert", (char*)"shaders/shader_color_instancing.frag");
	programInstanceTexture = shaderLoader.CreateProgram(
		(char*)"shaders/shader_texture_instancing.vert", (char*)"shaders/shader_texture_instancing.frag");
	programStarTexture = shaderLoader.CreateProgram(
		(char*)"shaders/shader_star_tex.vert", (char*)"shaders/shader_star_tex.frag");
	
	GLuint programBlur = shaderLoader.CreateProgram(
		(char*)"shaders/bloom/shader_gaussian_blur.vert", (char*)"shaders/bloom/shader_gaussian_blur.frag");
	Game::programBlur = programBlur;
	GLuint programBloomFinalBlend = shaderLoader.CreateProgram(
		(char*)"shaders/bloom/shader_bloom_final_blend.vert", (char*)"shaders/bloom/shader_bloom_final_blend.frag");
	Game::programBloomFinalBlend = programBloomFinalBlend;

	obj::Model shipModel = obj::loadModelFromFile("models/spaceship_model.obj");
	ModelData shipModelData = ModelData(shipModel, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	const RenderData shipRenderData = RenderData(shipModelData);

	obj::Model sphereModel = obj::loadModelFromFile("models/sphere.obj");
	obj::Model sphereModelSimplified = obj::loadModelFromFile("models/sphere-simpl.obj");
	ModelData sphereModelData = ModelData(sphereModel, sphereModelSimplified,
		glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	const RenderData sphereRenderData = RenderData(sphereModelData);



	obj::Model asteroid1Model = obj::loadModelFromFile("models/asteroid1.obj");
	obj::Model asteroid1ModelSimplified = obj::loadModelFromFile("models/asteroid1-simpl.obj");
	ModelData asteroid1ModelData = ModelData(asteroid1Model, asteroid1ModelSimplified,
		glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	const RenderDataInstancing asteroid1RenderData = RenderDataInstancing(asteroid1ModelData);

	Textures textures = Textures(3, 2, 10, 4);

	_skybox[0] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[1] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[2] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[3] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[4] = Core::LoadTexture("textures/kosmos3.png");
	_skybox[5] = Core::LoadTexture("textures/kosmos3.png");

	cubemapTexture = loadCubemap(faces);
	
	initScene(shipRenderData, sphereRenderData, asteroid1RenderData, ship, camera, renderableObjects,
		renderableObjectsCount, asteroidFields,
		starsLights, programTexture, programStar, programInstanceTexture,
		programStarTexture, textures);

	bloom = new Bloom(Game::windowWidth, Game::windowHeight, programBlur, programBloomFinalBlend);


	GLuint programSmoke = shaderLoader.CreateProgram(
		(char*)"shaders/particles/shader_particles.vert", (char*)"shaders/particles/shader_particles.frag");
	smoke = new ParticleGenerator(glm::vec3(-0.05f, 0, 1.0f), ship->getRotationQuat(), glm::vec3(0), 2000, 0.5, programSmoke,
		textures.getSmokeTextureData().getTexture(), 0.1);
	smoke->minParticleSize = 0.03f;
	smoke->maxParticleSize = 0.1f;
	smoke->minParticleSpeed = 0.01f;
	smoke->maxParticleSpeed = 1.0f;
	ship->engineSmokeParticleGenerator = smoke;

	Time::start();
	PerformanceMeasure::addMeasuresTakenListener(printPerformanceMeasures);
}

void windowResizeHandler(int ww, int wh) 
{
	Game::windowWidth = ww;
	Game::windowHeight = wh;
	const float aspectRatio = ((float)ww) / wh;
	frustumScale = aspectRatio;
	float xSpan = 1; // Feel free to change this to any xSpan you need.
	float ySpan = 1; // Feel free to change this to any ySpan you need.

	if (aspectRatio > 1) {
		// Width > Height, so scale xSpan accordinly.
		xSpan *= aspectRatio;
	}
	else {
		// Height >= Width, so scale ySpan accordingly.
		ySpan = xSpan / aspectRatio;
	}
	// Use the entire window for rendering.
	glViewport(0, 0, ww, wh);
	bloom = new Bloom(Game::windowWidth, Game::windowHeight, Game::programBlur, Game::programBloomFinalBlend);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Game::windowWidth, Game::windowHeight);
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
	glutReshapeFunc(windowResizeHandler);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
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






