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



public class HelpHandler {  
    private static boolean optNoArgHelp = true;
    private static boolean optExtraStrings = true;
    private static boolean optUnknownArgHelp = false;

    
    private static String  verStr = "No version is available";
    private static double  verNum = 0;


    private static enum varType {
        verStr,
        verNum,
    }

    private static varType mostRecentVer = varType.verStr;




    public static void version(final String ver) throws RuntimeException {
        if (ver == null) {
            throw new RuntimeException("given version string is null"); }
        if (ver.length() <= 0) {
            throw new RuntimeException("given version string is empty"); }

        verStr = ver;
        mostRecentVer = varType.verStr;
    }
    public static void version(final Double ver) {
        verNum = ver;
        mostRecentVer = varType.verNum;
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

        /****************/
        /* Error checks */
        /****************/
        if (args == null) {
            throw new RuntimeException(functionName + "argument vector is null"); }
        if (args.length < 0) {
            throw new RuntimeException(functionName + "argument vector count is below 0 (should always be at least 0)"); }

        /*******/
        /* Run */
        /*******/
        String regexVersion = "-{0,}v{1,}e{1,}r{1,}s{1,}i{1,}o{1,}n{1,}(.*)";
        String regexHelp    = "-{0,}h{1,}e{1,}l{1,}p{1,}(.*)";

        if (optExtraStrings == true) {
            regexVersion += "|^-{0,}v$";
            regexHelp    += "|-{0,}h{1,}$";
        }

        boolean matchedVersion = false;
        boolean matchedHelp = false;
        int matches = 0;

        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                throw new RuntimeException(functionName + "argument index " + i + "is null despite being of length greater than 0"); }
            if (Pattern.matches(regexHelp, args[i].toLowerCase())) { //Might switch to setting the CASE_INSENSITIVE regex flag as it seems to be ~50ns faster
                matchedHelp = true;
                matches++; } 
            if (Pattern.matches(regexVersion, args[i].toLowerCase())) {
                matchedVersion = true;
                matches++; } 
        }

        if (matchedVersion == true) {
            if (mostRecentVer == varType.verStr) {
                System.out.println(verStr);
            } else if (mostRecentVer == varType.verNum) {
                System.out.println(verNum); }
            System.out.flush(); }
        if (matchedHelp == true) {
            System.out.println(helpDialogue);
            System.out.flush(); }

        if (matchedVersion == true || matchedHelp == true) {
            return matches; }


        if (optUnknownArgHelp == true && args.length > 0) {
            System.out.flush();
            return 0;
        }


        return 0;
    }
    public static int handle(final String args[], String help, final String version) throws RuntimeException {
        verStr = version;
        mostRecentVer = varType.verStr;
        return HelpHandler.handle(args, help);
    }
    public static int handle(final String args[], String help, final Double version) throws RuntimeException {
        verNum = version;
        mostRecentVer = varType.verNum;
        return HelpHandler.handle(args, help);
    }

}




