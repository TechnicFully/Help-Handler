public class example1 {
    public static void example1(final String args[]) {
        try {
            HelpHandler.name("TestApp"); //This must also come before HelpHandler.handle, however it doesn't matter if it's called/set before or after HelpHandler.version()
            HelpHandler.version("1.0");
            HelpHandler.handle(args, "usage: help dialogue example");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
