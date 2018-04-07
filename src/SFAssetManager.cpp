#include "SFAssetManager.h"

SFAssetManager::AssetContainer SFAssetManager::assets;

SFAssetManager::AssetContainer SFAssetManager::RetrieveAllAssets() { return assets; }

void SFAssetManager::UpdateAssets(std::vector<std::shared_ptr<SFAsset>> updated) { assets = updated; }
