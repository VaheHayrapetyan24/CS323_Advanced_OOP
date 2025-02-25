import java.lang.reflect.*;

public class Person {
    String name, surname;
    int age, height, weight;

    // Correct constructor with no parameters
    public Person() {
        name = "N";
        surname = "N";
        age = height = weight = 0;
    }

    // Constructor with two String parameters
    public Person(String n, String s) {
        name = n;
        surname = s;
        age = height = weight = 0;
    }

    // Constructor with two String and three int parameters
    public Person(String n, String s, int a, int h, int w) {
        name = n;
        surname = s;
        age = a;
        height = h;
        weight = w;
    }

    public Person addAge(int x) {
        age += x;
        return this;
    }

    public Person changeName(String x, String y) {
          name = x; surname = y; 
          return this;
    }

    @Override
    public String toString() {
        return "Name: " + name + " " + surname + " \nAge: " + age + " Height: " + height + " Weight: " + weight;
    }

    public static void main(String args[]) throws Exception {
     
        Class<?> c = Person.class;

        // Define the parameter types for the constructor
        Class<?>[] ar = new Class[]{String.class, String.class};

        // Get the constructor with two String parameters
        Constructor<?> ctr = c.getConstructor(ar);
 
        // Create an instance using the constructor
        Object[] x = new Object[]{"Simon", "Baloian"};
        Object o = ctr.newInstance(x);

        // Print the object
        System.out.println(o);

       // Get the constructor with two String and three int parameters
        ar = new Class[]{String.class, String.class,int.class, int.class, int.class};
        ctr = c.getConstructor(ar);
       // Create an instance using the constructor
        x = new Object[]{"Andrea","Castillo",60,70,168};
        o = ctr.newInstance(x);
        System.out.println(o);
    }
}


   


   
