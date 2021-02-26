#include "Game.h"

int Game::windowWidth = 1400;
int Game::windowHeight = 1000;

unsigned int Game::programBlur = 0;
unsigned int Game::programBloomFinalBlend = 0;


void Game::updateNormalScene()
{
	Physics* p = Physics::getInstance();
	PxScene* pxScene = p->getPxScene();
	
    // Here we retrieve the current transforms of the objects from the physical simulation.
    auto actorFlags = PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC;
    PxU32 nbActors = pxScene->getNbActors(actorFlags);
    if (nbActors)
    {
        std::vector<PxRigidActor*> actors(nbActors);
        pxScene->getActors(actorFlags, (PxActor**)&actors[0], nbActors);
        for (auto actor : actors)
        {
            // We use the userData of the objects to set up the model matrices
            // of proper renderables.
            if (!actor->userData) continue;
            RenderableObject* renderable = (RenderableObject*)actor->userData;

            RenderableUpdateData updateData(actor->getGlobalPose());

            renderable->physicsUpdate(updateData);
        }
    }
}

void Game::gameover()
{
    std::cout << "###########################" << std::endl;
    std::cout << "Game over" << std::endl;
    std::cout << "###########################" << std::endl;
    glutLeaveMainLoop();
}
