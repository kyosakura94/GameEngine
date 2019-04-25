#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;
union SDL_Event;
class Camera;
class GameObject;
class Mesh;
class Shader;
class Texture;
union SDL_Event;

class Scene1 : public Scene {
private:
	Camera *camera;
	GameObject *moon;
	GameObject *earth;
	float earthRotation, moonRotation;
	Vec3 lightSource;
	Mesh *meshPtr;
	Shader *shaderPtr;
	Texture *earthtexurePtr;
	Texture *moontexurePtr;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
};


#endif // !SCENE1_H