package.path = package.path .. ";../?.lua"
require "HelpHandler"




HelpHandler.info("TestApp", "1.0")

HelpHandler.config(DISABLE_EXTRA_STRINGS) --Disables matching abbreviated arguments, v, -v, --v, h, -h, --h
                                          --You can also pass...
                                              --DISABLE_NO_ARGS_HELP
                                              --DISABLE_MATCH_HYPHENS
                                              --ENABLE_UNKNOWN_ARGS_HELP
                                              --ENABLE_HYPHENS_ONLY

HelpHandler.handle("usage: help dialogue example")
