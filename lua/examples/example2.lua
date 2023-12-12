package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.version("1.0") --This must come before the main helpHandler::handle function, which is what processes the arguments
HelpHandler.handle("usage: help dialogue example")
