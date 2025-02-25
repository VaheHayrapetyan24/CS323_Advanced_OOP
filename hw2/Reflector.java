import java.lang.reflect.*;
import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.stream.*;
import java.util.Scanner;

public class Reflector {
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter class name: ");
        String className = scanner.nextLine();

        System.out.print("Enter method name: ");
        String methodName = scanner.nextLine();

        System.out.print("Enter number of constructor arguments: ");
        int consArgCount = Integer.parseInt(scanner.nextLine());

        String[] consArgTypes = new String[consArgCount];
        String[] consArgValues = new String[consArgCount];

        for (int i = 0; i < consArgCount; i++) {
            System.out.print("Enter type of constructor argument " + (i + 1) + " (int/String): ");
            consArgTypes[i] = scanner.nextLine().equals("int") ? "int" : "java.lang.String";

            System.out.print("Enter value of constructor argument " + (i + 1) + ": ");
            consArgValues[i] = scanner.nextLine();
        }

        System.out.print("Enter number of method arguments: ");
        int methodArgCount = Integer.parseInt(scanner.nextLine());

        String[] methodArgTypes = new String[methodArgCount];
        String[] methodArgValues = new String[methodArgCount];

        for (int i = 0; i < methodArgCount; i++) {
            System.out.print("Enter type of method argument " + (i + 1) + " (int/String): ");
            methodArgTypes[i] = scanner.nextLine().equals("int") ? "int" : "java.lang.String";

            System.out.print("Enter value of method argument " + (i + 1) + ": ");
            methodArgValues[i] = scanner.nextLine();
        }

        scanner.close();

        Object obj = Reflector.perform(className, methodName, consArgTypes, consArgValues, methodArgTypes, methodArgValues);

        System.out.println(obj);
    }

    public static Object perform(
        String className,
        String methodName,
        String[] consArgTypes,
        String[] consArgValues,
        String[] methodArgTypes,
        String[] methodArgValues
    ) throws Exception {
        Class classObj = Class.forName(className);

        Class[] consArgClasses = Arrays.stream(consArgTypes).map(Reflector::getClassForName).toArray(size -> new Class[size]);
        Object[] consArgVals = IntStream.range(0, consArgValues.length)
            .mapToObj(i -> createInstance(consArgClasses[i], consArgValues[i]))
            .toArray(size -> new Object[size]);

        Constructor ctor = classObj.getConstructor(consArgClasses);

        Object obj = ctor.newInstance(consArgVals);

        Class[] methodArgClasses = Arrays.stream(methodArgTypes).map(Reflector::getClassForName).toArray(size -> new Class[size]);
        Method mthod = classObj.getMethod(methodName, methodArgClasses);
        Object[] mthodArgVals = IntStream.range(0, methodArgValues.length)
            .mapToObj(i -> createInstance(methodArgClasses[i], methodArgValues[i]))
            .toArray(size -> new Object[size]);

        Object result = mthod.invoke(obj, mthodArgVals);

        return result;
    }


    private static Class<?> getClassForName(String name) {
        if (name == "int") {
            return int.class;
        }
        try {
            return Class.forName(name);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private static Object createInstance(Class<?> clazz, String value) {
        if (clazz == int.class) {
            return Integer.parseInt(value);
        }
        try {
            Constructor<?> ctor = clazz.getConstructor(String.class);
            return ctor.newInstance(value);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

}