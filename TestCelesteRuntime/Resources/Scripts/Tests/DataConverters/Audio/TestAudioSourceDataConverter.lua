local CelesteAssert = require "CelesteAssert"


local TestAudioSourceDataConverter = { }

	local FILE_PATH = path.combine(TestResources.TempDirectory, "Test.xml")

	TestAudioSourceDataConverter.name = "Test Audio Source Data Converter"

	-- Initialize/Cleanup
    ------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.testInitialize()
		Resources.unloadData(FILE_PATH)
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.testCleanup()
		Resources.unloadData(FILE_PATH)
	end

	-- Registration Tests
    ------------------------------------------------------------------------------------------------
    function TestAudioSourceDataConverter.converterRegistered()
        CelesteAssert.isTrue(LuaComponentDataConverter.hasConverter("AudioSource"))
    end

	-- Sound Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.hasSoundAttribute()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		
		CelesteAssert.hasAttribute(audioSourceDataConverter, "sound")
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.soundAttribute_IsString()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local soundAttribute = audioSourceDataConverter:findAttribute("sound")

		CelesteAssert.attributeIsString(soundAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.soundAttributeDefaultValue_IsEmptyString()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local soundAttribute = audioSourceDataConverter:findAttribute("sound")

		CelesteAssert.areEqual("", soundAttribute:asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.soundAttribute_IsNotRequired()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local soundAttribute = audioSourceDataConverter:findAttribute("sound")

		CelesteAssert.isFalse(soundAttribute:isRequired())
	end

	-- IsPlaying Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.hasIsPlayingAttribute()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.hasAttribute(audioSourceDataConverter, "is_playing")
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.isPlayingAttribute_IsBool()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local isPlayingAttribute = audioSourceDataConverter:findAttribute("is_playing")

		CelesteAssert.attributeIsBool(isPlayingAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.isPlayingAttributeDefaultValue_IsFalse()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local isPlayingAttribute = audioSourceDataConverter:findAttribute("is_playing")

		CelesteAssert.isFalse(isPlayingAttribute:asBool())
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.isPlayingAttribute_IsNotRequired()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local isPlayingAttribute = audioSourceDataConverter:findAttribute("is_playing")

		CelesteAssert.isFalse(isPlayingAttribute:isRequired())
	end

	-- IsLooping Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.hasIsLoopingAttribute()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.hasAttribute(audioSourceDataConverter, "is_looping")
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.isLoopingAttribute_IsBool()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local isPlayingAttribute = audioSourceDataConverter:findAttribute("is_looping")

		CelesteAssert.attributeIsBool(isPlayingAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.isLoopingAttributeDefaultValue_IsFalse()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local isLoopingAttribute = audioSourceDataConverter:findAttribute("is_looping")

		CelesteAssert.isFalse(isLoopingAttribute:asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.isLoopingAttribute_IsNotRequired()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local isLoopingAttribute = audioSourceDataConverter:findAttribute("is_looping")

		CelesteAssert.isFalse(isLoopingAttribute:isRequired())
	end

	-- Volume Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.hasVolumeAttribute()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.hasAttribute(audioSourceDataConverter, "volume")
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.volumeAttribute_IsFloat()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local volumeAttribute = audioSourceDataConverter:findAttribute("volume")

		CelesteAssert.attributeIsFloat(volumeAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.volumeAttributeDefaultValue_IsOne()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local volumeAttribute = audioSourceDataConverter:findAttribute("volume")

		CelesteAssert.areEqual(1, volumeAttribute:asFloat());
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.volumeAttribute_IsNotRequired()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local volumeAttribute = audioSourceDataConverter:findAttribute("volume")

		CelesteAssert.isFalse(volumeAttribute:isRequired())
	end

	-- AudioType Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.hasAudioTypeAttribute()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		
		CelesteAssert.hasAttribute(audioSourceDataConverter, "audio_type")
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.audioTypeAttribute_IsString()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local audioTypeAttribute = audioSourceDataConverter:findAttribute("audio_type")

		CelesteAssert.attributeIsString(audioTypeAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.audioTypeAttributeDefaultValue_IsSFX()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local audioTypeAttribute = audioSourceDataConverter:findAttribute("audio_type")

		CelesteAssert.areEqual("SFX", audioTypeAttribute:asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.audioTypeAttribute_IsRequired()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		local audioTypeAttribute = audioSourceDataConverter:findAttribute("audio_type")

		CelesteAssert.isTrue(audioTypeAttribute:isRequired())
	end

	-- Convert From XML Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_InputtingPathToNonExistentFile_ReturnsFalse()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isFalse(audioSourceDataConverter:convertFromXML("WubbaLubbaDubDub"))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_InputtingPathToInvalidFile_ReturnsFalse()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isFalse(audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Invalid))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_InputtingPathToValidFile_ReturnsTrue()
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Valid))
	end
	
	-- Convert Sound Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoSoundAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("sound"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoSoundAttribute_SetsSoundToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("sound"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", audioSourceDataConverter:findAttribute("sound"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_SoundAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("sound", "")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("sound"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_SoundAttribute_EmptyString_SetsSoundToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("sound", "")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("sound"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", audioSourceDataConverter:findAttribute("sound"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_SoundAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("sound", "Wubba Lubba Dub Dub")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Wubba Lubba Dub Dub", element:findAttribute("sound"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_SoundAttribute_NonEmptyString_SetsSoundToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("sound", "Wubba Lubba Dub Dub")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Wubba Lubba Dub Dub", element:findAttribute("sound"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Wubba Lubba Dub Dub", audioSourceDataConverter:findAttribute("sound"):asString())
	end

	-- Convert Is Playing Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoIsPlayingAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("is_playing"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoIsPlayingAttribute_SetsIsPlayingToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("is_playing"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(audioSourceDataConverter:findAttribute("is_playing"):asBool())
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsPlayingAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_playing", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("WubbaLubbaDubDub", element:findAttribute("is_playing"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isFalse(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsPlayingAttribute_SetToInvalidString_SetsIsPlayingToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_playing", "WubbaLubbaDubDub")
		document:insertFirstChild(element)
		
		CelesteAssert.areEqual("WubbaLubbaDubDub", element:findAttribute("is_playing"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(audioSourceDataConverter:findAttribute("is_playing"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsPlayingAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_playing", "True")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("True", element:findAttribute("is_playing"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsPlayingAttribute_SetToValidString_SetsIsPlayingToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_playing", "True")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("True", element:findAttribute("is_playing"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(audioSourceDataConverter:findAttribute("is_playing"):asBool())
	end

	-- Convert Is Looping Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoIsLoopingAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("is_looping"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoIsLoopingAttribute_SetsIsPlayingToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("is_looping"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(audioSourceDataConverter:findAttribute("is_looping"):asBool())
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsLoopingAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_looping", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("WubbaLubbaDubDub", element:findAttribute("is_looping"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isFalse(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsLoopingAttribute_SetToInvalidString_SetsIsLoopingToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_looping", "WubbaLubbaDubDub")
		document:insertFirstChild(element)
		
		CelesteAssert.areEqual("WubbaLubbaDubDub", element:findAttribute("is_looping"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(audioSourceDataConverter:findAttribute("is_looping"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsLoopingAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_looping", "True")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("True", element:findAttribute("is_looping"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_IsLoopingAttribute_SetToValidString_SetsIsLoopingToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("is_looping", "True")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("True", element:findAttribute("is_looping"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(audioSourceDataConverter:findAttribute("is_looping"):asBool())
	end
	
	-- Convert Volume Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoVolumeAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("volume"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoVolumeAttribute_SetsVolumeToOne()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("volume"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual(1, audioSourceDataConverter:findAttribute("volume"):asFloat())
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_VolumeAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("volume", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("WubbaLubbaDubDub", element:findAttribute("volume"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isFalse(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_VolumeAttribute_SetToInvalidString_SetsVolumeToOne()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("volume", "WubbaLubbaDubDub")
		document:insertFirstChild(element)
		
		CelesteAssert.areEqual("WubbaLubbaDubDub", element:findAttribute("volume"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areAlmostEqual(1, audioSourceDataConverter:findAttribute("volume"):asFloat(), 0.00001)
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_VolumeAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("volume", "0.12")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("0.12", element:findAttribute("volume"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_VolumeAttribute_SetToValidString_SetsVolumeToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music") -- Required
		element:setAttribute("volume", "0.12")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("0.12", element:findAttribute("volume"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areAlmostEqual(0.12, audioSourceDataConverter:findAttribute("volume"):asFloat(), 0.000001)
	end
	
	-- Convert Audio Type Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoAudioTypeAttribute_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("audio_type"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isFalse(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_NoAudioTypeAttribute_SetsAudioTypeToSFX()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("audio_type"))

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("SFX", audioSourceDataConverter:findAttribute("audio_type"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_AudioTypeAttribute_SetToEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("audio_type"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_AudioTypeAttribute_SetToEmptyString_SetsAudioTypeToMusic()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "")
		document:insertFirstChild(element)
		
		CelesteAssert.areEqual("", element:findAttribute("audio_type"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", audioSourceDataConverter:findAttribute("audio_type"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_AudioTypeAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Music", element:findAttribute("audio_type"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")

		CelesteAssert.isTrue(audioSourceDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.convertFromXML_AudioTypeAttribute_SetToValidString_SetsAudioTypeToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("AudioSource")
		element:setAttribute("audio_type", "Music")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Music", element:findAttribute("audio_type"):asString())

		document:saveFile(FILE_PATH)
		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Music", audioSourceDataConverter:findAttribute("audio_type"):asString())
	end

	-- SetValues Tests
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.setValues_SetsSoundToAttributeValue()
        local screen = TestAudioSourceDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local audioSource = gameObject:addComponent("AudioSource")

		CelesteAssert.isNotNil(audioSource)
	    CelesteAssert.isNil(audioSource:getSound())

		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Valid);

        CelesteAssert.hasAttribute(audioSourceDataConverter, "sound")
		CelesteAssert.areEqual("Audio\\SFX\\ButtonHover.wav", audioSourceDataConverter:findAttribute("sound"):asString())

		audioSourceDataConverter:setValues(audioSource)

		CelesteAssert.isNotNil(audioSource:getSound())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.setValues_SetsLoopingToAttributeValue()
		local screen = TestAudioSourceDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local audioSource = gameObject:addComponent("AudioSource")

		CelesteAssert.isNotNil(audioSource)
	    CelesteAssert.isFalse(audioSource:isLooping())

		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Valid);

        CelesteAssert.hasAttribute(audioSourceDataConverter, "is_looping")
		CelesteAssert.isTrue(audioSourceDataConverter:findAttribute("is_looping"):asBool())

		audioSourceDataConverter:setValues(audioSource)

		CelesteAssert.isTrue(audioSource:isLooping())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.setValues_SetsVolumeToAttributeValue()
		local screen = TestAudioSourceDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local audioSource = gameObject:addComponent("AudioSource")

		CelesteAssert.isNotNil(audioSource)
	    CelesteAssert.areEqual(1, audioSource:getVolume())

		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Valid);

        CelesteAssert.hasAttribute(audioSourceDataConverter, "volume")
		CelesteAssert.areEqual(0.5, audioSourceDataConverter:findAttribute("volume"):asFloat())

		audioSourceDataConverter:setValues(audioSource)

		CelesteAssert.areEqual(0.5, audioSource:getVolume())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.setValues_SetsAudioTypeToAttributeValue()
		local screen = TestAudioSourceDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local audioSource = gameObject:addComponent("AudioSource")

		CelesteAssert.isNotNil(audioSource)
	    CelesteAssert.areEqual("SFX", audioSource:getAudioType())

		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Valid);

        CelesteAssert.hasAttribute(audioSourceDataConverter, "audio_type")
		CelesteAssert.areEqual("Music", audioSourceDataConverter:findAttribute("audio_type"):asString())

		audioSourceDataConverter:setValues(audioSource)

		CelesteAssert.areEqual("Music", audioSource:getAudioType())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAudioSourceDataConverter.setValues_IfIsPlayingTrue_PlaysAudioSource()
		local screen = TestAudioSourceDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local audioSource = gameObject:addComponent("AudioSource")

		CelesteAssert.isNotNil(audioSource)
	    CelesteAssert.isFalse(audioSource:isPlaying())

		local audioSourceDataConverter = LuaComponentDataConverter.getConverter("AudioSource")
		audioSourceDataConverter:convertFromXML(AudioSourceLoadingResources.Valid);

        CelesteAssert.hasAttribute(audioSourceDataConverter, "is_playing")
		CelesteAssert.isTrue(audioSourceDataConverter:findAttribute("is_playing"):asBool())

		audioSourceDataConverter:setValues(audioSource)

		CelesteAssert.isTrue(audioSource:isPlaying())
	end


return TestAudioSourceDataConverter