#include "Scene1.h"
#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
#include "Camera.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"


Scene1::Scene1() :earthRotation(0.0), moonRotation(0.0) {
}


Scene1::~Scene1() {
	if (meshPtr)  delete meshPtr;
	if (shaderPtr)delete shaderPtr;
	if (moontexurePtr)  delete moontexurePtr;
	if (earthtexurePtr) delete earthtexurePtr;
	if (moon)	delete moon;
	if (earth)  delete earth;
}

bool Scene1::OnCreate() {

	camera = new Camera();

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");

	moontexurePtr = new Texture();
	moontexurePtr->LoadImage("moon.jpg");

	earthtexurePtr = new Texture();
	earthtexurePtr->LoadImage("earthclouds.jpg");

	moon = new GameObject(meshPtr, shaderPtr, moontexurePtr);

	earth = new GameObject(meshPtr, shaderPtr, earthtexurePtr);

	lightSource = Vec3(-8.0, 6.0, 0.0);
	return true;
}

void Scene1::OnDestroy() {}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene1::Update(const float deltaTime_) {
	moonRotation += 0.5f;
	earthRotation += 0.7f;

	Matrix4 model = MMath::rotate(moonRotation, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::translate(0.0, 0.0, 4.0) *
		MMath::scale(0.5, 0.5, 0.5) *
		MMath::rotate(180.0, Vec3(0.0, 1.0, 0.0));

	Matrix4 earthmodel = MMath::rotate(earthRotation, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::scale(1.5, 1.5, 1.5) *
		MMath::rotate(-90.0, Vec3(1.0f, 0.0f, 0.0f));

	moon->setModelMatrix(model);
	earth->setModelMatrix(earthmodel);


	moon->Update(deltaTime_);
	earth->Update(deltaTime_);
}

void Scene1::Render() const {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = moon->getShader()->getProgram();
	glUseProgram(program);

	/// This should not be done here. You only need to get these
	/// ID's once after the sharder has been created - TODO
	GLint projectionMatrixID = glGetUniformLocation(program, "projectionMatrix");
	GLint viewMatrixID = glGetUniformLocation(program, "viewMatrix");
	GLint lightPosID = glGetUniformLocation(program, "lightPos");


	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(lightPosID, 1, lightSource);



	moon->Render();
	earth->Render();

	glUseProgram(0);
}
