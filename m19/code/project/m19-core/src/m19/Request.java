package m19;

import java.io.Serializable;

/**
 * Class representing a request
 */
public class Request implements Serializable {

    private Work _requestedWork;
    private int _daysLeft;
    private int _fine = 0;
    public boolean _overdue = false;

    public Request(Work work, int days) {
        _requestedWork = work;
        _daysLeft = days;
    }

    public Work getRequestedWork() { return _requestedWork; }
    public int getDaysLeft() { return _daysLeft; }
    public int getFine() { return _fine; }
    public boolean isOverdue() { return _overdue; }

    public void setDaysLeft(int daysLeft) { _daysLeft = daysLeft; }
    public void setFine(int fine) { _fine = fine; }
    public void setOverdue(boolean overdue) { _overdue = overdue; }

}