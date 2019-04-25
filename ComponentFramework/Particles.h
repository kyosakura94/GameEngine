#ifndef PARTICLES_H
#define PARTICLES_H
#include <SDL.h>
#include "Matrix.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

using namespace MATH;
struct Particle {
public:
	Vec3 position;
	Vec3 velocity;
	Vec4 color;
	GLfloat Life;

	Particle() : position(0.0f), velocity(0.0f), color(1.0f), Life(0.0f) { }
};

class GenerateParticles
{
public:
	bool OnCreate();
	void Render() const;

	inline Shader * getShader() const { return shader; }

	void Update(GLfloat dt, GameObject &object, GLuint newParticles, Vec3 offset);

	GenerateParticles(Shader *shader_, Texture *texture_, GLuint amount);
	~GenerateParticles();
private:
	GLuint vao, vbo;
	std::vector<Particle> particles;

	GLint amount;
	Shader *shader;
	Texture *texture;

	GLuint firstUnusedParticle();
	void respawnParticle(Particle &particle, GameObject &object, Vec3 offset);
};
#endif