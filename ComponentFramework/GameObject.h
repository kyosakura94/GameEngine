#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glew.h>
#include "Matrix.h"
using namespace MATH;
class GameObject {
	
private:
	Vec3 velocity;
	Vec3 position;
	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;
	class Mesh *mesh;
	class Shader *shader;
	class Texture *texture;
public:
	GameObject(Mesh *mesh_, Shader *shader_, Texture *texture_);
	~GameObject();
	void Render() const;
	void Update(float deltaTime_);
	inline Shader* getShader() const { return shader; }
	void SetInitialValues(Vec3 position, Vec3 vel);
	inline Vec3& getPosition() { return position; }
	inline Vec3& getVelocity() { return velocity; }

	inline void setModelMatrix(const Matrix4 &modelMatrix_) { modelMatrix = modelMatrix_; }
	inline Matrix4& getModelMatrix() { return modelMatrix; }
};

#endif

