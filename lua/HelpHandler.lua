--[[
MIT License

Copyright (c) 2022 TechnicFully
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--]]


--██╗   ██╗███████╗███████╗██████╗     ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
--██║   ██║██╔════╝██╔════╝██╔══██╗    ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
--██║   ██║███████╗█████╗  ██████╔╝    ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
--██║   ██║╚════██║██╔══╝  ██╔══██╗    ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
--╚██████╔╝███████║███████╗██║  ██║     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
-- ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝
-- These should be the only relevant variables to any library user not trying to change functionality

HELP_HANDLER_ALL_MATCHED = 1
HELP_HANDLER_HELP_MATCHED = 2
HELP_HANDLER_VERSION_MATCHED = 3
HELP_HANDLER_NONE_MATCHED = 4

DISABLE_NO_ARGS_HELP     = 00000001
DISABLE_EXTRA_STRINGS    = 00000010
DISABLE_MATCH_HYPHENS    = 00000100
ENABLE_UNKNOWN_ARGS_HELP = 00000200 --Value being higher than DISABLE_MATCH_HYPHENS is intentional, to override in case both are set
ENABLE_HYPHENS_ONLY      = 00001000




--██╗███╗   ██╗████████╗███████╗██████╗ ███╗   ██╗ █████╗ ██╗         ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
--██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗████╗  ██║██╔══██╗██║         ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
--██║██╔██╗ ██║   ██║   █████╗  ██████╔╝██╔██╗ ██║███████║██║         ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
--██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗██║╚██╗██║██╔══██║██║         ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
--██║██║ ╚████║   ██║   ███████╗██║  ██║██║ ╚████║██║  ██║███████╗     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
--╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝
HelpHandler = {}


local info_t = {
    name        = "",
    version     = "No version is available",
}

local options_t = {
    no_arg_help      = true,
    extra_strings    = true,
    match_hyphens    = true,
    hyphens_only     = false,
    unknown_arg_help = false,
}

local HELP_HANDLER_DEBUG = false --Enable to print debug messaging, or comment out to enable debug messaging AND dialogue output

local DEBUG_TRACE
local DEBUG_INFO
local DEBUG_WARN
local DEBUG_ERR




---- ██╗      ██████╗  ██████╗ █████╗ ██╗         ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
---- ██║     ██╔═══██╗██╔════╝██╔══██╗██║         ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
---- ██║     ██║   ██║██║     ███████║██║         █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
---- ██║     ██║   ██║██║     ██╔══██║██║         ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
---- ███████╗╚██████╔╝╚██████╗██║  ██║███████╗    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
---- ╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝                                                                                                                     
local function debug_print(msg, msg_type)
    if HELP_HANDLER_DEBUG == false then
        return
    end

    if msg_type == DEBUG_TRACE then
        io.write("HELP HANDLER (TRACE):  ")
        print(msg)
    elseif msg_type == DEBUG_INFO then
        io.write("HELP HANDLER (INFO):   ")
        print(msg)
    elseif msg_type == DEBUG_WARN then
        io.write("HELP HANDLER (WARN):   ")
        print(msg)
    elseif msg_type == DEBUG_ERR then
        io.write("HELP HANDLER (ERROR)   ")
        print(msg)
    end
end


