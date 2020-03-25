local Queue = {}

---------------------------------------------------------------------------------
function Queue:new ()
    self.first = 0
    self.last = 0
end
 
---------------------------------------------------------------------------------
function Queue:size(value)
    return self.last - self.first
end
  
---------------------------------------------------------------------------------
function Queue:push(value)
    local last = self.last + 1
    self.last = last
    self[last] = value
end
    
---------------------------------------------------------------------------------
function Queue:pop()
    if self:size() == 0 then error("list is empty") end

    local last = self.last
    local value = self[last]
    self[last] = nil         -- to allow garbage collection
    self.last = last - 1

    return value
end

return Queue