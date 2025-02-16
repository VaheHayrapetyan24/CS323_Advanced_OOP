
interface Actionable {
    public Room getCurrentRoom();
    public void setCurrentRoom(Room room);

    public int getHealth();
    public void setHealth();

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
        } else {
            actionable.setCurrentRoom(nextRoom);
            actionable.output(nextRoom.getLongDescription());
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
    private String validCommands[];

    public HelpAction(Actionable actionable, String validCommands[]) {
        this.actionable = actionable;
        this.validCommands = validCommands;
    }

    public boolean execute() {
        actionable.output("You are lost. You are alone. You wander\n");
        actionable.output("around at the university.\n\n");
        actionable.output("Your command words are: ");
        actionable.output(String.join(" ", validCommands) + "\n");

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
    private static final String validCommands[] = {
        "go", "quit", "help"
    };

    private Actionable actionable;
    private NoOpAction noOpAction;

    public CommandMapper(Actionable actionable) {
        this.actionable = actionable;
        this.noOpAction = new NoOpAction(actionable);
    }

    public Action getAction(Command command) {
        String commandWord = command.getCommandWord();

        if (commandWord == null) {
            return noOpAction;
        }
        
        switch (commandWord) {
            case "go":
                return new GoRoomAction(actionable, command);
            case "quit": 
                return new QuitAction(actionable, command);
            case "help":
                return new HelpAction(actionable, CommandMapper.validCommands);
            default:
                return noOpAction;
        }
    }

}