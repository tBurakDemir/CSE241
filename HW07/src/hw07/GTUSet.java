//Burak Demir
//131044045
//Hw07

package hw07;

import hw07.GTUSetInt;
import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import java.util.Arrays;
import java.util.NoSuchElementException;

public class GTUSet<T> implements GTUSetInt<T> {

    private T[] _data;
    private int size = 0, max_size = 10;


    @Override
    public boolean empty() {
        return size == 0;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public int max_size() {
        return max_size;
    }

    @Override
    public void insert(T element) throws InvalidParameterException {

        for (int i = 0; i < size; i++) {
            if(_data[i].equals(element))
                throw new InvalidParameterException();
        }

        if(size < max_size) {
            _data[size] = element;
            size++;
        }
        else
        {
            resize(size*2+1);
            _data[size] = element;
            size++;
        }

    }
    public GTUSet() {

        this.size = 0;
        this.max_size = 10;
        _data = (T[])new Object[10];

    }



    public GTUSet(int size) {

        this.size = 0;
        this.max_size = size;
    }

    public GTUSet(Class<T[]> cls) {
        this.size = 0;
        this.max_size = 10;
        _data = cls.cast(Array.newInstance(cls.getComponentType(), max_size));
    }

    public GTUSet(Class<T[]> cls, int size) {
        this.size = size;
        this.max_size = size*2;
        _data = cls.cast(Array.newInstance(cls.getComponentType(), max_size));
    }

    public GTUSet(T[] _data, int size, int max_size) {

        this._data = _data;
        this.size = size;
        this.max_size = max_size;
    }

    public void resize(int newSize){

        max_size = newSize;
        _data = Arrays.copyOf(_data, max_size);

    }

    public T getElement(int index){
        return _data[index];
    }

    //The returned set is the intersection of this set and the given set.
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other) {

        GTUSet<T> interSet = new GTUSet();
        GTUIterator myitr =  this.begin();
        GTUIterator otheritr = other.begin();
        T elem = null;
        while (myitr.hasNext()){
            elem = (T) myitr.next();
            while (otheritr.hasNext()){
                if(otheritr.next().equals(elem))
                    interSet.insert(elem);
            }
            otheritr = other.begin();

        }
        return  interSet;
    }

    @Override
    public void erase(T element) {

        int index = 0;
        for (int i = 0; i < size; i++) {
            if(_data[i].equals(element))
                index = i;
        }
        GTUIterator itr = find(element); //Pass the element
        if(itr.hasNext()) {
            itr.next();
            while (itr.hasNext()) {
                _data[index] = (T) itr.next();
                index++;
            }
        }
        _data[--size] = null;

    }

    @Override
    public void clear() {
        for (int i = 0; i < size; i++) {
            _data[i] = null;
        }
        size = 0;
    }

    @Override
    public GTUIterator find(T element) {

        GTUIterator gtuIterator = new GTUIterator(element);
        return gtuIterator;
    }

    @Override
    public int count(T element) {
        GTUIterator itr = begin();
        while(itr.hasNext())
            if(itr.next().equals(element))
                return 1;
        return 0;
    }

    @Override
    public GTUIterator begin() {
        return find(_data[0]);
    }

    @Override
    public GTUIterator end() {
        return find(_data[size-1]);
    }

    public class GTUIterator {

        private int cursor = 0;

        GTUIterator(){

        }

        GTUIterator(T elem){
            for (int i = 0; i < size; i++) {
                if(_data[i].equals(elem)){
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

        T next(){
            T elem;

            if (hasNext()){
                elem = (T) _data[cursor++];
            }
            else
                throw new NoSuchElementException();

            return elem;
        }

        T previous(){
            T elem;
            if (hasPrevious()){
                elem = (T) _data[cursor--];
            }
            else
                throw new NoSuchElementException();

            return elem;
        }

    }

}
