local PerformanceDolceWindow = require 'Debug.Windows.PerformanceDolceWindow'
local InputDolceWindow = require 'Debug.Windows.InputDolceWindow'
local WindowInfoDolceWindow = require 'Debug.Windows.WindowInfoDolceWindow'

Dolce.instance:addWindow("Performance", PerformanceDolceWindow)
Dolce.instance:addWindow("Input", InputDolceWindow)
Dolce.instance:addWindow("Window Info", WindowInfoDolceWindow)