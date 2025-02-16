import java.util.Set;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Collection;

enum Direction {
    EAST,
    SOUTH,
    WEST,
    NORTH,
    DOWN,
    UP,
}

class Room {
    private String description;
    private HashMap<Direction, Room> exits;

    private HashMap<String, Item> items;

    public Room(String description) 
    {
        this.description = description;
        exits = new HashMap<Direction, Room>();
        items = new HashMap<String, Item>();
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


    public void addItem(Item item) {
        items.put(item.name, item);
    }

    public Item getItem(String name) {
        return items.get(name);
    }

    public Item removeItem(String name) {
        return items.remove(name);
    }


    public void encounter(Player player) {
        for (Item item : items.values()) {
            item.encounter(player);
        }
    }

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


    
    public Room getExit(Direction direction) 
    {
        return exits.get(direction);
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
        return returnString + "\n";
    }

    public String getItemsString() {
        Collection<Item> values = items.values();
        if (values.isEmpty()) {
            return "Room is empty \n";
        }
        String returnString = "Items: ";
        for (Item item: values) {
            returnString += item.name + " ";
        }
        return returnString + "\n";
    }

}

