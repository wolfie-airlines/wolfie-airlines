#include "User.h"
#include "../functions/info_print_functions.h"
#include "../env/EnvParser.h"
#include "../functions/helpers.h"
#include "../admin/Admin.h"
#include <utility>

User::User(std::string username, std::string email, double discount, std::string discountType, std::string premiumCard,
           std::string paymentMethod, mongocxx::client &client, std::string  profession,
           std::string registrationDate, double moneySpent, double moneySaved, int ticketBought,
           std::vector<bsoncxx::document::value> userFlights, bool isAdmin)
        : username(std::move(username)), email(std::move(email)),
        discount(discount), discountType(std::move(discountType)), premiumCard(std::move(premiumCard)),
        paymentMethod(std::move(paymentMethod)), _client(client),
        profession(std::move(profession)), registrationDate(std::move(registrationDate)),
        moneySpent(moneySpent), moneySaved(moneySaved), ticketBought(ticketBought),
        userFlights(std::move(userFlights)), isAdmin(isAdmin)  {}

void User::reset() {
    username = "gosc";
    email = "brak";
    discount = 0.0;
    discountType = "brak";
    premiumCard = "brak";
    paymentMethod = "blik";
    profession = "brak";
    registrationDate = "brak";
    moneySpent = 0;
    moneySaved = 0;
    ticketBought = 0;
    userFlights.clear();
    isAdmin = false;
}
mongocxx::collection& User::getCollection() {
    return _collection;
}

mongocxx::collection User::getSpecificCollection(const std::string &collectionName) {
    return _db[collectionName];
}

std::string User::getPassword() {
    std::string hashedPassword = hashString(password);
    return hashedPassword;
}

void User::setPassword(const std::string &newPass) {
    User::password = newPass;
}

void User::changeUsername(const std::string &newUsername) {
    // sprawdzenie czy nazwa jest zajeta
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("username", newUsername)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    if (cursor.begin() != cursor.end()) {
        errorFunction("Nazwa użytkownika jest już zajęta.", "");
        return;
    }

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        std::cout << email << " " << password << std::endl;
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("username", newUsername)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    username = newUsername;
    validFunction("Nazwa użytkownika została pomyślnie zmieniona.", "");
}

void User::changeEmail(const std::string &newEmail) {
    //sprawdzanie czy email jest zajety
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", newEmail)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    if (cursor.begin() != cursor.end()) {
        errorFunction("Ten adres e-mail jest już zajęty.", "");
        return;
    }

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        std::cout << email << " " << password << std::endl;
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("email", newEmail)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    email = newEmail;
    validFunction("Adres e-mail został pomyślnie zmieniony.", "");
}

void User::changePassword(const std::string &newPassword) {

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        std::cout << email << " " << password << std::endl;
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    std::cout << "Podaj ponownie nowe hasło żeby potwierdzić zmianę: ";
    std::string repeatedPassword;
    std::cin >> repeatedPassword;
    if (newPassword != repeatedPassword) {
        errorFunction("Podane hasła nie są takie same.", "Spróbuj ponownie.");
        return;
    }

    std::cout << "Podaj stare hasło żebyśmy mieli 200% pewności że to ty: ";
    std::string oldPassword;
    std::cin >> oldPassword;
    if (oldPassword != password) {
        errorFunction("Podane hasło nie jest poprawne.", "Spróbuj ponownie.");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("password", newPassword)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    password = newPassword;
    validFunction("Hasło zostało pomyślnie zmienione.", "");
}


void User::addTicketToUser(const std::vector<int>& seats, const FlightConnection& flightConnection) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", getPassword())
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    if (cursor.begin() == cursor.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("ticketBought", ticketBought + (int) seats.size())
            ))
    );

    ticketBought += (int) seats.size();

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view, update_view);

    bsoncxx::builder::basic::array seats_array;
    for (const auto& seat : seats) {
        seats_array.append(seat);
    }

    std::string flightId = flightConnection.getIdentifier();
    std::string departure = flightConnection.getDepartureCity();
    std::string destination = flightConnection.getDestinationCity();
    std::string departureTime = flightConnection.getDepartureTime();
    std::string arrivalTime = flightConnection.getArrivalTime();
    auto flightPrice = flightConnection.getPrice();

    // sprawdzanie czy użytkownik "dokupuje" miejsca do zakupionego już lotu
    for (auto&& userFlight : userFlights) {
        bsoncxx::document::view userFlightView = userFlight.view();
        std::string userFlightId = (std::string) userFlightView["flightId"].get_string().value;
        if (userFlightId == flightId) {
            bsoncxx::document::value flight_filter_builder = bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("email", email),
                    bsoncxx::builder::basic::kvp("password", password),
                    bsoncxx::builder::basic::kvp("userFlights.flightId", flightId)
            );
            _collection.update_one(flight_filter_builder.view(), bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("$push", bsoncxx::builder::basic::make_document(
                            bsoncxx::builder::basic::kvp("userFlights.$.seats", bsoncxx::builder::basic::make_document(
                                    bsoncxx::builder::basic::kvp("$each", seats_array)
                            ))
                    ))
            ));
            validFunction("Bilet został pomyślnie zakupiony.", "Możesz zobaczyć go w zakładce 'Moje bilety'.");
            return;
        }
    }

    // jeśli nie dokupuje to zakupuje nowy bilet
    bsoncxx::document::value ticket_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("flightId", flightId),
            bsoncxx::builder::basic::kvp("departure", departure),
            bsoncxx::builder::basic::kvp("destination", destination),
            bsoncxx::builder::basic::kvp("departureTime", departureTime),
            bsoncxx::builder::basic::kvp("arrivalTime", arrivalTime),
            bsoncxx::builder::basic::kvp("price", flightPrice),
            bsoncxx::builder::basic::kvp("seats", seats_array),
            bsoncxx::builder::basic::kvp("checkin", false)
    );

    bsoncxx::document::view ticket_view = ticket_builder.view();
    _collection.update_one(filter_view, bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$push", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("userFlights", ticket_view)
            ))
    ));

    if(seats.size() == 1) {
        validFunction("Bilet został pomyślnie zakupiony.", "Możesz zobaczyć go w zakładce 'Moje bilety'.");
    } else {
        validFunction("Bilety zostały pomyślnie zakupione.", "Możesz zobaczyć je w zakładce 'Moje bilety'.");
    }

}

void User::updateMoneySaved(double normPrice, double discPrice) {
    double saved = normPrice - discPrice;
    moneySaved += saved;

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", getPassword())
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    if (cursor.begin() == cursor.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("moneySaved", moneySaved += saved)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view, update_view);
}

void User::loginAsAdmin() {
    if(isAdmin) {
        errorFunction("Jesteś już zalogowany jako administrator.", "");
        return;
    }
    EnvParser envParser;
    envParser.parseEnvFile();
    std::string adminPassword = envParser.getValue("ADMIN_PASSWORD");
    std::string adminPasswordHashed = hashString(adminPassword);

    std::cout << "Podaj hasło administratora: ";
    std::string providedPassword;
    std::cin >> providedPassword;

    std::string providedPasswordHashed = hashString(providedPassword);

    if(providedPasswordHashed == adminPasswordHashed) {
        validFunction("Zalogowano jako administrator.", "");
        Admin admin = Admin(username, email, discount, discountType, premiumCard, paymentMethod, _client, profession, registrationDate, moneySpent, moneySaved, ticketBought, userFlights, true, adminPasswordHashed);
        setIsAdmin(true);
    } else {
        errorFunction("Błędne hasło administratora.", "");
    }

}

bool User::checkIfAdmin() const {
    return isAdmin;
}