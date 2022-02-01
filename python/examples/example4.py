import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.info("TestApp", "1.0")  #This is self-explanatory: the info() and version() functions combined for convenience
    HelpHandler.handle("usage: help dialogue example")


if __name__ == "__main__":
    main()
