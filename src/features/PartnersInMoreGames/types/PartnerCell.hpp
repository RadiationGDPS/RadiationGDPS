#pragma once

#include <Geode/cocos/sprite_nodes/CCSprite.h>


class PartnerCell final : public cocos2d::CCSprite {
public:
	enum Partner : std::uint8_t {
		High,
		Future
	};

	static PartnerCell* create(Partner partner);

private:
	bool init(Partner);

	// Fields
	static float s_width;
};