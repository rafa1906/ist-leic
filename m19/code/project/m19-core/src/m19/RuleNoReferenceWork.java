package m19;

import java.io.Serializable;

/**
 * Class encoding the no reference works requests rule
 */
public class RuleNoReferenceWork extends Rule implements Serializable {

    @Override
    public boolean ok(User user, Work workToRequest) {
        return workToRequest.getCategory() != Category.REFERENCE;
    }
}