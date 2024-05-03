import React, { useEffect, useRef } from "react";
import PropTypes from "prop-types";
import "../../fonts/fonts.css";
import "../../css/App.css";
import { motion } from "framer-motion";
import { generateCardBoardNumber } from "../functions/BoardCardFunctions";

const BoardCardCanvas = ({
  height,
  width,
  imageUrl,
  user,
  email,
  flightId,
  departure,
  departureTime,
  destination,
  destinationTime,
  seat,
  gateNumber,
}) => {
  const canvasRef = useRef(null);
  useEffect(() => {
    const draw = (context) => {
      // Numer karty pokładowej
      context.fillStyle = "#585a5c";
      context.font = "bold 60px 'Girloy-Bold', sans-serif";

      const randomCode = generateCardBoardNumber();
      const letterSpacing = 1;

      let xCode = 3000;
      const yCode = 540;

      for (let i = 0; i < randomCode.length; i++) {
        context.fillText(randomCode[i], xCode, yCode);
        xCode += context.measureText(randomCode[i]).width + letterSpacing;
      }

      // Nazwa użytkownika
      context.fillStyle = "#585a5c";
      context.font = "bold 220px 'Gilroy-Bold', sans-serif";

      let xUser = 380;
      const yUser = 950;
      let username = user.toUpperCase();

      for (let i = 0; i < username.length; i++) {
        context.fillText(username[i], xUser, yUser);
        xUser += context.measureText(username[i]).width + letterSpacing;
      }

      //* Lewa kolumna

      // Gate
      context.fillStyle = "#585a5c";
      context.font = "bold 125px 'Gilroy-Bold', sans-serif";
      context.fillText(gateNumber, 700, 1290);

      // Miejsce
      context.fillStyle = "#585a5c";
      context.font = "bold 125px 'Gilroy-Bold', sans-serif";
      let rowNumber =
        seat % 9 === 0 ? Math.floor(seat / 9) : Math.floor(seat / 9) + 1;
      let seatInRow = seat % 9 === 0 ? 9 : seat % 9;

      let place = `R${rowNumber}M${seatInRow}`;
      context.fillText(place, 800, 1550);

      // Czas odlotu
      context.fillStyle = "#585a5c";
      context.font = "bold 120px 'Gilroy-Bold', sans-serif";
      context.fillText(departureTime, 1020, 1800);

      //* Prawa kolumna

      // Id lotu
      context.fillStyle = "#585a5c";
      context.font = "bold 150px 'Gilroy-Bold', sans-serif";
      context.fillText(flightId, 2500, 1030);

      // Miejsce odlotu
      context.fillStyle = "#585a5c";
      context.font = "bold 125px 'Gilroy-Bold', sans-serif";
      context.fillText(departure.toUpperCase(), 2525, 1280);

      // Miejsce przylotu
      context.fillStyle = "#585a5c";
      context.font = "bold 125px 'Gilroy-Bold', sans-serif";
      context.fillText(destination.toUpperCase(), 2550, 1530);

      // Czas przylotu
      context.fillStyle = "#585a5c";
      context.font = "bold 120px 'Gilroy-Bold', sans-serif";
      context.fillText(destinationTime, 2900, 1780);

      //* Prawa karta pokładowa

      // Nazwa użytkownika
      context.fillStyle = "#f2f3f4";
      let username2 = user.toUpperCase();
      let fontSize = 220;
      const yUser2 = 1020;

      if (username2.length > 10) {
        fontSize = 220 * (10 / username2.length);
      }

      context.font = `bold ${fontSize}px 'Gilroy-Bold', sans-serif`;

      let textWidth = 0;
      for (let i = 0; i < username2.length; i++) {
        textWidth += context.measureText(username2[i]).width;
      }

      let xUser2 = 4930;
      if (username2.length > 10) {
        xUser2 = xUser2 - textWidth / 2 - 40;
      } else {
        xUser2 = xUser2 - textWidth + 300;
      }

      for (let i = 0; i < username2.length; i++) {
        context.fillText(username2[i], xUser2, yUser2);
        xUser2 += context.measureText(username2[i]).width;
      }

      // Gate
      context.fillStyle = "#f2f3f4";
      context.font = "bold 105px 'Gilroy-Bold', sans-serif";
      context.fillText(gateNumber, 4530, 1350);

      // Miejsce
      context.fillStyle = "#f2f3f4";
      context.font = "bold 95px 'Gilroy-Bold', sans-serif";
      context.fillText(place, 4600, 1484);

      // Data lotu
      context.fillStyle = "#f2f3f4";
      context.font = "bold 95px 'Gilroy-Bold', sans-serif";
      let date = departureTime.split(" ")[0].slice(0, 5);
      context.fillText(date, 4630, 1625);

      // Id lotu
      context.fillStyle = "#f2f3f4";
      context.font = "bold 95px 'Gilroy-Bold', sans-serif";
      context.fillText(flightId, 5100, 1351);

      // Odlot
      context.fillStyle = "#f2f3f4";
      context.font = "bold 70px 'Gilroy-Bold', sans-serif";
      context.fillText(departure.toUpperCase(), 5170, 1465);

      // Przylot
      context.fillStyle = "#f2f3f4";
      context.font = "bold 70px 'Gilroy-Bold', sans-serif";
      context.fillText(destination.toUpperCase(), 5200, 1590);

      const courseCanvas = document.createElement("canvas");
      courseCanvas.width = 830;
      courseCanvas.height = 706;
      context.drawImage(courseCanvas, 0, 0);

      const tempCanvas = context.canvas.cloneNode();
      const singContext = tempCanvas.getContext("2d");
      singContext.fillStyle = "#192e50";
      singContext.font = "9px 'Ubuntu', serif";
      singContext.justifyContent = "center";

      context.drawImage(tempCanvas, 0, 0);

      singContext.clearRect(0, 0, tempCanvas.width, tempCanvas.height);
    };

    const canvas = canvasRef.current;
    const context = canvas.getContext("2d");
    const image = new Image();
    image.crossOrigin = "anonymous";

    image.onload = () => {
      context.drawImage(image, 0, 0, width, height);
      draw(context);
    };
    image.src = imageUrl;
  }, [
    height,
    width,
    imageUrl,
    user,
    seat,
    departureTime,
    flightId,
    departure,
    destination,
    destinationTime,
    gateNumber,
  ]);

  return (
    <motion.div
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      transition={{ duration: 2 }}
      className="z-[50]"
    >
      <canvas
        ref={canvasRef}
        height={height}
        width={width}
        className="rounded-xl mx-auto  h-auto w-3/5 mb-4 max-md:w-full z-[50]"
      />
    </motion.div>
  );
};

BoardCardCanvas.propTypes = {
  height: PropTypes.number.isRequired,
  width: PropTypes.number.isRequired,
  imageUrl: PropTypes.string.isRequired,
};

export default BoardCardCanvas;
