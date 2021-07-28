package m19;

import java.io.Serializable;

/**
 * Abstract class for rules
 */
public abstract class Rule implements Serializable {

    public abstract boolean ok(User user, Work workToRequest);

}