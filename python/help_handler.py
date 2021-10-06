'''
MIT License

Copyright (c) 2021 Inaff
 
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


#Settings
_extraStringsGlob = True
_noArgHelpGlob = True
_unknownArgHelpGlob = False

#User data
_verGlob = "No version available"
_appNameGlob = ""




class HelpHandler():
    @staticmethod
    def config(no_arg_help, extra_strings=None, unknown_arg_help=None):
        #Error checking
        if not (isinstance(no_arg_help, int)):
            raise TypeError("argument noArgHelp is not of type bool or int")
        if not (isinstance(extra_strings, int)):
            raise TypeError("argument extraStrings is not of type bool or int")
        if not (isinstance(unknown_arg_help, int)):
            raise TypeError("argument unknownArgHelp is not of type bool or int")


        global _extraStringsGlob
        global _noArgHelpGlob
        global _unknownArgHelpGlob

        _extraStringsGlob   = extra_strings
        _noArgHelpGlob      = no_arg_help
        _unknownArgHelpGlob = unknown_arg_help


    @staticmethod
    def version(version):
        #Error checking
        if not version:
            raise ValueError("given version string is empty")

        if sys.version_info.major >= 3:
            if not (isinstance(version, str), isinstance(version, int), isinstance(version, float)):
                raise TypeError("argument version is not of type string, int, or double")
        elif sys.version_info.major <= 2:
            if not (isinstance(version, basestring), isinstance(version, int), isinstance(version, float)):
                raise TypeError("argument version is not of type string, int, or double")


        global _verGlob
        _verGlob = version


    @staticmethod
    def name(app_name):
        #Error checking
        if not app_name:
            raise ValueError("given app name string is empty")
        
        if sys.version_info.major >= 3:
            if not (isinstance(app_name, str)):
                raise TypeError("argument appName is not of type string")
        elif sys.version_info.major <= 2:
            if not (isinstance(app_name, basestring)):
                raise TypeError("argument appname is not of type basestring")


        global _appNameGlob
        _appNameGlob = app_name


    @staticmethod
    def info(app_name, version):
        HelpHandler.name(app_name)
        HelpHandler.version(version)


    @staticmethod
    def handle(help_dialogue):
        if not help_dialogue:
            help_dialogue = "No usage help is available"
        if (len(sys.argv) == 1 and _noArgHelpGlob == True):
            print(help_dialogue)
            return
        
        #Set regex
        helpRegex    = "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)"
        versionRegex = "-{0,}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)"

        global _extraStringsGlob
        if _extraStringsGlob == True:
            helpRegex    += "|-{0,}h{1,}$"
            versionRegex += "|^-{0,}v$"


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
        global _appNameGlob
        global _verGlob
        if foundMatchHelp and foundMatchVer:
            if _appNameGlob:
                print(_appNameGlob + " ", end='')

            print(_verGlob)
            print(help_dialogue)
        elif foundMatchHelp == True:
            if _appNameGlob:
                print(_appNameGlob + " ", end='')
            print(help_dialogue)
        elif foundMatchVer == True:
            print(_verGlob)
        
        if foundMatchHelp or foundMatchVer:
            return matches


        #Nothing matched
        if _unknownArgHelpGlob == True:
            if (len(sys.argv) > 2):
                print("Unknown arguments given")
            else:
                print("Unknown argument given")

        return 0


    @staticmethod
    def handleFile(file_name):
        if not os.path.exists(file_name):
            if sys.version_info.major >= 3:
                raise FileNotFoundError("given file name does not refer to an existing file")
            elif sys.version_info.major <= 2:
                raise IOError("given file name does not refer to an existing file")

        contents = open(file_name, 'r').read()
        if re.search(r'^\s*$', contents):
            raise EOFError("given file name was found, but contains no data")

        return HelpHandler.handle(contents)

