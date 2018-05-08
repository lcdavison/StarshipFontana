#include "SFParticleEmitter.h"

SFParticleEmitter::SFParticleEmitter(int num_particles, 
									 int alpha, 
									 std::shared_ptr<SFWindow> window) 
									 : num_particles(num_particles), 
									   alpha(alpha), 
									   window(window) 
{ }	

SFParticleEmitter::~SFParticleEmitter() 
{
	particles.clear();
}

//	
//	Emit
//		Emits the particles from the x and y position
//
void SFParticleEmitter::Emit(int x_pos, int y_pos) 
{
	if(particles.size() != num_particles) 
	{
		for(int i = 0; i < num_particles - particles.size(); i++) 
		{
			particles.push_back(std::make_shared<SFParticle>(x_pos, y_pos, 
															 alpha, window));
		}
	} 

	for(auto particle : particles) 
	{
		particle->OnUpdate();
	}

	RemoveDeadParticles();
}

//	
//	ParticleDead
//		Used as a predicate function to return particle state
//
bool ParticleDead(const std::shared_ptr<SFParticle> particle) 
{
	return particle->IsDead();
}

//	
//	RemoveDeadParticles
//		Removes all of the dead particles from the emitter
//
void SFParticleEmitter::RemoveDeadParticles() 
{
	particles.erase(std::remove_if(particles.begin(), particles.end(), ParticleDead), 
								   particles.end());
}

//	
//	OnRender
//		Renders each of the particles
//
void SFParticleEmitter::OnRender() 
{
	for(auto particle : particles) 
	{
		particle->OnRender();
	}
}
