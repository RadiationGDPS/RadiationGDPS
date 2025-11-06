#include <Geode/modify/GJMoreGamesLayer.hpp>

#include <amber/layouts/ListLayout.hpp>

using namespace geode::prelude;


class $modify(GJMoreGamesLayer) {
	void customSetup() $override {
		GJMoreGamesLayer::customSetup();

		m_listLayer->getChildByType<CustomListView>(0)->setVisible(false);
		m_mainLayer->getChildByType<CCLabelBMFont>(0)->setVisible(false);

		static_cast<CCLabelBMFont*>(m_listLayer->getChildByID("title"))->setString("Neon Partners");


		auto const scrollSize = m_listLayer->getContentSize();

		auto scrollLayer = ScrollLayer::create(scrollSize);
		scrollLayer->setID("partners-scroll-layer"_spr);
		m_listLayer->addChild(scrollLayer);

		auto contentLayer = scrollLayer->m_contentLayer;
		contentLayer->setLayout(ListLayout::create(scrollSize.height));


		auto createPartnerButton = [&scrollSize](std::string_view partner, std::string link) {
			auto partnerStr = fmt::format("partner-{}.png"_spr, partner);

			auto sprite = CCSprite::createWithSpriteFrameName(partnerStr.c_str());
			sprite->setScale(scrollSize.width / sprite->getContentWidth());
			auto ret = CCMenu::create();
			ret->setContentSize(sprite->getScaledContentSize());

			auto button = CCMenuItemExt::createSpriteExtra(
				sprite,
				[capLink = std::move(link)](CCMenuItemSpriteExtra*) {
					geode::utils::web::openLinkInBrowser(capLink);
				}
			);
			button->ignoreAnchorPointForPosition(true);
			button->m_scaleMultiplier = 1.f;

			ret->addChild(button);
			ret->setID(std::move(partnerStr));

			return ret;
		};

		contentLayer->addChild(createPartnerButton("high", "https://highgdps.ps.fhgdps.com/dashboard"));
		contentLayer->addChild(createPartnerButton("future", "https://futuregdpss.ps.fhgdps.com/dashboard"));

		contentLayer->updateLayout();

		return;
	}
};