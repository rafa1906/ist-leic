package m19.exceptions;

/**
 * Class encoding active user exception.
 */
public class UserNotSuspendedException extends Exception {

    /** Serial number for serialization. */
    static final long serialVersionUID = 201912060031L;

    private int _id;

    public UserNotSuspendedException(int id) {
        _id = id;
    }

    public int getId() {
        return _id;
    }

}