#include <iostream>
#include "Scene2.h"
#include "SkyBox.h"
#include <glew.h>
#include "Camera.h"
Scene2::Scene2() {
}


Scene2::~Scene2() {
}

bool Scene2::OnCreate() {

	trackBall = new Trackball();
	cameraPtr = new Camera();
	skyBoxPtr = new SkyBox();
	skyBoxPtr->OnCreate();
	std::cout << "Creating Scene 2" << std::endl;
	return true;
}

void Scene2::OnDestroy() {}

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {
	trackBall->HandleEvents(sdlEvent);
}

void Scene2::Update(const float deltaTime_) {
	SDL_Event sdlEvent;
	HandleEvents(sdlEvent);
	//skyBoxPtr->Update(deltaTime_);
	//HandleEvents();
	//skyBoxPtr->HandleEvents(SDL_Event &sdlEvent);
	//static float rotation = 0.0f;
	//rotation += 0.5;
	//gameObject->setModelMatrix(MMath::rotate(rotation, Vec3(0.0, 1.0, 0.0)));
	
}

void Scene2::Render() const {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(skyBoxPtr->getShader()->getProgram());

	glUniformMatrix4fv(skyBoxPtr->getShader()->getUniformID("projectionMatrix"), 1 , GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(skyBoxPtr->getShader()->getUniformID("viewMatrix"), 1 , GL_FALSE, Matrix4 ());
	
	glDepthMask(GL_FALSE);
	skyBoxPtr->Render(trackBall->getMatrix4());
	glDepthMask(GL_TRUE);

}
