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

#ifndef HELP_MATCH_EXTRA_STRINGS
    #define HELP_MATCH_EXTRA_STRINGS true
#endif

#include <iostream>
#include <cstring>
#include <climits>

static bool noArgHelpGlob = true;
static bool unknownArgHelpGlob = true;
static bool extraStringsGlob = false;
static std::string verGlob = "No version is available";




void helpHandlerVer(std::string ver) {
    verGlob = ver;
}


void helpHandlerConfig(bool noArgHelp = true, bool unknownArgHelp = true, bool extraStrings = false, std::string ver = "") {
    if (false == noArgHelp) noArgHelpGlob = false;
    if (false == unknownArgHelp) unknownArgHelpGlob = false;
    if (true == extraStrings) extraStringsGlob = true;
    if (!ver.empty()) helpHandlerVer(ver);
    
    return;
}


int helpHandler(int argc, char** argv, std::string help, std::string unknownArg = "") {
    if (help.empty()) {
        help = "No usage help is available"; }
    if (noArgHelpGlob == true && argc <= 1) {
        std::cout << help << std::endl;
        return EXIT_SUCCESS; }
    
    const std::string warn = ". Define HELP_IGNORE_WARN to ignore this warning";
    std::string helpLex[] = { "h", "-h", "--h",
        "help", "-help","--help",
        "hhelp", "heelp", "hellp", "helpp",
        "-hhelp", "-heelp", "-hellp", "-helpp",
        "--hhelp", "--heelp", "--hellp", "--helpp" };
    std::string verLex[] = { "v", "-v", "--v",
        "version", "-version", "--version",
        "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
        "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
        "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" };
    
    
    
    /****************/
    /* Error checks */
    /****************/
    if (!argv) {
        #ifndef HELP_IGNORE_WARN
        std::cerr << "WARNING:" << __func__ << "() argument help string (argv) is NULL" << warn << std::endl;
        #endif
        return EXIT_FAILURE;
    }
    
    
    if (argc > 128) {
        if (argc > INT_MAX || argc < INT_MIN) {
            std::cerr << "ERROR:" << __func__ << "() argument count (argc) is outside the limit of int type" << std::endl;
            return EXIT_FAILURE;
        }
        
    #ifndef HELP_IGNORE_WARN
        else {
            std::cerr << "WARNING:" << __func__ << "() argument count (argc) is extremely large (128+)" <<  warn << std::endl; }
    } else if (argc < 1) {
        std::cerr << "WARNING:" << __func__ << "() argument count (argc) is 0 or less (should always be at least 1)" << warn << std::endl; }
    
    if (CHAR_BIT != 8) {
        std::cerr << "Char type is not defined as 8 bits. This is untested and may result in issues and/or crashing" << warn << std::endl; }
    #else
    }
    #endif


    /*******/
    /* Run */
    /*******/
    if (extraStringsGlob != true) {
        helpLex[0].clear(); helpLex[1].clear(); helpLex[2].clear();
        verLex[0].clear();  verLex[1].clear();  verLex[2].clear();
    }


    const int helpLexElementCount = sizeof(helpLex)/sizeof(std::string);
    const int verLexElementCount  = sizeof(verLex) /sizeof(std::string);

    int i; for (i = 1; i < argc; i++) {
        if (nullptr == argv[i]) {
            std::cerr << "ERROR:" << __func__ << "() argument count (argc) exceeds actual number of arguments (argv) or argv is NULL\n";
            return EXIT_FAILURE;
        }

           
        //There is no standard C++ library function for case-insensitive comparison of strings, so we will continue using the same C functions
        int j; for (j = 0; j < helpLexElementCount; j++) {
            #if defined _WIN32 || defined _WIN64
            int result = _stricmp(argv[i], helpLex[j].c_str());
            #else
            int result = strcasecmp(argv[i], helpLex[j].c_str());
            #endif

            if (result == 0) {
                std::cout << help << std::endl;
                //std::cout << "Matched " << argv[i] << "with lex " << helpLex[j] << std::endl << help << std::endl; //Debug
                return EXIT_SUCCESS; }
        
        } int k; for (k = 0; k < verLexElementCount; k++) {
            #if defined _WIN32 || defined _WIN64
            int result = _stricmp(argv[i], verLex[k].c_str());
            #else
            int result = strcasecmp(argv[i], verLex[k].c_str());
            #endif
        
            if (result == 0) {
                std::cout << verGlob << std::endl;
                //std::cout << "Matched " << argv[i] << "with lex " << verLex[k] << std::endl << help << std::endl; //Debug
                return EXIT_SUCCESS; }
        }
    }
            
    
    if (true == unknownArgHelpGlob && argc > 1) {
        if (unknownArg.empty()) {
            unknownArg = "Unknown argument given"; }
        
        std::cerr << unknownArg << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
#endif
