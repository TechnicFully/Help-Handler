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

#define HELP_NO_ARGS 1
#define HELP_UNK_ARGS 1
#define HELP_UNKNOWN_ARGS 1
#define HELP_MATCH_EXTRA_STRINGS 1
#define HELP_DISABLE_NO_ARGS 0
#define HELP_DISABLE_UNK_ARGS 0
#define HELP_DISABLE_UNKNOWN_ARGS 0
#define HELP_DISABLE_EXTRA_STRINGS 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //For CHAR_BIT and INT_MIN
#include <stdbool.h>


static struct options_t {
    char ver[512];
    bool no_arg_help;
    bool unknown_arg_help;
    bool extra_strings;
} options = { {0}, 1, 1, 1 }; 




static void help_print(const char* s, int err_val) {
    #ifndef HELP_IGNORE_ALL
    const char* help_func_name = "help_handler()";

    if (err_val == 0) {
        #ifndef HELP_IGNORE_WARN
        fprintf(stderr, "WARNING:%s ", help_func_name);
        fprintf(stderr, "%s", s);
        fprintf(stderr, ". Define HELP_IGNORE_WARN to ignore this warning");
        #endif
    } else if (err_val == 1) {
        #ifndef HELP_IGNORE_ERR
        fprintf(stderr, "ERROR:%s ", help_func_name);
        fprintf(stderr, "%s", s);
         fprintf(stderr, ". Define HELP_IGNORE_ERR to ignore this warning");
        #endif
    } else {
        #ifndef HELP_IGNORE_UNKNOWN
        #ifndef HELP_IGNORE_UNK
        fprintf(stderr, "UNKNOWN:%s ", help_func_name);
        fprintf(stderr, "%s", s);
        fprintf(stderr, ". Define HELP_IGNORE_UNKNOWN to ignore this warning");
        #endif
        #endif
    }

    fprintf(stderr, "\n");
    fflush(stderr); //stderr isn't buffered by default, but flush just in case
    #endif

    return;
}

static int string_check(char* s) {
    if (!s) {
        help_print("string check value s is NULL", 1);
        return EXIT_FAILURE;
    } if (s[strlen(s)] != '\0') {
        help_print("argument is of type array, not string", 1);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
} 


void help_handler_ver(char* ver) {
    if (ver == NULL) {
        help_print("Given version string is NULL", 0);
        return;
    } if (strlen(ver) <= 0) {
        help_print("Given version string is empty", 0);
        return;
    } if (sizeof(ver) > sizeof(options.ver)) {
        help_print("Given version string is larger than allowed", 0);
        return;
    }

    if (string_check(ver) == EXIT_FAILURE) return;
    strcpy(options.ver, ver);
}

void help_handler_config(int no_arg_help, int unknown_arg_help, int extra_strings, char* ver) {
    if (false == no_arg_help)       options.no_arg_help = false;
    if (false == unknown_arg_help)  options.unknown_arg_help = false;
    if (true == extra_strings)      options.extra_strings = true;
    if (ver != NULL)                help_handler_ver(ver);
}

int help_handler(int argc, char** argv, char* help, const char* unknown_arg) {
    if (argc == 1 && options.no_arg_help == true) {
        if (!help) {
            help_print("argv is NULL", 1);
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
        help_print("argument help string (argv) is NULL", 1);
        return EXIT_FAILURE; 
    } if (!help) {
        help_print("argument help string (help) is NULL", 1);
        return EXIT_FAILURE;
    } if (strlen(options.ver) <= 0) {
        strcpy(options.ver, "No version is available\n");
    } if (string_check(*argv) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    } if (string_check(help) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    if (argc > 128) {
        if (argc > INT_MAX) {
            help_print("argument count (argc) is larger than the limit of int type", 1);
            return EXIT_FAILURE;
        }
        help_print("argument count (argc) is very large", 0);
    } else if (argc < 1) {
        if (argc < INT_MIN) {
            help_print("argument count (argc) is smaller than the limit of int type", 1);
        } else {
            help_print("argument count (argc) is 0 or less (should always be at least 1)..", 1);
        }

        return EXIT_FAILURE;
    }

    if (CHAR_BIT != 8) {
        help_print("Char type is not defined as 8 bits. This is untested and may result in issues and/or crashing", 0); 
    }


    /*******/
    /* Run */
    /*******/
    char* help_lex[] = { 
        "h", "-h", "--h",
        "help", "-help","--help",
        "hhelp", "heelp", "hellp", "helpp",
        "-hhelp", "-heelp", "-hellp", "-helpp",
        "--hhelp", "--heelp", "--hellp", "--helpp" };
    char* ver_lex[] = { 
        "v", "-v", "--v",
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

    for (int i = 1; i < argc; i++) { //Start from 1 to skip binary name
        if (argv[i] == NULL) {
            help_print("Argument count (argc) exceeds actual number of arguments (argv) or argument argv is NULL", 1);
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
        
        } for (int j = 0; j < ver_lex_element_count; j++) {
            #if defined _WIN32 || defined _WIN64
            int result = _stricmp(argv[i], ver_lex[k]);
            #else
            int result = strcasecmp(argv[i], ver_lex[j]);
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
             printf("Unknown argument given\n");
        } else {
             printf("%s", unknown_arg); }

        fflush(stdout);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
#endif
