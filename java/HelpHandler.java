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


import java.util.regex.*;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.io.IOException;




public class HelpHandler {
    final static public int helpHandlerNone   = 0; //Returned if no arguments were matched; otherwise the number of arguments matched are returned

    private static boolean optNoArgHelp = true;
    private static boolean optExtraStrings = true;
    private static boolean optUnknownArgHelp = false;

    
    private static String  verStr = "No version is available";
    private static double  verNum = 0;
    private static String  name = "";

    
    final private static int typeVerStr = 0;
    final private static int typeVerNum = 1;
    private static  int mostRecentVer = typeVerStr;



    static String readFile(String path, Charset encoding) throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        if (encoded.length <= 0) {
            throw new IOException("usage file is empty");
        }

        return new String(encoded, encoding);
    }

    //Set your programs version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number
    public static void version(final String version) throws IllegalArgumentException {
        if (version == null) {
            throw new IllegalArgumentException("version string is null"); }
        if (version.length() <= 0) {
            throw new IllegalArgumentException("version string is empty"); }

        verStr = version;
        mostRecentVer = typeVerStr;
    }
    //Set your programs version which will be output as appropriate. This shouldn't be anything fancy, just a simple version number
    public static void version(final Double version) {
        verNum = version;
        mostRecentVer = typeVerNum;
    }

    //Defines your program name which will be output alongside help dialogue
    public static void name(final String appName) throws IllegalArgumentException {
        if (appName == null) {
            throw new IllegalArgumentException("app name string is null"); }
        if (appName.length() <= 0) {
            throw new IllegalArgumentException("app name string is empty"); }

        name = appName;
    }

    //A single function for passing your program's name as well as its version
    public static void info(final String appName, final String version) throws IllegalArgumentException {
        HelpHandler.name(appName);
        HelpHandler.version(version);
    }
    //A single function for passing your program's name as well as its version
    public static void info(final String appName, final Double version) throws IllegalArgumentException {
        HelpHandler.name(appName);
        HelpHandler.version(version);
    }

    //For configuring functionality that might conflict/clutter other program output
    public static void config(final boolean noArgHelp) {
        optNoArgHelp = noArgHelp;

        return;
    }
    //For configuring functionality that might conflict/clutter other program output
    public static void config(final boolean noArgHelp, final boolean extraStrings) {
        config(noArgHelp);
        optExtraStrings = extraStrings;

        return;
    }
    //For configuring functionality that might conflict/clutter other program output
    public static void config(final boolean noArgHelp, final boolean extraStrings, final boolean unknownArgHelp) {
        config(noArgHelp, extraStrings);
        optUnknownArgHelp = unknownArgHelp;

        return;
    }

    //This is the main function which processes and outputs the appropriate dialogue based on the user's input. You must pass or set any other options and info before calling this
    public static int handle(final String args[], String helpDialogue) throws RuntimeException {
        if (helpDialogue.length() <= 0)
            helpDialogue = "No usage help is available";
        if (args.length == 0 && optNoArgHelp == true ) {
            System.out.println(helpDialogue);
            System.out.flush();
            return helpHandlerNone; }


        //Error checks
        if (args == null) {
            throw new RuntimeException("argument vector is null"); }
        if (args.length < 0) {
            throw new RuntimeException("argument vector count is below 0 (should always be at least 0)"); }


        //Set regex
        String regexHelp = "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)";
        String regexVer  = "-{0,}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)";

        if (optExtraStrings == true) {
            regexHelp += "|-{0,}h{1,}$";
            regexVer  += "|^-{0,}v$";
        }


        //Match and count arguments
        boolean matchedHelp = false;
        boolean matchedVer = false;
        int matches = 0;
        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                throw new RuntimeException("argument index " + i + " is null despite being of length greater than 0"); }
            if (Pattern.matches(regexHelp, args[i].toLowerCase())) { //Might switch to setting the CASE_INSENSITIVE regex flag as it seems to be ~50ns faster
                matchedHelp = true;
                matches++; } 
            if (Pattern.matches(regexVer, args[i].toLowerCase())) {
                matchedVer = true;
                matches++; } 
        }


        //Print respective output if arguments found and return number of args matched
        if (matchedHelp && matchedVer) {
            if (name.length() > 0) {
                System.out.print(name + " ");
            }
            
            System.out.println(verStr);
            System.out.println(helpDialogue);
        } else if (matchedVer == true) {
            if (mostRecentVer == typeVerStr) {
                System.out.println(verStr);
            } else if (mostRecentVer == typeVerNum) {
                System.out.println(verNum); }
            System.out.flush(); 
        } else if (matchedHelp == true) {
            if (name.length() > 0) {
                System.out.print(name + " ");
            }

            System.out.println(helpDialogue);
            System.out.flush(); }

        if (matchedVer == true || matchedHelp == true) {
            return matches; 
        }


        //Nothing matched
        if (optUnknownArgHelp == true) {
            String result = (args.length > 2) ? "Unknown arguments given" : "Unknown argument given";
            System.out.println(result);
            System.out.flush();
        }

        
        return helpHandlerNone;
    }

    //This function like helpHandler.handle, will processes and output the appropriate dialogue based on the user's input, but using a file as its dialogue source. You must pass or set any other options and info before calling this
    public static int handleFile(final String args[], final String file_name) throws Exception {
        if (file_name == null) {
            throw new IllegalArgumentException("file name is null");
        }
        if (file_name.length() <= 0) {
            throw new IllegalArgumentException("file name is empty");
        }

        Path path = Paths.get(file_name);
        if (Files.notExists(path)) {
            throw new IOException("file name does not refer to an existing file");
        }

        String contents = readFile(file_name, Charset.defaultCharset());
        return HelpHandler.handle(args, contents);
    }

}
