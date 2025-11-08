#include "createQuestsButton.hpp"

using namespace geode::prelude;


CCMenuItemSpriteExtra* rgdps::createQuestsButton(char const* sprFrameName, float sprScale) {
	auto unclaimedQuests = []() {
		auto gsm = GameStatsManager::get();

		for (std::uint8_t i = 1u; i <= 3u; ++i) {
			if (gsm->getChallenge(i)->m_canClaim)
				return true;
		}

		return false;
	};

	auto spr = CCSprite::createWithSpriteFrameName(sprFrameName);
	spr->setScale(sprScale);
	CCSprite* exMark = nullptr;
	if (unclaimedQuests()) {
		exMark = CCSprite::createWithSpriteFrameName("exMark_001.png");
		exMark->CCNodeRGBA::setPosition(spr->getContentWidth() - 7.f, 40.f);
		exMark->setScale(0.6f);

		spr->addChild(exMark);
	}

	auto ret = CCMenuItemExt::createSpriteExtra(
		spr,
		[exMark](CCMenuItemSpriteExtra*) {
			ChallengesPage::create()->show();
			if (exMark)
				exMark->setVisible(false);
		}
	);
	ret->setID("quests-button"_spr);

	return ret;
}