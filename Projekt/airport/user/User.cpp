#include "User.h"
#include "../functions/info_print_functions.h"
#include <utility>

User::User(std::string username, std::string email, double discount, std::string discountType, std::string premiumCard,
           std::string paymentMethod, mongocxx::client &client, std::string  profession,
           std::string registrationDate, double moneySpent, int ticketBought,
           bsoncxx::array::view userFlights)
        : username(std::move(username)), email(std::move(email)),
        discount(discount), discountType(std::move(discountType)), premiumCard(std::move(premiumCard)),
        paymentMethod(std::move(paymentMethod)), _client(client),
        profession(std::move(profession)), registrationDate(std::move(registrationDate)),
        moneySpent(moneySpent), ticketBought(ticketBought),
        userFlights(userFlights)  {}


mongocxx::collection& User::getCollection() {
    return _collection;
}

mongocxx::collection User::getSpecificCollection(const std::string &collectionName) {
    return _db[collectionName];
}

std::string User::getPassword() {
    return password;
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
            bsoncxx::builder::basic::kvp("password", password)
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

    // zapisywanie LOTU
    bsoncxx::document::value ticket_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("flightId", flightId),
            bsoncxx::builder::basic::kvp("departure", departure),
            bsoncxx::builder::basic::kvp("destination", destination),
            bsoncxx::builder::basic::kvp("departureTime", departureTime),
            bsoncxx::builder::basic::kvp("arrivalTime", arrivalTime),
            bsoncxx::builder::basic::kvp("price", flightPrice),
            bsoncxx::builder::basic::kvp("seats", seats_array)
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