/* MIT License
 *
 * Copyright (c) 2022 TechnicFully
 
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

/* * * * * * * * * * * * * * * * * * * */
/* * * * USER MACROS & VARIABLES * * * */
/* * * * * * * * * * * * * * * * * * * */
/* 
 * These should be the only relevant variables to any library user not trying to change functionality
 */

#define HELP_HANDLER_VERSION_MAJOR 0.1
#define HELP_HANDLER_VERSION_MINOR 0
#define HELP_HANDLER_VERSION_STR "0.1.0"

//Parameters for help_handler_config()
int DISABLE_EXTRA_STRINGS    = 0x00000001;
int DISABLE_NO_ARGS_HELP     = 0000000010;
int UNKNOWN_ARGS_HELP        = 0000000100;

//Return values
static const int helpHandlerSuccess = 0; //This should remain 0, as it's also used to indicate no arguments were matched
static const int helpHandlerFailure = -1;




/* * * * * * * * * * * * * * * */
/* * * * INTERNAL MACROS * * * */
/* * * * * * * * * * * * * * * */
//C++ does not support the _Generic macro. This is important for C++-like function overloading for ease-of-use for library users
#ifndef HELP_HANDLER_NO_OVERLOAD
#ifndef __cplusplus
#ifdef __STDC__
#ifdef __STDC_VERSION__
#if (__STDC_VERSION__ >= 201112L)
#define HELP_HANDLER_OVERLOAD_SUPPORTED
#endif
#endif
#endif
#endif
#endif
//If overloading is supported, define macro functions
#ifdef HELP_HANDLER_OVERLOAD_SUPPORTED       //(0,help) makes arrays decay to a pointer, otherwise _Generic will throw selection errors (not sure if this is only an issue with Clang, but GCC *does* throw an unused-value warning)
#if defined (__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#endif
#define help_handler(argc, argv, help) _Generic((0,help), \
                                const char*: help_handler_s, \
                                const wchar_t*: help_handler_w, \
                                wchar_t*: help_handler_w, \
                                default: help_handler_s) \
                        (argc, argv, help)
#define help_handler_version(ver) _Generic(ver, \
                                const char*: help_handler_version_s, \
                                int: help_handler_version_i, \
                                double: help_handler_version_d, \
                                default: help_handler_version_s) \
                        (ver)
#define help_handler_info(app_name, ver) _Generic(ver, \
                                const char*: help_handler_info_s, \
                                int: help_handler_info_i, \
                                double: help_handler_info_d, \
                                default: help_handler_info_s) \
                        (app_name, ver)
#define help_handler_name(app_name) _Generic(app_name, \
                                const char*: help_handler_name_s, \
                                const wchar_t*: help_handler_name_w, \
                                default: help_handler_name_s) \
                        (app_name)
#define help_handler_pipe(outputPipe) _Generic(outputPipe, \
                                int: help_handler_pipe_i, \
                                default: help_handler_pipe_s) \
                        (outputPipe)
#endif



#include <errno.h> //For strerror and errno
#include <ctype.h> //For isspace()
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <strings.h> //strcasecmp causes an implicit function declaration warning in Ubuntu 18.04 with just string.h, but I don't believe macOS does
#endif
#include <limits.h> //For INT_MIN and INT_MAX
#include <stdbool.h>

/*
 * Sort of macro spaghetti, but a necessary evil for finding and/or warning about regex capability (or lack thereof)
 */
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))) //POSIX and Unix
    #include <unistd.h> //unistd.h and regex.h are OS-specific headers, so check for them on an opt-in basis
    #if defined(_POSIX_VERSION) //is POSIX compliant
        #define HELP_HANDLER_POSIX_C
        #include <regex.h>
    #endif
#elif defined(__CYGWIN__) && !defined(_WIN32) //Windows with Cygwin (POSIX)
    #define HELP_HANDLER_POSIX_C
    #include <regex.h>
#elif defined(_WIN64) || defined(_WIN32) //Windows
#include <windows.h>
#else
    //MSVC is the only common compiler that doesn't support the warning directive
    #if _MSC_VER && !__INTEL_COMPILER
        #pragma message("warning: Compiling without regular expression support") //Prefixing "warning:" makes MSVC output a warning instead of a message
    #else
        #warning "Compiling without regular expression support" //#warning is a non-standard directive, but extremely common, so we presume this will work
    #endif
#endif

