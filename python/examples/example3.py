import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.name("TestApp") #This must also come before HelpHandler.handle(), however it doesn't matter if it's called/set before or after help_handler.version()
    HelpHandler.version("1.0")
    HelpHandler.handle("usage: help dialogue example")


if __name__ == "__main__":
    main()
