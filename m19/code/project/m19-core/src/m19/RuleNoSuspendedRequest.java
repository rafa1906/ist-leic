package m19;

import java.io.Serializable;

/**
 * Class encoding the no requests if user is suspended rule
 */
public class RuleNoSuspendedRequest extends Rule implements Serializable {

    @Override
    public boolean ok(User user, Work workToRequest) {
        return !user.isSuspended();
    }
}