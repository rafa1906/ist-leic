package m19;

import java.io.Serializable;

/**
 * The user state class
 */
public abstract class Classification implements Serializable {

    protected User _user;
    protected int _onTimeDevolutions;

    public Classification(User user, int onTimeDevolutions) {
        _user = user;
        _onTimeDevolutions = onTimeDevolutions;
    }

    public abstract int getMaxRequests();
    public abstract boolean isCompliant();
    public abstract int getAvailableDays(Work work);
    public abstract void updateClassification(boolean onTime);

    public abstract String toString();

}