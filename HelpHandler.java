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
    
    
    public static void ver(String ver) {
        if (ver.length() <= 0) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING: given version string is empty" + warn);
                return;
            }
        }
        
        verGlob = ver;
    }

    
    public static void config(boolean noArgHelp, boolean unknownArgHelp, boolean extraStrings, String ver) {
        if (false == noArgHelp) noArgHelpGlob = false;
        if (false == unknownArgHelp) unknownArgHelpGlob = false;
        if (true == extraStrings) extraStringsGlob = false;
        if (ver.length() >= 1) HelpHandler.ver(ver);
        
        return;
    } public static void config(boolean noArgHelp, boolean unknownArgHelp, boolean extraStrings) {
        if (false == noArgHelp) noArgHelpGlob = false;
        if (false == unknownArgHelp) unknownArgHelpGlob = false;
        if (true == extraStrings) extraStringsGlob = false;

        return;
    }


    public static void handle(String args[], String help, String unknownArgument) {
        if (help.length() <= 0) help = "No usage help is available";
        if (noArgHelpGlob == true && args.length <= 0) {
            System.out.println(help);
            return; }


        /****************/
        /* Error checks */
        /****************/
        String functionName = new Object(){}.getClass().getEnclosingMethod().getName();

        if (args == null) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" +functionName+ "() argument is null" +warn);
                return;
            }
        }
        
        if (args.length > 128) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" +functionName+ "() argument length is extremely large (128+)" +warn);
            }
        } if (args.length < 0) {
            if (ignoreWarningsGlob == true) {
                System.err.println("WARNING:" +functionName+ "() argument length is smaller than 0 (should always be at least 0).." +warn);
            }
        }


        /*******/
        /* Run */
        /*******/
        final String helpLexOptionals[] = { "h", "-h", "--h" };
        final String helpLex[] = {
            "help", "-help","--help",
            "hhelp", "heelp", "hellp", "helpp",
            "-hhelp", "-heelp", "-hellp", "-helpp",
            "--hhelp", "--heelp", "--hellp", "--helpp" };
        final String verLexOptionals[] = { "v", "-v", "--v" };
        final String verLex[] = {
            "version", "-version", "--version",
            "vversion", "veersion", "verrsion", "verssion", "versiion", "versioon", "versionn",
            "-vversion", "-veersion", "-verrsion", "-verssion", "-versiion", "-versioon", "-versionn",
            "--vversion", "--veersion", "--verrsion", "--verssion", "--versiion", "--versioon", "--versionn" };
        
        int helpLexElementCount = helpLex.length;
        int verLexElementCount  = verLex.length;
        if (extraStringsGlob == true) {
            helpLexElementCount += helpLexOptionals.length;
            verLexElementCount  += verLexOptionals.length;
        }
        
        
        for (int i = 0; i < args.length; i++) {
            if (args[i] == null) {
                System.err.println("ERROR:" +functionName+ "() args[] argument is null despite being of length greater than zero");
                return;
            }
            
            for (int j = 0; j < helpLexElementCount; j++) {
                int result = args[i].compareToIgnoreCase(helpLex[j]);
                if (result == 0) {
                    System.out.println(help);
                    return;
                }
            } for (int k = 0; k < verLexElementCount; k++) {
                int result = args[i].compareToIgnoreCase(verLex[k]);
                
                if (result == 0) {
                    System.out.println(verGlob);
                    return;
                }
            }
        }
            
        
        if (true == unknownArgHelpGlob && args.length > 0) {
            if (unknownArgument.length() <= 0) {
                unknownArgument = "Unknown argument given"; }
            
            System.err.println(unknownArgument);
            return;
        }

        return;
    }
}




