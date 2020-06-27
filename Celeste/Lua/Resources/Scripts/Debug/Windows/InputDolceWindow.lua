local InputDolceWindow = {}

---------------------------------------------------------------------------------
function InputDolceWindow:render()
    local mousePosition = Mouse.getPosition()
    ImGui.text(string.format("Mouse Position: %d %d", mousePosition.x, mousePosition.y))
end

return InputDolceWindow