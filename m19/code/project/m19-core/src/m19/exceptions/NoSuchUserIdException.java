package m19.exceptions;

/**
 * Class encoding user lookup failure.
 */
public class NoSuchUserIdException extends Exception {

    /** Serial number for serialization. */
    static final long serialVersionUID = 201911121756L;

    /** Non-existent id. */
    private int _id;

    /**
     * @param id
     */
    public NoSuchUserIdException(int id) {
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