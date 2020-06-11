LuaComponentDataConverter.register("ProgressBar", 
{
    ["Attributes"] = 
    {
		["Progress"] = 
        {
            ["Name"] = "progress",
            ["Type"] = "float",
            ["Default Value"] = "0",
        },
		["Min"] = 
        {
            ["Name"] = "min",
            ["Type"] = "float",
            ["Default Value"] = "0",
        },
		["Max"] = 
        {
            ["Name"] = "max",
            ["Type"] = "float",
            ["Default Value"] = "100",
        }
    },

    ["SetValues"] = function(converter, progress)
        progress:setMin(converter:findAttribute("min"):asFloat())
		progress:setMax(converter:findAttribute("max"):asFloat())
		progress:setProgress(converter:findAttribute("progress"):asFloat())
    end
})