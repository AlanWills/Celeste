LuaComponentDataConverter.register("Canvas", 
{
    ["Attributes"] = 
    {
        ["ProjectionMode"] = 
        {
            ["Name"] = "projection_mode",
            ["Type"] = "string",
            ["Default Value"] = "Perspective",
        },
        ["Dimensions"] = 
        {
            ["Name"] = "dimensions",
            ["Type"] = "vec2",
            ["Default Value"] = "1, 1",
			      ["Is Reference"] = true,
            ["Is Required"] = true;
        }
    },

    ["SetValues"] = function(converter, canvas)
		canvas:setProjectionMode(converter:findAttribute("projection_mode"):asString())
        canvas:setDimensions(converter:findAttribute("dimensions"):asVec2())
    end
})