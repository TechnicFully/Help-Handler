package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.info("TestApp", "1.0")
HelpHandler.config(DISABLE_NO_ARGS_HELP) --Disable output of help dialogue if the user passes no arguments
return_value = HelpHandler.handle(nil) --We can also ONLY check what happened with a nil value, and no help dialogue will be output

if HELP_HANDLER_ALL_MATCHED == return_value then --This will only have output the program version (1.0)
    print("Help and version arguments were found")
elseif HELP_HANDLER_HELP_MATCHED == return_value then --This will have output nothing
    print("Only help arguments were found")
elseif HELP_HANDLER_VERSION_MATCHED == return_value then --This will also have output the program version
    print("Only version arguments were found")
elseif HELP_HANDLER_NONE_MATCHED == return_value then --This will have output nothing
    print("No arguments were found")
end
