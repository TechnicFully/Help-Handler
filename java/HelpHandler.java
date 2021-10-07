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


import java.util.regex.*;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.io.IOException;



public class HelpHandler {  
    private static boolean optNoArgHelp = true;
    private static boolean optExtraStrings = true;
    private static boolean optUnknownArgHelp = false;

    
    private static String  verStr = "No version is available";
    private static double  verNum = 0;
    private static String  name = "";

    private static enum varType {
        verStr,
        verNum,
    }

    private static varType mostRecentVer = varType.verStr;


    static String readFile(String path, Charset encoding) throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        if (encoded.length <= 0) {
            throw new IOException("given usage file is empty");
        }

        return new String(encoded, encoding);
    }

    public static void version(final String version) throws RuntimeException {
        if (version == null) {
            throw new RuntimeException("given version string is null"); }
        if (version.length() <= 0) {
            throw new RuntimeException("given version string is empty"); }

        verStr = version;
        mostRecentVer = varType.verStr;
    }
    public static void version(final Double version) {
        verNum = version;
        mostRecentVer = varType.verNum;
    }

    public static void name(final String appName) throws RuntimeException {
        if (appName == null) {
            throw new RuntimeException("given app name string is null"); }
        if (appName.length() <= 0) {
            throw new RuntimeException("given app name string is empty"); }

        name = appName;
    }

    public static void info(final String appName, final String version) throws RuntimeException {
        HelpHandler.name(appName);
        HelpHandler.version(version);
    }
    public static void info(final String appName, final Double version) throws RuntimeException {
        HelpHandler.name(appName);
        HelpHandler.version(version);
    }

    public static void config(final boolean noArgHelp) {
        optNoArgHelp = noArgHelp;

        return;
    }
    public static void config(final boolean noArgHelp, final boolean extraStrings) {
        optNoArgHelp = noArgHelp;
        optExtraStrings = extraStrings;

        return;
    }
    public static void config(final boolean noArgHelp, final boolean extraStrings, final boolean unknownArgHelp) {
        optNoArgHelp = noArgHelp;
        optExtraStrings = extraStrings;
        optUnknownArgHelp = unknownArgHelp;

        return;
    }


    public static int handle(final String args[], String helpDialogue) throws RuntimeException {
        if (helpDialogue.length() <= 0)
            helpDialogue = "No usage help is available";
        if (args.length == 0 && optNoArgHelp == true ) {
            System.out.println(helpDialogue);
            System.out.flush();
            return 0; }


        final String functionName = "HelpHandler." + new Object(){}.getClass().getEnclosingMethod().getName() + " ";

        //Error checks
        if (args == null) {
            throw new RuntimeException(functionName + "argument vector is null"); }
        if (args.length < 0) {
            throw new RuntimeException(functionName + "argument vector count is below 0 (should always be at least 0)"); }


        //Set regex
        String regexHelp    = "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)";
        String regexVer     = "-{0,}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)";

        if (optExtraStrings == true) {
            regexHelp    += "|-{0,}h{1,}$";
            regexVer += "|^-{0,}v$";
        }


        //Match and count arguments
        boolean matchedHelp = false;
        boolean matchedVer = false;
        int matches = 0;
        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                throw new RuntimeException(functionName + "argument index " + i + " is null despite being of length greater than 0"); }
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
            if (mostRecentVer == varType.verStr) {
                System.out.println(verStr);
            } else if (mostRecentVer == varType.verNum) {
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

        
        return 0;
    }


    public static int handleFile(final String args[], final String file_name) throws Exception {
        Path path = Paths.get(file_name);
        if (Files.notExists(path)) {
            throw new IOException("given file name does not refer to an existing file");
        }

        String contents = readFile(file_name, Charset.defaultCharset());
        return HelpHandler.handle(args, contents);
    }

}
