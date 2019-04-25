#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Trackball.h"
#include "Mesh.h"

union SDL_Event;
class Scene3 : public Scene {
public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
private:
	float rotation;
	Camera *cameraPtr;
	SkyBox *skyBoxPtr;
	Shader *shaderPtr;
	GameObject *sphere;
	Trackball *trackBall;
	Mesh *meshPtr;
};


#endif // !SCENE1_H