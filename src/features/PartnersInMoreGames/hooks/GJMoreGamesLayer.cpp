#include <Geode/modify/GJMoreGamesLayer.hpp>

#include "../types/PartnerCell.hpp"

//#include <amber/layouts/ListLayout.hpp>

using namespace geode::prelude;


class $modify(GJMoreGamesLayer) {
	void customSetup() $override {
		GJMoreGamesLayer::customSetup();

		m_listLayer->getChildByType<CustomListView>(0)->setVisible(false);
		if (auto nothingHereLabel = m_mainLayer->getChildByType<CCLabelBMFont>(0))
			nothingHereLabel->setVisible(false);

		static_cast<CCLabelBMFont*>(m_listLayer->getChildByID("title"))->setString("Neon Partners");


		auto const scrollSize = m_listLayer->getContentSize();

		auto scrollLayer = ScrollLayer::create(scrollSize);
		scrollLayer->setID("partners-scroll-layer"_spr);
		m_listLayer->addChild(scrollLayer);

		auto contentLayer = scrollLayer->m_contentLayer;
		//contentLayer->setLayout(ListLayout::create(scrollSize.height));

		contentLayer->addChild(PartnerCell::create(PartnerCell::High));
		contentLayer->addChild(PartnerCell::create(PartnerCell::Future));

		contentLayer->updateLayout();

		return;
	}
};