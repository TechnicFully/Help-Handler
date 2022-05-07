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
    version     = "",
}

local options_t = {
    no_arg_help      = true,
    extra_strings    = true,
    unknown_arg_help = false,
}




HelpHandler.version = function(version)
    if type(version) ~= "number" and type(version) ~= "string" then
        error("Version argument given is not a string or number")
    end

    info_t.version = version
end 
HelpHandler.ver = function(version)
    HelpHandler.version(version)
end 

HelpHandler.config = function(extra_strings, no_arg_help, unknown_arg_help)
    if type(extra_strings) ~= "boolean" and type(extra_strings) ~= "number" then error("Argument no_arg_help is not a bool or number") end
    if type(no_arg_help) ~= "boolean" and type(no_arg_help) ~= "number" then error("Argument no_arg_help is not a bool or number") end
    if type(unknown_arg_help) ~= "boolean" and type(unknown_arg_help) ~= "number" then error("Argument no_arg_help is not a bool or number") end
    
    if extra_strings ~= nil then options_t.extra_strings = extra_strings end
    if no_arg_help ~= nil then options_t.unknown_arg_help = no_arg_help end
    if unknown_arg_help ~= nil then options_t.unknown_arg_help = unknown_arg_help end
end

HelpHandler.name = function(app_name)
    if app_name == nil then
        error("App name called, but is nil")
    end
    if type(app_name) ~= "string" then
        error("App name given, but is not string type")
    end
    if app_name == '' then
        error("App name given, but is empty")
    end
    
    info_t.name = app_name
end

HelpHandler.info = function(app_name, version)
    HelpHandler.name(app_name)
    HelpHandler.ver(version)
end

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

    matches = 0
    matchHelp, matchVer = false
    for i = 1, #arg do
        if (string.match(arg[i], '-*h+e+l+p+')) then
            matchHelp = true
            matches = matches + 1
        end 
        if (options_t.extra_strings == true) then
            if (string.match(arg[i], '-*h+')) then
                matchHelp = true
                matches = matches + 1
            end
        end

        if (string.match(arg[i], '-*v+e+r+s+i+o+n+')) then
            matchVer = true
            matches = matches + 1
        end 
        if (options_t.extra_strings == true) then
            if (string.match(arg[i], '-*v+')) then
                matchVer = true
                matches = matches + 1
            end
        end
    end

    if matchVer == true then
        print(info_t.version)
    end
    if matchHelp == true then
        print(help_dialogue)
    end
    
    if unknown_arg ~= nil and type(unknown_arg) ~= "string" then
        error("Unknown argument parameter was given, but is not type string")
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

HelpHandler.handleFile = function(file_name)
    local f = io.open(file_name, "r")
    if not f then
        error("File could not be opened")
    end

    local content = f:read("*all")
    return HelpHandler.handle(content)
end
