
abstract class GameItem {
    private String description;

    public String getDescription() {
        return description;
    }

    public abstract void encounterAction();
    public abstract void interactAction();
}