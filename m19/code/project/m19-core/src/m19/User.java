package m19;

import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.io.Serializable;

import m19.exceptions.WorkNotBorrowedException;

/**
 * Class that represents a user
 */
public class User implements Serializable {

    private int _id;
    private String _name;
    private String _email;
    private boolean _isSuspended = false;
    private int _fine = 0;
    private Classification _classification;

    private List<String> _notifications = new ArrayList<String>();
    private Map<Integer, Request> _requests = new TreeMap<Integer, Request>();

    public User(int id, String name, String email) {
        _id = id;
        _name = name;
        _email = email;
        _classification = new Normal(this, 0);
    }

    public int getID() { return _id; }
    public String getName() { return _name; }
    public boolean isSuspended() { return _isSuspended; }
    public Classification getClassification() { return _classification; }

    public List<String> getNotifications() { return _notifications; }
    public Map<Integer, Request> getRequests() { return _requests; }

    public void setClassification(Classification c) { _classification = c; }
    
    public void addNotification(Notification n) { _notifications.add(n.toString()); }

    public void clearNotifications() { _notifications.clear(); }
    
    public int request(Work workToRequest) {
        int daysToReturn = _classification.getAvailableDays(workToRequest);

        Request r = new Request(workToRequest, daysToReturn);
        _requests.put(workToRequest.getID(), r);

        workToRequest.setStock(workToRequest.getStock() - 1);

        return daysToReturn;
    }

    public int returnByWID(int wid) throws WorkNotBorrowedException {
        if (!_requests.containsKey(wid))
            throw new WorkNotBorrowedException(wid, _id);

        Work workToReturn = _requests.get(wid).getRequestedWork();
        workToReturn.setStock(workToReturn.getStock() + 1);
        workToReturn.notifyInterested();
        
        int fine = _requests.remove(wid).getFine() + _fine;

        if (fine == 0)
            _classification.updateClassification(true);
        else
            _classification.updateClassification(false);

        return fine;
    }

    public void payFine() {
        _fine = 0;

        for (Request r: _requests.values()) {
            if (r.isOverdue()) return;
        }

        _isSuspended = false;
    }

    public void updateFineData(boolean payFine, int fine) {
        if (!payFine) _fine = fine;
        else {
            fine = 0;

            for (Request r: _requests.values()) {
                if (r.isOverdue()) return;
            }

            _isSuspended = false;
        }
    }

    public void update(int daysToAdvance) {
        for (Request r: _requests.values()) {
            r.setDaysLeft(r.getDaysLeft() - daysToAdvance);

            if (r.getDaysLeft() < 0) {
                r.setFine(5 * Math.abs(r.getDaysLeft()));
                _isSuspended = true;

                if (!r.isOverdue())
                    r.setOverdue(true);
            }
        }
    }

    @Override
    @SuppressWarnings("nls")
    public String toString() {
        String formatted = "";

        if (!_isSuspended) {
            formatted = String.format("%d - %s - %s - %s - ACTIVO", _id, _name, _email,
                                      _classification);
        } else {
            formatted = String.format("%d - %s - %s - %s - SUSPENSO - EUR %d", _id, _name, _email,
                    _classification, _fine);
        }

        return formatted;
    }
}