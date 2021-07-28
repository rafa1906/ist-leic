package m19.app.requests;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;
import pt.tecnico.po.ui.DialogException;

import m19.LibraryManager;
import m19.app.exceptions.NoSuchUserException;
import m19.app.exceptions.NoSuchWorkException;
import m19.app.exceptions.WorkNotBorrowedByUserException;
import m19.exceptions.NoSuchUserIdException;
import m19.exceptions.NoSuchWorkIdException;
import m19.exceptions.WorkNotBorrowedException;

/**
 * 4.4.2. Return a work.
 */
public class DoReturnWork extends Command<LibraryManager> {

  private Input<Integer> _uid;
  private Input<Integer> _wid;
  private Input<Boolean> _payFine;


  /**
   * @param receiver
   */
  public DoReturnWork(LibraryManager receiver) {
    super(Label.RETURN_WORK, receiver);
    _uid = _form.addIntegerInput(Message.requestUserId());
    _wid = _form.addIntegerInput(Message.requestWorkId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    try {
      _form.parse();

      int fine = _receiver.returnWork(_uid.value(), _wid.value());

      if (fine > 0) {
        _display.popup(Message.showFine(_uid.value(), fine));

        int uid = _uid.value();
        _form.clear();

        _payFine = _form.addBooleanInput(Message.requestFinePaymentChoice());
        _form.parse();

        _receiver.updateFines(uid, _payFine.value(), fine);
        
        _form.clear();

        _uid = _form.addIntegerInput(Message.requestUserId());
        _wid = _form.addIntegerInput(Message.requestWorkId());
      }

    } catch (NoSuchUserIdException nsuie) {
      throw new NoSuchUserException(_uid.value());
    } catch (NoSuchWorkIdException nswie) {
      throw new NoSuchWorkException(_wid.value());
    } catch (WorkNotBorrowedException rfe) {
      throw new WorkNotBorrowedByUserException(rfe.getWid(), rfe.getUid());
    }
  }

}
