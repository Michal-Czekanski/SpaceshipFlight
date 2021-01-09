#include "../headers/Star.h"

Star::Star(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, 
	obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace, glm::vec3 scale): 
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale)
{

}
