package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.info("TestApp", "1.0")

HelpHandler.config(DISABLE_EXTRA_STRINGS) --Disables matching abbreviated arguments, v, -v, --v, h, -h, --h
                                          --You can also pass...
                                              --no_arg_help
                                              --match_hyphens
                                              --unknown_args_help
                                              --hyphens_only

HelpHandler.handle("example_dialogue_file.txt")
