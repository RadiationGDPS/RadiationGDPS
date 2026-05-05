#include "PartnerCell.hpp"


using namespace geode::prelude;


// Static fields init
float PartnerCell::s_width = 55.f;


PartnerCell* PartnerCell::create(Partner partner) {
	auto ret = new PartnerCell;

	if (ret->init(partner)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool PartnerCell::init(Partner partner) {
	char const* partnerStr;
	char const* link;
	char const* particleStr;
	float particleY;
	ccColor3B glowColor;
	bool mismatch = false;
	switch (partner) {
		case Partner::High:
			partnerStr = "high";
			link = "https://highgdps.ps.fhgdps.com/dashboard";
			particleStr = "20a-1a3a0.3a6a-65a14a7a0a65a0a0a0a0a0a0a0a5a1a0a0a0.215686a0a0.929412a0a0.788235a0a0.6a0a2a1a0a0a0.356863a0a1a0a0.92549a0a0.25a0a0a0a0a0a0a0a0a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0";
			particleY = 80.f;
			glowColor = { .r=0u, .g=233u, .b=131u };
			break;

		case Partner::Future:
			partnerStr = "future";
			link = "https://futuregdpss.ps.fhgdps.com/dashboard";
			particleStr = "20a-1a3a0.3a6a0a180a1a0a65a10a0a0a0a0a0a0a5a1a0a0a0.929412a0a0.211765a0a0.737255a0a0.6a0a2a1a0a0a0.929412a0a0.211765a0a0.737255a0a0.25a0a0a0a0a0a0a0a0a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0";
			particleY = 65.f;
			glowColor = { .r=213u, .g=47u, .b=216u };
			break;

		default:
			mismatch = true;
			break;
	}

	if (!CCSprite::initWithSpriteFrameName(
		mismatch ?
			"GJ_longBtn04_001.png"
			:
			fmt::format("partner-{}.png"_spr, partnerStr).c_str()
	)) return false;

	this->setID(
		fmt::format("partner-{}", mismatch ? "fallback" : partnerStr)
	);
	this->setScale(s_width / this->getContentWidth());

	auto logo = CCSprite::createWithSpriteFrameName(
		fmt::format("partner-{}-logo.png"_spr, partnerStr).c_str()
	);
	logo->CCNodeRGBA::setPosition(56.f, 48.f);
	logo->setZOrder(2);
	logo->setID(
		fmt::format("partner-{}-logo", mismatch ? "fallback" : partnerStr)
	);
	this->addChild(logo);

	auto logoGlow = CCSprite::createWithSpriteFrameName("lightsquare_05_01_glow_001.png");
	logoGlow->setColor(glowColor);
	logoGlow->CCNodeRGBA::setPosition(56.f, 48.f);
	logoGlow->setScale(2.15f);
	logoGlow->setZOrder(1);
	logoGlow->runAction(
		CCRepeatForever::create(
			CCSequence::createWithTwoActions(
				CCFadeTo::create(1.f, 10u),
				CCFadeTo::create(1.f, 240u)
			)
		)
	);
	logoGlow->setID("logo-glow");
	this->addChild(logoGlow);

	auto menu = CCMenu::create();
	menu->setPosition(0.f, 0.f);
	menu->setContentSize(this->getContentSize());
	menu->setID("download-menu");
	this->addChild(menu);

	auto downloadBtn = CCMenuItemExt::createSpriteExtra(
		CCLabelBMFont::create("Download now!", "goldFont.fnt"),
		[link](CCMenuItemSpriteExtra*) { web::openLinkInBrowser(link); }
	);
	downloadBtn->setSelectedImage(CCLabelBMFont::create("Download now!", "goldFont.fnt"));
	downloadBtn->m_pNormalImage->runAction(
		CCRepeatForever::create(
			CCSequence::create(
				CCEaseInOut::create(CCScaleTo::create(0.5f, 1.1f), 2.f),
				CCEaseInOut::create(CCScaleTo::create(0.5f, 1.0f), 2.f),
				nullptr
			)
		)
	);
	menu->addChildAtPosition(downloadBtn, Anchor::BottomRight, { -130.f, 27.f });
	menu->ignoreAnchorPointForPosition(true);

	auto particles = GameToolbox::particleFromString(particleStr, nullptr, false);
	particles->setPosition(220.f, particleY);
	particles->setScale(1.65f);
	particles->setID("particles");
	this->addChild(particles);

	return true;
}