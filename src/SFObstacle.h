#ifndef SFOBSTACLE_H
#define SFOBSTACLE_H

#include "SFAsset.h"

class SFObstacle : public SFAsset {
	public:
		SFObstacle(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);
		~SFObstacle();

		void OnUpdate();
	private:
		
};
#endif
