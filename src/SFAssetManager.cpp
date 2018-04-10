#include "SFAssetManager.h"

SFAssetManager::AssetContainer SFAssetManager::assets;

SFAssetManager::AssetContainer SFAssetManager::RetrieveAllAssets() { return assets; }

void SFAssetManager::UpdateAssets(std::vector<std::shared_ptr<SFAsset>> updated) { 
	assets.clear();

	for(auto it = updated.begin(); it != updated.end(); ++it) {
		if((*it)->IsAlive()) {
			assets.push_back(*it);
		} else {
			printf("Found Dead\n");
		}
	}
}
