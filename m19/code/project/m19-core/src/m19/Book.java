package m19;

import java.io.Serializable;

/**
 * Represents a book
 */
public class Book extends Work implements Serializable {

    private String _author;
    private String _isbn;

    public Book(int id, int stock, int price, String name, Category category, String author, String isbn) {
        super("Livro", id, stock, price, name, category);
        _author = author;
        _isbn = isbn;
    }

    public String getAuthor() { return _author; }
    public String getISBN() { return _isbn; }

    @Override
    public boolean beSearched(Search search, String s){
        return search.searchInBook(this, s);
    }

    @Override
    @SuppressWarnings("nls")
    public String toString(){
        return super.toString() + String.format(" - %s - %s", _author, _isbn);
    }
}