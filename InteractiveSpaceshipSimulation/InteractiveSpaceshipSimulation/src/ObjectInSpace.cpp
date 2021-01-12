#include "../headers/ObjectInSpace.h"

void ObjectInSpace::updateDirections(glm::quat rotation)
{
    this->vectorForward = glm::normalize(this->rotationQuat * this->initialVectorForward);
    this->vectorTop = glm::normalize(this->rotationQuat * this->initialVectorTop);
    this->vectorRight = glm::normalize(glm::cross(this->vectorForward, this->vectorTop));
}

ObjectInSpace::ObjectInSpace(glm::vec3 position, glm::vec3 vectorForward, glm::vec3 vectorTop)
{
    this->position = position;
    
    this->vectorForward = vectorForward;
    this->initialVectorForward = vectorForward;

    this->vectorTop = vectorTop;
    this->initialVectorTop = vectorTop;

    this->vectorRight = glm::normalize(glm::cross(this->vectorForward, this->vectorTop));

    this->rotationQuat = glm::quat();
}


void ObjectInSpace::rotate(glm::quat rotation)
{
    this->rotationQuat = rotation;
    updateDirections(rotation);
}


glm::quat ObjectInSpace::getRotationQuat()
{
    return this->rotationQuat;
}


glm::vec3 ObjectInSpace::getPosition()
{
    return this->position;
}

glm::vec3 ObjectInSpace::getVectorForward()
{
    return this->vectorForward;
}

glm::vec3 ObjectInSpace::getVectorTop()
{
    return this->vectorTop;
}

void ObjectInSpace::setPosition(glm::vec3 newPosition)
{
    this->position = newPosition;
}