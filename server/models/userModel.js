const mongoose = require("mongoose");

const flightSchema = new mongoose.Schema({
  flightId: String,
  departure: String,
  destination: String,
  departureTime: String,
  arrivalTime: String,
  price: Number,
  seats: [Number],
  checkin: Boolean,
});

const userSchema = new mongoose.Schema({
  _id: { type: mongoose.Schema.Types.ObjectId, required: true },
  username: String,
  email: String,
  password: String,
  profession: String,
  premiumCard: String,
  moneySpent: Number,
  moneySaved: Number,
  ticketBought: Number,
  discountType: String,
  discount: Number,
  registrationDate: String,
  paymentMethod: {
    type: { type: String },
    cardNumber: String,
    cvv: String,
  },
  userFlights: [flightSchema],
});

const userModel = mongoose.model("users", userSchema);

module.exports = userModel;
