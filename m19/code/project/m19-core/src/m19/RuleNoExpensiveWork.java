package m19;

import java.io.Serializable;

/**
 * Class encoding the no works above 25EUR requests rule
 */
public class RuleNoExpensiveWork extends Rule implements Serializable {

    @Override
    public boolean ok(User user, Work workToRequest) {
        if (user.getClassification().isCompliant())
            return true;
        else
            return workToRequest.getPrice() <= 25;
    }
}