#ifndef SKYBOX_H
#define SKYBOX_H
#include <SDL.h>
#include "Matrix.h"
#include "Shader.h"
#include "Trackball.h"
using namespace MATH;
class SkyBox {
private:
	unsigned int textureID;
	Shader *shaderPtr;
	class Mesh *meshPtr;
	Matrix4 modelMatrix;
	Trackball trackBall;
	GLubyte *bytePtr;
public:
	SkyBox();
	~SkyBox();
	bool OnCreate();
	void OnDestroy();
	void Render(Matrix4 modelMatrix) const;
	void HandleEvents(const SDL_Event &sdlEvent);
	inline Shader * getShader() const { return shaderPtr; }

};

#endif
