LuaComponentDataConverter.register("Animator", 
{
    ["Attributes"] = 
    {
        ["SpriteSheetDimensions"] = 
        {
            ["Name"] = "sprite_sheet_dimensions",
            ["Type"] = "uvec2",
            ["Default Value"] = "1, 1",
            ["Is Required"] = true,
            ["Is Reference"] = true
        },
        ["Looping"] = 
        {
            ["Name"] = "looping",
            ["Type"] = "bool",
            ["Default Value"] = "true"
        },
        ["SecondsPerFrame"] = 
        {
            ["Name"] = "seconds_per_frame",
            ["Type"] = "float",
            ["Default Value"] = "0.1";
        },
        ["PlayImmediately"] = 
        {
            ["Name"]= "play_immediately",
            ["Type"] = "bool",
            ["Default Value"] = "true"
        }
    },

    ["SetValues"] = function(converter, animator)
        animator:setSpriteSheetDimensions(converter:findAttribute("sprite_sheet_dimensions"):asUVec2())
        animator:setLooping(converter:findAttribute("looping"):asBool())
        animator:setSecondsPerFrame(converter:findAttribute("seconds_per_frame"):asFloat())

        if converter:findAttribute("play_immediately"):asBool() then
            animator:play()
        end
    end
})