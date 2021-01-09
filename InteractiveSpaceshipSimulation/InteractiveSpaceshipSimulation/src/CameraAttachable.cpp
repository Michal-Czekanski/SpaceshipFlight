#include "../headers/CameraAttachable.h"

CameraAttachable::CameraAttachable(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop)
{
    this->position = position;
    this->rotationQuat = rotationQuat;
    this->vectorForward = glm::normalize(vectorForward);
    this->vectorTop = glm::normalize(vectorTop);
    this->vectorRight = glm::normalize(glm::cross(vectorForward, vectorTop));
}

glm::vec3 CameraAttachable::getPosition()
{
    return this->position;
}

glm::quat CameraAttachable::getRotationQuat()
{
    return this->rotationQuat;
}

glm::vec3 CameraAttachable::getVectorForward()
{
    return this->vectorForward;
}

glm::vec3 CameraAttachable::getVectorTop()
{
    return this->vectorTop;
}
