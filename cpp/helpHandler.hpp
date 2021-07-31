/* MIT License
 *
 * Copyright (c) 2021 Inaff
 
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

#include <regex>
#include <limits>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>


//Using globals instead of macros to avoid polluting namespace where possible
static constexpr unsigned int version_str    = 0;
static constexpr unsigned int version_int    = 1;
static constexpr unsigned int version_double = 2;

static struct info_t {
    std::string name        = "";
    std::string versionStr  = "";
    unsigned int versionInt = 0;
    double versionDouble    = 0;
    unsigned int versionMostRecent = 0; //Used to determine which overloaded version function was called last
} info_t;

static struct options_t {
    bool noArgHelp      = true;
    bool extraStrings   = true;
    bool unknownArgHelp = false;
} options_t;




namespace helpHandler {
    /*****************/
    /**** PRIVATE ****/
    /*****************/
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) {
            return str; }
            
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }


    /****************/
    /**** PUBLIC ****/
    /****************/
    int handle(int argc, char** argv, std::string help) {
        if (help.empty()) {
            help = "No usage help is available"; }
        if (argc == 1 && options_t.noArgHelp == true) {
            std::cout << help << std::endl;
            return EXIT_SUCCESS; }

        /****************/
        /* Error checks */
        /****************/
        if (!argv) {
            throw std::invalid_argument("Argument value (argv) is NULL"); } 
            
        if (argc > std::numeric_limits<int>::max()) {
            throw std::invalid_argument("Argument count (argc) is larger than the limit of int type"); }
        } else if (argc < 1) {
            if (argc < std::numeric_limits<int>::min()) {
                throw std::invalid_argument("Argument count (argc) is smaller than the limit of int type");
            } else {
                throw std::invalid_argument("Argument count (argc) is 0 or less (should always be at least 1)..."); }
        }

        /*******/
        /* Run */
        /*******/
        unsigned matches = 0;
        bool matchedHelp = false;
        bool matchedVer  = false;

        //Match arguments
        std::vector<std::string> arguments(argv+1, argv+argc); //Start from argv+1 to skip binary name
        for (auto arg: arguments) {
                std::string r = "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)";
                if (options_t.extraStrings == true) { r += "|-{0,}h{1,}$"; }
                if (std::regex_match(arg, std::regex(r)) == true) {
                    matchedHelp = true;
                    matches++; }

                r = "-{0,}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)";
                if (options_t.extraStrings == true) { r += "|^-{0,}v$"; }
                if (std::regex_match(arg, std::regex(r)) == true) {
                    matchedVer = true;
                    matches++; }
        }

        //Output appropriate results
        if (matches > 0) {
            if (matchedVer == true) {
                switch (info_t.versionMostRecent) {
                    case version_str: std::cout << trim(info_t.versionStr); break;
                    case version_int: std::cout << info_t.versionInt; break; 
                    case version_double: std::cout << info_t.versionDouble; break;
                }

            }

            if (matchedHelp == true) {
                if (info_t.name.empty() == false) { std::cout << trim(info_t.name) << " "; }
                    std::cout << help;
                }

            std::cout << std::endl;
            return matches;
        }

        //End
        if (options_t.unknownArgHelp == true && argc > 1) {
            if (argc > 2) {
                std::cout << "Unknown arguments given" << std::endl; 
            } else {
                std::cout << "Unknown argument given" << std::endl; }

            return 0;
        }

        return 0;
    }

    int handleFile(int argc, char** argv, const std::string& fileName) {
        std::ifstream f;
        std::string s;

        f.open(fileName, std::ios::in);
        if (!f.is_open()) {
            throw std::ios_base::failure("Could not open file"); }
        if (f.peek() == std::ifstream::traits_type::eof()) {
            throw std::runtime_error("Given help file is empty"); }

        std::string line;
        while(getline(f, line)) {
            s += line; }

         f.close();

        return helpHandler::handle(argc, argv, s);
    } 

    void version(double version) noexcept {
        info_t.versionDouble = version;
        info_t.versionMostRecent = version_double;
    } void version(unsigned int version) noexcept {
        info_t.versionInt = version;
        info_t.versionMostRecent = version_int;
    } void version(std::string version) { //Parent
        if (version.empty()) {
            throw std::invalid_argument("Version string was given, but is empty"); }
        
        info_t.versionStr = trim(version);
        info_t.versionMostRecent = version_str;
    }

    int handle(int argc, char** argv, std::string helpDialogue, std::string version) {
        helpHandler::version(version);
        return helpHandler::handle(argc, argv, helpDialogue);
    } int handle(int argc, char** argv, std::string helpDialogue, double version) {
        helpHandler::version(version);
        return helpHandler::handle(argc, argv, helpDialogue);
    } int handle(int argc, char** argv, std::string helpDialogue, unsigned int version) {
        helpHandler::version(version);
        return helpHandler::handle(argc, argv, helpDialogue);
    }

    int handleFile(int argc, char** argv, const std::string& fileName, std::string version) {
        helpHandler::version(version);
        return helpHandler::handleFile(argc, argv, fileName);
    } int handleFile(int argc, char** argv, const std::string& fileName, double version) {
        helpHandler::version(version);
        return helpHandler::handleFile(argc, argv, fileName);
    } int handleFile(int argc, char** argv, const std::string& fileName, unsigned int version) {
        helpHandler::version(version);
        return helpHandler::handleFile(argc, argv, fileName);
    }


    void name(const std::string& appName) { //Parent
        if (appName.empty()) {
            throw std::invalid_argument("App name was given, but is empty"); }

        info_t.name = trim(appName);
    }

    void info(const std::string& appName, std::string version) {
        helpHandler::name(appName);
        helpHandler::version(version);
    } void info(const std::string& appName, double version) {
        helpHandler::name(appName);
        helpHandler::version(version);
    } void info(const std::string& appName, unsigned int version) {
        helpHandler::name(appName);
        helpHandler::version(version);
    }

    void config(bool extraStrings=true, bool noArgHelp=true, bool unknownArgHelp=false) noexcept {
        if (options_t.extraStrings != extraStrings) options_t.extraStrings = extraStrings;
        if (options_t.noArgHelp != noArgHelp) options_t.noArgHelp = noArgHelp;
        if (options_t.unknownArgHelp != unknownArgHelp)  options_t.unknownArgHelp = unknownArgHelp;
        return;
    }
}
#endif  /* HELP_HANDLER_HPP */
