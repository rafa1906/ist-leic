package m19;

import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

import m19.exceptions.BadEntrySpecificationException;
import m19.exceptions.UserRegistrationFailureException;
import m19.exceptions.NoSuchUserIdException;
import m19.exceptions.NoSuchWorkIdException;
import m19.exceptions.RuleFailureException;
import m19.exceptions.WorkNotBorrowedException;
import m19.exceptions.UserNotSuspendedException;

/**
 * Class that represents the library as a whole.
 */
public class Library implements Serializable {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201901101348L;

  private Map<Integer, User> _users = new TreeMap<Integer, User>();
  private Map<Integer, Work> _works = new TreeMap<Integer, Work>();

  private Rule[] _rules = new Rule[6];

  private int _date = 0;

  public Library() {
      _rules[0] = new RuleNoDoubleRequest();
      _rules[1] = new RuleNoSuspendedRequest();
      _rules[2] = new RuleNoCopiesAvailable();
      _rules[3] = new RuleMaxRequestsAvailable();
      _rules[4] = new RuleNoReferenceWork();
      _rules[5] = new RuleNoExpensiveWork();
  }

  public Map<Integer, Work> getWorks() { return _works; }
  public int getDate() { return _date; }

  public void setDate(int date) { _date = date; }

  /**
   * Registers a user
   *
   * @param name
   *          name of the user to register
   * @param email
   *          email of the user to register
   * @return
   *          user id
   * @throws UserRegistrationFailureException
   */
  public int registerUser(String name, String email) throws UserRegistrationFailureException {
    if (name.equals("") || email.equals(""))
      throw new UserRegistrationFailureException(name, email);

    User user = new User(_users.size(), name, email);
    _users.put(user.getID(), user);

    return user.getID();
  }

  /**
   * Shows a user by id
   *
   * @param id
   * @return
   *          string with user data
   * @throws NoSuchUserIdException
   */
  public String showUser(int id) throws NoSuchUserIdException {
    if (id < 0 || id >= _users.size())
      throw new NoSuchUserIdException(id);

    return _users.get(id).toString();
  }

  /**
   * Shows all users
   *
   * @return
   *          string with data from all users
   */
  public String showUsers() {
      List<User> sortedUsers = new ArrayList<>(_users.values());
      String formattedUsers = "";

      Collections.sort(sortedUsers, new Comparator<User>() {
          @Override
          public int compare(User u1, User u2) {
              if (u1.getName() != u2.getName())
                  return u1.getName().compareTo(u2.getName());
              else
                  return u2.getID() - u1.getID();
          }
      });

      for (User user: sortedUsers)
          formattedUsers += user + "\n";

      return formattedUsers;
  }
  /**
   * Shows a user notifications by id
   *
   * @param id
   * @return
   *          string with user notifications
   * @throws NoSuchUserIdException
   */
  public String showUserNotifications(int id) throws NoSuchUserIdException {
    if (id < 0 || id >= _users.size())
        throw new NoSuchUserIdException(id);

    String formattedNotifications = "";

    for (String notification : _users.get(id).getNotifications())
        formattedNotifications += notification + "\n";

    _users.get(id).clearNotifications();

    return formattedNotifications;
  }

    /**
     * Registers a book
     *
     * @param title
     *          title of the book to register
     * @param author
     *          author of the book to register
     * @param price
     *          price of the book to register
     * @param category
     *          category of the book to register
     * @param isbn
     *          ISBN of the book to register
     * @param copies
     *          copies of the book to register
     * @return
     *          work id
     */
    public int registerBook(String title, String author, int price, String category, String isbn, int copies) {
        Work work = new Book(_works.size(), copies, price, title, Category.valueOf(category), author, isbn);
        _works.put(work.getID(), work);

        return work.getID();
    }

  /**
   * Registers a DVD
   * 
   * @param name
   *          name of the DVD to register
   * @param author
   *          author of the DVD to register
   * @param price
   *          price of the DVD to register
   * @param category
   *          category of the DVD to register
   * @param igac
   *          IGAC of the DVD to register
   * @param copies
   *          copies of the DVD to register
   * @return
   *          work id
   */
  public int registerDVD(String name, String director, int price, String category, String igac, int copies) {
    Work work = new DVD(_works.size(), copies, price, name, Category.valueOf(category), director, igac);
    _works.put(work.getID(), work);

    return work.getID();
  }

  /**
   * Shows a work by id
   *
   * @param id
   *          work id
   * @return
   *          string with work data
   * @throws NoSuchWorkIdException
   */
  public String showWork(int id) throws NoSuchWorkIdException {
    if (id < 0 || id >= _works.size())
      throw new NoSuchWorkIdException(id);

    return _works.get(id).toString();
  }
  
