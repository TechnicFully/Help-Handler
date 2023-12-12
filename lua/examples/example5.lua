package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.info("TestApp", "1.0") --Also note that this is optional
HelpHandler.handleFile("example_dialogue_file.txt") --Like helpHandler::handle(), this will process arguments once called as well, but gets the help dialogue from a text file
