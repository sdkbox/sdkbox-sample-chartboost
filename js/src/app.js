
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        return true;
    },

    createTestMenu:function() {
        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        var coin = 0;
        var coinLabel = new cc.LabelTTF("0", "sans", 32);
        coinLabel.x = size.width / 2;
        coinLabel.y = size.height - 80;
        this.addChild(coinLabel);

        // init plugin
        sdkbox.PluginChartboost.init();
        sdkbox.PluginChartboost.cache("Default");
        sdkbox.PluginChartboost.cache("Level Complete");

        var menu = new cc.Menu(
            new cc.MenuItemFont("video", function() {
                sdkbox.PluginChartboost.show("Default");
                cc.log("sdkbox.PluginChartboost.show(\"Default\")");
            }),
            new cc.MenuItemFont("reward", function() {
                sdkbox.PluginChartboost.show("Level Complete");
                cc.log("sdkbox.PluginChartboost.show(\"Level Complete\")");
            })
        );

        sdkbox.PluginChartboost.setListener({
            onChartboostCached : function (name) {
                cc.log("onChartboostCached " + name);
            },
            onChartboostShouldDisplay : function (name) {
                cc.log("onChartboostShouldDisplay " + name);
            },
            onChartboostDisplay : function (name) {
                cc.log("onChartboostDisplay " + name);
            },
            onChartboostDismiss : function (name) {
                cc.log("onChartboostDismiss " + name);
            },
            onChartboostClose : function (name) {
                cc.log("onChartboostClose " + name);
            },
            onChartboostClick : function (name) {
                cc.log("onChartboostClick " + name);
            },
            onChartboostReward : function (name, reward) {
                cc.log("onChartboostReward " + name + " reward " + reward.toString());
                coin += reward;
                coinLabel.setString(coin.toString());
            },
            onChartboostFailedToLoad : function (name, e) {
                cc.log("onChartboostFailedToLoad " + name + " load error " + e.toString());
            },
            onChartboostFailToRecordClick : function (name, e) {
                cc.log("onChartboostFailToRecordClick " + name + " click error " + e.toString());
            },
            onChartboostConfirmation : function () {
                cc.log("onChartboostConfirmation");
            },
            onChartboostCompleteStore : function () {
                cc.log("onChartboostCompleteStore");
            }
        });

        menu.alignItemsVerticallyWithPadding(5);
        menu.x = size.width/2;
        menu.y = size.height/2;
        this.addChild(menu);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

