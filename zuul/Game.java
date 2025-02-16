/**
 *  This class is the main class of the "World of Zuul" application. 
 *  "World of Zuul" is a very simple, text based adventure game.  Users 
 *  can walk around some scenery. That's all. It should really be extended 
 *  to make it more interesting!
 * 
 *  To play this game, create an instance of this class and call the "play"
 *  method.
 * 
 *  This main class creates and initialises all the others: it creates all
 *  rooms, creates the parser and starts the game.  It also evaluates and
 *  executes the commands that the parser returns.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0 (February 2002)
 */

class Game implements Actionable
{
    private Parser parser;
    private Room currentRoom;
    private CommandMapper commandMapper;

    public static void main(String [] args) {
        Game game = new Game();
        game.commandMapper = new CommandMapper(game);
        game.play();
    }

        
    /**
     * Create the game and initialise its internal map.
     */
    private Game() 
    {
        createRooms();
        parser = new Parser();
    }

    /**
     * Create all the rooms and link their exits together.
     */
    private void createRooms()
    {
        Room outside, theatre, pub, pubBasement, tunnel, secretClub, lab, office;
      
        // create the rooms
        outside = new Room("outside the main entrance of the university");
        theatre = new Room("in a lecture theatre");
        pub = new Room("in the campus pub");
        pubBasement = new Room("in the dark and mysterious basement of the pub. there's a door here.");
        tunnel = new Room("in a tunnel now. it's dark and dirty in here. wonder who built it");
        secretClub = new Room("in a secret club. there's a pool table here and a bar");
        lab = new Room("in a computing lab");
        office = new Room("in the computing admin office");

        
        // initialise room exits
        outside.setExit(Direction.EAST, theatre, true);
        outside.setExit(Direction.SOUTH, lab, true);
        outside.setExit(Direction.WEST, pub, true);


        pub.setExit(Direction.DOWN, pubBasement, true);

        pubBasement.setExit(Direction.EAST, tunnel, true);

        tunnel.setExit(Direction.SOUTH, secretClub, true);

        // you can't get to the secret club from the lab
        secretClub.setExit(Direction.UP, lab);

        lab.setExit(Direction.EAST, office, true);

        currentRoom = outside; 
    }

    public void play() 
    {            
        printWelcome();
                
        boolean finished = false;
        Action action;
        do {
            Command command = parser.getCommand();
            action = commandMapper.getAction(command);
        } while (action.execute());

        System.out.println("Thank you for playing.  Good bye.");
    }

    private void printWelcome()
    {
        System.out.println();
        System.out.println("Welcome to Adventure!");
        System.out.println("Adventure is a new, incredibly boring adventure game.");
        System.out.println("Type 'help' if you need help.");
        System.out.println();
        System.out.println(currentRoom.getLongDescription());
    }

    public Room getCurrentRoom() {
        return currentRoom;
    }
    public void setCurrentRoom(Room room) {
        currentRoom = room;
    }

    public int getHealth() {
        return 100;
    }
    public void setHealth() {

    }

    public void output(String string) {
        System.out.print(string);
    }
}
