#include <Geode/modify/MenuLayer.hpp>

#include "../utils/createQuestsButton.hpp"

using namespace geode::prelude;


class $modify(MenuLayer) {
	$override
	bool init() {
		if (!MenuLayer::init())
			return false;

		auto menu = static_cast<CCMenu*>(this->getChildByID("right-side-menu"));
		menu->addChild(rgdps::createQuestsButton(true));
		menu->updateLayout();

		return true;
	}
};