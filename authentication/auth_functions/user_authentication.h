/**
 * @file user_authentication.h
 * @brief This file contains the declarations of functions used for user authentication.
 */

#ifndef AIRPORT_AUTHPRINTHANDLER_H
#define AIRPORT_AUTHPRINTHANDLER_H

#include <string>
#include <tuple>
#include "../../user/user.h"
#include "../authentication.h"

/**
 * @brief Registers a new user.
 * @return A tuple containing the username, password, email, and a boolean indicating if the registration was successful.
 */
std::tuple<std::string, std::string, std::string, bool> RegisterUser();

/**
 * @brief Logs in a user.
 * @return A tuple containing the username, password, and a boolean indicating if the login was successful.
 */
std::tuple<std::string, std::string, bool> Login();

/**
 * @brief Handles the registration process.
 * @param auth The Authentication object.
 */
void HandleRegistration(Authentication &auth);

/**
 * @brief Handles the login process.
 * @param auth The Authentication object.
 * @param user The User object.
 * @return A boolean indicating if the login was successful.
 */
bool HandleLogin(Authentication &auth, User &user);

#endif  // AIRPORT_AUTHPRINTHANDLER_H