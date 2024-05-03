const mongoose = require("mongoose");

const flightSchema = new mongoose.Schema({
  _id: { type: mongoose.Schema.Types.ObjectId, required: true },
  identifier: String,
  departureCity: String,
  destinationCity: String,
  departureTime: String,
  arrivalTime: String,
  price: Number,
  availableSeats: Number,
  seatsTaken: [Number],
});

const flightModel = mongoose.model("flight_connections", flightSchema);

module.exports = flightModel;
