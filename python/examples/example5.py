import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.info("TestApp", "1.0")  #Also note that this is optional
    HelpHandler.handleFile("example_dialogue_file.txt") #Like help_handler(), this will process arguments once called as well, but gets the help dialogue from a text file


if __name__ == "__main__":
    main()
