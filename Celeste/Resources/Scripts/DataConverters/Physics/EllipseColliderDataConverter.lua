LuaComponentDataConverter.register("EllipseCollider", 
{
    ["Attributes"] = 
    {
        ["Dimensions"] = 
        {
            ["Name"] = "dimensions",
            ["Type"] = "vec2",
            ["Default Value"] = "0, 0",
            ["Is Required"] = true,
            ["Is Reference"] = true
        },
        ["IsTrigger"] = 
        {
            ["Name"] = "is_trigger",
            ["Type"] = "bool",
            ["Default Value"] = false,
        },
        ["Offset"] = 
        {
            ["Name"] = "offset",
            ["Type"] = "vec2",
            ["Default Value"] = "0, 0",
            ["Is Reference"] = true
        }
    },

    ["SetValues"] = function(converter, collider)
        collider:setDimensions(converter:findAttribute("dimensions"):asVec2())
        collider:setIsTrigger(converter:findAttribute("is_trigger"):asBool())
        collider:setOffset(converter:findAttribute("offset"):asVec2())
    end
})