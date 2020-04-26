Dolce.instance:registerWindow("Performance", 
{ 
    render = function() 
        local elapsedTime = Time.getDeltaTime()
        local fps = math.floor(1 / elapsedTime)
        
        ImGui.Text(string.format("%d", fps))
    end 
})