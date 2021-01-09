#include "../headers/Scene.h"

void initScene(obj::Model& shipModel, obj::Model& sphereModel, Ship* &ship, AttachableCamera* &camera, std::vector<RenderableObject*> &renderableObjects,
	int &renderableObjectsCount)
{
	ship = new Ship(initialShipPosition, initialShipDirection, initialShipTop, shipSpeed, shipRotationSpeed,
		shipModel, initialShipRotation, shipTopInModelSpace, shipDirectionInModelSpace, shipScale);
	camera = new AttachableCamera(camOffsetMultiplier, camUpOffsetMultiplier, (ObjectInSpace*)ship);
	Planet* planet = new Planet(glm::vec3(0, 0, 5), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(3.0f));
	Star* star = new Star(glm::vec3(50, -10.0f, 125), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(75));

	Planet* planet2 = new Planet(glm::vec3(0, 0, 15), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(3.0f),
		star, glm::vec3(0, -3, 2), 0.001f);

	Moon* moon = new Moon(glm::vec3(0, 0, -5), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(0.75f), planet, glm::vec3(1, 1, 12), 0.001f);

	renderableObjects.push_back((RenderableObject*)ship); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)planet); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)star); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)planet2); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)moon); renderableObjectsCount++;

}
