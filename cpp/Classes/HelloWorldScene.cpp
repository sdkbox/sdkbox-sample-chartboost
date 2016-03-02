
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CCLOG("Sample Startup");
    
    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);
    
    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));
    
    // add test menu
    createTestMenu();
    
    return true;
}

void HelloWorld::createTestMenu()
{
    sdkbox::PluginChartboost::setListener(this);
    sdkbox::PluginChartboost::cache(sdkbox::CB_Location_Default);
    sdkbox::PluginChartboost::cache(sdkbox::CB_Location_LevelComplete);
    
    MenuItemFont::setFontName("sans");
    Size size = Director::getInstance()->getWinSize();
    
    auto menu = Menu::create();
    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("video", "sans", 32), [](Ref*){
        CCLOG("sdkbox::PluginChartboost::show(sdkbox::CB_Location_Default);");
        sdkbox::PluginChartboost::show(sdkbox::CB_Location_Default);
    }));
    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("reward", "sans", 32), [](Ref*){
        CCLOG("sdkbox::PluginChartboost::show(sdkbox::CB_Location_LevelComplete);");
        sdkbox::PluginChartboost::show(sdkbox::CB_Location_LevelComplete);
    }));
    
    menu->alignItemsVerticallyWithPadding(15);
    menu->setPosition(Vec2(size.width / 2, size.height / 2));
    addChild(menu);
    
    _coin = 0;
    _coinLabel = Label::createWithSystemFont("0", "sans", 32);
    _coinLabel->setPosition(Vec2(size.width / 2, size.height - 80));
    addChild(_coinLabel);
}

void HelloWorld::onChartboostCached(const std::string& name)
{
    CCLOG("onChartboostCached: %s", name.c_str());
}

bool HelloWorld::onChartboostShouldDisplay(const std::string& name)
{
    CCLOG("onChartboostShouldDisplay: %s", name.c_str());
    return true;
}

void HelloWorld::onChartboostDisplay(const std::string& name)
{
    CCLOG("onChartboostDisplay: %s", name.c_str());
}

void HelloWorld::onChartboostDismiss(const std::string& name)
{
    CCLOG("onChartboostDismiss: %s", name.c_str());
}

void HelloWorld::onChartboostClose(const std::string& name)
{
    CCLOG("onChartboostClose: %s", name.c_str());
}

void HelloWorld::onChartboostClick(const std::string& name)
{
    CCLOG("onChartboostClick: %s", name.c_str());
}

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

void HelloWorld::onChartboostReward(const std::string& name, int reward)
{
    CCLOG("onChartboostReward: %s, %d", name.c_str(), reward);
    _coin += reward;
    _coinLabel->setString(to_string(_coin));
}

void HelloWorld::onChartboostFailedToLoad(const std::string& name, sdkbox::CB_LoadError e)
{
    CCLOG("onChartboostFailedToLoad: %s, %d", name.c_str(), static_cast<int>(e));
}

void HelloWorld::onChartboostFailToRecordClick(const std::string& name, sdkbox::CB_ClickError e)
{
    CCLOG("onChartboostFailToRecordClick: %s, %d", name.c_str(), static_cast<int>(e));
}

void HelloWorld::onChartboostConfirmation()
{
    CCLOG("onChartboostConfirmation");
}

void HelloWorld::onChartboostCompleteStore()
{
    CCLOG("onChartboostCompleteStore");
}
