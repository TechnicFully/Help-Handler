import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.version("1.0")  #This must come before the main HelpHandler.handle() function, which is what actually processes arguments
    HelpHandler.handle("usage: help dialogue example")


if __name__ == "__main__":
    main()
