LuaComponentDataConverter.register("KeyboardVisibility", 
{
    ["Attributes"] = 
    {
        ["VisibilityKey"] = 
        {
            ["Name"] = "visibility_key",
            ["Type"] = "string",
            ["Default Value"] = "",
            ["Is Reference"] = true,
        },
        ["InvisibilityKey"] = 
        {
            ["Name"] = "invisibility_key",
            ["Type"] = "string",
            ["Default Value"] = "",
            ["Is Reference"] = true,
        },
        ["InputMode"] = 
        {
            ["Name"] = "input_mode",
            ["Type"] = "string",
            ["Default Value"] = "Toggle",
            ["Is Reference"] = true,
        }
    },

    ["SetValues"] = function(converter, visibility)
        visibility:setVisibilityKey(converter:findAttribute("visibility_key"):asString())
        visibility:setInvisibilityKey(converter:findAttribute("invisibility_key"):asString())
        visibility:setInputMode(converter:findAttribute("input_mode"):asString())
    end
})