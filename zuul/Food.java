

class Food extends Item {
    public final int weight;
    public final int healthBoost;

    public final boolean isStorable = true;

    private String description;

    public Food(String name, int weight, int healthBoost) {
        super(name);
        this.weight = weight;
        this.healthBoost = healthBoost;
    }

    // interacting with Food = eating it
    public void interact(Player player) {
        player.increaseHealth(healthBoost);
    }


}