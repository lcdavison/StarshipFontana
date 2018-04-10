#ifndef SFASSETMANAGER_H
#define SFASSETMANAGER_H

#include <memory>
#include <vector>

#include "SFAsset.h"
#include "SFPlayer.h"
#include "SFCoin.h"
#include "SFEnemy.h"
#include "SFProjectile.h"

class SFAssetManager {
	public:
		typedef std::vector<std::shared_ptr<SFAsset>> AssetContainer;

		template<class T> static void AddAsset(std::shared_ptr<T>);
		template<class T> static void CreateAsset(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);
		template<class T> static std::shared_ptr<T> FindAssetByName(const std::string);
		template<class T> static std::vector<std::shared_ptr<T>> FindAssetsOfType(const SFASSETTYPE);

		static AssetContainer RetrieveAllAssets();
		static void UpdateAssets(AssetContainer);
	private:
		static AssetContainer assets;
};

template<class T>
void SFAssetManager::AddAsset(std::shared_ptr<T> asset) {
	assets.push_back(asset);
}

template<class T>
void SFAssetManager::CreateAsset(const std::string name, const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) {
	auto asset = std::make_shared<T>(name, type, window);
	assets.push_back(asset);
}

template<class T>
std::shared_ptr<T> SFAssetManager::FindAssetByName(const std::string name) {
	for(auto asset : assets) {
		if(asset->GetName() == name) {
			auto found = std::dynamic_pointer_cast<T>(asset);
			return found; 
		}
	}

	return nullptr;
}

template<class T>
std::vector<std::shared_ptr<T>> SFAssetManager::FindAssetsOfType(const SFASSETTYPE type) {
	std::vector<std::shared_ptr<T>> found;

	for(auto asset : assets) {
		if(asset->GetType() == type) {
			auto typefound = std::dynamic_pointer_cast<T>(asset);
			found.push_back(typefound);
		}
	}

	return found;
}
#endif
