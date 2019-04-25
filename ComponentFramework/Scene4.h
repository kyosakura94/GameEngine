#ifndef SCENE4_H
#define SCENE4_H
#include "Scene.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Trackball.h"
#include "Mesh.h"
#include "Particles.h"
#include "Texture.h"

union SDL_Event;
class Scene4 : public Scene {
public:
	explicit Scene4();
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
private:
	float rotation;
	float elapsedtime;
	Camera *cameraPtr;
	GenerateParticles *particles;
	SkyBox *skyBoxPtr;
	Shader *shaderPtr;
	Shader *parshaderPtr;
	Texture *parTexture;
	GameObject *sphere;
	Trackball *trackBall;
	Mesh *meshPtr;
};


#endif // !SCENE4_H