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


---- Local functions
local function match(regex, optional_regex)
    for i = 1, #arg do
        if (string.match(arg[i], regex)) then
            return true
        end

        if (string.match(arg[i], optional_regex)) then
            return true
        end    
    end

    return false
end





---- Public function

--Set your programs version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number
HelpHandler.version = function(version)
    if type(version) ~= "number" and type(version) ~= "string" then
        error("Version argument given is not a string or number")
    end

    info_t.version = version
end

--Defines your program name which will be output alongside help dialogue
HelpHandler.name = function(app_name)
    if type(app_name) ~= "string" then
        error("App name given, but is not string type")
    end
    if app_name == '' then
        error("App name given, but is empty")
    end
    
    info_t.name = app_name
end

--A single function for passing your program's name as well as its version
HelpHandler.info = function(app_name, version)
    HelpHandler.name(app_name)
    HelpHandler.ver(version)
end

--[[ For configuring functionality that might conflict/clutter other program output. The parameters are as follows...
        no_arg_help         - Print help dialogue when no arguments are given
        extra_strings       - Whether to match for h, -h, --h, v, -v and --v specifically (which may conflict with your program’s flags)
        match_hyphens       - Match arguments beginning with hyphens (i.e., "help" vs "--help")
        hyphens_only        - Only match arguments that begin with one or more hyphens
        unknown_arg_help    - Print help dialogue when an unknown argument is passed. You would typically whitelist your program’s option flags in combination with this
        disable_output      - Disable all output of HelpHandler
--]]
HelpHandler.config = function(extra_strings, no_arg_help, match_hyphens, hyphens_only, unknown_arg_help)
    if type(extra_strings) == "nil" and
        type(no_arg_help) == "nil" and
        type(match_hyphens) == "nil" and
        type(hyphens_only) == "nil" and
        type(unknown_arg_help) == "nil" then
            error("Invalid arguments passed")
    end


    if type(extra_strings) ~= "boolean" and type(extra_strings) ~= "nil" then error("Argument extra_strings is not a boolean") end
    if type(no_arg_help) ~= "boolean" and type(no_arg_help) ~= "nil" then error("Argument no_arg_help is not a boolean") end
    if type(match_hyphens) ~= "boolean" and type(match_hyphens) ~= "nil" then error("Argument match_hyphens is not a boolean") end
    if type(hyphens_only) ~= "boolean" and type(hyphens_only) ~= "nil" then error("Argument hyphens_only is not a boolean") end
    if type(unknown_arg_help) ~= "boolean" and type(unknown_arg_help) ~= "nil" then error("Argument unknown_arg_help is not a boolean") end


    if extra_strings ~= nil then options_t.extra_strings = extra_strings end
    if no_arg_help ~= nil then options_t.unknown_arg_help = no_arg_help end
    if match_hyphens ~= nil then options_t.match_hyphens = match_hyphens end
    if hyphens_only ~= nil then options_t.hyphens_only = hyphens_only end
    if unknown_arg_help ~= nil then options_t.unknown_arg_help = unknown_arg_help end
end

--This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this
HelpHandler.handle = function(help_dialogue)
    if help_dialogue == nil or help == '' then
        help_dialogue = "No usage help is available"
    end
    if type(help_dialogue) ~= "string" then
        error("Help argument given is not a string")
    end


    if (#arg == 0 and options_t.no_arg_help == true) then
        if (info_t.name ~= '' and info_t.version ~= '') then
            io.write(info_t.name, " (Version ", string.gsub(info_t.version, "%s+", ""), ")")
        elseif (info_t.name ~= '' and info_t.version == '') then
            io.write(info_t.name)
        elseif(info_t.name == '' and info_t.version ~= '') then
            io.write(info_t.version)
        end

        if (info_t.name ~= '' or info_t.version ~= '') then
            io.write("\n")
        end

        print(help_dialogue)
        return
    end

    matchHelp, matchVer = false
    matches = 0
    if (match('-*h+e+l+p+', '-*h+') == true) then
        matchHelp = true
        matches = matches + 1
    end 

    if (match('-*v+e+r+s+i+o+n+', '-*v+') == true) then
        matchVer = true
        matches = matches + 1
    end 


    if matchVer == true then
        print(info_t.version)
    end
    if matchHelp == true then
        print(help_dialogue)
    end
    
        
    if options_t.unknown_arg_help == true and #arg > 0 then
        if #arg > 1 then
            print("Unknown arguments given")
        else
            print("Unknown argument given")
        end

        return
    end

    return matches
end

--This function like helpHandler.handle, will processes and output the appropriate dialogue based on the user's input, but using a file as its dialogue source. You must pass or set any other options and info before calling this
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
