import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *




def main():
    HelpHandler.info("TestApp", "1.0")
    HelpHandler.config(extra_strings=False) #Disables matching abbreviated arguments, v, -v, --v, h, -h, --h
                                                #You can also set...
                                                #  no_arg_help
                                                #  match_hyphens
                                                #  unknown_args_help
                                                #  hyphens_only
                                                #  disable_output

    HelpHandler.handle("usage: help dialogue example")


if __name__ == "__main__":
    main()
