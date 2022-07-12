package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.name("TestApp") --This must also come before HelpHandler.handle, however it doesn't matter if it's called/set before or after HelpHandler.version()
HelpHandler.version("1.0")
HelpHandler.handle("usage: help dialogue example")
