import React from "react";
import Navbar from "../components/navigation/Navbar";
import { Footer } from "../components/components/Footer";
import { BackgroundBeams } from "../components/components/BackgroundBeams";

export const Checkin = () => {
  //   const navigate = useNavigate();

  return (
    <div>
      <BackgroundBeams />
      <Navbar />
      <div className="py-12">
        <div className="container m-auto px-6 text-gray-600 md:px-12 xl:px-6">
          <section>
            <div className="2xl:mx-32">
              <div className="py-8 px-4 mx-auto max-w-screen-xl lg:py-8 lg:px-6 flex max-lg:flex-col">
                <div className="lg:ml-0 lg:text-start mx-auto max-w-screen-md text-center mb-8 lg:mb-12 ">
                  <h2 className="mb-4 text-4xl tracking-tight font-extrabold text-white firefox:font-inter">
                    Odprawy online
                  </h2>
                  <p className="text-gray-300 lg:mx-auto font-inter">
                    Chcesz odprawić się <strong>online</strong>? <br />Z{" "}
                    <strong>Wolfie Airlines</strong> to możliwe! <br />
                    <br />
                  </p>
                  <h2 className="font-inter mt-2 mb-1 text-lg tracking-tight font-semibold text-white">
                    Co potrzebujesz?
                  </h2>
                  <p className="text-gray-300 lg:mx-auto font-inter max-w-screen-md">
                    Do odprawy online jest obowiązkowy wygenerowany{" "}
                    <strong>kod QR</strong>, <br /> który wyświetla się po
                    zakupie biletów, bądź w naszej aplikacji, <br /> kiedy
                    użytkownik wybierze opcję <strong>odprawy online</strong>.
                    <br />
                    <span className="text-blue-500 font-semibold">
                      Wystarczy go zeskanować a magia zadzieje się sama!
                    </span>
                  </p>
                </div>

                <form className="max-w-sm justify-end flex-col items-end max-lg:justify-end max-lg:items-end max-lg:flex-col max-lg:mx-auto max-lg:pr-0">
                  <h2 className="text-end max-lg:text-center mb-4 text-3xl tracking-tight font-bold text-white firefox:font-inter">
                    Sprawdź czy masz wszystko potrzebne do odprawy:
                  </h2>
                  <div class="flex items-center justify-end mb-2">
                    <label
                      for="disabled-checked-checkbox"
                      class="me-2 text-lg font-medium text-gray-100 dark:text-gray-100"
                    >
                      Pobraną aplikację
                    </label>
                    <input
                      disabled
                      checked
                      id="disabled-checked-checkbox"
                      type="checkbox"
                      value=""
                      class="w-4 h-4 text-blue-600 bg-gray-100 border-gray-300 rounded focus:ring-blue-500 dark:focus:ring-blue-600 dark:ring-offset-gray-800 focus:ring-2 dark:bg-gray-700 dark:border-gray-600"
                    />
                  </div>
                  <div class="flex items-center justify-end mb-2">
                    <label
                      for="disabled-checked-checkbox"
                      class="me-2 text-lg font-medium text-gray-100 dark:text-gray-100"
                    >
                      Kupiony bilet
                    </label>
                    <input
                      disabled
                      checked
                      id="disabled-checked-checkbox"
                      type="checkbox"
                      value=""
                      class="w-4 h-4 text-blue-600 bg-gray-100 border-gray-300 rounded focus:ring-blue-500 dark:focus:ring-blue-600 dark:ring-offset-gray-800 focus:ring-2 dark:bg-gray-700 dark:border-gray-600"
                    />
                  </div>
                  <div class="flex items-center justify-end mb-2">
                    <label
                      for="disabled-checked-checkbox"
                      class="me-2 text-lg font-medium text-gray-100 dark:text-gray-100"
                    >
                      Przydzielone miejsce w samolocie
                    </label>
                    <input
                      disabled
                      checked
                      id="disabled-checked-checkbox"
                      type="checkbox"
                      value=""
                      class="w-4 h-4 text-blue-600 bg-gray-100 border-gray-300 rounded focus:ring-blue-500 dark:focus:ring-blue-600 dark:ring-offset-gray-800 focus:ring-2 dark:bg-gray-700 dark:border-gray-600"
                    />
                  </div>
                  <div class="flex items-center justify-end mb-2">
                    <label
                      for="disabled-checked-checkbox"
                      class="me-2 text-lg font-medium text-gray-100 dark:text-gray-100 whitespace-nowrap"
                    >
                      Uregulowane płatności (bagaż/zwierzęta/bilet)
                    </label>
                    <input
                      disabled
                      checked
                      id="disabled-checked-checkbox"
                      type="checkbox"
                      value=""
                      class="w-4 h-4 text-blue-600 bg-gray-100 border-gray-300 rounded focus:ring-blue-500 dark:focus:ring-blue-600 dark:ring-offset-gray-800 focus:ring-2 dark:bg-gray-700 dark:border-gray-600"
                    />
                  </div>
                  <div class="flex items-center justify-end mb-2">
                    <label
                      for="disabled-checked-checkbox"
                      class="me-2 text-lg font-medium text-gray-100 dark:text-gray-100"
                    >
                      Wygodny kocyk i przekąski
                    </label>
                    <input
                      disabled
                      checked
                      id="disabled-checked-checkbox"
                      type="checkbox"
                      value=""
                      class="w-4 h-4 text-blue-600 bg-gray-100 border-gray-300 rounded focus:ring-blue-500 dark:focus:ring-blue-600 dark:ring-offset-gray-800 focus:ring-2 dark:bg-gray-700 dark:border-gray-600"
                    />
                  </div>

                  <div className="flex items-end justify-end">
                    <button
                      type="button"
                      // onClick={() =>
                      //   navigate("app-release-link")
                      // }
                      className="max-sm:text-xs max-xl:text-sm font-inter py-2 px-6 mt-5 text-white font-semibold bg-blue-600 rounded-lg hover:bg-blue-700"
                    >
                      Pobierz naszą aplikację
                    </button>
                  </div>
                </form>
              </div>
            </div>
          </section>
        </div>
      </div>
      <Footer />
    </div>
  );
};
