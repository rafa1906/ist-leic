package m19;

import java.io.Serializable;

/**
 * Class encoding the max requests available rule
 */
public class RuleMaxRequestsAvailable extends Rule implements Serializable {

    @Override
    public boolean ok(User user, Work workToRequest) {
        return user.getRequests().size() < user.getClassification().getMaxRequests();
    }
}