/*
 * Strcpy_s (or strlcpy in BSD) is a secure variant of strcpy that prevents buffer overflows if the source buffer is larger than the destination buffer. 
 * The function is only guaranteed to be available if, before including string.h, C11 or later is supported and STDC_WANT_LIB_EXT1 is defined with an integer value of 1.
 */
#ifdef __STDC__
#ifdef __STDC_VERSION__
#if (__STDC_VERSION__ >= 201112L) || defined(_WIN32)
#ifdef __STDC_WANT_LIB_EXT1__
#if (__STDC_WANT_LIB_EXT1__ == 1)
#define HELP_HANDLER_SECURE_VARIANTS
#endif
#endif
#endif
#endif
#endif

#ifdef _WIN32
#define HELP_HANDLER_SECURE_VARIANTS
#endif

//Only used for internal strings
#define MAX_STRING_LEN 128
#define MAX_STRING_COUNT 32

//A newline feed does have the correct output on Windows and should on any modern OS, but older OSs or log reader programs may interpret a single \n wrong
#ifdef _WIN32
static const char* newline = "\r\n";
#else
static const char* newline = "\n";
#endif

static bool printErr = false;
static struct err { //Ring buffer for error messages
    char err[MAX_STRING_COUNT][MAX_STRING_LEN];
    size_t count;
} err = { {{0}}, 0 };

/*
 * These enums below are used for verbosity/changeability internally, in place of what'd otherwise be magic numbers
 */
//C99 and above allows trailing commas
enum output { 
    outDefault = 0, //stdout
    outStdout,
    outStderr, };
enum varTypes {
    nameChar = 0,
    nameWChar,
    versionStr,
    versionInt,
    versionDouble, };
enum returnVal {
    dialogHelp = 1,
    dialogVer,
    dialogHelpVer, };
enum errTypes {
    silent = 0,
    warning,
    error, };

static int  outputPipe = outDefault; //Used by print_pipe()

/*
 * User info/setting structs
 */
static struct most_recent {
    unsigned int name;
    unsigned int ver;
} most_recent = { 0, versionStr };

static struct info { //Probably best to malloc this struct in the future, though 512 bytes is likely more than enough for any use of this data
    char name[512];
    wchar_t name_w[512];
    char ver_str[512];
    unsigned int ver_int;
    double ver_double;
} info = { {0}, {0}, "No version is available", 0, 0 };

static struct options {
    bool no_args_help;
    bool extra_strings;
    bool unknown_args_help;
} options = { true, true, false }; 


bool help_handler_is_err(int errorCode); //Forward declaration so private/static functions can use this to check for errors



//NOTE: It's understood that casting the return of malloc is bad practice and can hide issues, however it is necessary to silence C++ warnings

/***************************/
/*                         */
/**** PRIVATE FUNCTIONS ****/
/*                         */
/***************************/
/*
 * String functions
 */
/*
 * While making print_pipe use varargs would obviate calling the functions repeatedly in some areas, it would also cause string-nonliteral warnings - surpressing these would require non-portable macros
 */
static int print_pipe(const char* s) {
    if (outputPipe == outDefault) {
        if (fprintf(stdout, "%s", s) < 0) {
            return helpHandlerFailure; }
        fflush(stdout);
    } else if (outputPipe == outStdout) {
        if (fprintf(stdout, "%s", s) < 0) {
            return helpHandlerFailure; }
        fflush(stdout);
    } else if (outputPipe == outStderr) {
        if (fprintf(stderr, "%s", s) < 0) {
            return helpHandlerFailure; }
        fflush(stderr); //stderr isn't buffered by default, but flush just in case
    }

    return helpHandlerSuccess;
}
static int print_pipe_i(int n) {
    if (outputPipe == outDefault) {
        if (fprintf(stdout, "%d", n) < 0) {
            return helpHandlerFailure; }
        fflush(stdout);
    } else if (outputPipe == outStdout) {
        if (fprintf(stdout, "%d", n) < 0) {
            return helpHandlerFailure; }
        fflush(stdout);
    } else if (outputPipe == outStderr) {
        if (fprintf(stderr, "%d", n) < 0) {
            return helpHandlerFailure; }
        fflush(stderr); //stderr isn't buffered by default, but flush just in case
    }

    return helpHandlerSuccess;
}
static int print_pipe_w(const wchar_t* s) {
    if (outputPipe == outDefault) {
        if (fwprintf(stdout, L"%ls", s) < 0) {
            return helpHandlerFailure; }
        fflush(stdout);
    } else if (outputPipe == outStdout) {
        if (fwprintf(stdout, L"%ls", s) < 0) {
            return helpHandlerFailure; }
        fflush(stdout);
    } else if (outputPipe == outStderr) {
        if (fwprintf(stderr, L"%ls", s) < 0) {
            return helpHandlerFailure; }
        fflush(stderr); //stderr isn't buffered by default, but flush just in case
    }

    return helpHandlerSuccess;
}

