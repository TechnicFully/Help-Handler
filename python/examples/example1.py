import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Needed to find the help_handler file in the parent directory
from help_handler import *




def main():
    help_handler_version("1.0")
    help_handler("Usage: Test")


if __name__ == "__main__":
    main()