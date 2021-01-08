#include "../headers/ICameraAttachable.h"

glm::vec3 ICameraAttachable::getPosition()
{
    return this->position;
}

glm::quat ICameraAttachable::getRotationQuat()
{
    return this->rotationQuat;
}

glm::vec3 ICameraAttachable::getVectorForward()
{
    return this->vectorForward;
}

glm::vec3 ICameraAttachable::getVectorTop()
{
    return this->vectorTop;
}
