#include <Geode/modify/PauseLayer.hpp>

#include "../utils/createQuestsButton.hpp"

using namespace geode::prelude;


class $modify(PauseLayer) {
	$override
	void customSetup() {
		PauseLayer::customSetup();

		auto menu = static_cast<CCMenu*>(this->getChildByID("right-button-menu"));
		menu->addChild(rgdps::createQuestsButton("quests-icon-pause.png"_spr, 0.6f));
		menu->updateLayout();

		return;
	}
};