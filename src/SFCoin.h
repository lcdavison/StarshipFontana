#ifndef SFCOIN_H
#define SFCOIN_H

#include "SFAssetManager.h"

class SFCoin : public SFAsset {
public:
	SFCoin(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

	void OnUpdate();
private:
	void SetupSprite();

	std::shared_ptr<SFPlayer> player;
};

#endif
