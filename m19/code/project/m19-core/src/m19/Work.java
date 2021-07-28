package m19;

import java.io.Serializable;
import java.util.List;
import java.util.ArrayList;

/**
 * Abstract class representing a work
 */
public abstract class Work implements Serializable {

    private String _type;
    private int _id;
    private int _stock;
    private int _copies;
    private int _price;
    private String _title;
    private Category _category;
    private List<User> _interested = new ArrayList<User>();

    public Work(String type, int id, int copies, int price, String title, Category category) {
        _type = type;
        _id = id;
        _copies = copies;
        _stock = copies;
        _price = price;
        _title = title;
        _category = category;
    }

    public int getID() { return _id; }
    public int getCopies() { return _copies; }
    public int getStock() { return _stock; }
    public int getPrice() { return _price; }
    public String getTitle() { return _title; }
    public Category getCategory() { return _category; }
    
    public void setStock(int stock) { _stock = stock; }
    
    public abstract boolean beSearched(Search search, String s);
    
    public void addInterested(User u) { _interested.add(u); }

    public void notifyInterested() {
        Notification notification = new Notification(this);

        for (User user : _interested)
            user.addNotification(notification);

        _interested.clear();
    }
    
    @Override
    @SuppressWarnings("nls")
    public String toString(){
        return String.format("%d - %d de %d - %s - %s - %d - %s",
                                _id, _stock, _copies, _type, _title, _price, _category.toString());
    }

}