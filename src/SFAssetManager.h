#ifndef SFASSETMANAGER_H
#define SFASSETMANAGER_H

#include <vector>

#include "SFAsset.h"
#include "SFPlayer.h"

class SFAssetManager {
	public:
		template<class T> static void CreateAsset(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);
		static std::shared_ptr<SFAsset> FindAssetByName(std::string);
	private:
		static std::vector<SFAsset> assets;
};

template<class T>
void SFAssetManager::CreateAsset(const std::string name, const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) {
	auto asset = T(type, window);
	assets.push_back(asset);

	for(auto asseti : assets) {
		printf("ASSET WIDTH : %d", asseti.GetBoundingBox()->GetWidth());
	}
}
#endif
