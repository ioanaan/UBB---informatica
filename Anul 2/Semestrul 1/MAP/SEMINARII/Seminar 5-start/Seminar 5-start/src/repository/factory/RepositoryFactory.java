package repository.factory;

import domain.User;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.db.UserDBRepository;
import repository.file.UserFileRepository;

import java.util.HashMap;
import java.util.Map;
import java.util.Properties;
import java.util.function.Supplier;

/**
 * Simple factory: the only place that knows the concrete repository classes.
 */
public class RepositoryFactory {

    private final Properties properties;

    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        String value = properties.getProperty("repository.type");
        if (value == null) {
            throw new IllegalArgumentException("The key repository.type is missing from the properties file");
        }

        RepositoryType type = RepositoryType.valueOf(value.trim().toUpperCase());

        Map<RepositoryType, Supplier<Repository<Long,User>>> map = new Map.of(
                RepositoryType.MEMORY, () -> new InMemoryRepository<>(validator),
                RepositoryType.FILE, () -> new UserFileRepository(validator, properties.getProperty()),
                RepositoryType.DATABASE, () -> new UserDBRepository(validator,
                properties.getProperty("db.url"),
                properties.getProperty("db.user"),
                properties.getProperty("db.password"))
        );
    }
}
