import java.util.ArrayList;

public class Flight {
    private final String flightNumber;
    private final String origin;
    private final String destination;
    private final String departureTime;
    private final String arrivalTime;
    private final int capacity;
    private final ArrayList<Passenger> passengers;

    public Flight(String flightNumber, String origin, String destination, String departureTime, String arrivalTime, int capacity) {
        this.flightNumber = flightNumber;
        this.origin = origin;
        this.destination = destination;
        this.departureTime = departureTime;
        this.arrivalTime = arrivalTime;
        this.capacity = capacity;
        this.passengers = new ArrayList<>();
    }

    public String getFlightNumber() {
        return flightNumber;
    }

    public String getOrigin() {
        return origin;
    }

    public String getDestination() {
        return destination;
    }

    public String getDepartureTime() {
        return departureTime;
    }

    public String getArrivalTime() {
        return arrivalTime;
    }

    public int getAvailableSeats() {
        return capacity - passengers.size();
    }

    public boolean bookTicket(Passenger passenger) {
        if (passengers.size() < capacity) {
            passengers.add(passenger);
            return true;
        }
        return false;
    }

    public void displayPassengerList() {
        for (Passenger passenger : passengers) {
            System.out.println("Pasazer: " + passenger.getName() + ", Paszport: " + passenger.getPassportNumber());
        }
    }
}
