
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()
    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    sdkbox.PluginChartboost:init()
    sdkbox.PluginChartboost:setListener(function(args)
        if "onChartboostCached" == args.func then
            printf("onChartboostCached: %s", args.name)
        elseif "onChartboostShouldDisplay" == args.func then
            printf("onChartboostShouldDisplay: %s", args.name)
        elseif "onChartboostDisplay" == args.func then
            printf("onChartboostDisplay: %s", args.name)
        elseif "onChartboostDismiss" == args.func then
            printf("onChartboostDismiss: %s", args.name)
        elseif "onChartboostClose" == args.func then
            printf("onChartboostClose: %s", args.name)
        elseif "onChartboostClick" == args.func then
            printf("onChartboostClick: %s", args.name)
        elseif "onChartboostReward" == args.func then
            printf("onChartboostReward: %s, %s", args.name, tostring(args.reward))
        elseif "onChartboostFailedToLoad" == args.func then
            printf("onChartboostFailedToLoad: %s, %s", args.name, tostring(args.e))
        elseif "onChartboostFailToRecordClick" == args.func then
            printf("onChartboostFailToRecordClick: %s, %s", args.name, tostring(args.e))
        elseif "onChartboostConfirmation" == args.func then
            print("onChartboostConfirmation")
        elseif "onChartboostCompleteStore" == args.func then
            print("onChartboostCompleteStore")
        end
    end)

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("show ads"):onClicked(function()
            sdkbox.PluginChartboost:show("Default")
            print("sdkbox.PluginChartboost:show(\"Default\")");
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

return MainScene
