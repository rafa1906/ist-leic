package m19;

import java.io.Serializable;

/**
 * Represents a DVD
 */
public class DVD extends Work implements Serializable {

    private String _director;
    private String _igac;

    public DVD(int id, int stock, int price, String name, Category category, String director, String igac) {
        super("DVD", id, stock, price, name, category);
        _director = director;
        _igac = igac;
    }

    public String getDirector(){ return _director; }
    public String getIGAC(){ return _igac; }

    @Override
    public boolean beSearched(Search search, String s){
        return search.searchInDVD(this, s);
    }

    @Override
    @SuppressWarnings("nls")
    public String toString(){
        return super.toString() + String.format(" - %s - %s", _director, _igac);
    }
}