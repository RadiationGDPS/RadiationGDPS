#include <Geode/modify/PauseLayer.hpp>

#include "../utils/createQuestsButton.hpp"

using namespace geode::prelude;


class $modify(PauseLayer) {
	$override
	void customSetup() {
		PauseLayer::customSetup();

		auto menu = static_cast<CCMenu*>(this->getChildByID("right-button-menu"));
		menu->addChild(rgdps::createQuestsButton(false));
		menu->updateLayout();

		return;
	}
};