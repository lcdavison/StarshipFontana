#ifndef SFASSETMANAGER_H
#define SFASSETMANAGER_H

#include <memory>
#include <vector>

#include "SFAsset.h"
#include "SFPlayer.h"
#include "SFCoin.h"
#include "SFEnemy.h"
#include "SFProjectile.h"
#include "SFObstacle.h"

class SFAssetManager 
{
	public:
		typedef std::vector<std::shared_ptr<SFAsset>> 				AssetContainer;

		template<class T> static void 								AddAsset(std::shared_ptr<T>);
		template<class T> static void 								CreateAsset(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

		template<class T> static std::shared_ptr<T> 				GetAssetByName(const std::string);
		template<class T> static std::vector<std::shared_ptr<T>> 	GetAssetsOfType(const SFASSETTYPE);

		template<class T> static void 								SpawnAtPosition(std::shared_ptr<T>, Point2);

		static AssetContainer 										RetrieveAllAssets();
		static void 												RemoveAsset(std::shared_ptr<SFAsset>);
		static void 												Clear();
	private:
		static AssetContainer assets;
};

//
//	AddAsset
//		Adds an asset of any type to the asset manager
//
template<class T>
void SFAssetManager::AddAsset(std::shared_ptr<T> asset) 
{
	assets.push_back(asset);
}

//
//	CreateAsset
//		Creates an asset in the asset manager
//
template<class T>
void SFAssetManager::CreateAsset(const std::string name, 
							 	 const SFASSETTYPE type, 
								 const std::shared_ptr<SFWindow> window) 
{
	auto asset = std::make_shared<T>(name, type, window);
	assets.push_back(asset);
}

//
//	GetAssetByName
//		Searches manager for asset and returns it if found
//
template<class T>
std::shared_ptr<T> SFAssetManager::GetAssetByName(const std::string name) 
{
	for(auto asset : assets) 
	{
		if(asset->GetName() == name) 
		{
			auto found = std::dynamic_pointer_cast<T>(asset);
			return found; 
		}
	}

	return nullptr;
}

//
//	GetAssetsOfType
//		Returns all assets of a specific type
//
template<class T>
std::vector<std::shared_ptr<T>> SFAssetManager::GetAssetsOfType(const SFASSETTYPE type) 
{
	std::vector<std::shared_ptr<T>> found;

	for(auto asset : assets) 
	{
		if(asset->GetType() == type) 
		{
			auto typefound = std::dynamic_pointer_cast<T>(asset);
			found.push_back(typefound);
		}
	}

	return found;
}

//
//	SpawnAtPosition
//		Spawns the provided asset at a location
//
template<class T>
void SFAssetManager::SpawnAtPosition(std::shared_ptr<T> asset, Point2 position) 
{
	asset->SetPosition(position);
	assets.push_back(asset);
}
#endif
