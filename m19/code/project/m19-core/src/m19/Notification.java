package m19;

import java.io.Serializable;

public class Notification implements Serializable {

    private Work _work;


    public Notification(Work work) { _work = work; }

    @Override
    @SuppressWarnings("nls")
    public String toString(){
        return "ENTREGA: " + _work.toString();
    }

}
