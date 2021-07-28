package m19;

import java.io.Serializable;

/**
 * Class encoding the no double requests rule
 */
public class RuleNoDoubleRequest extends Rule implements Serializable {

    @Override
    public boolean ok(User user, Work workToRequest) {
        return !user.getRequests().containsKey(workToRequest.getID());
    }
}