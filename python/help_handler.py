'''
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
'''

from __future__ import print_function #For compatibility between Python 2 and 3 print functions
import os
import sys, re, warnings


#██╗   ██╗███████╗███████╗██████╗     ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
#██║   ██║██╔════╝██╔════╝██╔══██╗    ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
#██║   ██║███████╗█████╗  ██████╔╝    ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
#██║   ██║╚════██║██╔══╝  ██╔══██╗    ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
#╚██████╔╝███████║███████╗██║  ██║     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
# ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝
#Magic numbers
found_all     = 0x0a4f781db
found_help    = 0x7b0acb244
found_version = 0xaa502bf21
found_none    = 0x819657e71




#██╗███╗   ██╗████████╗███████╗██████╗ ███╗   ██╗ █████╗ ██╗         ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
#██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗████╗  ██║██╔══██╗██║         ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
#██║██╔██╗ ██║   ██║   █████╗  ██████╔╝██╔██╗ ██║███████║██║         ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
#██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗██║╚██╗██║██╔══██║██║         ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
#██║██║ ╚████║   ██║   ███████╗██║  ██║██║ ╚████║██║  ██║███████╗     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
#╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝                                                                                                                                    
_extraStringsGlob = True
_noArgHelpGlob = True
_matchHyphens = True
_hyphensOnly = False
_unknownArgHelpGlob = False
_disableOutput = False


_verGlob = "No version available"
_appNameGlob = ""




