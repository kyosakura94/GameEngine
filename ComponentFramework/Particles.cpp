#include "Particles.h"
#include <glew.h>
#include <SDL_image.h>
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameObject.h"

bool GenerateParticles::OnCreate()
{
    GLfloat particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(this->vao);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

	//push each particles to arr
	for (GLuint i = 0; i < this->amount; ++i)
		this->particles.push_back(Particle());
		
	return true;
}

void GenerateParticles::Render() const
{
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	for (Particle particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{
			glUniform3fv(shader->getUniformID("offset"),3,particle.position);
			glUniform4fv(shader->getUniformID("color"),4,particle.color);

			if (texture) {
				glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
			}

			glBindVertexArray(this->vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

}


void GenerateParticles::Update(GLfloat dt, GameObject & object, GLuint newParticles, Vec3 offset)
{
	// Add new particles 
	for (GLuint i = 0; i < newParticles; ++i)
	{
		int unusedParticle = firstUnusedParticle();
		respawnParticle(particles[unusedParticle], object, offset);
	}
	// Update all particles
	for (GLuint i = 0; i < amount; ++i)
	{
		Particle &p = particles[i];
		p.Life -= dt; // reduce life
		if (p.Life > 0.0f)
		{	// particle is alive, thus update
			p.position -= p.velocity * dt;
			p.color.w -= dt * 2.5;
		}
	}
}

GenerateParticles::GenerateParticles(Shader *shader_, Texture *texture_, GLuint amount_)
	: shader(nullptr), texture(nullptr), amount(amount_)
{
	shader = shader_;
	texture = texture_;
	amount = amount_;
}


GenerateParticles::~GenerateParticles()
{
}
GLuint lastUsedParticle = 0;
GLuint GenerateParticles::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void GenerateParticles::respawnParticle(Particle & particle, GameObject & object, Vec3 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);

	object.getPosition().x += random;
	object.getPosition().y += random;
	object.getPosition().z += random;

	particle.position = object.getPosition() + offset;
	particle.color = Vec4(rColor, rColor, rColor, 1.0f);
	particle.Life = 1.0f;

	particle.velocity = object.getVelocity() * 0.1f;
}
