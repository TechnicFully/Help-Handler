from __future__ import print_function #Compatibility
import sys
from sys import stderr
import os


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


def help_handler_ver(ver):
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


