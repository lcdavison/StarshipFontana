#include "SFAssetManager.h"

SFAssetManager::AssetContainer SFAssetManager::assets;

/*
	RetrieveAllAsset
		Returns all of the current loaded assets
*/
SFAssetManager::AssetContainer SFAssetManager::RetrieveAllAssets() 
{ 
	return assets; 
}

/*
	RemoveAsset
		Removes an asset from the asset manager
*/
void SFAssetManager::RemoveAsset(std::shared_ptr<SFAsset> asset) 
{
	for(auto it = assets.begin(); it != assets.end(); ) 
	{
		if((*it) == asset) 
		{
			it = assets.erase(it);
		} 
		else 
		{
			++it;
		}
	}
}

/*
	Clear
		Clears the asset manager
*/
void SFAssetManager::Clear() 
{
	assets.clear();
}
