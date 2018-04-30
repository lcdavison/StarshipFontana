#ifndef SFCOIN_H
#define SFCOIN_H

#include "SFAssetManager.h"
#include "SFMath.h"

class SFPlayer;

class SFCoin : public SFAsset {
public:
	SFCoin(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

	void OnUpdate();
private:
	std::shared_ptr<SFPlayer> player;
};

#endif
