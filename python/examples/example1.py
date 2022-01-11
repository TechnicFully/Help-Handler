import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Needed to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.handle("usage: help dialogue example")


if __name__ == "__main__":
    main()