/*
 * As noted above, strcpy is an unsecure function, with secure variants only available in C11 and above, or OS-specific.
 * With that in mind, that leaves us at minimum leaving C99 open to buffer overflows, or partly rolling our own.
 */
static int bounds_check(size_t dst_size, const char* src) {
    if (src == NULL) { return helpHandlerFailure; }
    if (dst_size < strlen(src)+1) {
        return helpHandlerFailure; }

    return helpHandlerSuccess;
}

static int help_handler_strcpy(char* dst, size_t dst_size, const char* src) {
    if (bounds_check(dst_size, src) == helpHandlerFailure) { return helpHandlerFailure; }
    
    #ifdef HELP_HANDLER_SECURE_VARIANTS
    strcpy_s(dst_size, src);
    #else
    strcpy(dst, src);
    #endif

    return helpHandlerSuccess;
}
static int help_handler_strcat(char* dst, size_t dst_size, const char* src) {
    if (bounds_check(dst_size, src) == helpHandlerFailure) { return helpHandlerFailure; }

    #ifdef HELP_HANDLER_SECURE_VARIANTS
    strcat_s(dst_size, src);
    #else
    strcat(dst, src);
    #endif

    return helpHandlerSuccess;
}


bool help_handler_is_err(int errorCode) {
    return (errorCode < 0) ? true : false;
}

void help_handler_disable_err(bool disableErrorOutput) {
    printErr = disableErrorOutput;
}

void help_handler_print_err(void) {
    for (size_t i = 0; err.count != i; err.count--) {
        print_pipe(err.err[err.count]);
    }
}

char* help_handler_get_err(void) {
    if (err.count > 0) {
        err.count--;
        return err.err[err.count];
    }

    return NULL;
}

static int err_buf_put(const char* s) {
    if (err.count >= MAX_STRING_COUNT) {
        err.count = 0; }

    help_handler_strcpy(err.err[err.count], MAX_STRING_LEN, s);
    err.count++;

    return helpHandlerSuccess;
}

static int print_err(const char* s, int err_line, int err_val) {    
    #ifndef HELP_HANDLER_IGNORE_ALL
    if (err_val == silent) { //Sometimes used internally to skip outputting anything when being called from string_check
        return helpHandlerSuccess; }

    if (printErr == true) {
        if (err_val == warning) {
            #ifndef HELP_HANDLER_IGNORE_WARN
            print_pipe("help_handler:");
            print_pipe_i(err_line);
            print_pipe(" warning: ");
            print_pipe(s);
            print_pipe(". Call help_handler_disable_err() or define HELP_HANDLER_IGNORE_WARN to ignore this warning");
            #endif
        } else if (err_val == error) {
            #ifndef HELP_HANDLER_IGNORE_ERR
            print_pipe("help_handler:");
            print_pipe_i(err_line);
            print_pipe(" error: ");
            print_pipe(s);
            print_pipe(". Call help_handler_disable_err() or define HELP_HANDLER_IGNORE_ERR to ignore this error");
            #endif
        }

        print_pipe(newline);
        return helpHandlerSuccess;
    }
    #endif

    return err_buf_put(s);
}

static int string_check(const char* s, int s_line, int err_val, const char* var_name) {
    char err_msg[MAX_STRING_LEN];

    if (var_name == NULL) {
        string_check(s, s_line, err_val, "variable"); }

    if (var_name != NULL) {
        help_handler_strcpy(err_msg, sizeof(err_msg), var_name); //TODO: fix overflow
    }
    if (s == NULL) {
        help_handler_strcat(err_msg, sizeof(err_msg), " is NULL");
        print_err(err_msg, s_line,  err_val);
        return EXIT_FAILURE; }
    if (s[0] == '\0') {
        help_handler_strcat(err_msg, sizeof(err_msg), "is empty");
        print_err(err_msg, s_line,  err_val);
        return EXIT_FAILURE; } 

    return EXIT_SUCCESS;
}
static int string_check_w(const wchar_t* s, int s_line, int err_val, const char* var_name) {
    char err_msg[MAX_STRING_LEN];

    if (var_name == NULL) {
        string_check_w(s, s_line, err_val, "variable"); }

    help_handler_strcpy(err_msg, sizeof(err_msg), var_name);

    if (s == NULL) {
        help_handler_strcat(err_msg, sizeof(err_msg), " is NULL");
        print_err(err_msg, s_line,  err_val);
        return EXIT_FAILURE; }
    if (s[0] == L'\0') {
            help_handler_strcat(err_msg, sizeof(err_msg), "is empty");
            print_err(err_msg, s_line,  err_val);
            return EXIT_FAILURE; }

    return EXIT_SUCCESS;
}

