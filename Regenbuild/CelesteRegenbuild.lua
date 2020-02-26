local xml2lua = require("xml2lua")
--Uses a handler that converts the XML to a Lua table
local handler = require("xmlhandler.tree")

--Instantiates the XML parser
local parser = xml2lua.parser(handler)
local xml = xml2lua.loadFile("C:\\Repos\\ModernCocoaFarmer\\ModernCocoaFarmer\\Resources\\Data\\Settings\\WindowSettings.asset")
print(xml)
--parser:parse(xml)
--xml2lua.printable(handler.root)