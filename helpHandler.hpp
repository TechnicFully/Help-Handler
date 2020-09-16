/* MIT License
 *
 * Copyright (c) 2020 Acinomatnas
 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef HELP_HANDLER_HPP
#define HELP_HANDLER_HPP

#ifndef HELP_NO_ARGS
    #define HELP_NO_ARGS true
    #define HELP_DISABLE_NO_ARGS false
#endif
#ifndef HELP_UNK_ARGS
    #define HELP_UNK_ARGS true
    #define HELP_DISABLE_UNK_ARGS false
#endif
#ifndef HELP_UNKNOWN_ARGS
    #define HELP_UNKNOWN_ARGS true
    #define HELP_DISABLE_UNKNOWN_ARGS false
#endif
#ifndef HELP_EXTRA_STRINGS
    #define HELP_EXTRA_STRINGS true
    #define HELP_DISABLE_EXTRA_STRINGS false
#endif

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <limits>


const std::string warn = ". Define HELP_IGNORE_WARN to ignore this warning";

static struct options_t {
    std::string ver     = "No version is available";
    bool noArgHelp      = true;
    bool unknownArgHelp = true;
    bool extraStrings   = true;
} options;




namespace helpHandler {
    static void helpPrint(std::string s, int err_val) noexcept {
        #ifndef HELP_IGNORE_ALL
        constexpr const char* helpFuncName = "helpHandler() ";

        if (err_val == 0) {
            #ifndef HELP_IGNORE_WARN
            std::cerr << "WARNING:" << helpFuncName << s << ". Define HELP_IGNORE_WARN to ignore this warning";
            #endif
        } else if (err_val == 1) {
            #ifndef HELP_IGNORE_ERR
            std::cerr << "ERROR:" << helpFuncName << s << ". Define HELP_IGNORE_ERR to ignore this warning";
            #endif
        } else {
            #ifndef HELP_IGNORE_UNKNOWN
            #ifndef HELP_IGNORE_UNK
            std::cerr << "UNKNOWN:" << helpFuncName << s << ". Define HELP_IGNORE_UNKNOWN to ignore this warning";
            #endif
            #endif
        }

        std::cerr << std::endl;
        #endif

        return;
    }


    void ver(std::string ver) noexcept {
        if (ver.empty()) {
            helpPrint("version string was given, but is empty", 0);
            return;
        }
        
        options.ver = ver;
    }

    void config(bool noArgHelp = true, bool unknownArgHelp = true, bool extraStrings = false, std::string ver = "") noexcept {
        if (false == noArgHelp)       options.noArgHelp = false;
        if (false == unknownArgHelp)  options.unknownArgHelp = false;
        if (true == extraStrings)     options.extraStrings = true;
        if (ver.length() >= 1)        helpHandler::ver(ver);
        return;
    }

    int handle(int argc, char** argv, std::string help, std::string unknownArg = "") {
        if (help.empty()) {
            help = "No usage help is available"; }
        if (argc == 1 && options.noArgHelp == true) {
            std::cout << help << std::endl;
            return EXIT_SUCCESS; 
        }
    
    
        /****************/
        /* Error checks */
        /****************/
        if (!argv) {
            throw std::invalid_argument("Argument value (argv) is NULL");
        } 
        
        if (argc > 128) {
            if (argc > std::numeric_limits<int>::max()) {
                throw std::invalid_argument("Argument count (argc) is larger than the limit of int type");
            }

            helpPrint("argument count (argc) is extremely large (128+)", 0);
        } else if (argc < 1) {
            if (argc < std::numeric_limits<int>::min()) {
                throw std::invalid_argument("Argument count (argc) is smaller than the limit of int type");
            } else {
                throw std::invalid_argument("Argument count (argc) is 0 or less (should always be at least 1)...");
            }
        }


        /*******/
        /* Run */
        /*******/
        std::string helpLex[] = {
            "h", "-h", "--h",
            "help", "-help","--help",
            "hhelp", "heelp", "hellp", "helpp",
            "-hhelp", "-heelp", "-hellp", "-helpp",
            "--hhelp", "--heelp", "--hellp", "--helpp" };
        std::string verLex[] = {
            "v", "-v", "--v",
            "version", "-version", "--version",
            "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
            "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
            "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" };
        constexpr int helpLexElementCount = sizeof(helpLex)/sizeof(std::string);
        constexpr int verLexElementCount  = sizeof(verLex)/sizeof(std::string);


        if (options.extraStrings != true) {
            helpLex[0].clear(); helpLex[1].clear(); helpLex[2].clear();
            verLex[0].clear();  verLex[1].clear();  verLex[2].clear();
        }

        for (int i = 1; i < argc; i++) { //Start from 1 to skip binary name
            if (argv[i] == nullptr) {
                throw std::out_of_range("Argument value (argv) index is a nullptr (argc exceeds actual number count?)");
                return EXIT_FAILURE;
            }

            //There is no standard C++ library function for case-insensitive comparison of strings, so we will continue using the same C functions, and argv is a C-style string regardless
            for (int j = 0; j < helpLexElementCount; j++) {
                #if defined _WIN32 || defined _WIN64
                int result = _stricmp(argv[i], helpLex[j].c_str());
                #else
                int result = strcasecmp(argv[i], helpLex[j].c_str());
                #endif

                if (result == 0) {
                    std::cout << help << std::endl;
                    //std::cout << "Matched " << argv[i] << "with lex " << helpLex[j] << std::endl << help << std::endl; //Debug
                    return EXIT_SUCCESS; }
        
            } for (int j = 0; j < verLexElementCount; j++) {
                #if defined _WIN32 || defined _WIN64
                int result = _stricmp(argv[i], verLex[k].c_str());
                #else
                int result = strcasecmp(argv[i], verLex[j].c_str());
                #endif
        
                if (result == 0) {
                    std::cout << options.ver << std::endl;
                    //std::cout << "Matched " << argv[i] << "with lex " << verLex[k] << std::endl << help << std::endl; //Debug
                    return EXIT_SUCCESS; }
            }
        }
            
    
        if (options.unknownArgHelp == true && argc > 1) {
            if (unknownArg.empty()) {
                if (argc > 2) {
                    unknownArg = "Unknown arguments given"; 
                } else {
                    unknownArg = "Unknown argument given"; }
            }
        
            std::cout << unknownArg << std::endl;
            return EXIT_SUCCESS;
        }

        return EXIT_FAILURE;
    }
}
#endif
