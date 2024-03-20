public class Main {
    public static void main(String[] args) {
        Flight flight = new Flight("POLSL24", "Radzionkow", "Gliwice", "10:00", "11:00", 100);

        Passenger passenger1 = new Passenger("Szymon Wilczek", "SW2024");
        if (flight.bookTicket(passenger1)) {
            if (passenger1.getName().endsWith("a")) {
                System.out.println("Pomyslnie zarezerwowano bilet Szanowna Pani " + passenger1.getName());
            } else {
                System.out.println("Pomyslnie zarezerwowano bilet Szanowny Panie " + passenger1.getName());
            }

        } else {
            System.out.println("Nie udalo sie zarezerwowac biletu. Lot jest juz pelny, wszystkie miejsca obsadzone.");
        }

        flight.displayPassengerList();
    }
}
