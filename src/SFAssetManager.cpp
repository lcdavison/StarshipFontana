#include "SFAssetManager.h"

std::vector<SFAsset> SFAssetManager::assets;

/*template<class T>
void SFAssetManager::CreateAsset(const std::string name, const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) {

		auto asset = T(type, window);
		switch(type) {
				case SFASSET_PLAYER:
						asset = SFPlayer(type, window);
						break;
		}

		assets.push_back(asset);
}*/

std::shared_ptr<SFAsset> SFAssetManager::FindAssetByName(std::string name) {

		for(auto asset : assets) {
				// DO SOMETHING
		}







		/*std::map<std::string, std::shared_ptr<SFAsset>>::iterator it = assets.find(name);

		  if(it == assets.end()) {
		  printf("Cannot Find Asset : %s", name.c_str());
		  return nullptr;
		  }

		  printf("Found It");

		  return it->second;*/
}
