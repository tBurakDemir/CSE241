//Burak Demir
//131044045
//Hw07

package hw07;

import java.security.InvalidParameterException;

public interface GTUSetInt<T> {
    
    /*Test whether container is empty*/
    boolean empty();
    
    //Return container size
    int size();

    //Return maximum size
    int max_size();

    //Insert element, 
    //throws exception InvalidParameterException 
    //if the element is already in the set
    void insert(T element) throws InvalidParameterException;
    
    //The returned set is the intersection of this set and the given set.
    GTUSetInt<T> intersection(GTUSetInt<T> other);

    //Erase element
    void erase(T element);

    //Clear all content
    void clear();

    //Get iterator to element
    GTUSet.GTUIterator find(T element);

    //Count elements with a specific value
    int count(T element);

    //Return iterator to beginning
    GTUSet<T>.GTUIterator begin();

    //Return iterator to end
    GTUSet<T>.GTUIterator end();
}
