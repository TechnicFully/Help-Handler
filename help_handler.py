from __future__ import print_function #Compatibility
import sys #Compatibility
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
            print("WARNING: " + help_handler_config.__name__ + "() argument noArgHelp is not of type bool or int")

    if (isinstance(unknownArgHelp, int)):
        unknownArgHelpGlob = unknownArgHelp
    else:
        if (False == help_ignore_warnings):
            print("WARNING: " + help_handler_config.__name__ + "() argument unknownArgHelp is not of type bool or int")

    if (isinstance(extraStrings, int)):
        extraStringsGlob = True
    else:
        if (False == help_ignore_warnings):
            print("WARNING: " + help_handler_config.__name__ + "() argument extraStrings is not of type bool or int")

    if sys.version_info.major >= 3:
        if (isinstance(ver, str)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str")
    elif sys.version_info.major <= 2:
        if (isinstance(ver, basestring)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str")

    return


def help_handler_ver(ver):
    global verGlob

    if sys.version_info.major >= 3:
        if (isinstance(ver, str)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str")
    elif sys.version_info.major <= 2:
        if (isinstance(ver, basestring)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                print("WARNING: " + help_handler_config.__name__ + "() argument ver is not of type str")


def help_handler(help, unknownArg=None):
    if (True == noArgHelpGlob and len(sys.argv) <= 1):
        if not help:
            help = "No usage help is available"
        print(help)
        return
    
    global unknownArgHelpGlob
    warn = ". Define the variable help_ignore_warnings as global and set it to True to ignore this warning"
    helpLex = [ "h", "-h", "--h",
        "help", "-help","--help",
        "hhelp", "heelp", "hellp", "helpp",
        "-hhelp", "-heelp", "-hellp", "-helpp",
        "--hhelp", "--heelp", "--hellp", "--helpp"]
    verLex = [ "v", "-v", "--v",
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


    if unknownArgHelpGlob == True:
        if not unknownArg:
            unknownArg = "Unknown argument given"
        print(unknownArg)

    return



def main():
    os.system('clear')

    if sys.version_info.major > 3:
        print("Python version is newer than expected, issues may occur")
    elif sys.version_info.major < 2:
        print("Python version is older than expected, issues may occur")

    help_handler_config(True, True, True, "1.0.0")
    help_handler_ver("2.0.0")
    help_handler("Usage: Test")




if __name__ == "__main__":
    main()



