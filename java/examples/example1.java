public class example1 {
    public static void example1(final String args[]) {
        try {
            HelpHandler.handle(args, "usage: help dialogue example");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
