public class main {
    public static void main(final String args[]) throws Exception {
        HelpHandler.version("1.0");
        HelpHandler.handle(args, "Usage: Test"); //You can pass the version as the third argument here instead for convenience
    }
}
