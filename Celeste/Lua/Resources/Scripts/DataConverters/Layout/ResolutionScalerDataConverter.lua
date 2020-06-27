LuaComponentDataConverter.register("ResolutionScaler", 
{
    ["Attributes"] = 
    {
        ["TargetResolution"] = 
        {
            ["Name"] = "target_resolution",
            ["Type"] = "vec2",
            ["Default Value"] = "1920, 1080",
            ["Is Reference"] = true
        }
    },

    ["SetValues"] = function(converter, resolutionScaler)
        resolutionScaler:setTargetResolution(converter:findAttribute("target_resolution"):asVec2())
    end
})