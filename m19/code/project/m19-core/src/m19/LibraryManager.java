package m19;

import java.io.ObjectOutputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;

import m19.exceptions.MissingFileAssociationException;
import m19.exceptions.FailedToOpenFileException;
import m19.exceptions.BadEntrySpecificationException;
import m19.exceptions.ImportFileException;
import m19.exceptions.UserRegistrationFailureException;
import m19.exceptions.NoSuchUserIdException;
import m19.exceptions.NoSuchWorkIdException;
import m19.exceptions.RuleFailureException;
import m19.exceptions.WorkNotBorrowedException;
import m19.exceptions.UserNotSuspendedException;


/**
 * The façade class.
 */
public class LibraryManager {

  private Library _library  = new Library();
  private String _filename = "";
  private boolean _saved = true;


  public int getDate() { return _library.getDate(); }

  public String getFilename() {
    return _filename;
  }

  public boolean isSaved() {
    return _saved;
  }

  public void setFilename(String filename) { _filename = filename; }

  public void advanceDate(int daysToAdvance) {
    _library.setDate(_library.getDate() + daysToAdvance);
    _library.update(daysToAdvance);
    _saved = false;
  }

  /** @see m19.Library#registerUser(String name, String email) */
  public int registerUser(String name, String email) throws UserRegistrationFailureException {
    int id = _library.registerUser(name, email);
    _saved = false;

    return id;
  }

  /** @see m19.Library#showUser(int id) */
  public String showUser(int id) throws NoSuchUserIdException { return _library.showUser(id); }
  
  /** @see m19.Library#showUsers() */
  public String showUsers() { return _library.showUsers(); }
  
  /**@see m19.Library#shoUserNotifications(int id) */
  public String showUserNotifications(int id) throws NoSuchUserIdException { return _library.showUserNotifications(id); }

  /** @see m19.Library#showWork(int id) */
  public String showWork(int id) throws NoSuchWorkIdException { return _library.showWork(id); }

  /** @see m19.Library#showWorks() */
  public String showWorks() { return _library.showWorks(); }

  /** @see m19.Library#searchWork(String s) */
  public String searchWork(String s){ return _library.searchWork(s); }

  /** @see m19.Library#requestWork(int uid, int wid) */
  public int requestWork(int uid, int wid) throws NoSuchUserIdException, NoSuchWorkIdException, RuleFailureException {
    int returnDay = _library.requestWork(uid, wid);
    _saved = false;

    return returnDay;
  }

  /** @see m19.Library#returnWork(int uid, int wid) */
  public int returnWork(int uid, int wid) throws NoSuchUserIdException, NoSuchWorkIdException, WorkNotBorrowedException {
    int fine = _library.returnWork(uid, wid);
    _saved = false;

    return fine;
  }

  /** @see m19.Library#payFine(int id) */
  public void payFine(int id) throws NoSuchUserIdException, UserNotSuspendedException {
    _library.payFine(id);
    _saved = false;
  }

  /** @see m19.Library#updateFine(int id, boolean payFine, int fine) */
  public void updateFines(int id, boolean payFine, int fine) {
    _library.updateFines(id, payFine, fine);
    _saved = false;
  }

  /** @see m19.Library#updateFine(int uid, int wid) */
  public void addInterested(int uid, int wid) {
    _library.addInterested(uid, wid);
    _saved = false;
  }

  /**
   * @throws MissingFileAssociationException
   * @throws IOException
   * @throws FileNotFoundException
   */
  public void save() throws MissingFileAssociationException, IOException {
    try {
      ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(_filename)));
      oos.writeObject(_library);
      oos.close();

      _saved = true;
    }
    catch (FileNotFoundException fnfe) { throw new MissingFileAssociationException(); }
  }

  /**
   * @param filename
   * @throws MissingFileAssociationException
   * @throws IOException
   */
  public void saveAs(String filename) throws MissingFileAssociationException, IOException {
    _filename = filename;
    save();
  }

  /**
   * @param filename
   * @throws FailedToOpenFileException
   * @throws IOException
   * @throws ClassNotFoundException
   */
  public void load(String filename) throws FailedToOpenFileException, IOException, ClassNotFoundException {
    try {
      ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(new FileInputStream(filename)));
      _library = (Library) ois.readObject();
      ois.close();

      _filename = filename;
    }
    catch (FileNotFoundException fnfe) { throw new FailedToOpenFileException(filename); }
  }

  /**
   * @param datafile
   * @throws ImportFileException
   */
  public void importFile(String datafile) throws ImportFileException {
    try {
      _library.importFile(datafile);
      _saved = false;
    } catch (UserRegistrationFailureException | IOException | BadEntrySpecificationException e) {
      throw new ImportFileException(e);
    }
  }
}
