#include "createQuestsButton.hpp"

using namespace geode::prelude;


CCMenuItemSpriteExtra* rgdps::createQuestsButton(bool menu) {
	auto unclaimedQuests = []() {
		auto gsm = GameStatsManager::get();

		for (std::uint8_t i = 1u; i <= 3u; ++i) {
			if (auto quest = gsm->getChallenge(i); quest && quest->m_canClaim)
				return true;
		}

		return false;
	};

	auto spr = CCSprite::createWithSpriteFrameName(menu ? "quests-icon-menu.png"_spr : "quests-icon-pause.png"_spr);
	spr->setScale(menu ? 0.55f : 0.6f);
	CCSprite* exMark = nullptr;
	if (unclaimedQuests()) {
		exMark = CCSprite::createWithSpriteFrameName("exMark_001.png");
		exMark->CCNodeRGBA::setPosition(spr->getContentWidth() - 7.f, spr->getContentHeight() - 10.f);
		exMark->setScale(menu ? 0.9f : 0.6f);

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