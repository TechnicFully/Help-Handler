import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.handle("usage: help dialogue example") #Set help dialogue and process arguments


if __name__ == "__main__":
    main()
