#include "../headers/CameraAttachable.h"

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
