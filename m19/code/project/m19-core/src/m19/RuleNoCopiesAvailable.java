package m19;

import java.io.Serializable;

/**
 * Class encoding the no requests if no copies available rule
 */
public class RuleNoCopiesAvailable extends Rule implements Serializable {

    @Override
    public boolean ok(User user, Work workToRequest) {
        return workToRequest.getStock() > 0;
    }
}