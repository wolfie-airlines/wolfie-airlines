/**
 * @file luggage.h
 * @brief Ten plik zawiera deklarację klasy Luggage.
 */

#ifndef AIRPORT_LUGGAGE_H
#define AIRPORT_LUGGAGE_H

#include <vector>
#include <iostream>
#include "item/item.h"

class User;

/**
 * @class Luggage
 * @brief Ta klasa reprezentuje bagaż w systemie lotniska.
 */
class Luggage {
  std::vector<Item> items_; ///< Przedmioty w bagażu.
  double total_weight_ = 0.0; ///< Całkowita waga bagażu.

 public:
  /**
   * @brief Konstruuje nowy obiekt Luggage.
   * @param items Przedmioty w bagażu.
   * @param total_weight Całkowita waga bagażu.
   */
  Luggage(
      const std::vector<Item> &items,
      double total_weight
  ) : items_(items), total_weight_(total_weight) {}

  /**
   * @brief Przetwarza przedmioty i pobiera wagę.
   * @return Waga przedmiotów.
   */
  double ProcessItemsAndGetWeight();

  /**
   * @brief Potwierdza przedmioty w bagażu.
   * @param user Użytkownik potwierdzający przedmioty.
   * @return Krotka zawierająca boolean wskazujący, czy potwierdzenie było udane, i wiadomość typu string.
   */
  std::tuple<bool, std::string> ConfirmItems(User &user);

  const double overweight_fee_per_kg_ = 2.0; ///< Opłata za nadbagaż na kg.
  const double euro_to_pln_ = 4.32; ///< Kurs wymiany euro na pln.
  const double max_allowed_weight_ = 32.0; ///< Maksymalna dozwolona waga.
  double max_weight_ = 20.0; ///< Maksymalna waga.

  /**
   * @brief Oblicza opłatę za nadbagaż.
   * @param weight Waga bagażu.
   * @return Opłata za nadbagaż.
   */
  double CalculateOverweightFee(double weight) const;
};

#endif //AIRPORT_LUGGAGE_H