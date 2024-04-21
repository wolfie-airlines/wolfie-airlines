const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");
const dotenv = require("dotenv");
dotenv.config();

const app = express();
app.use(
  cors({
    origin: true,
  })
);

const userModel = require("./models/userModel");
const flightModel = require("./models/flightModel");

mongoose
  .connect(process.env.DATABASE_URL, {
    useNewUrlParser: true,
    autoIndex: false,
    connectTimeoutMS: 10000,
    family: 4,
    useUnifiedTopology: true,
  })
  .then(() => {
    console.log("Połączono z bazą danych.");
  })
  .catch((err) => {
    console.error("Wystąpił błąd podczas łączenia się z bazą danych: ", err);
  });

// Definicja endpointów API

//* Odprawa online
app.get("/odprawa/:username/:email/:flightId/:seats", async (req, res) => {
  try {
    const username = req.params.username;
    const email = req.params.email;
    const flightId = req.params.flightId;
    let seats = req.params.seats;
    seats = seats.split(",").map((seat) => parseInt(seat));

    console.log("username", username);
    console.log("email", email);
    console.log("flightId", flightId);
    console.log("seats", seats);

    // sprawdzanie czy lot istnieje
    const existingFlight = await flightModel.findOne({ identifier: flightId });
    if (!existingFlight) {
      console.log("Nie znaleziono lotu w bazie danych.");
      return res.json({
        type: "error",
        error: "Nie znaleziono lotu w bazie danych.",
        code: 4041,
      });
    }

    // sprawdzanie czy użytkownik istnieje
    const existingUser = await userModel.findOne({ username, email });
    if (!existingUser) {
      console.log("Nie znaleziono użytkownika w bazie danych.");
      return res.json({
        type: "error",
        error: "Nie znaleziono użytkownika w bazie danych.",
        code: 4042,
      });
    }

    // sprawdzanie czy ilość miejsc jest poprawna
    const userFlight = existingUser.userFlights.find(
      (flight) => flight.flightId === flightId
    );

    if (!userFlight) {
      console.log("Nie znaleziono lotu w bazie danych użytkownika.");
      return res.json({
        type: "error",
        error: "Nie znaleziono lotu w bazie danych użytkownika.",
        code: 4043,
      });
    }

    if (userFlight.seats.length !== seats.length) {
      console.log("Niepoprawna ilość miejsc.");
      return res.json({
        type: "error",
        error: "Niepoprawna ilość miejsc.",
        code: 4044,
      });
    }

    // sprawdź czy miejsca użytkownika z bazy danych są takie same jak te podane w parametrze
    const userSeats = userFlight.seats;
    const sortedUserSeats = userSeats.slice().sort();
    const sortedSeats = seats.slice().sort();

    // sprawdzenie czy tablice są identyczne
    if (JSON.stringify(sortedUserSeats) !== JSON.stringify(sortedSeats)) {
      console.log("Niepoprawne miejsca.");
      return res.json({
        type: "error",
        error: "Niepoprawne miejsca.",
        code: 4045,
      });
    }

    // sprawdzenie czy już wykonał odprawę
    if (userFlight.checkin) {
      console.log("Użytkownik już ma odprawę online.");
      return res.json({
        type: "error",
        error: "Użytkownik już ma odprawę online.",
        code: 4046,
      });
    }

    let foundFlight = existingUser.userFlights.find(
      (flight) => flight.flightId === flightId
    );
    foundFlight.checkin = true;

    await existingUser.save();

    return res.json({
      type: "success",
      message: "Odprawa online zakończona pomyślnie.",
      username: username,
      email: email,
      flightId: flightId,
      departure: foundFlight.departure,
      departureTime: foundFlight.departureTime,
      destination: foundFlight.destination,
      seats: seats,
    });
  } catch (error) {
    console.error(
      "Wystąpił błąd przy sprawdzeniu/zapisywaniu danych użytkownika",
      error
    );
    res.status(500).json({ error: "Server error" });
  }
});

const port = process.env.PORT || 5000;
app.listen(port, () => {
  console.log(`Serwer startnął na porcie: ${port}`);
});

app.get("/", (req, res) => {
  res.send("Hello World!");
});
