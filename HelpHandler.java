import java.lang.StringBuilder;


public class HelpHandler {
    final static String warn = ". Call the class function HelpHandler.ignoreWarnings() to disable this warning";

    private static boolean ignoreWarningsGlob = false;

    private static boolean noArgHelpGlob = true;
    private static boolean unknownArgHelpGlob = true;
    private static boolean extraStringsGlob = false;
    private static String  verGlob = "No version is available";
    
    
    
    public static void ignoreWarnings() {
        ignoreWarningsGlob = true;
    }


    public static void ver(final String ver) {
        if (ver.length() <= 0) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING: given version string is empty" + warn);
                return;
            }
        }

        verGlob = ver;
    }


    public static void config(final boolean noArgHelp, final boolean unknownArgHelp, final boolean extraStrings,
            final String ver) {
        if (false == noArgHelp)
            noArgHelpGlob = false;
        if (false == unknownArgHelp)
            unknownArgHelpGlob = false;
        if (true == extraStrings)
            extraStringsGlob = true;
        if (ver.length() >= 1)
            HelpHandler.ver(ver);

        return;
    } public static void config(final boolean noArgHelp, final boolean unknownArgHelp, final boolean extraStrings) {
        if (false == noArgHelp)
            noArgHelpGlob = false;
        if (false == unknownArgHelp)
            unknownArgHelpGlob = false;
        if (true == extraStrings)
            extraStringsGlob = true;

        return;
    }


    public static void handle(final String args[], String help, String unknownArgument) {
        if (help.length() <= 0)
            help = "No usage help is available";
        if (args.length == 0 && noArgHelpGlob == true ) {
            System.out.println(help);
            System.out.flush();
            return;
        }

        /****************/
        /* Error checks */
        /****************/
        final String functionName = new Object() {
        }.getClass().getEnclosingMethod().getName();

        if (args == null) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" + functionName + "() argument is null" + warn);
                return;
            }
        }

        if (args.length > 128) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" + functionName + "() argument length is extremely large (128+)" + warn);
            }
        }
        if (args.length < 0) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" + functionName
                        + "() argument length is smaller than 0 (should always be at least 0).." + warn);
            }
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
        if (extraStringsGlob == true) {
            helpLex[0] = "h"; helpLex[1] = "-h"; helpLex[2] = "--h";
            verLex[0] = "v"; verLex[1] = "-v"; verLex[2] = "--v";
        }

        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                System.err.println("ERROR:" + functionName
                        + "() argument args[] is null despite being of length greater than zero");
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
                    System.out.println(verGlob);
                    System.out.flush();
                    return;
                }
            }
        }

        if (true == unknownArgHelpGlob && args.length > 0) {
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
    } public static void handle(final String args[], String help) {
        if (help.length() <= 0)
            help = "No usage help is available";
        if (args.length == 0 && noArgHelpGlob == true ) {
            System.out.println(help);
            System.out.flush();
            return;
        }

        /****************/
        /* Error checks */
        /****************/
        final String functionName = new Object() {
        }.getClass().getEnclosingMethod().getName();

        if (args == null) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" + functionName + "() argument is null" + warn);
                return;
            }
        }

        if (args.length > 128) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" + functionName + "() argument length is extremely large (128+)" + warn);
            }
        }
        if (args.length < 0) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" + functionName
                        + "() argument length is smaller than 0 (should always be at least 0).." + warn);
            }
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
        if (extraStringsGlob == true) {
            helpLex[0] = "h"; helpLex[1] = "-h"; helpLex[2] = "--h";
            verLex[0] = "v"; verLex[1] = "-v"; verLex[2] = "--v";
        }

        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                System.err.println("ERROR:" + functionName
                        + "() argument args[] is null despite being of length greater than zero");
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
                    System.out.println(verGlob);
                    System.out.flush();
                    return;
                }
            }
        }

        if (true == unknownArgHelpGlob && args.length > 0) {
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




