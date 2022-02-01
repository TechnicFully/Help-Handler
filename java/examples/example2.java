public class example1 {
    public static void example1(final String args[]) {
        try {
            HelpHandler.version("1.0"); //This must come before the main HelpHandler.handle function, which is what actually processes arguments
            HelpHandler.handle(args, "usage: help dialogue example");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
