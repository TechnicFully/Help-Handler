package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.info("TestApp", "1.0") --This is self-explanatory: the info() and version() functions combined for convenience
HelpHandler.handle("usage: help dialogue example")
