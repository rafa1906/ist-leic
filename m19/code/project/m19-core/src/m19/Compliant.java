package m19;

import java.io.Serializable;

/**
 * Compliant user state
 */
public class Compliant extends Classification implements Serializable {

    public Compliant(User user) { super(user, 0); }

    @Override
    public int getMaxRequests() { return 5; }

    @Override
    public boolean isCompliant() { return true; }

    @Override
    public int getAvailableDays(Work work) {
        if (work.getCopies() == 1)
            return 8;
        else if (work.getCopies() <= 5)
            return 15;
        else
            return 30;
    }

    @Override
    public void updateClassification(boolean onTime) {
        if (onTime) _onTimeDevolutions = 0;
        else _user.setClassification(new Normal(_user, -1));
    }

    @Override
    @SuppressWarnings("nls")
    public String toString() {
        return "CUMPRIDOR";
    }
}