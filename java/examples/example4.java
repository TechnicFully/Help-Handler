public class example1 {
    public static void example1(final String args[]) {
        try {
            HelpHandler.info("TestApp", "1.0"); //This is self-explanatory: the info() and version() functions combined for convenience
            HelpHandler.handle(args, "usage: help dialogue example");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
