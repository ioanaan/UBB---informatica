package repository.db;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

/**
 * Database repository for users (skeleton).
 * The methods will be implemented with JDBC in a future seminar.
 */
public class UserDBRepository implements Repository<Long, User> {

    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    public UserDBRepository(Validator<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public User findOne(Long id) {
        return null;
    }

    @Override
    public Iterable<User> findAll() {
        return null;
    }

    @Override
    public User save(User entity) {
        return null;
    }

    @Override
    public User delete(Long id) {
        return null;
    }

    @Override
    public User update(User entity) {
        return null;
    }
}
