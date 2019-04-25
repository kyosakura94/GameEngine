#include <iostream>
#include "Scene4.h"
#include "SkyBox.h"
#include <glew.h>
#include "Camera.h"
#include "ObjLoader.h"
#include "Texture.h"
Scene4::Scene4() {
}


Scene4::~Scene4() {
}

bool Scene4::OnCreate() {
	trackBall = new Trackball();
	cameraPtr = new Camera();
	skyBoxPtr = new SkyBox();



	parshaderPtr = new Shader("particlesVert.glsl", "particlesFrag.glsl");

	//add texture for particle
	parTexture = new Texture();
	parTexture->LoadImage("particle.png");

	particles = new GenerateParticles(parshaderPtr, parTexture, 500);

	skyBoxPtr->OnCreate();

	particles->OnCreate();

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}

	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	shaderPtr = new Shader("waterVert.glsl", "waterFrag.glsl");

	sphere = new GameObject(meshPtr, shaderPtr, nullptr);


	std::cout << "Creating Scene 4" << std::endl;
	return true;
}

void Scene4::OnDestroy() {}

void Scene4::HandleEvents(const SDL_Event &sdlEvent) {
	trackBall->HandleEvents(sdlEvent);
}

void Scene4::Update(const float deltaTime_) {
	SDL_Event sdlEvent;
	HandleEvents(sdlEvent);

	rotation += 0.5f;
	
	elapsedtime += deltaTime_;


	//Matrix4 model =  MMath::scale(1.0, 1.0, 1.0);

	//sphere->setModelMatrix(model);
	particles->Update(deltaTime_, *sphere, 2, Vec3(2.0f));

	sphere->Update(deltaTime_);
}

void Scene4::Render() const {

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

	glUniform1f(sphere->getShader()->getUniformID("time"), elapsedtime);

	glUniformMatrix4fv(sphere->getShader()->getUniformID("projectionMatrix"), 1 , GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(sphere->getShader()->getUniformID("viewMatrix"), 1 , GL_FALSE, cameraPtr->getViewMatrix());
	
		
	sphere->Render();

	glUseProgram(particles->getShader()->getProgram());

	particles->Render();
}
