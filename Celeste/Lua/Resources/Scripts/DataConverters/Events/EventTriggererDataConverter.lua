LuaComponentDataConverter.register("EventTriggerer", 
{
    ["Attributes"] = 
    {
        ["TriggerMode"] = 
        {
            ["Name"] = "trigger_mode",
            ["Type"] = "string",
            ["Default Value"] = "Once"
        },
		["TriggerDelay"] = 
        {
            ["Name"] = "trigger_delay",
            ["Type"] = "float",
            ["Default Value"] = "-1",
        },
		["TriggerKey"] = 
        {
            ["Name"] = "trigger_key",
            ["Type"] = "string",
            ["Default Value"] = "",
            ["Is Reference"] = true,
        }
    },

    ["SetValues"] = function(converter, eventTriggerer)
        eventTriggerer:setTriggerMode(converter:findAttribute("trigger_mode"):asString())
        eventTriggerer:setTriggerDelay(converter:findAttribute("trigger_delay"):asFloat())

        local triggerKey = converter:findAttribute("trigger_key"):asString()
        if triggerKey ~= "" then
            eventTriggerer:setTriggerKey(triggerKey)
        end
    end
})