#include <Geode/modify/MenuLayer.hpp>

#include "../utils/createQuestsButton.hpp"

using namespace geode::prelude;


class $modify(MenuLayer) {
	bool init() $override {
		if (!MenuLayer::init())
			return false;

		auto menu = static_cast<CCMenu*>(this->getChildByID("right-side-menu"));
		menu->addChild(rgdps::createQuestsButton("quests-icon-menu.png"_spr, 0.9f));
		menu->updateLayout();

		return true;
	}
};