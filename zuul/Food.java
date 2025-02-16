

class Food extends GameItem {
    public final String name;
    public final int weight;
    public final int healthBoost;

    private String description;

    public Food(String name, int weight, int healthBoost) {
        this.name = name;
        this.weight = weight;
        this.healthBoost = healthBoost;
    }

    public void encounterAction() {};

    public void interactAction() {

    }
}