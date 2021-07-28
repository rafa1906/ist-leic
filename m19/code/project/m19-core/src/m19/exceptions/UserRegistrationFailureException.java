package m19.exceptions;

/**
 * Class encoding user registration failure.
 */
public class UserRegistrationFailureException extends Exception {

    /** Serial number for serialization. */
    static final long serialVersionUID = 201912042045L;

    private String _name;
    private String _email;

    public UserRegistrationFailureException(String name, String email) {
        _name = name;
        _email = email;
    }

    public String getName() { return _name; }
    public String getEmail() { return _email; }

}