class HelpHandler():
    #██████╗ ██████╗ ██╗██╗   ██╗ █████╗ ████████╗███████╗    ███╗   ███╗███████╗████████╗██╗  ██╗ ██████╗ ██████╗ ███████╗
    #██╔══██╗██╔══██╗██║██║   ██║██╔══██╗╚══██╔══╝██╔════╝    ████╗ ████║██╔════╝╚══██╔══╝██║  ██║██╔═══██╗██╔══██╗██╔════╝
    #██████╔╝██████╔╝██║██║   ██║███████║   ██║   █████╗      ██╔████╔██║█████╗     ██║   ███████║██║   ██║██║  ██║███████╗
    #██╔═══╝ ██╔══██╗██║╚██╗ ██╔╝██╔══██║   ██║   ██╔══╝      ██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║   ██║██║  ██║╚════██║
    #██║     ██║  ██║██║ ╚████╔╝ ██║  ██║   ██║   ███████╗    ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝██████╔╝███████║
    #╚═╝     ╚═╝  ╚═╝╚═╝  ╚═══╝  ╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝
    @staticmethod
    def __print(string, newline=True):
        global _disableOutput
        if _disableOutput != True:
            if newline == True:
                print(string)
            else:
                print(string, end='')


    #██████╗ ██╗   ██╗██████╗ ██╗     ██╗ ██████╗    ███╗   ███╗███████╗████████╗██╗  ██╗ ██████╗ ██████╗ ███████╗
    #██╔══██╗██║   ██║██╔══██╗██║     ██║██╔════╝    ████╗ ████║██╔════╝╚══██╔══╝██║  ██║██╔═══██╗██╔══██╗██╔════╝
    #██████╔╝██║   ██║██████╔╝██║     ██║██║         ██╔████╔██║█████╗     ██║   ███████║██║   ██║██║  ██║███████╗
    #██╔═══╝ ██║   ██║██╔══██╗██║     ██║██║         ██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║   ██║██║  ██║╚════██║
    #██║     ╚██████╔╝██████╔╝███████╗██║╚██████╗    ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝██████╔╝███████║
    #╚═╝      ╚═════╝ ╚═════╝ ╚══════╝╚═╝ ╚═════╝    ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝

    ''' For configuring functionality that might conflict/clutter other program output. The parameters are as follows...
          no_arg_help         - Print help dialogue when no arguments are given
          extra_strings       - Whether to match for h, -h, --h, v, -v and --v specifically (which may conflict with your program’s flags)
          match_hyphens       - Match arguments beginning with hyphens (i.e., "help" vs "--help")
          hyphens_only        - Only match arguments that begin with one or more hyphens
          unknown_arg_help    - Print help dialogue when an unknown argument is passed. You would typically whitelist your program’s option flags in combination with this
          disable_output      - Disable all output of HelpHandler
    '''
    @staticmethod
    def config(no_arg_help=True, extra_strings=True, match_hyphens=True, hyphens_only=False, unknown_arg_help=False, disable_output=False):
        #Error checking
        if not (isinstance(no_arg_help, int)):
            raise TypeError("argument no_arg_help is not of type bool or int")
        if not (isinstance(extra_strings, int)):
            raise TypeError("argument extra_strings is not of type bool or int")
        if not (isinstance(match_hyphens, int)):
            raise TypeError("argument match_hyphens is not of type bool or int")
        if not (isinstance(hyphens_only, int)):
            raise TypeError("argument hyphens_only is not of type bool or int")
        if not (isinstance(unknown_arg_help, int)):
            raise TypeError("argument unknown_arg_help is not of type bool or int")
        if not (isinstance(disable_output, int)):
            raise TypeError("argument disable_output is not of type bool or int")


        global _extraStringsGlob
        global _noArgHelpGlob
        global _unknownArgHelpGlob
        global _matchHyphens
        global _hyphensOnly
        global _disableOutput

        _extraStringsGlob   = extra_strings
        _noArgHelpGlob      = no_arg_help
        _matchHyphens       = match_hyphens
        _hyphensOnly        = hyphens_only
        _unknownArgHelpGlob = unknown_arg_help
        _disableOutput      = disable_output


    # Set your program version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number
    # Throws an error if the given version is not a str / basestring, int, or float type
    @staticmethod
    def version(version):
        #Error checking
        if sys.version_info.major >= 3:
            if not (isinstance(version, str), isinstance(version, int), isinstance(version, float)):
                raise TypeError("argument version is not of type string, int, or double")
        elif sys.version_info.major <= 2:
            if not (isinstance(version, basestring), isinstance(version, int), isinstance(version, float)):
                raise TypeError("argument version is not of type string, int, or double")

        if isinstance(version, list) or isinstance(version, tuple) or isinstance(version, dict):
            raise TypeError("argument version is not of type string, int, or double")

        if type(version) == type(True):
            raise TypeError("argument version should not be of type boolean")

        if not version:
            raise ValueError("given version string is empty")


        global _verGlob
        _verGlob = version

    # Defines your program name which will be output alongside help dialogue
    # Throws an error if the given app_name is not a string, or empty
    @staticmethod
    def name(app_name):
        #Error checking
        if sys.version_info.major >= 3:
            if not (isinstance(app_name, str)):
                raise TypeError("argument app name is not of type string")
        elif sys.version_info.major <= 2:
            if not (isinstance(app_name, basestring)):
                raise TypeError("argument app name is not of type basestring")

        if not app_name:
            raise ValueError("given app name string is empty")
        

        global _appNameGlob
        _appNameGlob = app_name

    # A single function for passing your program's name as well as its version
    # Returns the same values as HelpHandler.name() and HelpHandler.version()
    # Throws the same errors as HelpHandler.name() and HelpHandler.version()
    @staticmethod
    def info(app_name, version):
        HelpHandler.name(app_name)
        HelpHandler.version(version)

    # This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this
    # Returns found_all, found_help, found_version, or found_none
    @staticmethod
    def handle(help_dialogue):
        global _disableOutput
        
        if not help_dialogue:
            help_dialogue = "No usage help is available"
        if (len(sys.argv) == 1) and (_noArgHelpGlob == True):
            HelpHandler.__print(help_dialogue)
            return found_none
        
        #Set regex
        numHyphens = 0
        if _matchHyphens == False:
            numHyphens = 1
        numHyphens = str(numHyphens)

        helpRegex    = "-{" + numHyphens + ",}h{1,}e{1,}l{1,}p{1,}(.*)"
        versionRegex = "-{" + numHyphens + ",}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)"

        global _extraStringsGlob
        if _extraStringsGlob == True:
            helpRegex    += "|-{" + numHyphens + ",}h{1,}$"
            versionRegex += "|^-{" + numHyphens + ",}v$"
            

        #Match and count arguments
        foundMatchHelp = False
        foundMatchVer  = False
        matches = 0
        for arg in sys.argv[1:]:
            if re.match(versionRegex, arg, flags=re.IGNORECASE):
                foundMatchVer = True
                matches += 1
        for arg in sys.argv[1:]:
            if re.match(helpRegex, arg, flags=re.IGNORECASE):
                foundMatchHelp = True
                matches += 1

        #Print respective output if arguments found and return number of args matched
        if _disableOutput != True:
            global _appNameGlob
            global _verGlob
            if foundMatchHelp and foundMatchVer:
                if _appNameGlob:
                    HelpHandler.__print(_appNameGlob + " ", False)

                HelpHandler.__print(_verGlob)
                HelpHandler.__print(help_dialogue)
            elif foundMatchHelp == True:
                if _appNameGlob:
                    HelpHandler.__print(_appNameGlob + " ", False)
                HelpHandler.__print(help_dialogue)
            elif foundMatchVer == True:
                HelpHandler.__print(_verGlob)


        #Return
        if foundMatchHelp and foundMatchVer:
            return found_all
        if foundMatchHelp:
            return found_help
        elif foundMatchVer:
            return found_version
        else:
            #Nothing matched
            if _unknownArgHelpGlob == True and _disableOutput != True:
                if (len(sys.argv) > 2):
                    HelpHandler.__print("Unknown arguments given")
                else:
                    HelpHandler.__print("Unknown argument given")

            return found_none

    # This function like helpHandler.handle, will processes and output the appropriate dialogue based on the user's input, but using a file as its dialogue source. You must pass or set any other options and info before calling this
    # Throws an error if the given file_name could not be opened (does not exist, etc.)
    @staticmethod
    def handleFile(file_name):
        if not os.path.exists(file_name):
            if sys.version_info.major >= 3:
                raise FileNotFoundError("given file name does not refer to an existing file")
            elif sys.version_info.major <= 2:
                raise IOError("given file name does not refer to an existing file")

        f = open(file_name, 'r')
        contents = f.read()

        if re.search(r'^\s*$', contents):
            f.close()
            raise EOFError("given file name was found, but contains no data")

        f.close()
        return HelpHandler.handle(contents)
