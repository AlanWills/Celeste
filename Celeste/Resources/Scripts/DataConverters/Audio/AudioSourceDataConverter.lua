LuaComponentDataConverter.register("AudioSource", 
{
    ["Attributes"] = 
    {
        ["Sound"] = 
        {
            ["Name"] = "sound",
            ["Type"] = "string",
            ["Default Value"] = "",
            ["Is Reference"] = true,
        },
		["IsPlaying"] = 
        {
            ["Name"] = "is_playing",
            ["Type"] = "bool",
            ["Default Value"] = "false",
        },
		["IsLooping"] = 
        {
            ["Name"] = "is_looping",
            ["Type"] = "bool",
            ["Default Value"] = "false",
        },
		["Volume"] = 
        {
            ["Name"] = "volume",
            ["Type"] = "float",
            ["Default Value"] = "1",
        },
		["AudioType"] = 
        {
            ["Name"] = "audio_type",
            ["Type"] = "string",
            ["Default Value"] = "SFX",
			["Is Reference"] = true,
			["Is Required"] = true,
        }
    },

    ["SetValues"] = function(converter, audioSource)
        audioSource:setSound(converter:findAttribute("sound"):asString())
		audioSource:setLooping(converter:findAttribute("is_looping"):asBool())
		audioSource:setVolume(converter:findAttribute("volume"):asFloat())
		audioSource:setAudioType(converter:findAttribute("audio_type"):asString())
		
		if converter:findAttribute("is_playing"):asBool() then
			audioSource:play()
		end
    end
})