  /**
   * Shows all works
   *
   * @return
   *          string with data from all works
   */
  public String showWorks() {
    List<Work> sortedWorks = new ArrayList<>(_works.values());
    String formattedWorks = "";

    for(Work work: sortedWorks)
        formattedWorks += work + "\n";

    return formattedWorks;
  }
  
  /**
   * Show all works that contain the search param in relevant field
   * 
   * @param s
   *        string to search
   * @return
   *        string with data from works that contain string s in a relevant field
   */
  public String searchWork(String s) {
    Search searchMethod = new StringSearch();

    return searchMethod.searchInLibrary(this, s);
  }
  
  /**
   * Requests a work for a given user
   *
   * @param uid
   *            the user id
   * @param wid
   *            the work id
   * @throws NoSuchUserIdException
   * @throws NoSuchWorkIdException
   * @throws RuleFailureException
   */
  public int requestWork(int uid, int wid) throws NoSuchUserIdException, NoSuchWorkIdException, RuleFailureException {
      if (uid < 0 || uid >= _users.size())
          throw new NoSuchUserIdException(uid);
      if (wid < 0 || wid >= _works.size())
          throw new NoSuchWorkIdException(wid);

      for (int i = 0; i < 6; i++) {
          if (!_rules[i].ok(_users.get(uid), _works.get(wid)))
              throw new RuleFailureException(uid, wid, i + 1);
      }
      
      return _users.get(uid).request(_works.get(wid)) + _date;
  }

    /**
     * Returns a work for a given user
     *
     * @param uid
     *            the user id
     * @param wid
     *            the work id
     * @return
     *            the fine to pay (0 if there is none)
     * @throws NoSuchUserIdException
     * @throws NoSuchWorkIdException
     * @throws WorkNotBorrowedException
     */
  public int returnWork(int uid, int wid) throws NoSuchUserIdException, NoSuchWorkIdException, WorkNotBorrowedException {
      if (uid < 0 || uid >= _users.size())
          throw new NoSuchUserIdException(uid);
      if (wid < 0 || wid >= _works.size())
          throw new NoSuchWorkIdException(wid);

      return _users.get(uid).returnByWID(wid);
  }

    /**
     * Settles user fine
     *
     * @param id
     *              the user id
     * @throws NoSuchUserIdException
     * @throws UserNotSuspendedException
     */
  public void payFine(int id) throws NoSuchUserIdException, UserNotSuspendedException {
      if (id < 0 || id >= _users.size())
          throw new NoSuchUserIdException(id);
      if (!_users.get(id).isSuspended())
          throw new UserNotSuspendedException(id);

      _users.get(id).payFine();
  }

    /**
     * Updates fine data
     *
     * @param id
     *          the user id
     * @param payFine
     *          flag signaling if user wants to pay the fine or not
     * @param fine
     *          fine value
     */
  public void updateFines(int id, boolean payFine, int fine) {
      _users.get(id).updateFineData(payFine, fine);
  }

    /**
     * Updates user and request data
     *
     * @param daysToAdvance
     *          number of days to advance in the system
     */
  public void update(int daysToAdvance) {
      for (User u: _users.values())
          u.update(daysToAdvance);
  }

    /**
     * Adds a user to the interested in a work
     *
     * @param uid
     *            the user id
     * @param wid
     *            the work id
     */
  public void addInterested(int uid, int wid) { _works.get(wid).addInterested(_users.get(uid)); }

  /**
   * Read the text input file at the beginning of the program and populates the
   * instances of the various possible types (books, DVDs, users).
   * 
   * @param filename
   *          name of the file to load
   * @throws BadEntrySpecificationException
   * @throws IOException
   */
  void importFile(String filename) throws UserRegistrationFailureException, BadEntrySpecificationException, IOException {
      BufferedReader reader = new BufferedReader(new FileReader(filename));
      String line;

      while ((line = reader.readLine()) != null) {
          String[] fields = line.split(":");

          Pattern patUser = Pattern.compile("^(USER)");
          Pattern patBook = Pattern.compile("^(BOOK)");
          Pattern patDVD = Pattern.compile("^(DVD)");

          if (patUser.matcher(fields[0]).matches()) {
            registerUser(fields[1], fields[2]);
          } else if (patBook.matcher(fields[0]).matches()) {
            registerBook(fields[1], fields[2], Integer.parseInt(fields[3]), fields[4], fields[5], Integer.parseInt(fields[6]));
          } else if (patDVD.matcher(fields[0]).matches()) {
            registerDVD(fields[1], fields[2], Integer.parseInt(fields[3]), fields[4], fields[5], Integer.parseInt(fields[6]));
          } else {
            throw new BadEntrySpecificationException(line);
          }
      }
  }
}
