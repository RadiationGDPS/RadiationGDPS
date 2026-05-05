#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;


class $modify(MenuLayer) {
	$override
	bool init() {
		if (!MenuLayer::init())
			return false;

		auto ogTitle = this->getChildByID("main-title");

		auto title = CCSprite::createWithSpriteFrameName("rgdps-title.png"_spr);
		title->setPosition(ogTitle->getPosition());
		title->setScale(1.25f);
		title->setID("title"_spr);

		this->addChild(title, ogTitle->getZOrder());
		ogTitle->setVisible(false);

		return true;
	}
};