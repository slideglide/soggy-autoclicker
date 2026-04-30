#include <Geode/Geode.hpp>
#include <alphalaneous.alphas_geode_utils/include/ObjectModify.hpp>

using namespace geode::prelude;

class $nodeModify(AutoclickSogLayer, soggy_mod::SogLayer) {
    struct Fields {
        CCMenuItemSpriteExtra* m_honk = nullptr;
        CCMenu* m_menu = nullptr;
        CCMenuItemToggler* m_toggler = nullptr;
        CCLabelBMFont* m_label = nullptr;
    };

    void modify() {
        auto interval = Mod::get()->getSettingValue<float>("interval");

        m_fields->m_menu = static_cast<CCMenu*>(this->getChildByID("button-menu"));
        if (!m_fields->m_menu) return;

        m_fields->m_honk = static_cast<CCMenuItemSpriteExtra*>(this->getChildByIDRecursive("honk-button"));
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        m_fields->m_toggler = CCMenuItemExt::createTogglerWithStandardSprites(
            1.f,
            [this, interval](CCMenuItemToggler* toggler) {
                if (toggler->isOn()) {
                    this->schedule(schedule_selector(AutoclickSogLayer::spamHonk), interval);
                } else {
                    this->unschedule(schedule_selector(AutoclickSogLayer::spamHonk));
                }
            }
        );

        m_fields->m_label = CCLabelBMFont::create("Auto Clicker", "goldFont.fnt");
        m_fields->m_label->setScale(0.6f);

        auto menuPos = m_fields->m_menu->getPosition();

        float localX = winSize.width - menuPos.x - 20.f - m_fields->m_label->getScaledContentSize().width - 4.f - m_fields->m_toggler->getContentSize().width / 2;
        float localY = -menuPos.y + 20.f;

        m_fields->m_toggler->setPosition(ccp(localX, localY));
        m_fields->m_label->setAnchorPoint({0.f, 0.5f});
        m_fields->m_label->setPosition(ccp(localX + m_fields->m_toggler->getContentSize().width / 2 + 4.f, localY));

        m_fields->m_menu->addChild(m_fields->m_toggler);
        m_fields->m_menu->addChild(m_fields->m_label);
    }

    void spamHonk(float dt) {
        if (m_fields->m_honk) m_fields->m_honk->activate();
    }
};