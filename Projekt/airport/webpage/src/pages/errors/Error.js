import React, { useEffect } from "react";
import Navbar from "../../components/navigation/Navbar";
import { useNavigate, useParams } from "react-router-dom";
import { auth } from "../../firebase";

export const Error = () => {
  const navigate = useNavigate();
  const { errorMessage, errorType } = useParams();

  useEffect(() => {
    const unsubscribe = auth.onAuthStateChanged((user) => {
      if (!user) {
        return navigate("/login"); // Przekierowanie na stronę logowania
      }
    });

    return () => {
      unsubscribe();
    };
  }, [navigate]);

  return (
    <>
      <Navbar />
      <div className="py-12">
        <div className="container m-auto px-6 text-gray-600 md:px-12 xl:px-6">
          <div className="mb-12 space-y-2 text-center">
            <h2 className="text-3xl font-bold  md:text-4xl text-white firefox:font-inter">
              {errorType === "payment" &&
                "Płatność nie została zrealizowana ❌"}
              {errorType === "exchange" &&
                "Wymiana planu nie została zrealizowana ❌"}
              {errorType === "certificate" &&
                "Błąd podczas wyświetlania certyfikatu ❌"}
            </h2>
            <p className="text-gray-300 lg:mx-auto lg:w-6/12 font-inter">
              {errorType === "payment" &&
                "Nie udało się przetworzyć płatności. Spróbuj ponownie później bądź skontaktuj się z administracją."}
              {errorType === "exchange" &&
                "Nie udało się zrealizować wymiany. Spróbuj ponownie później bądź skontaktuj się z administracją."}
              Błąd:{" "}
              <span className="font-semibold text-red-500">{errorMessage}</span>{" "}
              <br />
              {errorType === "payment" &&
                "Nie martw się, nie pobrano żadnych środków z Twojego konta. Spróbuj ponownie później bądź skontaktuj się z administracją."}
              {errorType === "exchange" &&
                "Nie udało się zrealizować wymiany. Spróbuj ponownie później bądź skontaktuj się z administracją."}
              {errorType === "certificate" &&
                "Serwer odpowiedzialny za tworzenie certyfikatów nie odpowiada. Spróbuj ponownie później bądź skontaktuj się z administracją."}
            </p>
            <button
              className="px-4 py-2 mt-5 text-white bg-blue-500 rounded-md hover:bg-blue-600 font-inter"
              onClick={() => navigate("/home")}
            >
              Wróć do strony głównej
            </button>
          </div>
        </div>
      </div>
    </>
  );
};
