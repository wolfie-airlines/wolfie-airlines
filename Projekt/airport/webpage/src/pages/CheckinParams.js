import React, { useEffect, useState } from "react";
import Navbar from "../components/navigation/Navbar";
import { Footer } from "../components/sections/Footer";
import { useParams } from "react-router-dom";
import TypewriterEffectSmooth from "../components/effects/TypewriterEffect";
import BoardCardCanvas from "../components/canvas/BoardCardCanvas";
import { motion } from "framer-motion";
import { generateGateNumber } from "../components/functions/BoardCardFunctions";
import { BackgroundBeams } from "../components/effects/BackgroundBeams";

export const CheckinParams = () => {
  //   const navigate = useNavigate();
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(false);
  const [departure, setDeparture] = useState("");
  const [departureTime, setDepartureTime] = useState("");
  const [destination, setDestination] = useState("");
  const [destinationTime, setDestinationTime] = useState("");
  const [gateNumber, setGateNumber] = useState(0);
  const [message, setMessage] = useState("");
  const [code, setCode] = useState(0);
  const { username, email, flightId, seats } = useParams();
  const seatsArray = seats.split(",").map(Number);

  useEffect(() => {
    fetch(
      `http://localhost:5000/odprawa/${username}/${email}/${flightId}/${seats}`
    )
      .then((response) => response.json())
      .then((data) => {
        if (data.type === "error") {
          setError(true);
          setMessage(data.error);
          setCode(data.code);
          setTimeout(() => {
            setLoading(false);
          }, 3500);
        } else {
          setMessage(data.message);
          setDeparture(data.departure);
          setDepartureTime(data.departureTime);
          setDestination(data.destination);
          setDestinationTime(data.destinationTime);
          setGateNumber(generateGateNumber());
          fetch(
            `http://localhost:5000/odprawa/accept/${username}/${email}/${flightId}/${seats}`
          ).then((response) => response.json());
          setTimeout(() => {
            setLoading(false);
          }, 3500);
        }
      })
      .catch((error) => console.log(error));
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return (
    <div>
      <Navbar />
      <div className="py-12">
        <div className="container m-auto px-6 text-gray-600 md:px-12 xl:px-6">
          <section>
            <div className="2xl:mx-32">
              <div className="py-8 px-4 mx-auto max-w-screen-xl lg:pt-2 lg:pb-0 lg:px-6 flex max-lg:flex-col">
                <div className="lg:text-center mx-auto max-w-screen-md text-center mb-8 lg:mb-2">
                  <h2 className="mb-4 text-4xl tracking-tight font-extrabold text-white firefox:font-inter">
                    Witamy na odprawie!
                  </h2>
                  <p className="text-gray-300 lg:mx-auto font-inter">
                    Chcesz odprawić się <strong>online</strong>? <br />Z{" "}
                    <strong>Wolfie Airlines</strong> to możliwe! <br />
                    <br />
                  </p>
                </div>
              </div>
            </div>
            {loading ? (
              <div className="flex items-center justify-center">
                <TypewriterEffectSmooth
                  words={[
                    { text: "Trwa " },
                    { text: "odprawa " },
                    { text: "online..." },
                  ]}
                />
              </div>
            ) : error ? (
              <div>
                <div className="flex items-center justify-center">
                  <TypewriterEffectSmooth
                    words={[
                      { text: "Błąd " },
                      { text: "odprawy " },
                      { text: "online..." },
                    ]}
                  />
                </div>
                <motion.div
                  initial={{ opacity: 0 }}
                  animate={{ opacity: 1 }}
                  transition={{ duration: 5 }}
                  className="flex flex-col justify-center items-center"
                >
                  <p className="text-white font-bold text-lg">{message}</p>
                  <p className="text-red-500 font-bold text-md">
                    Kod błędu: {code}
                  </p>
                </motion.div>
              </div>
            ) : (
              <div>
                <div className="flex justify-center items-center">
                  <TypewriterEffectSmooth
                    words={[{ text: "Odprawa " }, { text: "zakończona! " }]}
                  />
                </div>
                <motion.div
                  initial={{ opacity: 0 }}
                  animate={{ opacity: 1 }}
                  transition={{ duration: 5 }}
                  className="grid grid-cols-1 mb-2 z-[40]"
                >
                  {seatsArray.map((seat) => (
                    <BoardCardCanvas
                      key={seat}
                      width={5643}
                      height={2499}
                      imageUrl="https://i.imgur.com/o2paJAJ.png"
                      user={username}
                      email={email}
                      flightId={flightId}
                      departure={departure}
                      departureTime={departureTime}
                      destination={destination}
                      destinationTime={destinationTime}
                      seat={seat}
                      gateNumber={gateNumber}
                    />
                  ))}
                </motion.div>
              </div>
            )}
          </section>
        </div>
        <BackgroundBeams className="z-[30]" />
      </div>
      <Footer />
    </div>
  );
};
