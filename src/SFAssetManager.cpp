#include "SFAssetManager.h"

SFAssetManager::AssetContainer SFAssetManager::assets;

SFAssetManager::AssetContainer SFAssetManager::RetrieveAllAssets() { return assets; }

void SFAssetManager::RemoveAsset(std::shared_ptr<SFAsset> asset) {
	for(auto it = assets.begin(); it != assets.end(); ) {
		if((*it) == asset) {
			it = assets.erase(it);
		} else {
			++it;
		}
	}
}
