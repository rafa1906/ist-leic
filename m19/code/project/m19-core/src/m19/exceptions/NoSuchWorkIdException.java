package m19.exceptions;

/**
 * Class encoding work lookup failure.
 */
public class NoSuchWorkIdException extends Exception {

    /** Serial number for serialization. */
    static final long serialVersionUID = 201912041251L;

    /** Non-existent id. */
    private int _id;

    /**
     * @param id
     */
    public NoSuchWorkIdException(int id) {
        _id = id;
    }

    /**
     * @return
     *          the id
     */
    public int getId() {
        return _id;
    }

}