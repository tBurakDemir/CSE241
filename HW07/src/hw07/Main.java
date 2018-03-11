//@author Burak Demir
//131044045
//Hw07
package hw07;

/**
 *
 * @author burak
 */

import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.NoSuchElementException;
import javafx.util.Pair;


public class Main {

    public static void main(String[] args) throws Exception {

        testGtuSet();
        
        testGtuMap();

    }

    /*
    * Test all methods of GTUMap
    */
    public static void testGtuMap(){

        GTUMap<Integer, String> gtuMap = new GTUMap<>();
        GTUMap<Integer, String> emptyMap = new GTUMap<>();

        gtuMap.insert(new Pair<>(5, "a"));
        gtuMap.insert(new Pair<>(4, "b"));
        gtuMap.insert(new Pair<>(6, "a"));
        gtuMap.insert(new Pair<>(7, "c"));
        gtuMap.insert(new Pair<>(8, "d"));


        System.out.println("Empty Test");
        System.out.println("Empty Map: " + emptyMap.empty());
        System.out.println("Gtu Map: " + gtuMap.empty());

        System.out.println("\n\nSize Test");
        System.out.println("Empty Set: " + emptyMap.size());
        System.out.println("Gtu Set: " + gtuMap.size());

        System.out.println("\n\nInsert Test");
        try {
            gtuMap.insert(new Pair<>(1, "1a"));
            gtuMap.insert(new Pair<>(1, "2a"));
        }catch (InvalidParameterException e){
            System.out.println("Same key already in set!");
        }

        System.out.println("\n\nIterator and Find Test");

        GTUSet.GTUIterator itr = gtuMap.begin();
        System.out.println("\nFrom beginning");
        while (itr.hasNext())
            System.out.println(itr.next());


        System.out.println("\nFrom ending");
        itr = gtuMap.end();
        while (itr.hasPrevious())
            System.out.println(itr.previous());

        itr = gtuMap.find(new Pair<>(7, "7a"));
        System.out.println("\n7+7a and next pairs");
        while (itr.hasNext())
            System.out.println(itr.next());

        System.out.println("\n\nErase Test");
        try {
            System.out.println("Pair(6+6a) is deleted");
            gtuMap.erase(new Pair(6, "6a"));
            gtuMap.erase(new Pair<>(12, "12a"));

        }catch (NoSuchElementException e){
            System.out.println("The Pair(12+12a) doesnt exist. Erase failed.");
        }
        itr = gtuMap.begin();
        while(itr.hasNext())
            System.out.println(itr.next());

        System.out.println("\n\nCount Test");
        System.out.println("a in GtuMap: "+ gtuMap.count(new Pair<>(null, "a")));
        System.out.println("b in GtuMap: "+ gtuMap.count(new Pair<>(null, "b")));
        System.out.println("z in GtuMap: "+ gtuMap.count(new Pair<>(null, "z")));


        System.out.println("\n\nAt Test");
        System.out.println("Value of 5: "+gtuMap.at(5));
        System.out.println("Value of 7: "+gtuMap.at(7));
        System.out.println("Value of 22: "+gtuMap.at(22));

        System.out.println("\n\nClear Test");
        System.out.println("Pair of Gtumap:");
        gtuMap.clear();
        itr = gtuMap.begin();
        while(itr.hasNext())
            System.out.println(itr.next());
        System.out.println("Size: "+gtuMap.size());

    }

    /*
    * Test all methods of GTUSet
    */
    public static void testGtuSet(){

        GTUSet<Integer> gtuSet = new GTUSet(Integer[].class);
        GTUSet<Integer> gtuSet2 = new GTUSet(Integer[].class);
        GTUSetInt<Integer> interSet = new GTUSet(Integer[].class);
        GTUSet<Integer> emptySet = new GTUSet<>(Integer[].class);

        gtuSet.insert(1);
        gtuSet.insert(2);
        gtuSet.insert(3);
        gtuSet.insert(10);

        gtuSet2.insert(4);
        gtuSet2.insert(5);
        gtuSet2.insert(10);
        gtuSet2.insert(6);
        gtuSet2.insert(1);


        System.out.println("Empty Test");
        System.out.println("Empty Set: " + emptySet.empty());
        System.out.println("Gtu Set: " + gtuSet.empty());


        System.out.println("\n\nSize Test");
        System.out.println("Empty Set: " + emptySet.size());
        System.out.println("Gtu Set: " + gtuSet.size());

        System.out.println("\n\nInsert Test");
        try {
            gtuSet.insert(11);
            gtuSet.insert(11);
        }catch (InvalidParameterException e){
            System.out.println("Same value already in set!");
        }

        System.out.println("\n\nIterator and Find Test");

        GTUSet.GTUIterator itr = gtuSet.begin();
        System.out.println("\nFrom beginning");
        while (itr.hasNext())
            System.out.println(itr.next());

        itr = gtuSet.end();
        System.out.println("\nFrom ending");
        while (itr.hasPrevious())
            System.out.println(itr.previous());

        itr = gtuSet.find(3);
        System.out.println("\n3 and next elements");
        while (itr.hasNext())
            System.out.println(itr.next());


        System.out.println("\n\nIntersection Test");
        System.out.println("\n\nElement of IS Set");
        interSet = gtuSet.intersection(gtuSet2);
        itr = interSet.begin();
        while(itr.hasNext())
            System.out.println(itr.next());

        System.out.println("\n\nErase Test");
        System.out.println("Element of IS Set (Deleted 1)");
        interSet.erase(1);
        itr = interSet.begin();
        while(itr.hasNext())
            System.out.println(itr.next());


        System.out.println("\n\nCount Test");
        System.out.println("2 in GtuSet: "+ gtuSet.count(2));
        System.out.println("4 in GtuSet: "+ gtuSet.count(4));

        System.out.println("\n\nClear Test");
        System.out.println("Element of IS Set:");
        interSet.clear();
        itr = interSet.begin();
        while(itr.hasNext())
            System.out.println(itr.next());
        System.out.println("Size: "+interSet.size());

    }
}

