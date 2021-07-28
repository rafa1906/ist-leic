package m19.app.requests;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;
import pt.tecnico.po.ui.DialogException;

import m19.LibraryManager;
import m19.app.exceptions.NoSuchUserException;
import m19.app.exceptions.NoSuchWorkException;
import m19.app.exceptions.RuleFailedException;
import m19.exceptions.NoSuchUserIdException;
import m19.exceptions.NoSuchWorkIdException;
import m19.exceptions.RuleFailureException;

/**
 * 4.4.1. Request work.
 */
public class DoRequestWork extends Command<LibraryManager> {

  private Input<Integer> _uid;
  private Input<Integer> _wid;
  private Input<Boolean> _getNotifications;

  /**
   * @param receiver
   */
  public DoRequestWork(LibraryManager receiver) {
    super(Label.REQUEST_WORK, receiver);
    _uid = _form.addIntegerInput(Message.requestUserId());
    _wid = _form.addIntegerInput(Message.requestWorkId());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {
    try {
      _form.parse();

      int returnDay = _receiver.requestWork(_uid.value(), _wid.value());
      _display.popup(Message.workReturnDay(_wid.value(), returnDay));

    } catch (NoSuchUserIdException nsuie) {
      throw new NoSuchUserException(_uid.value());
    } catch (NoSuchWorkIdException nswie) {
      throw new NoSuchWorkException(_wid.value());
    } catch (RuleFailureException rfe) {
      if (rfe.getRuleIndex() != 3)
        throw new RuleFailedException(_uid.value(), _wid.value(), rfe.getRuleIndex());
      else {
        int uid = _uid.value();
        int wid = _wid.value();

        _form.clear();

        _getNotifications = _form.addBooleanInput(Message.requestReturnNotificationPreference());
        _form.parse();

        if (_getNotifications.value()) _receiver.addInterested(uid, wid);

        _form.clear();

        _uid = _form.addIntegerInput(Message.requestUserId());
        _wid = _form.addIntegerInput(Message.requestWorkId());
      }
    }
  }

}
