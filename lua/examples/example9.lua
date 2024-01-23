package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.info("TestApp", "1.0")
return_value = HelpHandler.handle() --This however, will print out text saying that no help dialogue has been set

if HELP_HANDLER_ALL_MATCHED == return_value then
    print("Help and version arguments were found")
elseif HELP_HANDLER_HELP_MATCHED == return_value then --This will have output "No usage help is available"
    print("Only help arguments were found")
elseif HELP_HANDLER_VERSION_MATCHED == return_value then
    print("Only version arguments were found")
elseif HELP_HANDLER_NONE_MATCHED == return_value then
    print("No arguments were found")
end
