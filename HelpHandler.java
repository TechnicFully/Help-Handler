public class HelpHandler {    
    private static class options {
        private static boolean noArgHelp = true;
        private static boolean unknownArgHelp = true;
        private static boolean extraStrings = false;
        private static String  ver = "No version is available";
    };
    
    private static class ignore {
        private static boolean warnings = false;
        private static boolean errors   = false;
        private static boolean unknown  = false;
        private static boolean all      = false;
    }

    private static void HelpPrint(final String s, int errorValue) {
        if (ignore.all == true) return;
        
        if (errorValue == 0 && ignore.warnings != true) {
            System.err.println("WARNING: " +s+ ". Call the class function HelpHandler.ignoreWarnings() or ignoreAll() to disable this warning");
        } else if (errorValue == 1 && ignore.errors != true) {
            System.err.println("ERROR: " +s+ ". Call the class function HelpHandler.ignoreErrors() or ignoreAll() to disable this error message");
        } else {
            if (ignore.unknown != true) {
                System.err.println("UNKNOWN: " +s+ ". Call the class function HelpHandler.ignoreUnknowns() or ignoreAll() to disable this message");
            }
        }

        System.err.flush();
        return;
    }


    public static void ignoreWarnings() {
        ignore.warnings = true;
    } public static void ignoreErrors() {
        ignore.errors = true;
    } public static void ignoreUnknowns() {
        ignore.unknown = true;
    } public static void ignoreAll() {
        ignore.all = true;
    } public static void ignoreWarnings(boolean b) {
        ignore.warnings = b;
    } public static void ignoreErrors(boolean b) {
        ignore.errors = b;
    } public static void ignoreUnknowns(boolean b) {
        ignore.unknown = b;
    } public static void ignoreAll(boolean b) {
        ignore.all = b;
    }

    public static void ver(final String ver) {
        if (ver.length() <= 0) {
            HelpPrint("given version string is empty", 1);
            return;
        }

        options.ver = ver;
    }


    public static void config(final boolean noArgHelp, final boolean unknownArgHelp, final boolean extraStrings,
            final String ver) {
        if (false == noArgHelp)
            options.noArgHelp = false;
        if (false == unknownArgHelp)
            options.unknownArgHelp = false;
        if (true == extraStrings)
            options.extraStrings = true;
        if (ver.length() >= 1)
            HelpHandler.ver(ver);

        return;
    } public static void config(final boolean noArgHelp, final boolean unknownArgHelp, final boolean extraStrings) {
        if (false == noArgHelp)
            options.noArgHelp = false;
        if (false == unknownArgHelp)
            options.unknownArgHelp = false;
        if (true == extraStrings)
            options.extraStrings = true;

        return;
    }


    public static void handle(final String args[], String help, String unknownArgument) {
        if (help.length() <= 0)
            help = "No usage help is available";
        if (args.length == 0 && options.noArgHelp == true ) {
            System.out.println(help);
            System.out.flush();
            return;
        }

        /****************/
        /* Error checks */
        /****************/
        //final String functionName = new Object() {}.getClass().getEnclosingMethod().getName();

        if (args == null) {
            HelpPrint("argument is null", 1);
            return;
        } if (args.length > 128) {
            HelpPrint("argument length is extremely large (128+)", 0);
        } if (args.length < 0) {
            HelpPrint("argument length is smaller than 0 (should always be at least 0)..", 0);
        }

        /*******/
        /* Run */
        /*******/
        String helpLex[] = {  
            "", "", "",         
            "help", "-help","--help",
            "hhelp", "heelp", "hellp", "helpp",
            "-hhelp", "-heelp", "-hellp", "-helpp",
            "--hhelp", "--heelp", "--hellp", "--helpp" };
        String verLex[] = {
            "", "", "",
            "version", "-version", "--version",
            "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
            "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
            "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" };

        int helpLexElementCount = helpLex.length;
        int verLexElementCount = verLex.length;
        if (options.extraStrings == true) {
            helpLex[0] = "h"; helpLex[1] = "-h"; helpLex[2] = "--h";
            verLex[0] = "v"; verLex[1] = "-v"; verLex[2] = "--v";
        }

        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                HelpPrint("argument args[] index is null despite being of length greater than 0", 1);
                return;
            }

            for (int j = 0; j < helpLexElementCount; j++) {
                final int result = args[i].compareToIgnoreCase(helpLex[j]);
                if (result == 0) {
                    System.out.println(help);
                    System.out.flush();
                    return;
                }
            }
            for (int j = 0; j < verLexElementCount; j++) {
                final int result = args[i].compareToIgnoreCase(verLex[j]);

                if (result == 0) {
                    System.out.println(options.ver);
                    System.out.flush();
                    return;
                }
            }
        }

        if (true == options.unknownArgHelp && args.length > 0) {
            if (unknownArgument.length() <= 0) {
                if (args.length > 1) {
                    unknownArgument = "Unknown arguments given";
                } else {
                    unknownArgument = "Unknown argument given"; }
            }

            System.out.println(unknownArgument);
            System.out.flush();
            return;
        }

        return;
    }
    public static void handle(final String args[], String help) {
        if (help.length() <= 0)
            help = "No usage help is available";
        if (args.length == 0 && options.noArgHelp == true ) {
            System.out.println(help);
            System.out.flush();
            return;
        }

        /****************/
        /* Error checks */
        /****************/
        //final String functionName = new Object() {}.getClass().getEnclosingMethod().getName();

        if (args == null) {
            HelpPrint("argument is null", 1);
            return;
        } if (args.length > 128) {
            HelpPrint("argument length is extremely large (128+)", 0);
        } if (args.length < 0) {
            HelpPrint("argument length is smaller than 0 (should always be at least 0)..", 0);
        }

        /*******/
        /* Run */
        /*******/
        String helpLex[] = {  
            "", "", "",         
            "help", "-help","--help",
            "hhelp", "heelp", "hellp", "helpp",
            "-hhelp", "-heelp", "-hellp", "-helpp",
            "--hhelp", "--heelp", "--hellp", "--helpp" };
        String verLex[] = {
            "", "", "",
            "version", "-version", "--version",
            "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
            "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
            "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" };

        int helpLexElementCount = helpLex.length;
        int verLexElementCount = verLex.length;
        if (options.extraStrings == true) {
            helpLex[0] = "h"; helpLex[1] = "-h"; helpLex[2] = "--h";
            verLex[0] = "v"; verLex[1] = "-v"; verLex[2] = "--v";
        }

        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                HelpPrint("argument args[] index is null despite being of length greater than 0", 1);
                return;
            }

            for (int j = 0; j < helpLexElementCount; j++) {
                final int result = args[i].compareToIgnoreCase(helpLex[j]);
                if (result == 0) {
                    System.out.println(help);
                    System.out.flush();
                    return;
                }
            }
            for (int j = 0; j < verLexElementCount; j++) {
                final int result = args[i].compareToIgnoreCase(verLex[j]);

                if (result == 0) {
                    System.out.println(options.ver);
                    System.out.flush();
                    return;
                }
            }
        }

        if (true == options.unknownArgHelp && args.length > 0) {
            if (args.length > 1) {
                System.out.println("Unknown arguments given");
            } else {
                System.out.println("Unknown argument given"); }

            System.out.flush();
            return;
        }

        return;
    } 


}




