package m19.app.main;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;

import m19.LibraryManager;

/**
 * 4.1.3. Advance the current date.
 */
public class DoAdvanceDate extends Command<LibraryManager> {

  private Input<Integer> _daysToAdvance;

  /**
   * @param receiver
   */
  public DoAdvanceDate(LibraryManager receiver) {
    super(Label.ADVANCE_DATE, receiver);
    _daysToAdvance = _form.addIntegerInput(Message.requestDaysToAdvance());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {
    _form.parse();
    if (_daysToAdvance.value() > 0)
      _receiver.advanceDate(_daysToAdvance.value());
  }
}
