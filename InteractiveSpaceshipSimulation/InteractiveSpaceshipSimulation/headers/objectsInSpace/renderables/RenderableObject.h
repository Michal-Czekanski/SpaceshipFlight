#pragma once

#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "objectsInSpace/ObjectInSpace.h"
#include "utils/Time.h"
#include  "data/RenderData.h"
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

	glm::vec3 color = glm::vec3();

	/// <summary>
	/// Program used to draw this renderable object.
	/// </summary>
	GLuint programDraw;

	GLuint texture;
	GLuint textureNormals;

	const RenderData renderData;
public:

	RenderableObject(glm::vec3 position, const RenderData& renderData, glm::vec3 scale, GLuint programDraw,
		GLuint texture, GLuint textureNormals=0);

	glm::mat4 getModelMatrix();

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

};

