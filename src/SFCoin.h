#ifndef SFCOIN_H
#define SFCOIN_H

#include "SFAsset.h"

class SFCoin : public SFAsset {
public:
	SFCoin(const SFASSETTYPE, const std::shared_ptr<SFWindow>);

	void Update();
private:
	void SetupSprite();
};

#endif
