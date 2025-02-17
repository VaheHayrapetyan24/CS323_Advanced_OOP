import java.util.Map;
import java.util.HashMap;
import java.util.function.Function;
import java.util.Arrays;
import java.util.stream.Collectors;

interface Actionable {
    public Room getCurrentRoom();
    public void setCurrentRoom(Room room);

    public Player getPlayer();
    // public void setHealth();

    public void output(String string);
}


abstract class Action {
    abstract public boolean execute();
}

class GoRoomAction extends Action {
    private Actionable actionable;
    private Command command;

    public GoRoomAction(Actionable actionable, Command command) {
        this.actionable = actionable;
        this.command = command;
    }

    public boolean execute() {
        Room currentRoom = actionable.getCurrentRoom();

        Direction direction = getDirection();
        if (direction == null) {
            return true;
        }

        Room nextRoom = currentRoom.getExit(direction);

        if (nextRoom == null) {
            actionable.output("No exit " + direction + "\n");
            return true;
        } 

        Player player = actionable.getPlayer();
        actionable.setCurrentRoom(nextRoom);
        actionable.output(nextRoom.getLongDescription());
        nextRoom.encounter(player);

        if (player.getHealth() == 0) {
            actionable.output("Alas, you brave soul, your jurney ends here. Rest well\n");
            return false;
        }

        return true;
    }

    private Direction getDirection() {
        if(!command.hasSecondWord()) {
            actionable.output("Go where?\n");
            return null;
        }

        String rawDirection = command.getSecondWord();

        try {
            Direction direction = Direction.valueOf(rawDirection);
            return direction;
        } catch (IllegalArgumentException e) {
            actionable.output("I don't know what " + rawDirection + " means.\n");
            return null;
        }
    }
}

class HelpAction extends Action {
    private Actionable actionable;

    public HelpAction(Actionable actionable) {
        this.actionable = actionable;
    }

    public boolean execute() {
        actionable.output("You are lost. You are alone. You wander\n");
        actionable.output("around at the university.\n\n");
        actionable.output("Your command words are: ");
        actionable.output(Arrays.stream(ValidCommand.values())
            .map(ValidCommand::getValue)  // Map to String
            .collect(Collectors.joining(" ")) + "\n");

        return true;
    }
}

class QuitAction extends Action {
    private Actionable actionable;
    private Command command;

    public QuitAction(Actionable actionable, Command command) {
        this.actionable = actionable;
        this.command = command;
    }

    public boolean execute() {
        if(command.hasSecondWord()) {
            actionable.output("Quit what?\n");
            return true;
        }

        return false;
    }
}

class LookAction extends Action {
    private Actionable actionable;

    public LookAction(Actionable actionable) {
        this.actionable = actionable;
    }

    public boolean execute() {
        actionable.output(actionable.getCurrentRoom().getItemsString());
        return true;
    }
}


class StatusAction extends Action {
    private Actionable actionable;
    private Command command;

    public StatusAction(Actionable actionable) {
        this.actionable = actionable;
    }

    public boolean execute() {
        Player player = actionable.getPlayer();
        actionable.output("Health: " + player.getHealth() + "/" + player.MAX_HEALTH + "\n");
        actionable.output("Backpack weight: " + player.getBackpackWeight() + "/" + player.MAX_WEIGHT + "\n");
        actionable.output(player.getBackpackItems());
        return true;
    }
}



class StoreAction extends Action {
    private Actionable actionable;
    private Command command;

    public StoreAction(Actionable actionable, Command command) {
        this.actionable = actionable;
        this.command = command;
    }

    public boolean execute() {
        if(!command.hasSecondWord()) {
            actionable.output("Store what?\n");
            return true;
        }

        String name = command.getSecondWord();
        Room room = actionable.getCurrentRoom();
        Item item = room.getItem(name);
        if (item == null) {
            actionable.output("Where'd you see that?\n");
            return true;
        }

        if (!(item instanceof Food)) {
            actionable.output("You can't add that to your backpack\n");
            return true;
        }

        if (!actionable.getPlayer().willFitInBackpack((Food)item)) {
            actionable.output("You don't have that much space in your backpack\n");
            return true;
        }

        room.removeItem(name);
        actionable.getPlayer().addToBackpack((Food)item);
        return true;
    }
}

class EatAction extends Action {
    private Actionable actionable;
    private Command command;

    public EatAction(Actionable actionable, Command command) {
        this.actionable = actionable;
        this.command = command;
    }

    public boolean execute() {
        if(!command.hasSecondWord()) {
            actionable.output("Eat what?\n");
            return true;
        }

        String name = command.getSecondWord();
        
        
        if (!tryToEatFromRoom(name)) {
            tryToEatFromBackpack(name);
        }
        
        return true;
    }

    private boolean tryToEatFromRoom(String name) {
        Room room = actionable.getCurrentRoom();
        Item roomItem = room.getItem(name);
        if (roomItem == null) {
            return false;
        }

        if (!(roomItem instanceof Food)) {
            actionable.output("You don't have the stomach for that.\n");
            return true;
        }

        room.removeItem(name);
        actionable.getPlayer().increaseHealth(((Food)roomItem).healthBoost);
        return true;
    }

    private void tryToEatFromBackpack(String name) {
        Player player = actionable.getPlayer();

        Item backpackItem = player.getFromBackpack(name);
        if (backpackItem == null) {
            actionable.output("A stomach full of nothing.\n");
            return;
        }

        if (!(backpackItem instanceof Food)) {
            actionable.output("You don't have the stomach for that.\n");
            return;
        }

        player.removeFromBackpack(name);
        player.increaseHealth(((Food)backpackItem).healthBoost);
    }
}

class NoOpAction extends Action {
    private Actionable actionable;

    public NoOpAction(Actionable actionable) {
        this.actionable = actionable;
    }

    public boolean execute() {
        actionable.output("What? I'll just stay here.\n");
        return true;
    }
}







class CommandMapper {
    private static final Map<String, Function<Command, Action>> commandMap = new HashMap<>();
    private Actionable actionable;

    public CommandMapper(Actionable actionable) {
        this.actionable = actionable;
        registerCommands();
    }

    private void registerCommands() {
        commandMap.put(ValidCommand.GO.getValue(), cmd -> new GoRoomAction(actionable, cmd));
        commandMap.put(ValidCommand.STATUS.getValue(), cmd -> new StatusAction(actionable));
        commandMap.put(ValidCommand.LOOK.getValue(), cmd -> new LookAction(actionable));
        commandMap.put(ValidCommand.STORE.getValue(), cmd -> new StoreAction(actionable, cmd));
        commandMap.put(ValidCommand.EAT.getValue(), cmd -> new EatAction(actionable, cmd));

        commandMap.put(ValidCommand.QUIT.getValue(), cmd -> new QuitAction(actionable, cmd));
        commandMap.put(ValidCommand.HELP.getValue(), cmd -> new HelpAction(actionable));

    }

    public Action getAction(Command command) {
        String commandWord = command.getCommandWord();
        return commandMap.getOrDefault(commandWord, cmd -> new NoOpAction(actionable)).apply(command);
    }
}