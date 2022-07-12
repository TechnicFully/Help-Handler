package.path = package.path .. ";../?.lua"


require "HelpHandler"

lu = require "luaunit"




local test_table = {"test1", "test2"}








function test_version()
    lu.assertErrorMsgContains("Version argument given is not a string or number", HelpHandler.version, nil)
    lu.assertErrorMsgContains("Version argument given is not a string or number", HelpHandler.version, true)
    lu.assertErrorMsgContains("Version argument given is not a string or number", HelpHandler.version, print)
    lu.assertErrorMsgContains("Version argument given is not a string or number", HelpHandler.version, test_table)
end


function test_name()
    lu.assertErrorMsgContains("App name given, but is not string type", HelpHandler.name, nil)
    lu.assertErrorMsgContains("App name given, but is not string type", HelpHandler.name, true)
    lu.assertErrorMsgContains("App name given, but is not string type", HelpHandler.name, print)
    lu.assertErrorMsgContains("App name given, but is not string type", HelpHandler.name, test_table)

    lu.assertErrorMsgContains("App name given, but is empty", HelpHandler.name, "")
end


function test_config()
    lu.assertErrorMsgContains("Invalid arguments passed", HelpHandler.config, nil, nil, nil, nil, nil)

    local invalid_arg = {}
    lu.assertErrorMsgContains("Argument extra_strings is not a boolean", HelpHandler.config, invalid_arg, true, invalid_arg, invalid_arg, invalid_arg)
    lu.assertErrorMsgContains("Argument no_arg_help is not a boolean", HelpHandler.config, true, invalid_arg, invalid_arg, invalid_arg, invalid_arg)
    lu.assertErrorMsgContains("Argument match_hyphens is not a boolean", HelpHandler.config, true, true, invalid_arg, invalid_arg, invalid_arg)
    lu.assertErrorMsgContains("Argument hyphens_only is not a boolean", HelpHandler.config, true, true, true, invalid_arg, invalid_arg)
    lu.assertErrorMsgContains("Argument unknown_arg_help is not a boolean", HelpHandler.config, true, true, true, true, invalid_arg)

    --TODO: Test all parameters with types besides nil
end


function test_handle()
    -- Nil and string values simply set the response to a default placeholder dialogue
    lu.assertErrorMsgContains("Help argument given is not a string", HelpHandler.handle, true)
    lu.assertErrorMsgContains("Help argument given is not a string", HelpHandler.handle, print)
    lu.assertErrorMsgContains("Help argument given is not a string", HelpHandler.handle, test_table)
end


function test_handle_file()
    lu.assertErrorMsgContains("File name argument given is not a string", HelpHandler.handleFile, nil)
    lu.assertErrorMsgContains("File name argument given is not a string", HelpHandler.handleFile, true)
    lu.assertErrorMsgContains("File name argument given is not a string", HelpHandler.handleFile, print)
    lu.assertErrorMsgContains("File name argument given is not a string", HelpHandler.handleFile, test_table)
end




os.exit(lu.LuaUnit.run())