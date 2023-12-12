package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.name("TestApp") --This sets the application name and must also come before helpHandler::handle(), however it doesn't matter if it's called before or after helpHandler::version()
HelpHandler.version("1.0")
HelpHandler.handle("usage: help dialogue example")
