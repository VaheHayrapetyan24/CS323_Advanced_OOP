
abstract class Item {
    public final String name;

    public Item(String name) {
        this.name = name;
    }

    public void encounter(Player player) {};
}