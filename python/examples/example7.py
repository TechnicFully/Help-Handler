import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.info("TestApp", "1.0")
    
    return_value = HelpHandler.handle("usage: help dialogue example") #This time, let's catch the return value and check what happened...

    #These are all the possible return values
    if found_all == return_value:
        print("Help and version arguments were found")
    elif found_help == return_value:
        print("Only help arguments were found")
    elif found_version == return_value:
        print("Only version arguments were found")
    elif found_none == return_value:
        print("No arguments were found")


if __name__ == "__main__":
    main()
