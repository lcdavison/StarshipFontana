#ifndef SFPARTICLEEMITTER_H
#define SFPARTICLEEMITTER_H

#include <SDL.h>

#include "SFWindow.h"
#include "SFAsset.h"
#include "SFParticle.h"

#include <vector>

class SFParticleEmitter {
	public:
		SFParticleEmitter(std::shared_ptr<SFAsset>, int, std::shared_ptr<SFWindow>);
	
		void Emit();
		void RemoveDeadParticles();

		void OnRender();	
	private:
		int num_particles;

		std::shared_ptr<SFAsset> parent;
		std::shared_ptr<SFWindow> window;

		std::vector<std::shared_ptr<SFParticle>> particles;
};
#endif
