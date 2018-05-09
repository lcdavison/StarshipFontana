#ifndef SFPARTICLEEMITTER_H
#define SFPARTICLEEMITTER_H

#include "SFWindow.h"
#include "SFAsset.h"
#include "SFParticle.h"

#include <vector>
#include <algorithm>

class SFParticleEmitter 
{
	public:

		SFParticleEmitter(const int, const int, const std::shared_ptr<SFWindow>);
		~SFParticleEmitter();
	
		void 										Emit(const Point2&);
		void 										OnRender();	

	private:

		void 										RemoveDeadParticles();

		int 										num_particles;
		int 										alpha;

		std::shared_ptr<SFWindow> 					window;
		std::vector<std::shared_ptr<SFParticle>> 	particles;

};
#endif
