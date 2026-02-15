#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>

using namespace geode::prelude;

bool m_enabled = false;
bool m_tall = false;
float m_scaleFactor = 0.5f;

class $modify(WideSprite, CCSprite) {
	// init
	virtual bool init() {
		bool ret = CCSprite::init();
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithTexture(cocos2d::CCTexture2D* pTexture) {
		bool ret = CCSprite::initWithTexture(pTexture);
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithTexture(cocos2d::CCTexture2D* pTexture, cocos2d::CCRect const& rect) {
		bool ret = CCSprite::initWithTexture(pTexture, rect);
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithTexture(cocos2d::CCTexture2D* pTexture, cocos2d::CCRect const& rect, bool rotated) {
		bool ret = CCSprite::initWithTexture(pTexture, rect, rotated);
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithSpriteFrame(cocos2d::CCSpriteFrame* pSpriteFrame) {
		bool ret = CCSprite::initWithSpriteFrame(pSpriteFrame);
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithSpriteFrameName(char const* pszSpriteFrameName) {
		bool ret = CCSprite::initWithSpriteFrameName(pszSpriteFrameName);
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithFile(char const* pszFilename) {
		bool ret = CCSprite::initWithFile(pszFilename);
		if (ret) sizeUp();
		return ret;
	}
	virtual bool initWithFile(char const* pszFilename, cocos2d::CCRect const& rect) {
		bool ret = CCSprite::initWithFile(pszFilename, rect);
		if (ret) sizeUp();
		return ret;
	}

	// scale
	virtual void setScaleX(float fScaleX) {
		if (m_enabled) {
			CCSprite::setScaleX(fScaleX + (m_scaleFactor / 2.5f));
		} else {
			CCSprite::setScaleX(fScaleX);
		}
	}

	virtual void setScaleY(float fScaleY) {
		if (m_enabled) {
			CCSprite::setScaleY(fScaleY + (m_scaleFactor / 2.5f));
		} else {
			CCSprite::setScaleY(fScaleY);
		}
	}

	// new function
	void sizeUp() {
		if (m_enabled) {
			if (m_tall) {
				// tall
				this->setScaleY(getScaleY() + m_scaleFactor);
			} else {
				// wide
				this->setScaleX(getScaleX() + m_scaleFactor);
			}
		}
	}
};

// settings
$on_mod(Loaded) {
	m_enabled = Mod::get()->getSettingValue<bool>("enabled");
	m_scaleFactor = Mod::get()->getSettingValue<double>("scale-factor");
	m_tall = Mod::get()->getSettingValue<bool>("tall");

	listenForSettingChanges<bool>("enabled", [](bool value) {
		m_enabled = value;
	});
	listenForSettingChanges<float>("scale-factor", [](float value) {
		m_scaleFactor = value;
	});
	listenForSettingChanges<bool>("tall", [](bool value) {
		m_tall = value;
	});
}