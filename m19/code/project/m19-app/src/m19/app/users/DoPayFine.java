package m19.app.users;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;
import pt.tecnico.po.ui.DialogException;

import m19.LibraryManager;
import m19.app.exceptions.NoSuchUserException;
import m19.app.exceptions.UserIsActiveException;
import m19.exceptions.NoSuchUserIdException;
import m19.exceptions.UserNotSuspendedException;

/**
 * 4.2.5. Settle a fine.
 */
public class DoPayFine extends Command<LibraryManager> {

  private Input<Integer> _id;

  /**
   * @param receiver
   */
  public DoPayFine(LibraryManager receiver) {
    super(Label.PAY_FINE, receiver);
    _id = _form.addIntegerInput(Message.requestUserId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    try {
      _form.parse();
      _receiver.payFine(_id.value());
    } catch (NoSuchUserIdException nsuie) {
      throw new NoSuchUserException(_id.value());
    } catch (UserNotSuspendedException unse) {
      throw new UserIsActiveException(_id.value());
    }
  }
}
