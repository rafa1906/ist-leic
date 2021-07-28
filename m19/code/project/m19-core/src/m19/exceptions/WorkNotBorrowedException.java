package m19.exceptions;

/**
 * Class encoding work not borrowed exception.
 */
public class WorkNotBorrowedException extends Exception {

    /** Serial number for serialization. */
    static final long serialVersionUID = 201912052344L;

    private int _wid;
    private int _uid;

    public WorkNotBorrowedException(int wid, int uid) {
        _wid = wid;
        _uid = uid;
    }

    public int getWid() { return _wid; }
    public int getUid() { return _uid; }
}