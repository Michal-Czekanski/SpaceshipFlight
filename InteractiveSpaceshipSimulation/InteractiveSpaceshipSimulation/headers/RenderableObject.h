#pragma once

#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "ObjectInSpace.h"
#include "Time.h"
#include "data/ModelData.h"
#include "data/ShipLight.h"
#include "data/StarLight.h"
#include "utils/Render_Utils.h"
#include "graphics_techniques/DiscreteLOD.h"
#include "utils/Texture.h"



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
	Core::RenderContext renderContext;

	glm::vec3 color = glm::vec3();

	/// <summary>
	/// Program used to draw this renderable object.
	/// </summary>
	GLuint programDraw;

	obj::Model simplifiedModel;
	Core::RenderContext simplifiedRenderContext;
	GLuint texture;

public:

	RenderableObject(glm::vec3 position, ModelData &modelData,
		glm::vec3 scale, GLuint programDraw);

	glm::mat4 getModelMatrix();

	obj::Model getModel();

	/// <summary>
	/// Update is called on every frame.
	/// </summary>
	virtual void update();

	glm::vec3 getScale();

	void rotate(glm::quat rotation);

	virtual void draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos,
		std::vector<StarLight*> &starsLights);

	glm::vec3 getColor();
	void setColor(glm::vec3 color);

	Core::RenderContext getRenderContext();
	Core::RenderContext getSimplifiedRenderContext();

	void setTexture(GLuint texture);
};

