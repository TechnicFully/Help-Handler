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
import sys, re, warnings #sys is for grabbing arguments


noArgHelpGlob = True;
extraStringsGlob = True;
unknownArgHelpGlob = False;
verGlob = "No version available";

help_ignore_warnings = False


def _warning_formatted(message, category, filename, lineno, file=None, line=None):
        return '%s at line %s: %s\n' % (filename, lineno, message)

warnings.formatwarning = _warning_formatted




def help_handler_config(noArgHelp=None, extraStrings=None, unknownArgHelp=None):
    global noArgHelpGlob
    global unknownArgHelpGlob
    global extraStringsGlob
    global verGlob


    if (isinstance(noArgHelp, int)):
        noArgHelpGlob = noArgHelp
    else:
        if (False == help_ignore_warnings):
            warnings.warn("argument noArgHelp is not of type bool or int")

    if (isinstance(extraStrings, int)):
        extraStringsGlob = True
    else:
        if (False == help_ignore_warnings):
            warnings.warn("argument extraStrings is not of type bool or int")

    if (isinstance(unknownArgHelp, int)):
        unknownArgHelpGlob = unknownArgHelp
    else:
        if (False == help_ignore_warnings):
            warnings.warn("argument unknownArgHelp is not of type bool or int")

    return


def help_handler_version(ver):
    global verGlob

    if sys.version_info.major >= 3:
        if (isinstance(ver, str)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                warnings.warn("argument ver is not of type str")
    elif sys.version_info.major <= 2:
        if (isinstance(ver, basestring)):
            verGlob = ver
        else:
            if (False == help_ignore_warnings):
                warnings.warn("argument ver is not of type str")


def help_handler(helpDialogue, version=None):
    if not helpDialogue:
        helpDialogue = "No usage help is available"
    if (len(sys.argv) == 1 and noArgHelpGlob == True):
        print(helpDialogue)
        return
    
    helpRegex    = "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)"
    versionRegex = "-{0,}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)"
    foundRegexMatch = False

    if extraStringsGlob == True:
        helpRegex    += "|-{0,}h{1,}$"
        versionRegex += "|^-{0,}v$"

    for arg in sys.argv[1:]:
        if re.match(versionRegex, arg):
            print(verGlob)
            foundRegexMatch = True
    for arg in sys.argv[1:]:
        if re.match(helpRegex, arg):
            print(helpDialogue)
            foundRegexMatch = True

    if foundRegexMatch == True: 
        return


    if unknownArgHelpGlob == True:
        if (len(sys.argv) > 2):
            print("Unknown arguments given")
        else:
            print("Unknown argument given")

    return


