cmake_minimum_required(VERSION 3.27)
project(airport)

set(CMAKE_CXX_STANDARD 20)

add_executable(airport main.cpp
        env/EnvParser.h
        env/EnvParser.cpp
        authentication/Authentication.cpp
        user/User.cpp
        functions/info_print_functions.h
        functions/info_print_functions.cpp
        flights/FlightConnection.h
        flights/FlightConnection.cpp
        functions/handling_functions.cpp
        functions/handling_functions.h
        flights/flights_functions/flight_functions.h
        flights/flights_functions/flight_functions.cpp
        flights/flights_functions/flight_prints/flight_print_functions.h
        flights/flights_functions/flight_prints/flight_print_functions.cpp
        tickets/tickets_prints/tickets_print_functions.cpp
        user/user_functions/user_prints/user_print_functions.h
        user/user_functions/user_prints/user_print_functions.cpp
        tickets/tickets.h
        tickets/tickets.cpp
        user/user_functions/user_settings/user_settings_functions.h
        user/user_functions/user_settings/user_settings_functions.cpp
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


find_package(mongocxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/mongo-cxx-driver_x64-windows")
find_package(bsoncxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/mongo-cxx-driver_x64-windows")

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(airport PRIVATE cryptopp::cryptopp)

find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

