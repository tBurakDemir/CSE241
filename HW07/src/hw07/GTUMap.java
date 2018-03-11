//Burak Demir
//131044045
//Hw07


package hw07;

import hw07.GTUSet;
import java.security.InvalidParameterException;
import java.util.Arrays;
import java.util.NoSuchElementException;
import javafx.util.Pair;

public class GTUMap<K, V> extends GTUSet<javafx.util.Pair<K, V> > {

    private javafx.util.Pair<K, V>[] pair;
    private int size;
    private int max_size;

    public GTUMap() {
        size = 0;
        max_size = 10;
        pair = new Pair[10];

    }


    public GTUIterator find(Pair<K,V> element) {

        GTUIterator gtuIterator = new GTUIterator(element);
        return gtuIterator;
    }


    V at(K k){

        for (int i = 0; i < size(); i++) {
            if(pair[i].getKey().equals(k))
                return pair[i].getValue();
        }
        return null;
    }

    public void insert(javafx.util.Pair element) throws InvalidParameterException {

        for (int i = 0; i < size; i++) {
            if(pair[i].getKey().equals(element.getKey()))
                throw new InvalidParameterException();
        }

        if(size < max_size) {
            pair[size] = element;
            //key[size] = element.getKey();
            //value[size] = element.getValue();

            size++;
        }
        else
        {
            resize(size*2+1);
            pair[size]=element;

            //key[size] = element.getKey();
            //value[size] = element.getValue();

            size++;
        }
    }

    public GTUMap(int size) {
        pair = new Pair[size];
    }

    public GTUMap(Class<javafx.util.Pair<K, V>[]> cls) {
        super(cls);
    }

    public GTUMap(Class<javafx.util.Pair<K, V>[]> cls, int size) {
        super(cls, size);
    }


    @Override
    public void resize(int newSize) {
        max_size = newSize;
        //key = Arrays.copyOf(key, max_size);
        //value = Arrays.copyOf(value, max_size);
        pair = Arrays.copyOf(pair, max_size);
    }

    @Override
    public int max_size() {
        return max_size;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean empty() {
        return size == 0;
    }

    @Override
    public GTUIterator begin() {
        return find(pair[0]);
    }

    @Override
    public GTUIterator end() {
        return find(pair[size-1]);
    }

    private class GTUIterator extends GTUSet.GTUIterator{

        private int cursor = 0;

        GTUIterator(Pair elem){
            for (int i = 0; i < size; i++) {
                if(pair[i].getKey().equals(elem.getKey())){
                    cursor = i;
                }
            }
        }


        boolean hasNext(){

            return cursor < size;
        }

        boolean hasPrevious(){

            return cursor >= 0;
        }

        Pair next(){
            Pair elem;

            if (hasNext()){
                elem = pair[cursor++];
            }
            else
                throw new NoSuchElementException();

            return elem;
        }

        Pair<K, V> previous(){
            Pair<K, V> elem;
            if (hasPrevious()){
                elem = pair[cursor--];
            }
            else
                throw new NoSuchElementException();

            return elem;
        }

        void setCursor(int index){
            cursor = index;
        }

    }

    @Override
    public void clear() {
        for (int i = 0; i < size; i++) {
            pair[i] = null;
        }
        size = 0;
    }

    @Override
    public int count(Pair<K, V> element) {
       int count = 0;
        for (int i = 0; i < size() ; i++) {
            if(pair[i].getValue().equals(element.getValue()))
                count++;
        }
        return count;
    }


    @Override
    public void erase(Pair<K, V> element) throws NoSuchElementException{

        int index = -1;
        for (int i = 0; i < size; i++) {
            if(pair[i].equals(element))
                index = i;
        }
        if (index == -1)
            throw new NoSuchElementException();


        GTUIterator itr = find(element); //Pass the element
        if(itr.hasNext()) {
            itr.next();
            while (itr.hasNext()) {
                pair[index] = itr.next();
                index++;
            }
        }
        pair[--size] = null;
    }
}
