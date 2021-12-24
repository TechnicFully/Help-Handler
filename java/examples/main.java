public class main {
    public static void main(final String args[]) {
        try {
            HelpHandler.version("1.0");
            HelpHandler.handle(args, "Usage: Example help");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
