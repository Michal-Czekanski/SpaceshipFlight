#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "ObjectInSpace.h"
#include "Time.h"
#include "data/ModelData.h"
#include "data/ShipLight.h"
#include "freeglut.h"
#include "data/StarLight.h"


/// <summary>
/// Object that can be drawn on the screen.
/// </summary>
class RenderableObject: public ObjectInSpace 
{
protected:
	glm::mat4 positionMat;

	glm::mat4 rotationMat;

	glm::vec3 scale;
	glm::mat4 scaleMat;

	glm::mat4 modelMatrix;

	obj::Model model;
public:

	RenderableObject(glm::vec3 position, ModelData &modelData,
		glm::vec3 scale);

	glm::mat4 getModelMatrix();

	obj::Model getModel();

	/// <summary>
	/// Update is called on every frame.
	/// </summary>
	virtual void update();

	glm::vec3 getScale();

	void rotate(glm::quat rotation);

	virtual void draw(GLuint program, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::vec3 color,
		ShipLight shipLight, std::vector<StarLight*>& starsLight) {};

};

