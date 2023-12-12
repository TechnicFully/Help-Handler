package.path = package.path .. ";../?.lua"
require "HelpHandler"





HelpHandler.info("TestApp", "1.0")
return_value = HelpHandler.handle("usage: help_dialogue_example") --This time, let's catch the return value and check what happened...

if HELP_HANDLER_ALL_MATCHED == return_value then
    print("Help and version arguments were found")
elseif HELP_HANDLER_HELP_MATCHED == return_value then
    print("Only help arguments were found")
elseif HELP_HANDLER_VERSION_MATCHED == return_value then
    print("Only version arguments were found")
elseif HELP_HANDLER_NONE_MATCHED == return_value then
    print("No arguments were found")
end
