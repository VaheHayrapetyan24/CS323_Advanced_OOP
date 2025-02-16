

class Demon extends Item {
    public final String description;
    public final int damage;

    public Demon(String name, String description, int damage) {
        super(name);
        this.description = description;
        this.damage = damage;
    }

    public void encounter(Player player) {
        player.damage(this.damage);
    }
}