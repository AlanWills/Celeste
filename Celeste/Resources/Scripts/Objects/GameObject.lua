----------------------------------------------------------------------------------------
function GameObject.findComponent(go, componentName)
    local i = 0
    local componentCount = go:getComponentCount()
    
    while i < componentCount do
        local component = go:getComponent(i):as(componentName)
        if component ~= nil then
            return component
        end

        i = i + 1
    end

    return nil
end

----------------------------------------------------------------------------------------
function GameObject.findChild(go, childName)
    local i = 0
    local childCount = go:getChildCount()
    
    while i < childCount do
        local child = go:getChild(i)
        if child:getName() == childName then
            return child
        end

        i = i + 1
    end

    return nil
end

----------------------------------------------------------------------------------------
function GameObject.setupChildLeftButtonUpCallback(parent, childName, callback, extraArgs)
    local button = parent:findChild(childName)
    local buttonInteractionHandler = button:findComponent("MouseInteractionHandler")
    buttonInteractionHandler:subscribeOnLeftButtonUpCallback(callback, extraArgs or nil)
end