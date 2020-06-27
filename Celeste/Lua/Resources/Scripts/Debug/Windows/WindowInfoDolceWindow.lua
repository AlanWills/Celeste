local WindowInfoDolceWindow = {}

---------------------------------------------------------------------------------
function WindowInfoDolceWindow:render()
    local resolution = Viewport.getResolution()
    ImGui.text(string.format("Resolution: %d %d", resolution.x, resolution.y))

    local contentArea = Viewport.getContentArea()
    ImGui.text(string.format("Content Area: %d %d", contentArea.x, contentArea.y))
end

return WindowInfoDolceWindow