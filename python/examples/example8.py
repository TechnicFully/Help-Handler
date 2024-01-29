import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.info("TestApp", "1.0")
    HelpHandler.config(no_arg_help=True) #Disable output of help dialogue if the user passes no arguments

    return_value = HelpHandler.handle(None) #We can also then ONLY check what happened with a None value, and no help dialogue will be output

    #These are all the possible return values
    if found_all == return_value: #This will only have output the program version (1.0), only because it was set above
        print("Help and version arguments were found")
    elif found_help == return_value: #This will have output nothing
        print("Only help arguments were found")
    elif found_version == return_value: #This will also have output the program version
        print("Only version arguments were found")
    elif found_none == return_value: #This will have output nothing
        print("No arguments were found")


if __name__ == "__main__":
    main()
