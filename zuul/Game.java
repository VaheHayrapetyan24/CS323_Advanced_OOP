// I'm sorry I deleted unnecessary comments wherever I saw them
// I really don't like redundant comments especially if the code/method names
// are clear enough. So if I have a method named doThing and a comment that says "this method does thing"
// I find it absolutely unnecessary and even distracting.

class Game implements Actionable
{
    private Parser parser;
    private Room currentRoom;
    private CommandMapper commandMapper;
    private Player player;

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
        player = new Player();
    }

    private void createRooms()
    {
        Room outside, theatre, pub, pubBasement, tunnel, secretClub, lab, office;
      
        // create the rooms
        outside = new Room("outside the main entrance of the university");
        theatre = new Room("in a lecture theatre");
        pub = new Room("in the campus pub");
        pubBasement = new Room("in the dark and mysterious basement of the pub. there's a door here.");
        tunnel = new Room("in a tunnel now. it's dark and dirty in here. wonder who built it");
        secretClub = new Room("in a secret club. there's a blackjack table here and a bar");
        lab = new Room("in a chemistry lab");
        office = new Room("in the chemistry admin office");

        
        
        outside.setExit(Direction.EAST, theatre, true);
        outside.setExit(Direction.SOUTH, lab, true);
        outside.setExit(Direction.WEST, pub, true);

        Food water = new Food("water", 3, 5);
        Food popcorn = new Food("popcorn", 2, 2);
        Food beer = new Food("beer", 3, 2);
        Food rice = new Food("rice", 5, 6);
        Food burrito = new Food("burrito", 4, 7);

        Demon chemistryTeacher = new Demon("Chemistry Teacher", "Will use magic potions on you.", 90);
        Demon alcoholism = new Demon("Alcoholism", "Just one more drink", 4);
        Demon gambling = new Demon("Gambling", "You can't seem to stop going to him", 5);
        Demon dust = new Demon("Dust", "It's hard to breathe here", 2);

        


        pub.setExit(Direction.DOWN, pubBasement, true);

        pubBasement.setExit(Direction.EAST, tunnel, true);

        tunnel.setExit(Direction.SOUTH, secretClub, true);

        // you can't get to the secret club from the lab
        secretClub.setExit(Direction.UP, lab);

        lab.setExit(Direction.EAST, office, true);

        outside.addItem(water);
        theatre.addItem(popcorn);
        pub.addItem(beer);
        pub.addItem(rice);
        pub.addItem(burrito);

        pub.addItem(alcoholism);
        tunnel.addItem(dust);
        secretClub.addItem(gambling);
        lab.addItem(chemistryTeacher);





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

    public Player getPlayer() {
        return player;
    }


    public void output(String string) {
        System.out.print(string);
    }
}
