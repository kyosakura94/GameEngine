#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "SkyBox.h"
#include "Trackball.h"
union SDL_Event;
class Camera;
class Scene2 : public Scene {
public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
private:
	Camera *cameraPtr;
	SkyBox *skyBoxPtr;
	Trackball *trackBall;
};


#endif // !SCENE1_H