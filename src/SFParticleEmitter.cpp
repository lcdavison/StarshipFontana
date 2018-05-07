#include "SFParticleEmitter.h"

#include <algorithm>

SFParticleEmitter::SFParticleEmitter(std::shared_ptr<SFAsset> asset, int num_particles, std::shared_ptr<SFWindow> window) : parent(asset), num_particles(num_particles), window(window) {
}	

void SFParticleEmitter::Emit() {
	if(particles.size() != num_particles) {
		for(int i = 0; i < num_particles - particles.size(); i++) {
			particles.push_back(std::make_shared<SFParticle>(parent->GetBoundingBox()->GetX(), parent->GetBoundingBox()->GetY(), window));
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
