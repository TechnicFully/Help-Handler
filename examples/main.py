import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from help_handler import *




def main():
    os.system('clear')

    if sys.version_info.major > 3:
        print("Python version is newer than expected, issues may occur")
    elif sys.version_info.major < 2:
        print("Python version is older than expected, issues may occur")

    help_handler_config(True, True, True, "1.0.0")
    help_handler_ver("2.0.0")
    help_handler("Usage: Test")




if __name__ == "__main__":
    main()