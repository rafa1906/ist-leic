package m19;

import java.io.Serializable;

/**
 * Normal user state
 */
public class Faulty extends Classification implements Serializable {

    public Faulty(User user) { super(user, 0); }

    @Override
    public int getMaxRequests() { return 1; }

    @Override
    public boolean isCompliant() { return false; }

    @Override
    public int getAvailableDays(Work work) { return 2; }

    @Override
    public void updateClassification(boolean onTime) {
        if (onTime)  _onTimeDevolutions++;
        else _onTimeDevolutions = 0;

        if (_onTimeDevolutions == 3)
            _user.setClassification(new Normal(_user, 3));
    }


    @Override
    @SuppressWarnings("nls")
    public String toString() {
        return "FALTOSO";
    }
}