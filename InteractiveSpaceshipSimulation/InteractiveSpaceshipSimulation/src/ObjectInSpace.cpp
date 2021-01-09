#include "../headers/ObjectInSpace.h"

ObjectInSpace::ObjectInSpace(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop)
{
    this->position = position;
    this->rotationQuat = rotationQuat;
    this->vectorForward = glm::normalize(vectorForward);
    this->vectorTop = glm::normalize(vectorTop);
    this->vectorRight = glm::normalize(glm::cross(vectorForward, vectorTop));
}

glm::vec3 ObjectInSpace::getPosition()
{
    return this->position;
}

glm::quat ObjectInSpace::getRotationQuat()
{
    return this->rotationQuat;
}

glm::vec3 ObjectInSpace::getVectorForward()
{
    return this->vectorForward;
}

glm::vec3 ObjectInSpace::getVectorTop()
{
    return this->vectorTop;
}
