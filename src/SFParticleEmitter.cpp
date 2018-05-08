#include "SFParticleEmitter.h"

SFParticleEmitter::SFParticleEmitter(int num_particles, std::shared_ptr<SFWindow> window) : num_particles(num_particles), window(window) {
}	

SFParticleEmitter::~SFParticleEmitter() {
	particles.clear();
}

void SFParticleEmitter::Emit(int x_pos, int y_pos) {
	if(particles.size() != num_particles) {
		for(int i = 0; i < num_particles - particles.size(); i++) {
			particles.push_back(std::make_shared<SFParticle>(x_pos, y_pos, window));
		}
	} 

	for(auto particle : particles) {
		particle->OnUpdate();
	}

	RemoveDeadParticles();
}

bool ParticleDead(const std::shared_ptr<SFParticle> particle) {
	return particle->IsDead();
}

void SFParticleEmitter::RemoveDeadParticles() {
	particles.erase(std::remove_if(particles.begin(), particles.end(), ParticleDead), particles.end());
}

void SFParticleEmitter::OnRender() {
	for(auto particle : particles) {
		particle->OnRender();
	}
}
