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

    let flightForCheckin;

    for (let flight of existingUser.userFlights) {
      if (
        flight.flightId === flightId &&
        seats.every((seat) => flight.seats.includes(seat))
      ) {
        flightForCheckin = flight;
        break;
      }
    }

    if (!flightForCheckin) {
      console.log("Nie znaleziono odpowiedniego lotu.");
      return res.json({
        type: "error",
        error: "Nie znaleziono odpowiedniego lotu.",
        code: 4042,
      });
    }

    if (flightForCheckin.checkin) {
      console.log("Użytkownik już ma odprawę online.");
      return res.json({
        type: "error",
        error: "Użytkownik już ma odprawę online.",
        code: 4046,
      });
    }

    return res.json({
      type: "success",
      message: "Odprawa online zakończona pomyślnie.",
      username: username,
      email: email,
      flightId: flightId,
      departure: flightForCheckin.departure,
      departureTime: flightForCheckin.departureTime,
      destination: flightForCheckin.destination,
      destinationTime: flightForCheckin.arrivalTime,
      seats: seats,
    });
  } catch (error) {
    console.error(
      "Wystąpił błąd przy sprawdzeniu/zapisywaniu danych użytkownika",
      error
    );
    res.status(500).json({ error: "Błąd serwera" });
  }
});

app.get(
  "/odprawa/accept/:username/:email/:flightId/:seats",
  async (req, res) => {
    try {
      const username = req.params.username;
      const email = req.params.email;
      const flightId = req.params.flightId;

      const existingUser = await userModel.findOne({ username, email });
      if (!existingUser) {
        console.log("Nie znaleziono użytkownika w bazie danych.");
        return res.json({
          type: "error",
          error: "Nie znaleziono użytkownika w bazie danych.",
          code: 4042,
        });
      }

      let seats = req.params.seats;
      seats = seats.split(",").map((seat) => parseInt(seat));

      let userFlight;
      for (let flight of existingUser.userFlights) {
        if (
          flight.flightId === flightId &&
          seats.every((seat) => flight.seats.includes(seat))
        ) {
          userFlight = flight;
          break;
        }
      }

      if (!userFlight) {
        console.log("Nie znaleziono lotu w bazie danych użytkownika.");
        return res.json({
          type: "error",
          error: "Nie znaleziono lotu w bazie danych użytkownika.",
          code: 4043,
        });
      }

      if (userFlight.checkin) {
        console.log("Użytkownik już ma odprawę online.");
        return res.json({
          type: "error",
          error: "Użytkownik już ma odprawę online.",
          code: 4046,
        });
      }

      userFlight.checkin = true;
      await existingUser.save();

      return res.json({
        type: "success",
        message: "Odprawa online zakończona pomyślnie.",
      });
    } catch (error) {
      console.error(
        "Wystąpił błąd przy sprawdzeniu/zapisywaniu danych użytkownika",
        error
      );
      res.status(500).json({ error: "Błąd serwera" });
    }
  }
);

const port = process.env.PORT || 5000;
app.listen(port, () => {
  console.log(`Serwer startnął na porcie: ${port}`);
});

app.get("/", (req, res) => {
  res.send("Hello World!");
});
