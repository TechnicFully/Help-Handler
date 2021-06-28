'''
MIT License

Copyright (c) 2020 Inaff
 
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
import sys


noArgHelpGlob = True;
unknownArgHelpGlob = True;
extraStringsGlob = False;
verGlob = "No version available";

help_ignore_warnings = False



def help_handler_config(noArgHelp=None, unknownArgHelp=None, extraStrings=None, ver=None):
    global noArgHelpGlob
    global unknownArgHelpGlob
    global extraStringsGlob
    global verGlob


    if (isinstance(noArgHelp, int)):
        noArgHelpGlob = noArgHelp
    else:
        if (False == help_ignore_warnings):
            print("WARNING: " + help_handler_config.__name__ + "() argument noArgHelp is not of type bool or int", file=stderr)

    if (isinstance(unknownArgHelp, int)):
        unknownArgHelpGlob = unknownArgHelp
    else:
        if (False == help_ignore_warnings):
            print("WARNING: " + help_handler_config.__name__ + "() argument unknownArgHelp is not of type bool or int", file=stderr)

    if (isinstance(extraStrings, int)):
        extraStringsGlob = True
    else:
        if (False == help_ignore_warnings):
            print("WARNING: " + help_handler_config.__name__ + "() argument extraStrings is not of type bool or int", file=stderr)

    if sys.version_info.major >= 3:
        if (isinstance(ver, str)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str", file=stderr)
    elif sys.version_info.major <= 2:
        if (isinstance(ver, basestring)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str", file=stderr)

    return


def help_handler_version(ver):
    global verGlob

    if sys.version_info.major >= 3:
        if (isinstance(ver, str)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str", file=stderr)
    elif sys.version_info.major <= 2:
        if (isinstance(ver, basestring)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str", file=stderr)


def help_handler(help, unknownArg=None):
    if not help:
        help = "No usage help is available"
    if (len(sys.argv) == 1 and noArgHelpGlob == True):
        print(help)
        return
    

    helpLex = [
        "h", "-h", "--h",
        "help", "-help","--help",
        "hhelp", "heelp", "hellp", "helpp",
        "-hhelp", "-heelp", "-hellp", "-helpp",
        "--hhelp", "--heelp", "--hellp", "--helpp"]
    verLex = [
        "v", "-v", "--v",
        "version", "-version", "--version",
        "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
        "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
        "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" ]


    for arg in sys.argv[1:]:
        for i in helpLex:
            if arg.lower() == i:
                print(help)
                return
        for i in verLex:
            if arg.lower() == i:
                print(verGlob)
                return


    global unknownArgHelpGlob
    if unknownArgHelpGlob == True:
        if not unknownArg:
            if (len(sys.argv) > 2):
                unknownArg = "Unknown arguments given"
            else:
                unknownArg = "Unknown argument given"
        print(unknownArg)

    return


