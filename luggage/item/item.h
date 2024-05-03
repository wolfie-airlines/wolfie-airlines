/**
 * @file item.h
 * @brief Ten plik zawiera deklarację klasy Item.
 */

#ifndef AIRPORT_ITEM_H
#define AIRPORT_ITEM_H

#include <string>
#include <vector>

class User;

/**
 * @class Item
 * @brief Ta klasa reprezentuje przedmiot w systemie lotniska.
 */
class Item {
  std::string item_name_; ///< Nazwa przedmiotu.
  std::string description_; ///< Opis przedmiotu.
  std::vector<std::string> hints_; ///< Wskazówki dotyczące przedmiotu.
  bool forbidden_; ///< Wskazuje, czy przedmiot jest zabroniony.
  bool registered_luggage_; ///< Wskazuje, czy przedmiot może być transportowany jako bagaż rejestrowany.
  bool hand_luggage_; ///< Wskazuje, czy przedmiot może być transportowany jako bagaż podręczny.
  bool pilot_allowance_; ///< Wskazuje, czy przedmiot wymaga zgody pilota do transportu.
  double max_count_; ///< Maksymalna liczba przedmiotów.
  double weight_; ///< Waga przedmiotu.
  std::string profession_; ///< Zawód związany z przedmiotem.
  std::string category_ = "special"; ///< Kategoria przedmiotu.

 public:
  /**
   * @brief Konstruuje nowy obiekt Item.
   * @param item_name Nazwa przedmiotu.
   * @param description Opis przedmiotu.
   * @param hints Wskazówki dotyczące przedmiotu.
   * @param forbidden Wskazuje, czy przedmiot jest zabroniony.
   * @param registered_luggage Wskazuje, czy przedmiot może być transportowany jako bagaż rejestrowany.
   * @param hand_luggage Wskazuje, czy przedmiot może być transportowany jako bagaż podręczny.
   * @param pilot_allowance Wskazuje, czy przedmiot wymaga zgody pilota do transportu.
   * @param max_count Maksymalna liczba przedmiotów.
   * @param weight Waga przedmiotu.
   * @param profession Zawód związany z przedmiotem.
   * @param category Kategoria przedmiotu.
   */
  Item(const std::string &item_name,
       const std::string &description,
       const std::vector<std::string> &hints,
       bool forbidden,
       bool registered_luggage,
       bool hand_luggage,
       bool pilot_allowance,
       double max_count,
       double weight,
       std::string &profession,
       std::string &category);

  /**
   * @brief Konstruuje nowy obiekt Item.
   * @param item_name Nazwa przedmiotu.
   * @param description Opis przedmiotu.
   * @param hints Wskazówki dotyczące przedmiotu.
   * @param forbidden Wskazuje, czy przedmiot jest zabroniony.
   * @param registered_luggage Wskazuje, czy przedmiot może być transportowany jako bagaż rejestrowany.
   * @param hand_luggage Wskazuje, czy przedmiot może być transportowany jako bagaż podręczny.
   * @param pilot_allowance Wskazuje, czy przedmiot wymaga zgody pilota do transportu.
   * @param max_count Maksymalna liczba przedmiotów.
   * @param weight Waga przedmiotu.
   * @param category Kategoria przedmiotu.
   */
  Item(const std::string &item_name,
       const std::string &description,
       const std::vector<std::string> &hints,
       bool forbidden,
       bool registered_luggage,
       bool hand_luggage,
       bool pilot_allowance,
       double max_count,
       double weight,
       std::string &category);

  /**
   * @brief Pobiera nazwę przedmiotu.
   * @return Nazwa przedmiotu.
   */
  [[nodiscard]] const std::string &GetItemName() const;

  /**
   * @brief Pobiera opis przedmiotu.
   * @return Opis przedmiotu.
   */
  [[nodiscard]] const std::string &GetDescription() const;

  /**
   * @brief Pobiera zawód związany z przedmiotem.
   * @return Zawód związany z przedmiotem.
   */
  [[nodiscard]] const std::string &GetProfession() const;

  /**
   * @brief Pobiera wskazówki dotyczące przedmiotu.
   * @return Wskazówki dotyczące przedmiotu.
   */
  [[nodiscard]] const std::vector<std::string> &GetHints() const;

  /**
   * @brief Sprawdza, czy przedmiot jest zabroniony.
   * @return True, jeśli przedmiot jest zabroniony, false w przeciwnym razie.
   */
  [[nodiscard]] bool IsForbidden() const;

  /**
   * @brief Sprawdza, czy przedmiot może być transportowany jako bagaż rejestrowany.
   * @return True, jeśli przedmiot może być transportowany jako bagaż rejestrowany, false w przeciwnym razie.
   */
  [[nodiscard]] bool IsRegisteredLuggage() const;

  /**
   * @brief Sprawdza, czy przedmiot może być transportowany jako bagaż podręczny.
   * @return True, jeśli przedmiot może być transportowany jako bagaż podręczny, false w przeciwnym razie.
   */
  [[nodiscard]] bool IsHandLuggage() const;

  /**
   * @brief Sprawdza, czy przedmiot wymaga zgody pilota do transportu.
   * @return True, jeśli przedmiot wymaga zgody pilota do transportu, false w przeciwnym razie.
   */
  [[nodiscard]] bool IsPilotAllowance() const;

  /**
   * @brief Pobiera maksymalną liczbę przedmiotów.
   * @return Maksymalna liczba przedmiotów.
   */
  [[nodiscard]] double GetMaxCount() const;

  /**
   * @brief Pobiera wagę przedmiotu.
   * @return Waga przedmiotu.
   */
  [[nodiscard]] double GetWeight() const;

  /**
   * @brief Pobiera kategorię przedmiotu.
   * @return Kategoria przedmiotu.
   */
  [[nodiscard]] std::string GetCategory() const;
};

#endif  // AIRPORT_ITEM_H