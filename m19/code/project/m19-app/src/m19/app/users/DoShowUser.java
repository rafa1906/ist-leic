package m19.app.users;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;
import pt.tecnico.po.ui.DialogException;

import m19.LibraryManager;
import m19.app.exceptions.NoSuchUserException;
import m19.exceptions.NoSuchUserIdException;

/**
 * 4.2.2. Show specific user.
 */
public class DoShowUser extends Command<LibraryManager> {

  private Input<Integer> _id;

  /**
   * @param receiver
   */
  public DoShowUser(LibraryManager receiver) {
    super(Label.SHOW_USER, receiver);
    _id = _form.addIntegerInput(Message.requestUserId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    try {
      _form.parse();
      _display.popup(_receiver.showUser(_id.value()));
    } catch (NoSuchUserIdException nsuie) {
      throw new NoSuchUserException(_id.value());
    }
  }
}
