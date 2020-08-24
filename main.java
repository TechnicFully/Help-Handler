public class main {
    public static void main(String args[]) throws Exception {
        //HelpHandler.ignoreWarnings();
        HelpHandler.ver("1.0.0");
        HelpHandler.config(false, true, true, "2.0.0");
        HelpHandler.handle(args, "Usage: Test", "Unknown argument given");
    }
}




