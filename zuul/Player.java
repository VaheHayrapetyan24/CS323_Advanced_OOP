import java.util.HashMap;

class Player {
    public final int MAX_WEIGHT = 10;
    public final int MAX_HEALTH = 100;

    private HashMap<String, Food> backpack;
    private int health;

    public Player() {
        backpack = new HashMap<>();
        health = MAX_HEALTH;
    }

    public String getBackpackItems() {
        return "Backpack items: " + String.join(", ", backpack.keySet()) + ".";
    }

    public Food getFromBackpack(String name) {
        return backpack.get(name);
    }

    public boolean isInBackpack(String name) {
        return backpack.containsKey(name);
    }

    public Food removeFromBackpack(String name) {
        return backpack.remove(name);
    }

    public void addToBackpack(Food food) {
        // It's caller's responsibility to check if can add or no
        if (!willFitInBackpack(food)) {
            return;
        }

        backpack.put(food.name, food);
    }

    public boolean willFitInBackpack(Food food) {
        return getBackpackWeight() + food.weight <= MAX_WEIGHT;
    }

    public int getBackpackWeight() {
        int weight = 0;
        for (Food food : backpack.values()) {
            weight += food.weight;
        }
        return weight;
    }

    public int getHealth() {
        return health;
    }

    public void damage(int amount) {
        health = Math.max(0, health - amount);
    }

    public void increaseHealth(int amount) {
        health = Math.min(MAX_HEALTH, health + amount);
    }
}