local function match(regex, optional_regex)
    for i = 1, #arg do
        debug_print("Processing argument with regex (ROUND " .. tostring(i) .. " of " .. #arg .. ")")

        if (string.match(arg[i]:lower(), regex)) then
            return true
        end

        if options_t.extra_strings == true then
            if optional_regex ~= nil then
                debug_print("Processing argument with secondary regex (ROUND " .. tostring(i) .. " of " .. #arg .. ")")
                if (string.match(arg[i]:lower(), optional_regex)) then
                    return true
                end
            end
        end
    end

    return false
end


local function print_pipe(s) --Wrapper function for io.write() is to purely avoid cluttering test suite output when necesary
    if HELP_HANDLER_DEBUG == true then
        return
    end

    if s ~= nil then --Avoid printing help or version dialogue when they are not set
        print(s)
    end
end




---- ██████╗ ██╗   ██╗██████╗ ██╗     ██╗ ██████╗    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
---- ██╔══██╗██║   ██║██╔══██╗██║     ██║██╔════╝    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
---- ██████╔╝██║   ██║██████╔╝██║     ██║██║         █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
---- ██╔═══╝ ██║   ██║██╔══██╗██║     ██║██║         ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
---- ██║     ╚██████╔╝██████╔╝███████╗██║╚██████╗    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
---- ╚═╝      ╚═════╝ ╚═════╝ ╚══════╝╚═╝ ╚═════╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝                                                                                                                          
-- Set your programs version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number
-- Throws an error if the given version is not a string or number type
HelpHandler.version = function(version)
    if type(version) ~= "number" and type(version) ~= "string" then
        error("Version argument given is not a string or number")
    end

    debug_print("Setting given program version")
    info_t.version = version
end


-- Defines your program name which will be output alongside help dialogue
-- Throws an error if the given app_name is not a string, or empty
HelpHandler.name = function(app_name)
    if type(app_name) ~= "string" then
        error("App name given, but is not string type")
    end
    if app_name == '' then
        error("App name given, but is empty")
    end
    
    debug_print("Setting given program name")
    info_t.name = app_name
end


-- A single function for passing your program's name as well as its version
-- Returns the same values as HelpHandler.name() and HelpHandler.version()
-- Throws the same errors as HelpHandler.name() and HelpHandler.version()
HelpHandler.info = function(app_name, version)
    HelpHandler.name(app_name)
    HelpHandler.version(version)
end


--[[ For configuring functionality that might conflict/clutter other program output. You may pass the following flags...
        DISABLE_NO_ARGS_HELP     - Disable printing of help dialogue when no arguments are given
        DISABLE_EXTRA_STRINGS    - Disable matching of h, -h, --h, v, -v and --v which may conflict with your program’s flags
        DISABLE_MATCH_HYPHENS    - Disable matching of arguments with hyphens (i.e., Help Handler will match "help", but not "--help")
        ENABLE_HYPHENS_ONLY      - Only match arguments that begin with one or more hyphens
        ENABLE_UNKNOWN_ARGS_HELP - Print help dialogue when an unknown argument is passed. You would typically whitelist your program’s option flags in combination with this
--]]
-- Throws an error if a non-number type is passed, or an invalid flag is given
HelpHandler.config = function(option_flags)
    if type(option_flags) ~= "number" then
        error("Invalid argument type passed. Must be a number")
    end

    if option_flags & DISABLE_NO_ARGS_HELP then options_t.no_arg_help = false end
    if option_flags & DISABLE_EXTRA_STRINGS then options_t.extra_strings = false end
    if option_flags & DISABLE_MATCH_HYPHENS then options_t.match_hyphens = false end
    if option_flags & ENABLE_HYPHENS_ONLY then options_t.hyphens_only = true end
    if option_flags & ENABLE_UNKNOWN_ARGS_HELP then options_t.unknown_arg_help = true end
    
    if option_flags ~= (option_flags & DISABLE_NO_ARGS_HELP) and
        option_flags ~= (option_flags & DISABLE_EXTRA_STRINGS) and
        option_flags ~= (option_flags & DISABLE_MATCH_HYPHENS) and
        option_flags ~= (option_flags & ENABLE_UNKNOWN_ARGS_HELP) and
        option_flags ~= (option_flags & ENABLE_HYPHENS_ONLY) then
            error("Unknown flag passed")
    end
end


-- This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this
-- Returns HELP_HANDLER_ALL_MATCHED, HELP_HANDLER_HELP_MATCHED, HELP_HANDLER_VERSION_MATCHED, or HELP_HANDLER_NONE_MATCHED
HelpHandler.handle = function(help_dialogue)
    if help_dialogue ~= nil then
        if type(help_dialogue) ~= "string" then 
            error("Invalid help dialogue argument type given, must be nil, or a string")
        end
    end


    --Conditionally set help dialogue
    if help_dialogue == nil then
        debug_print("No help dialogue was given")

        --We want to avoid printing anything if the user only plans on using this library for detecting arguments, so remove the version dialogue unless it was set by the user
        if info_t.version == "No version is available" then
            debug_print("No version or help dialogue was set, clearing version string...")
            info_t.version = ""
        end
    else 
        local help_dialogue_trimmed = help_dialogue:gsub("%s+", "")
        if help_dialogue == '' then
            help_dialogue = "No usage help is available"
        end
    end



    if (#arg == 0 and options_t.no_arg_help == true) then
        debug_print("No arguments were given. Printing help dialogue and exiting...")
        print_pipe(help_dialogue)
        return HELP_HANDLER_NONE_MATCHED
    end


    --Process arguments
    local matchHelp, matchVer = false
    if (match('-*h+e+l+p+', '^-*h+$') == true) then
        debug_print("Matched help argument")
        matchHelp = true
    end 

    if (match('-*v+e+r+s+i+o+n+', '^-*v+$') == true) then
        debug_print("Matched version argument")
        matchVer = true
    end


    --Finish if arguments were matched
    if matchHelp == true and matchVer == true then
        debug_print("Outputting help and version info")
        print_pipe(info_t.version)
        print_pipe(help_dialogue)
        return HELP_HANDLER_ALL_MATCHED
    elseif matchHelp == true then
        debug_print("Outputting help info")
        print_pipe(help_dialogue)
        return HELP_HANDLER_HELP_MATCHED
    elseif matchVer == true then
        debug_print("Outputting version info")
        print_pipe(info_t.version)
        return HELP_HANDLER_VERSION_MATCHED
    end
    
    
    --Finish if no arguments were matched
    if options_t.unknown_arg_help == true and #arg > 0 then
        debug_print("Unknown arguments were given. Exiting...")

        if #arg > 1 then
            print_pipe("Unknown arguments given")
        else
            print_pipe("Unknown argument given")
        end

        return HELP_HANDLER_NONE_MATCHED
    end


    debug_print("No arguments were matched. Exiting...")
    return HELP_HANDLER_NONE_MATCHED
end


-- This function like helpHandler.handle, will processes and output the appropriate dialogue based on the user's input, but using a file as its dialogue source. You must pass or set any other options and info before calling this
-- Throws an error if the given file_name is not a string, or could not be opened (does not exist, etc.)
HelpHandler.handleFile = function(file_name)
    if type(file_name) ~= "string" then
        error("File name argument given is not a string")
    end
    
    local f = io.open(file_name, "r")
    if not f then
        error("File could not be opened")
    end

    local content = f:read("*all")
    return HelpHandler.handle(content)
end
