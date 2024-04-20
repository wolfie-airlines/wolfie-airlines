import { useNavigate } from "react-router-dom";
const NotFound = () => {
  const navigate = useNavigate();
  return (
    <section className="bg-gray-900 ">
      <div className="container flex items-center justify-center min-h-screen px-6 py-12 mx-auto">
        <div className="w-full ">
          <div className="flex flex-col items-center max-w-lg mx-auto text-center">
            <p className="text-4xl font-bold text-blue-400 firefox:font-inter">
              404
            </p>
            <h1 className="mt-3 text-2xl font-semibold text-white md:text-3xl firefox:font-inter">
              Strona nie istnieje
            </h1>
            <p className="mt-4 text-gray-400 firefox:font-inter">
              Przeszukaliśmy krainy i morza, lądy i jeziora. Byliśmy w
              Zasiedmiogórogrodzie ze Shrekiem i na pustkowiu Smauga. Niestety
              nawet tam nie byliśmy w stanie znaleźć tego czego szukasz. Ale
              znamy kapitana Jacka Sparrowa. Pożyczył nam kompas, który
              zaprowadzi Cię tam gdzie chcesz najbardziej. Możesz skorzystać z
              niego poniżej.
            </p>

            <button
              onClick={() => navigate("/sparrow")}
              className="p-2 font-inter text-md rounded-lg mt-2 bg-gradient-to-r from-teal-700 via-teal-800 to-teal-900"
            >
              🧭 Pokaż mi kompas!
            </button>

            <div className="flex items-center w-full mt-6 gap-x-3 shrink-0 sm:w-auto">
              <button className="flex items-center justify-center w-1/2 px-5 py-2 text-sm transition-colors duration-200 border rounded-lg text-gray-200 gap-x-2 sm:w-auto hover:bg-gray-800 bg-gray-900 border-gray-700">
                <svg
                  xmlns="http://www.w3.org/2000/svg"
                  fill="none"
                  viewBox="0 0 24 24"
                  strokeWidth="1.5"
                  stroke="currentColor"
                  className="w-5 h-5 rtl:rotate-180"
                >
                  <path
                    strokeLinecap="round"
                    strokeLinejoin="round"
                    d="M6.75 15.75L3 12m0 0l3.75-3.75M3 12h18"
                  />
                </svg>

                <span
                  className="font-inter font-bold"
                  onClick={() => navigate(-1)}
                >
                  Wróć
                </span>
              </button>

              <button
                onClick={() => navigate("/")}
                className="font-inter font-semibold w-1/2 px-5 py-2 text-sm tracking-wide text-white transition-colors duration-200 rounded-lg shrink-0 sm:w-auto hover:bg-blue-500 bg-blue-700"
              >
                🏠 Strona Główna
              </button>
            </div>
          </div>

          <div className="grid w-full max-w-6xl grid-cols-1 gap-8 mx-auto mt-8 sm:grid-cols-2 lg:grid-cols-3">
            <div className="p-6 rounded-lg bg-gray-800 border border-t border-gray-600">
              <span className="text-gray-400">
                <img
                  src="https://i.imgur.com/lx1mVG9.png"
                  alt="404-Kursy"
                  className="w-6 h-6 drag-none"
                />
              </span>

              <h3 className="mt-6 font-medium text-gray-200 font-inter">
                Kursy
              </h3>

              <p className="mt-2 text-gray-400 firefox:font-inter">
                Zanurkuj w fontannie wiedzy.
              </p>

              <div className="inline-flex items-center mt-4 text-sm font-inter gap-x-2 text-blue-400 hover:text-blue-500 transition-colors duration-200 hover:underline">
                <span
                  className="cursor-pointer"
                  onClick={() => navigate("/kursy")}
                >
                  Sprawdź
                </span>

                <svg
                  xmlns="http://www.w3.org/2000/svg"
                  fill="none"
                  viewBox="0 0 24 24"
                  strokeWidth="1.5"
                  stroke="currentColor"
                  className="w-5 h-5 rtl:rotate-180"
                >
                  <path
                    strokeLinecap="round"
                    strokeLinejoin="round"
                    d="M17.25 8.25L21 12m0 0l-3.75 3.75M21 12H3"
                  />
                </svg>
              </div>
            </div>

            <div className="p-6 rounded-lg bg-gray-800 border border-t border-gray-600">
              <span className=" text-gray-400">
                <img
                  src="https://i.imgur.com/mHRb0Yi.png"
                  alt="404-Artykuły"
                  className="w-6 h-6 drag-none"
                />
              </span>

              <h3 className="mt-6 font-medium text-gray-200 font-inter">
                Materiały
              </h3>

              <p className="mt-2 text-gray-400 firefox:font-inter">
                Zobacz co ciekawego w trawie piszczy w świecie matematyki.
              </p>

              <div className="inline-flex items-center mt-4 text-sm font-inter gap-x-2 text-blue-400 hover:text-blue-500 transition-colors duration-200 hover:underline">
                <span
                  className="cursor-pointer"
                  onClick={() => navigate("/materialy")}
                >
                  Zobacz
                </span>

                <svg
                  xmlns="http://www.w3.org/2000/svg"
                  fill="none"
                  viewBox="0 0 24 24"
                  strokeWidth="1.5"
                  stroke="currentColor"
                  className="w-5 h-5 rtl:rotate-180"
                >
                  <path
                    strokeLinecap="round"
                    strokeLinejoin="round"
                    d="M17.25 8.25L21 12m0 0l-3.75 3.75M21 12H3"
                  />
                </svg>
              </div>
            </div>

            <div className="p-6 rounded-lg bg-gray-800 border border-t border-gray-600">
              <span className="text-gray-400">
                <img
                  src="https://i.imgur.com/XbOqHOZ.png"
                  alt="404-Kontakt"
                  className="w-6 h-6 drag-none"
                />
              </span>

              <h3 className="mt-6 font-medium text-gray-200 font-inter">
                Skontaktuj się
              </h3>

              <p className="mt-2 text-gray-400 firefox:font-inter">
                Nawet kompas Sparrowa nie pomógł? Skontaktuj się z nami, żeby
                znaleźć to czego szukasz.
              </p>

              <div className="inline-flex items-center mt-4 text-sm font-inter gap-x-2 text-blue-400 hover:text-blue-500 transition-colors duration-200 hover:underline">
                <span
                  className="cursor-pointer"
                  onClick={() => navigate("/contact")}
                >
                  Napisz do nas
                </span>

                <svg
                  xmlns="http://www.w3.org/2000/svg"
                  fill="none"
                  viewBox="0 0 24 24"
                  strokeWidth="1.5"
                  stroke="currentColor"
                  className="w-5 h-5 rtl:rotate-180"
                >
                  <path
                    strokeLinecap="round"
                    strokeLinejoin="round"
                    d="M17.25 8.25L21 12m0 0l-3.75 3.75M21 12H3"
                  />
                </svg>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default NotFound;
