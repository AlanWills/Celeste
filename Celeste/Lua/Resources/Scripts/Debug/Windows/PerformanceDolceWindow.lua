local PerformanceDolceWindow = 
{
    ELAPSED_TIME_THRESHOLD = 1,
    currentElapsedTime = 1,
    currentFpsString = "0"
}

---------------------------------------------------------------------------------
function PerformanceDolceWindow:render()
    self:updateElapsedTime()
    
    ImGui.text(self.currentFpsString)
end

---------------------------------------------------------------------------------
function PerformanceDolceWindow:updateElapsedTime()
    local elapsedTime = Time.getDeltaTime()
    local newCurrentElapsedTime = self.currentElapsedTime + elapsedTime

    if newCurrentElapsedTime >= self.ELAPSED_TIME_THRESHOLD then
        self.currentFpsString = string.format("%d", math.round(1 / elapsedTime))
        newCurrentElapsedTime = newCurrentElapsedTime - 1
    end
    
    self.currentElapsedTime = newCurrentElapsedTime
end

return PerformanceDolceWindow