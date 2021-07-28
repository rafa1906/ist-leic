package m19;

public interface Search {

    public abstract String searchInLibrary(Library lib, String s);
    public abstract boolean searchInBook(Book book, String s);
    public abstract boolean searchInDVD(DVD dvd, String s);

}