/*
 * Utility functions
 */
#ifdef HELP_HANDLER_POSIX_C
static int regex_match(const char *s, const char *pattern) {
    regex_t reg;
    if (regcomp(&reg, pattern, REG_EXTENDED|REG_ICASE|REG_NOSUB) != 0) {
        print_err("failed to compile regex", __LINE__, error);
        return EXIT_FAILURE; }

    int status = regexec(&reg, s, 0, NULL, 0);
    regfree(&reg);

    if (status != 0) {
        return EXIT_FAILURE; }

    return EXIT_SUCCESS;
}
#endif

static size_t trim(char *out, size_t len, const char *str) {
    const char* end;
    size_t out_size;

    //Trim leading whitespace
    while(isspace((unsigned char)*str)) { str++; };
    //Trim trailing space
    end = str + strlen(str);
    if (strlen(str) >= 2) {
        end = end - 1;
    }
    while(isspace((unsigned char)*end)) { end--; };
    end++;

    //Set output size to minimum of trimmed string length and buffer size minus 1
    out_size = (end-str) < (unsigned int)len-1 ? (unsigned int)(end-str) : len-1;

    //Copy trimmed string and add null terminator
    memcpy(out, str, out_size);
    out[out_size] = '\0';

    return out_size;
}

//The two functions below are called from the two main help_handler functions, split up for code reuse
static int return_result(int result_help, int result_ver) {
    if (result_help > 0 && result_ver > 0) { return dialogHelpVer; }
    else if (result_help > 0) { return dialogHelp;
    } else if (result_ver > 0) { return dialogVer;
    } else if (result_help == 0 && result_ver == 0) { return 0;
    } else { return 0; }
}

static bool print_ver(void) {
    if (most_recent.ver == versionStr) {
        print_pipe(info.ver_str);
        return true;
    } else if (most_recent.ver == versionInt) {
        //Max number of digits a 64-bit int can hold. Calculating this maximum at compile-time would be prudent
        char n[20];
        sprintf(n, "%d", info.ver_int);
        print_pipe(n);
        return true;
    } else if (most_recent.ver == versionDouble) {
        //Maximum value for an IEEE 754 64-bit double is 1.8 × 10308, but cap to 20 digits (plus decimal point) for the time being
        char n[21]; 
        sprintf(n, "%lf", info.ver_double);
        print_pipe(n);
        return true; }

    return false;
}

static bool print_name(void) {
    if (strlen(info.name) > 0 && most_recent.name == nameChar) {
        print_pipe(info.name);
        return true;
    } else if (wcslen(info.name_w) > 0 && most_recent.name == nameWChar) {
        print_pipe_w(info.name_w);
        return true; }

    return false;
}

static void print_unknown(int argc) {
    if (true == options.unknown_args_help) {
        argc > 2 ? print_pipe("Unknown arguments given") : print_pipe("Unknown argument given");
    }
}

static int arg_match(int argc, char** argv, const char* regex_string, const char* fallback_string) {
    (void)regex_string; //Doesn't effect the variables. Only gets rid of unused parameter warning due to #ifdef below
    (void)fallback_string;

    if (argc > INT_MAX) {
        print_err("argument count (argc) is larger than the limit of int type", __LINE__, error);
        return helpHandlerFailure;
    } else if (argc < 1) {
        if (argc < INT_MIN) {
            print_err("argument count (argc) is smaller than the limit of int type", __LINE__, error);
        } else {
            print_err("argument count (argc) is 0 or less (should always be at least 1)..", __LINE__, error); }

        return helpHandlerFailure; }

    if (argv == NULL) {
        print_err("argument vector (argv) is NULL", __LINE__, error);
        return helpHandlerFailure; }
    if (string_check(*argv, __LINE__, error, "argument vector (argv)") == EXIT_FAILURE) {
        return helpHandlerFailure; }

    for (int i = 1; i < argc; i++) { //Start from 1 to skip executable name
        if (argv[i] == NULL) {
            print_err("argument count (argc) exceeds actual number of arguments", __LINE__, error);
            return helpHandlerFailure; }
    
        #ifdef HELP_HANDLER_POSIX_C
        if (regex_string != NULL) {
            if (regex_match(argv[i], regex_string) == EXIT_SUCCESS) {
                return i; }
        }
        #else
        if (fallback_string != NULL) {
            #if defined _WIN32 || defined _WIN64
            int result = _stricmp(argv[i], fallback_string);
            #else
            int result = strcasecmp(argv[i], fallback_string);
            #endif

            if (result == 0) {
                return i; }
        }
        #endif
    }

    return 0;
}

