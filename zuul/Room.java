import java.util.Set;
import java.util.HashMap;
import java.util.Iterator;

/*
 * Class Room - a room in an adventure game.
 *
 * This class is the main class of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.  
 *
 * A "Room" represents one location in the scenery of the game.  It is 
 * connected to other rooms via exits.  For each existing exit, the room 
 * stores a reference to the neighboring room.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0 (February 2002)
 */

enum Direction {
    EAST,
    SOUTH,
    WEST,
    NORTH,
    DOWN,
    UP,
}

class Room 
{
    private String description;
    private HashMap<Direction, Room> exits;        // stores exits of this room.

    /**
     * Create a room described "description". Initially, it has no exits.
     * "description" is something like "in a kitchen" or "in an open court 
     * yard".
     */
    public Room(String description) 
    {
        this.description = description;
        exits = new HashMap<Direction, Room>();
    }

    /**
     * Define an exit from this room.
     * If setOppositeDirection = true, will set the current 
     * room as an exit for the neighbor in the opposite direction.
     * 
     * 
     * Since java doesn't support default values for arguments
     * I'll need to override.
     */

    public void setExit(Direction direction, Room neighbor) {
        setExit(direction, neighbor, false); // default value: false
    }
    public void setExit(Direction direction, Room neighbor, boolean setOppositeDirection) 
    {
        exits.put(direction, neighbor);
        if (setOppositeDirection) {
            Direction oppositeDirection = getOppositeDirection(direction);
            neighbor.setExit(oppositeDirection, this);
        }
    }

    /**
     * Return the description of the room (the one that was defined in the
     * constructor).
     */
    public String getShortDescription()
    {
        return description;
    }

    /**
     * Return a long description of this room, in the form:
     *     You are in the kitchen.
     *     Exits: north west
     */
    public String getLongDescription()
    {
        return "You are " + description + ".\n" + getExitString();
    }

    private Direction getOppositeDirection(Direction direction) {
        Direction opposites[][] = {
            { Direction.EAST, Direction.WEST },
            { Direction.NORTH, Direction.SOUTH },
            { Direction.UP, Direction.DOWN },
        };

        for (Direction tuple[] : opposites) {
            if (tuple[0] == direction) {
                return tuple[1];
            }
            if (tuple[1] == direction) {
                return tuple[0];
            }
        }
        // default case, shouldn't happen
        return null;
    }

    /**
     * Return a string describing the room's exits, for example
     * "Exits: north west".
     */
    private String getExitString()
    {
        String returnString = "Exits:";
        Set keys = exits.keySet();
        for(Iterator iter = keys.iterator(); iter.hasNext(); )
            returnString += " " + iter.next();
        return returnString;
    }

    /**
     * Return the room that is reached if we go from this room in direction
     * "direction". If there is no room in that direction, return null.
     */
    public Room getExit(Direction direction) 
    {
        return exits.get(direction);
    }
}

