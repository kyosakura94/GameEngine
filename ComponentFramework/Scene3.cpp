#include <iostream>
#include "Scene3.h"
#include "SkyBox.h"
#include <glew.h>
#include "Camera.h"
#include "ObjLoader.h"
Scene3::Scene3() {
}


Scene3::~Scene3() {
}

bool Scene3::OnCreate() {
	trackBall = new Trackball();
	cameraPtr = new Camera();
	skyBoxPtr = new SkyBox();

	skyBoxPtr->OnCreate();

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}

	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	shaderPtr = new Shader("reflectionVert.glsl", "reflectionFrag.glsl");

	sphere = new GameObject(meshPtr, shaderPtr, nullptr);


	std::cout << "Creating Scene 3" << std::endl;
	return true;
}

void Scene3::OnDestroy() {}

void Scene3::HandleEvents(const SDL_Event &sdlEvent) {
	trackBall->HandleEvents(sdlEvent);
}

void Scene3::Update(const float deltaTime_) {
	SDL_Event sdlEvent;
	HandleEvents(sdlEvent);

	rotation += 0.5f;

	Matrix4 model = MMath::rotate(rotation, Vec3(0.0f, 1.0f, 0.0f)) * 
		MMath::rotate(rotation, Vec3(1.0f, 0.0f, 0.0f)) *
		MMath::scale(1.0, 1.0, 1.0);

	sphere->setModelMatrix(model);
	sphere->Update(deltaTime_);

}

void Scene3::Render() const {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(skyBoxPtr->getShader()->getProgram());
	
	glUniformMatrix4fv(skyBoxPtr->getShader()->getUniformID("projectionMatrix"), 1 , GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(skyBoxPtr->getShader()->getUniformID("viewMatrix"), 1 , GL_FALSE, Matrix4 ());

	glDepthMask(GL_FALSE);

	skyBoxPtr->Render(trackBall->getMatrix4());

	glDepthMask(GL_TRUE);

	//for render sphere
	GLuint program = sphere->getShader()->getProgram();
	glUseProgram(program);

	glUniformMatrix4fv(sphere->getShader()->getUniformID("projectionMatrix"), 1 , GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(sphere->getShader()->getUniformID("viewMatrix"), 1 , GL_FALSE, cameraPtr->getViewMatrix());
	
	sphere->Render();


}