static int help_handler_sub(int argc, char** argv) {
    //Avoiding this ifdef by embedding regex functionality in the future for Windows would be great
    #ifndef HELP_HANDLER_POSIX_C
    //Casts to silence C++ warnings
    char* help_lex[] = {
        (char*)"h", (char*)"-h", (char*)"--h",
        (char*)"help", (char*)"-help", (char*)"--help",
        (char*)"hhelp", (char*)"heelp", (char*)"hellp", (char*)"helpp",
        (char*)"-hhelp", (char*)"-heelp", (char*)"-hellp", (char*)"-helpp",
        (char*)"--hhelp", (char*)"--heelp", (char*)"--hellp", (char*)"--helpp" };
    char* ver_lex[] = { 
        (char*)"v", (char*)"-v", (char*)"--v",
        (char*)"version", (char*)"-version", (char*)"--version",
        (char*)"vversion", (char*)"veersion", (char*)"verrsion", (char*)"verssion", (char*)"versiion", (char*)"versioon", (char*)"versionn",
        (char*)"-vversion", (char*)"-veersion", (char*)"-verrsion", (char*)"-verssion", (char*)"-versiion", (char*)"-versioon", (char*)"-versionn",
        (char*)"--vversion", (char*)"--veersion", (char*)"--verrsion", (char*)"--verssion", (char*)"--versiion", (char*)"--versioon", (char*)"--versionn" };
    int i = 0;

    if (options.extra_strings != true) {
        ver_lex[0]  = "";ver_lex[1]  = "";ver_lex[2]  = "";
        help_lex[0] = "";help_lex[1] = "";help_lex[2] = ""; 
        i = 3; } //First three elements of help/ver array should be abbreviated terms, hence setting the array index to the fourth element

    int result_help = 0, result_ver = 0;
    for (int temp = i; temp != sizeof(help_lex)/sizeof(help_lex[0]); temp++) {
        result_help = arg_match(argc, argv, NULL, help_lex[temp]);
        if (help_handler_is_err(result_help)) { return result_help; }
        if (result_help > 0) { break; }
    }

    for (int temp = i; temp != sizeof(ver_lex)/sizeof(ver_lex[0]); temp++) {
        result_ver = arg_match(argc, argv, NULL, ver_lex[temp]);
        if (help_handler_is_err(result_ver)) { return result_ver; }
        if (result_ver > 0) { break; }
    }

    #else //HELP_HANDLER_POSIX_C

    char help_lex[MAX_STRING_LEN];
    char ver_lex[MAX_STRING_LEN];
    if (options.extra_strings == true) {
        help_handler_strcpy(help_lex, sizeof(help_lex), "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)|-{0,}h{1,}$");
        help_handler_strcpy(ver_lex, sizeof(ver_lex), "-{0,}v{1,}e{1,}r{1,}s{0,}i{0,}o{0,}n{0,}(.*)|^-{0,}v$");
    } else {
        help_handler_strcpy(help_lex, sizeof(help_lex), "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)"); 
        help_handler_strcpy(ver_lex, sizeof(ver_lex), "-{0,}v{1,}e{1,}r{1,}s{0,}i{0,}o{0,}n{0,}(.*)"); }

    int result_help = arg_match(argc, argv, help_lex, NULL);
    if (help_handler_is_err(result_help)) { return result_help; }
    int result_ver  = arg_match(argc, argv, ver_lex, NULL);
    if (help_handler_is_err(result_ver)) { return result_ver; }
    #endif //HELP_HANDLER_POSIX_C

    int r = return_result(result_help, result_ver);
    if (r != 0) { return r; }

    return helpHandlerSuccess;
}




