import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))) #Need to find help_handler.py file in the parent directory
from help_handler import *

try:
    # python 3.4+ should use builtin unittest.mock not mock package
    from unittest.mock import patch
except ImportError:
    from mock import patch

import unittest
import itertools




class HelpHandlerTests(unittest.TestCase):
    def test_handle(self):
        help_dialogue = "test dialogue"
        with patch.object(sys, "argv", ["help_handler.py", "help", "version"]):
            self.assertEqual(HelpHandler.handle(help_dialogue), found_all)

        with patch.object(sys, "argv", ["help_handler.py", "help"]):
            self.assertEqual(HelpHandler.handle(help_dialogue), found_help)

        with patch.object(sys, "argv", ["help_handler.py", "version"]):
            self.assertEqual(HelpHandler.handle(help_dialogue), found_version)
        
        with patch.object(sys, "argv", ["help_handler.py", "none"]):
            self.assertEqual(HelpHandler.handle(help_dialogue), found_none)


    def test_handleFile(self):
        with self.assertRaises(FileNotFoundError):
            HelpHandler.handleFile("thisFileShouldNotExist")

        if sys.version_info.major >= 3:
            with self.assertRaises(EOFError):
                HelpHandler.handleFile("emptyTestFile.txt")
        elif sys.version_info.major <= 2:
            with self.assertRaises(IOError):
                HelpHandler.handleFile("emptyTestFile.txt")


    def test_config(self):
        with self.assertRaises(TypeError):
            HelpHandler.config(no_arg_help="test")
            HelpHandler.config(extra_strings="test")
            HelpHandler.config(match_hyphens="test")
            HelpHandler.config(hyphens_only="test")
            HelpHandler.config(unknown_arg_help="test")
            HelpHandler.config(disable_output="test")
        
        with self.assertRaises(TypeError):
            float = 3.14159
            HelpHandler.config(no_arg_help=float)
            HelpHandler.config(extra_strings=float)
            HelpHandler.config(match_hyphens=float)
            HelpHandler.config(hyphens_only=float)
            HelpHandler.config(unknown_arg_help=float)
            HelpHandler.config(disable_output=float)
            
        with self.assertRaises(TypeError):
            list = ["test1", "test2" ]
            HelpHandler.config(no_arg_help=list)
            HelpHandler.config(extra_strings=list)
            HelpHandler.config(match_hyphens=list)
            HelpHandler.config(hyphens_only=list)
            HelpHandler.config(unknown_arg_help=list)
            HelpHandler.config(disable_output=list)
            
        with self.assertRaises(TypeError):
            tuple = ("test1", "test2", "test3")
            HelpHandler.config(no_arg_help=tuple)
            HelpHandler.config(extra_strings=tuple)
            HelpHandler.config(match_hyphens=tuple)
            HelpHandler.config(hyphens_only=tuple)
            HelpHandler.config(unknown_arg_help=tuple)
            HelpHandler.config(disable_output=tuple)
            
        with self.assertRaises(TypeError):
            dict = {}
            dict[0] = "test1"
            dict["one"] = "test2"
            HelpHandler.config(no_arg_help=dict)
            HelpHandler.config(extra_strings=dict)
            HelpHandler.config(match_hyphens=dict)
            HelpHandler.config(hyphens_only=dict)
            HelpHandler.config(unknown_arg_help=dict)
            HelpHandler.config(disable_output=dict)     


    def test_name(self):
        with self.assertRaises(ValueError):
            HelpHandler.name("")
            HelpHandler.name(" ")
            
        with self.assertRaises(TypeError):
            HelpHandler.name(0)
            HelpHandler.name(1)

            HelpHandler.name(3.14159)

        with self.assertRaises(TypeError):
            HelpHandler.name(True)
            HelpHandler.name(False)

        with self.assertRaises(TypeError):
            list = [ "test1", "test2" ]
            HelpHandler.name(list)

        with self.assertRaises(TypeError):
            tuple = ("test1", "test2", "test3")
            HelpHandler.name(tuple)

        with self.assertRaises(TypeError):
            dict = {}
            dict[0] = "test1"
            dict["one"] = "test2"
            HelpHandler.name(dict)


    def test_version(self):
        with self.assertRaises(ValueError):
            HelpHandler.version("")
            HelpHandler.version(" ")

        with self.assertRaises(TypeError):
            HelpHandler.version(True)
            HelpHandler.version(False)

        with self.assertRaises(TypeError):
            list = [ "test1", "test2" ]
            HelpHandler.version(list)

        with self.assertRaises(TypeError):
            tuple = ("test1", "test2", "test3")
            HelpHandler.version(tuple)

        with self.assertRaises(TypeError):
            dict = {}
            dict[0] = "test1"
            dict["one"] = "test2"
            HelpHandler.version(dict)




if __name__ == '__main__':
    unittest.main()