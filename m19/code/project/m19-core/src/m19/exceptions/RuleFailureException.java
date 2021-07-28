package m19.exceptions;

/**
 * Class encoding rule failure (for rules 1-2 and 4-6)
 */
public class RuleFailureException extends Exception {

    /** Serial number for serialization. */
    static final long serialVersionUID = 201912041253L;

    private int _uid;
    private int _wid;
    private int _ruleIndex;

    public RuleFailureException(int uid, int wid, int ruleIndex) {
        _uid = uid;
        _wid = wid;
        _ruleIndex = ruleIndex;
    }

    public int getUid() { return _uid; }
    public int getWid() { return _wid; }
    public int getRuleIndex() { return _ruleIndex; }

}