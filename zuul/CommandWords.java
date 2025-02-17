/*
 * This class is the main class of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.
 * 
 * This class holds an enumeration of all command words known to the game.
 * It is used to recognise commands as they are typed in.
 *
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0 (February 2002)
 */

enum ValidCommand {
    GO("go"),
    STATUS("status"),
    LOOK("look"),
    STORE("store"),
    EAT("eat"),
    QUIT("quit"),
    HELP("help");

    private final String value;

    ValidCommand(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}

class CommandWords
{
    /**
     * Constructor - initialise the command words.
     */
    public CommandWords()
    {
        // nothing to do at the moment...
    }

    /**
     * Check whether a given String is a valid command word. 
     * Return true if it is, false if it isn't.
     */
    public boolean isCommand(String aString)
    {
        for(ValidCommand cmd : ValidCommand.values()) {
            if(cmd.getValue().equals(aString))
                return true;
        }
        // if we get here, the string was not found in the commands
        return false;
    }

    /*
     * Print all valid commands to System.out.
     */
    public void showAll() 
    {
        for(ValidCommand cmd : ValidCommand.values()) {
            System.out.print(cmd.getValue() + "  ");
        }
        System.out.println();
    }
}
