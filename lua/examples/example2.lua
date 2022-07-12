package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.version("1.0") --This must come before the main HelpHandler.handle function, which is what actually processes arguments
HelpHandler.handle("usage: help dialogue example")
