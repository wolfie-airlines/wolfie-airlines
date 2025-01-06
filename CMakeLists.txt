cmake_minimum_required(VERSION 3.27)
project(airport)

set(CMAKE_CXX_STANDARD 20)

add_executable(airport main.cpp
        env/env.h
        env/env.cpp
        authentication/authentication.cpp
        user/user.cpp
        functions/info_prints/info_prints.h
        functions/info_prints/info_prints.cpp
        flights/flight_connection.h
        flights/flight_connection.cpp
        functions/main_handler.cpp
        functions/main_handler.h
        flights/flights_functions/flight_functions.h
        flights/flights_functions/flight_functions.cpp
        flights/flights_functions/flight_prints/flight_prints.h
        flights/flights_functions/flight_prints/flight_prints.cpp
        tickets/tickets_prints/tickets_prints.cpp
        user/user_functions/user_prints/user_prints.h
        user/user_functions/user_prints/user_prints.cpp
        tickets/tickets.h
        tickets/tickets.cpp
        user/user_functions/user_settings/user_settings_handler.h
        user/user_functions/user_settings/user_settings_handler.cpp
        user/user_functions/user_payments/user_payment_functions.cpp
        user/user_functions/user_payments/user_payment_functions.h
        user/professions/user_profession_functions.h
        user/professions/user_profession_functions.cpp
        user/professions/user_profession_functions.h
        user/professions/profession_prints/profession_prints.h
        user/professions/profession_prints/profession_prints.cpp
        user/professions/profession_choice.h
        user/professions/profession_choice.cpp
        functions/helpers.h
        functions/helpers.cpp
        user/professions/profession_handler.h
        user/professions/profession_handler.cpp
        user/premium_cards/premium_cards.h
        user/premium_cards/premium_cards.cpp
        user/premium_cards/premium_cards.cpp
        user/premium_cards/premium_cards.h
        user/premium_cards/premium_cards_prints/premium_cards_prints.h
        user/premium_cards/premium_cards_prints/premium_cards_prints.cpp
        user/discounts/discounts_prints/discounts_prints.h
        user/discounts/discounts_prints/discounts_prints.cpp
        user/discounts/discounts.h
        user/discounts/discounts.cpp
        plane/plane.cpp
        plane/plane.h
        admin/admin.cpp
        admin/admin.h
        qr_code/qrcode_prints.h
        qr_code/qrcode_prints.cpp
        user/user_functions/user_tickets/user_tickets_prints.h
        user/user_functions/user_tickets/user_tickets_prints.cpp
        checkin/checkin_prints.h
        checkin/checkin_prints.h
        checkin/checkin_prints.cpp
        luggage/item/item.h
        luggage/item/item.cpp
        luggage/luggage.h
        luggage/luggage.cpp
        luggage/luggage.h
        luggage/luggage_prints/luggage_prints.h
        luggage/luggage_prints/luggage_prints.cpp
        luggage/item/item_handler.h
        luggage/item/item_handler.cpp
        luggage/item/item_handler.h
        luggage/item/item_handler.h
        functions/main_prints/main_prints.h
        functions/main_prints/main_prints.cpp
        functions/main_prints/main_prints.cpp
        authentication/auth_functions/user_authentication.h
        authentication/auth_functions/user_authentication.cpp
        luggage/luggage_handler.h
        luggage/luggage_handler.cpp
        admin/admin_functions/admin_functions.h
        admin/admin_functions/admin_functions.cpp
        admin/admin_prints/admin_prints.h
        admin/admin_prints/admin_prints.cpp
        admin/admin_functions/validators.h
        admin/admin_functions/validators.cpp
        resources.rc
        admin/admin_functions/managing_flights/flight_binary_tree.h
        admin/admin_functions/managing_flights/custom_flight.h
)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

project(airport LANGUAGES CXX VERSION 1.0.0)
target_link_libraries(airport
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
)


find_package(mongocxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/vcpkg/packages/mongo-cxx-driver_x64-windows")
find_package(bsoncxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/vcpkg/packages/mongo-cxx-driver_x64-windows")

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(airport PRIVATE cryptopp::cryptopp)

find_package(unofficial-nayuki-qr-code-generator CONFIG REQUIRED)
target_link_libraries(airport PRIVATE unofficial::nayuki-qr-code-generator::nayuki-qr-code-generator)

find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

