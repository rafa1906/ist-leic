package m19;

import java.io.Serializable;

/**
 * Normal user state
 */
public class Normal extends Classification implements Serializable {

    public Normal(User user, int onTimeDevolutions) { super(user, onTimeDevolutions); }

    @Override
    public int getMaxRequests() { return 3; }

    @Override
    public boolean isCompliant() { return false; }

    @Override
    public int getAvailableDays(Work work) {
        if (work.getCopies() == 1)
            return 3;
        else if (work.getCopies() <= 5)
            return 8;
        else
            return 15;
    }

    @Override
    public void updateClassification(boolean onTime) {
        if (onTime) {
            if (_onTimeDevolutions < 0) _onTimeDevolutions = 1;
            else _onTimeDevolutions++;
        } else {
            if (_onTimeDevolutions <= 0) _onTimeDevolutions--;
            else _onTimeDevolutions = -1;
        }

        if (_onTimeDevolutions == -3)
            _user.setClassification(new Faulty(_user));
        if (_onTimeDevolutions == 5)
            _user.setClassification(new Compliant(_user));
    }

    @Override
    @SuppressWarnings("nls")
    public String toString() { return "NORMAL"; }
}