/**************************/
/*                        */
/**** PUBLIC FUNCTIONS ****/
/*                        */
/**************************/
#ifdef HELP_HANDLER_OVERLOAD_SUPPORTED
//Change Help-Handler's output data stream. You can pass either "stdout" or "stderr" as strings, or Help-Handler's outStdout/outStderr variables.
void help_handler_pipe_s(const char* output_pipe) {
#else
//Change Help-Handler's output data stream. You can pass "stdout" or "stderr" as strings.
void help_handler_pipe(const char* output_pipe) {
#endif
    if (string_check(output_pipe, __LINE__, warning, "output_pipe") == EXIT_FAILURE) {
        return; }

    #if defined _WIN32 || defined _WIN64
    if (_stricmp(output_pipe, "stdout") == 0) {
        outputPipe = outStdout;
    } else if (_stricmp(output_pipe, "stderr") == 0) {
        outputPipe = outStderr;
    } else {
        outputPipe = outDefault; }
    #else
    if (strcasecmp(output_pipe, "stdout") == 0) {
        outputPipe = outStdout;
    } else if (strcasecmp(output_pipe, "stderr") == 0) {
        outputPipe = outStderr;
    } else {
        outputPipe = outDefault; }
    #endif
}

//Change Help-Handler's output data stream. You can pass the predefined variables outStderr or outStdout.
void help_handler_pipe_i(int output_pipe) {
    if (output_pipe == outStdout) {
        outputPipe = output_pipe;
    } else if (output_pipe == outStderr) {
        outputPipe = output_pipe;
    } else {
        outputPipe = outDefault;
    }
}

//For configuring functionality that might conflict/clutter other program output. You may pass the following flags...
//      DISABLE_NO_ARGS_HELP   - Disable help dialogue output when no arguments are passed to your executable
//      DISABLE_EXTRA_STRINGS  - Disable matching of the following strings: h, -h, --h, v, -v, --v
//      UNKNOWN_ARGS_HELP      - Enable dialogue (not help dialogue) output when an unknown argument is passed
int help_handler_config(int option_flags) {
    if (option_flags & DISABLE_NO_ARGS_HELP) {      options.no_args_help = false; }
    if (option_flags & DISABLE_EXTRA_STRINGS) {     options.extra_strings = false; }
    if (option_flags & UNKNOWN_ARGS_HELP) {         options.unknown_args_help = true; }

    if (!(option_flags & DISABLE_NO_ARGS_HELP) &&
        !(option_flags & DISABLE_EXTRA_STRINGS) &&
        !(option_flags & UNKNOWN_ARGS_HELP)) {

        print_err("invalid flag passed", __LINE__, warning);
        return helpHandlerFailure;
    }

    return helpHandlerSuccess;
}

#ifdef HELP_HANDLER_OVERLOAD_SUPPORTED
//Set your programs version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number which you can pass as either a string, unsigned int, or double.
int help_handler_version_s(const char* ver) { //Parent function
#else
//Set your programs version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number.
int help_handler_version(const char* ver) {
#endif
    if (string_check(ver, __LINE__, error, "ver") != EXIT_SUCCESS) { 
        return helpHandlerFailure; }
    if (strlen(ver)+1 >= sizeof(info.ver_str)) {
        print_err("given version string is larger than allowed", __LINE__, error);
        return helpHandlerFailure; }

    char* version = (char*)malloc(strlen(ver)+1);
    if (version == NULL) {
        print_err("failed to allocate memory for version string", __LINE__, error);
        return helpHandlerFailure; }

    trim(version, strlen(ver)+1, ver);
    if (strlen(version) <= 0) { 
        free(version);
        return helpHandlerFailure; }

    help_handler_strcpy(info.ver_str, sizeof(info.ver_str), version);
    most_recent.ver = versionStr;

    free(version);
    return helpHandlerSuccess;
}
//Set your program version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number.
void help_handler_version_i(unsigned int ver) {
    info.ver_int = ver;
    most_recent.ver = versionInt;
}
//Set your program version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number.
void help_handler_version_d(double ver) {
    info.ver_double = ver;
    most_recent.ver = versionDouble;
}


#ifdef HELP_HANDLER_OVERLOAD_SUPPORTED
//Defines your program name which will be output when help dialogue is output, i.e. --help (but not version info, i.e. --version)
int help_handler_name_s(const char* app_name) { //Parent function
#else
//Defines your program name which will be output when help dialogue is output, i.e. --help (but not version info, i.e. --version)
int help_handler_name(const char* app_name) {
#endif
    if (string_check(app_name, __LINE__, error, "app_name") == EXIT_FAILURE) { return helpHandlerFailure; }
    if (strlen(app_name)+1 >= sizeof(info.name)) {
        print_err("given app name is larger than allowed", __LINE__, error);
        return helpHandlerFailure; }

    char* name = (char*)malloc(strlen(app_name)+1);
    if (name == NULL) {
        print_err("failed to allocate memory for app_name", __LINE__, error);
        return helpHandlerFailure; }

    trim(name, strlen(app_name)+1, app_name);
    if (strlen(name) <= 0) {
        free(name);
        return helpHandlerFailure;
    }

    help_handler_strcpy(info.name, sizeof(info.name), name);
    most_recent.name = nameChar;

    free(name);
    return helpHandlerSuccess;
}
//Defines your program name which will be output when help dialogue is output, i.e. --help (but not version info, i.e. --version)
int help_handler_name_w(const wchar_t* app_name) { //Parent function
    if (string_check_w(app_name, __LINE__, error, "app_name") == EXIT_FAILURE) { return helpHandlerFailure; }
    if (wcslen(app_name)+1 >= sizeof(info.name)) {
        print_err("given app name (wchar type) is larger than allowed", __LINE__, warning);
        return helpHandlerFailure; }

    wcscpy(info.name_w, app_name);
    most_recent.name = nameWChar;

    return helpHandlerSuccess;
}

#ifdef HELP_HANDLER_OVERLOAD_SUPPORTED
//A single function for passing your program's name as well as its version
int help_handler_info_s(const char* app_name, const char* ver) {
#else
//A single function for passing your program's name as well as its version
int help_handler_info(const char* app_name, const char* ver) {
#endif
    int result = help_handler_version(ver);
    if (help_handler_is_err(result)) { return result; }
    return help_handler_name(app_name);
}
//A single function for passing your program's name as well as its version
int help_handler_info_i(const char* app_name, unsigned int ver) {
    help_handler_version_d(ver);
    return help_handler_name(app_name);
}
//A single function for passing your program's name as well as its version
int help_handler_info_d(const char* app_name, double ver) {
    help_handler_version_d(ver);
    return help_handler_name(app_name);
}
//A single function for passing your program's name as well as its version
int help_handler_info_w(wchar_t* app_name, const char* ver) {
    int result = help_handler_version(ver);
    if (help_handler_is_err(result)) { return result; }
    return help_handler_name_w(app_name);
}
//A single function for passing your program's name as well as its version
int help_handler_info_wi(wchar_t* app_name, unsigned int ver) {
    help_handler_version_i(ver);
    return help_handler_name_w(app_name);
}
//A single function for passing your program's name as well as its version
int help_handler_info_wd(wchar_t* app_name, double ver) {
    help_handler_version_d(ver);
    return help_handler_name_w(app_name);
}


#ifdef HELP_HANDLER_OVERLOAD_SUPPORTED
//This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this.
int help_handler_s(int argc, char** argv, const char* help_dialogue) {
#else
//This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this.
int help_handler(int argc, char** argv, const char* help_dialogue) {
#endif
    char* help = (char*)malloc(strlen("No usage help is available")+1); //Cast to silence C++ warning
    if (string_check(help_dialogue, __LINE__, silent, NULL) == EXIT_SUCCESS) {
        char* tmp = (char*)realloc(help, strlen(help_dialogue)+1);
        if (tmp == NULL) {  
            free(help);
            return helpHandlerFailure; 
        }
        
        help = tmp;
    }

    //The C standard states it is undefined behavior to pass anything except a null-terminated string to printf. Most libc implementations will print "(null)" in such circumstances, but not all
    if (help == NULL) {
        print_err("failed to allocate memory for help dialogue", __LINE__, error);
        return helpHandlerFailure; }

    if (string_check(help_dialogue, __LINE__, silent, NULL) == EXIT_SUCCESS) {
        help_handler_strcpy(help, strlen(help_dialogue)+1, help_dialogue);
    }

    if (argc == 1 && options.no_args_help == true) {
        if (print_name()) { 
            print_pipe(" "); }
        print_pipe(help); 
        print_pipe(newline);
 
        free(help);
        return helpHandlerSuccess;
    }

    //Should probably find a better way to handle this than int variables as flags, to make it easier to expand
    int result = help_handler_sub(argc, argv);
    if (result == dialogHelpVer) {
        if (print_name()) {
            print_pipe(" "); }
        print_ver();
        print_pipe(newline);
        print_pipe(help);
    } else if (result == dialogHelp) {
        if (print_name()) {
            print_pipe(" "); }
        print_pipe(help);
    } else if (result == dialogVer) {
        print_ver();
    } else if (help_handler_is_err(result)) {
        free(help);
        return result; }

    if (result == 0) {
        print_unknown(argc); }

    if (result >= 0 && result != helpHandlerSuccess) {
        print_pipe(newline); }

    free(help);
    return helpHandlerSuccess;
}
//This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this.
int help_handler_w(int argc, char** argv, const wchar_t* help_dialogue) {
    wchar_t* help = (wchar_t*)malloc(wcslen(L"No usage help is available")); //Cast to silence C++ warning
    if (string_check_w(help_dialogue, __LINE__, silent, NULL) == EXIT_SUCCESS) {
        wchar_t* tmp = (wchar_t*)realloc(help, wcslen(help_dialogue)+1);
        if (tmp == NULL) {
            free(help);
            return helpHandlerFailure;
        }

        help = tmp;
    }

    //The C standard states it is undefined behavior to pass anything except a pointer to a null-terminated string to printf. Most libc implementations will print "(null)" in such circumstances, but not all
    if (help == NULL) {
        print_err("failed to allocate memory for help dialogue", __LINE__, error);
        return helpHandlerFailure; } 

    wcscpy(help, help_dialogue);

    if (argc == 1 && options.no_args_help == true) {
        if (print_name()) { 
            print_pipe(" "); }
        print_pipe_w(help); 
        print_pipe(newline);
        free(help);
        return helpHandlerSuccess;
    }

    //Should probably find a better way to handle this than variables as flags, to make it easier to expand
    int result = help_handler_sub(argc, argv);
    if (result == dialogHelpVer) {
        if (print_name()) {
            print_pipe(" Version "); }
        print_ver();
        print_pipe(newline);
        print_pipe_w(help);
    } else if (result == dialogHelp) {
        if (print_name()) {
            print_pipe(" "); }
        print_pipe_w(help);
    } else if (result == dialogVer) {
        print_ver();
    } else if (help_handler_is_err(result)) {
        free(help);
        return result; }

    if (result == 0) {
        print_unknown(argc); }

    print_pipe(newline);

    free(help);
    return helpHandlerSuccess;
}
//This function like help_handler(), will processes and output the appropriate dialogue based on the user's input, but using a file as its dialogue source. You must pass or set any other options and info before calling this.
int help_handler_f(int argc, char** argv, const char* file_name) {
    if (string_check(file_name, __LINE__, error, "file_name") == EXIT_FAILURE) {
        return helpHandlerFailure; }

    #ifdef HELP_HANDLER_SECURE_VARIANTS
    FILE* fp = NULL;
    int err = fopen_s(&fp, file_name, "rb");
    if (err < 0) { return helpHandlerFailure; }
    #else
    FILE* fp = fopen(file_name, "rb"); //Windows mangles newlines in r, so use rb
    #endif
    if (fp == NULL) {
        print_err(strerror(errno), __LINE__, error);
        return helpHandlerFailure; }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    if (size == -1L) {
        print_err(strerror(errno), __LINE__, error);
        fclose(fp);
        return helpHandlerFailure; }
    rewind(fp);

    char* contents = NULL;
    if ((contents = (char*)malloc((unsigned long)size+1)) == NULL) { 
        print_err("failed to allocate memory", __LINE__, error);
        fclose(fp);
        return helpHandlerFailure; }

    size_t n_items = fread(contents, 1, (size_t)size, fp);
    if (n_items == 0) {
        print_err("given help file is empty", __LINE__, warning); }
    if ((long)n_items < size) {
        print_err(strerror(errno), __LINE__, error);
        free(contents);
        fclose(fp);
        return helpHandlerFailure; }
    if (fclose(fp) == EOF) {
        print_err(strerror(errno), __LINE__, error);
        free(contents);
        return helpHandlerFailure; }

    int return_val = help_handler(argc, argv, (const char*)contents);
    free(contents);

    return return_val;
}


#undef MAX_STRING_LEN
#undef MAX_STRING_COUNT
#undef HELP_HANDLER_POSIX_C
#undef HELP_HANDLER_OVERLOAD_SUPPORTED
#endif /* HELP_HANDLER_H */
