#ifndef SFCOIN_H
#define SFCOIN_H

#include "SFAsset.h"

class SFCoin : public SFAsset {
public:
	SFCoin(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

	void OnUpdate();
private:
	void SetupSprite();
};

#endif
