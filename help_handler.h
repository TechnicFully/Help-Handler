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


#ifndef HELP_HANDLER_H
#define HELP_HANDLER_H

#define HELP_MATCH_EXTRA_STRINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //For CHAR_BIT and INT_MIN
#include <stdbool.h>


static const char* warn = ". Define HELP_IGNORE_WARN to ignore this warning";

static struct options_t {
    char ver[512];
    bool no_arg_help;
    bool unknown_arg_help;
    bool extra_strings;
} options = { {0}, 1, 1, 1 }; 




void help_handler_ver(char* ver) {
    if (ver == NULL) {
        #ifndef HELP_IGNORE_WARN
        fprintf(stderr, "WARNING: The given version string is NULL%s\n", warn);
        #endif
        return;
    } if (strlen(ver) <= 0) {
        #ifndef HELP_IGNORE_WARN
        fprintf(stderr, "WARNING: The given version string is empty%s\n", warn);
        #endif
        return;
    } if (sizeof(ver) > sizeof(options.ver)) {
        #ifndef HELP_IGNORE_WARN
        fprintf(stderr, "WARNING: The given version string is larger than allowed (%lu bytes)%s\n", sizeof(ver), warn);
        #endif
        return;
    }
    
    strcpy(options.ver, ver);
}


void help_handler_config(int no_arg_help, int unknown_arg_help, int extra_strings, char* ver) {
    if (false == no_arg_help)  options.no_arg_help = false;
    if (false == unknown_arg_help)  options.unknown_arg_help = false;
    if (true == extra_strings)      options.extra_strings = true;
    if (ver != NULL)                help_handler_ver(ver);
}


int help_handler(int argc, char** argv, char* help, char* unknown_arg) {
    if (argc <= 1 && options.no_arg_help == true) {
        if (!help) {
            #ifndef HELP_IGNORE_WARN
            fprintf(stderr, "WARNING:%s() argv is NULL%s\n", __func__, warn);
            fflush(stderr);
            #endif
            return EXIT_FAILURE; 
        }
        
        printf("%s", help);
        fflush(stdout);
        return EXIT_SUCCESS;
    }
    

    /****************/
    /* Error checks */
    /****************/
    if (!argv) {
        #ifndef HELP_IGNORE_WARN
        fprintf(stderr, "WARNING:%s() argument help string (argv) is NULL%s\n", __func__, warn);
        #endif
        return EXIT_FAILURE;
    } 
    if (!help)
        help = "No usage help is available\n";
    if (strlen(options.ver) <= 0)
        strcpy(options.ver, "No version is available\n");
    
    
    if (argc > 128) {
        if (argc > INT_MAX) {
            fprintf(stderr, "ERROR:%s() argument count (argc) is larger than the limit of int type\n", __func__);
            fflush(stderr); //stderr isn't buffered by default, but flush just in case
            return EXIT_FAILURE; }
    } else if (argc < 1) {
        if (argc < INT_MIN) {
            #ifndef HELP_IGNORE_WARN
            fprintf(stderr, "WARNING:%s() argument count (argc) is smaller than the limit of int type%s\n", __func__, warn);
            #endif
        } else {
            #ifndef HELP_IGNORE_WARN
            fprintf(stderr, "WARNING:%s() argument count (argc) is 0 or less (should always be at least 1)..%s\n", __func__, warn);
            #endif
            }
        fflush(stderr);
        return EXIT_FAILURE;
    }
    if (CHAR_BIT != 8) {
        fprintf(stderr, "Char type is not defined as 8 bits. This is untested and may result in issues and/or crashing%s\n", warn); }
    fflush(stderr);




    /*******/
    /* Run */
    /*******/
    char* help_lex[] = { "h", "-h", "--h",
        "help", "-help","--help",
        "hhelp", "heelp", "hellp", "helpp",
        "-hhelp", "-heelp", "-hellp", "-helpp",
        "--hhelp", "--heelp", "--hellp", "--helpp" };
    char* ver_lex[] = { "v", "-v", "--v",
        "version", "-version", "--version",
        "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
        "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
        "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" };
    const int help_lex_element_count = sizeof(help_lex)/CHAR_BIT;
    const int ver_lex_element_count = sizeof(ver_lex)/CHAR_BIT;


    if (options.extra_strings != true) {
        ver_lex[0] = "";ver_lex[1] = "";ver_lex[2] = "";
        help_lex[0] = "";help_lex[1] = "";help_lex[2] = "";
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) {
            fprintf(stderr, "ERROR:%s() argument count (argc) exceeds actual number of arguments (argv) or argument argv[%d] is NULL\n", __func__, i);
            fflush(stderr);
            return EXIT_FAILURE;
        }
    
        for (int j = 0; j < help_lex_element_count; j++) {
            #if defined _WIN32 || defined _WIN64
            int result = _stricmp(argv[i], help_lex[j]);
            #else
            int result = strcasecmp(argv[i], help_lex[j]);
            #endif

            if (result == 0) {
                printf("%s", help);
                fflush(stdout);
                //printf("Matched %s with lex %s\n%s\n", argv[i], help_lex[j], help);  //Debug
                return EXIT_SUCCESS; }
        
        } for (int k = 0; k < ver_lex_element_count; k++) {
            #if defined _WIN32 || defined _WIN64
            int result = _stricmp(argv[i], ver_lex[k]);
            #else
            int result = strcasecmp(argv[i], ver_lex[k]);
            #endif
        
            if (result == 0) {
                printf("%s", options.ver);
                fflush(stdout);
                //printf("Matched %s with lex %s\n%s\n", argv[i], ver_lex[k], help);  //Debug
                return EXIT_SUCCESS; }
        }
    }


    if (true == options.unknown_arg_help && argc > 1) {
        if (!unknown_arg || strlen(unknown_arg) <= 0) {
             fprintf(stderr, "Unknown argument given\n");
        } else {
             fprintf(stderr, "%s", unknown_arg);
            
        }
        
        fflush(stderr);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
#endif
