public class main {
    public static void main(final String args[]) {
        try {
            HelpHandler.handle(args, "usage: help dialogue example");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
