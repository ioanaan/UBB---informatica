package repository.factory;

import domain.User;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.db.UserDBRepository;
import repository.file.UserFileRepository;

import java.util.Properties;

public class RepositoryFactory {

    private final Properties properties;
    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    Repository<Long, User> createUserRepository(Validator<User> validator) {

        String value = properties.getProperty("repository.type");
        RepositoryType type = RepositoryType.valueOf(value.trim().toUpperCase());

        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UserFileRepository(validator, getProprity("file.name");
            case DATABASE:
                return new UserDBRepository(validator, proprities.getProprety("filename"));
                properties.
    }
}
