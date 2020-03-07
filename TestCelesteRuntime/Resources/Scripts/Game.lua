-- Load the Scene
local screenPath = path.combine(Resources.getResourcesDirectory(), "Data", "Scenes", "UnitTestScene.asset")
local screen = Scene.load(screenPath)

log("Loaded Scene")

if (screen == nil) then
    log("Scene could not be loaded")
    exit()
    return
end

local noGui = true

if noGui then
    -- Find the GameObject with the TestDiscover component on it
    local testDiscovererGameObject = screen:findGameObject("TestDiscoverer")
    if (testDiscovererGameObject == nil) then
        log("TestDiscover GameObject could not be found")
        exit()
        return
    end

    -- Find the TestDiscoverer component
    local testDiscoverer = testDiscovererGameObject:getComponent(0):as("TestDiscoverer")
    if (testDiscoverer == nil) then
        log("TestDiscoverer Component could not be found")
        exit()
        return
    end

    local testResults = testDiscoverer:executeTests()
    local testResultsPath = path.combine(Resources.getResourcesDirectory(), "TestResults.xml")

    -- Save the test results
    if (not testResults:saveFile(testResultsPath)) then
        log("Error saving test results")
        exit()
        return
    end

    exit()
end