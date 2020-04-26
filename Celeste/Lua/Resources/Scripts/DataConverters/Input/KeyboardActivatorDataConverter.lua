LuaComponentDataConverter.register("KeyboardActivator", 
{
    ["Attributes"] = 
    {
        ["ActivationKey"] = 
        {
            ["Name"] = "activation_key",
            ["Type"] = "string",
            ["Default Value"] = "",
            ["Is Reference"] = true,
        },
        ["DeactivationKey"] = 
        {
            ["Name"] = "deactivation_key",
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
        },
        ["Target"] = 
        {
            ["Name"] = "target",
            ["Type"] = "string",
            ["Is Reference"] = true,
            ["Is Required"] = true
        }
    },

    ["SetValues"] = function(converter, activator)
        activator:setActivationKey(converter:findAttribute("activation_key"):asString())
        activator:setDeactivationKey(converter:findAttribute("deactivation_key"):asString())
        activator:setInputMode(converter:findAttribute("input_mode"):asString())
    end
})