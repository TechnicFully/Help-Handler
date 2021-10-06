import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Needed to find the help_handler file in the parent directory
from help_handler import *




def main():
    HelpHandler.version("1.0")
    HelpHandler.handle("Usage: Help")


if __name__ == "__main__":
    main()