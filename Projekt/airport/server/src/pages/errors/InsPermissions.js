import { useNavigate } from "react-router-dom";
const InsPermissions = () => {
  const navigate = useNavigate();
  return (
    <section className="bg-gray-900 ">
      <div className="container flex items-center justify-center min-h-screen px-6 py-12 mx-auto">
        <div className="w-full ">
          <div className="flex flex-col items-center max-w-lg mx-auto text-center">
            <p className="text-4xl font-bold text-blue-400 firefox:font-inter">
              Hola hola! 🤚
            </p>
            <h1 className="mt-3 text-2xl font-semibold text-white md:text-3xl firefox:font-inter">
              Nie posiadasz permisji na dostęp do tej części strony!
            </h1>
            <p className="mt-4 text-gray-400 firefox:font-inter">
              Kolego, nie próbuj się włamywać! 🤨 <br />
              Nie masz permisji na wykonanie tej akcji. Jeśli uważasz, że
              powinieneś je mieć lub nie zostały Ci one jeszcze nadane proszę o
              kontakt z administratorem strony przez zakładkę
              <a href="/contact" className="text-blue-500 hover:underline">
                {" "}
                kontakt
              </a>
              .
            </p>
            <div className="flex items-center w-full mt-6 gap-x-3 shrink-0 sm:w-auto">
              <button
                onClick={() => navigate("/")}
                className="font-inter font-semibold w-1/2 px-5 py-2 text-sm tracking-wide text-white transition-colors duration-200 rounded-lg shrink-0 sm:w-auto hover:bg-blue-500 bg-blue-700"
              >
                🏠 Strona Główna
              </button>
            </div>
          </div>

          <div className="grid w-full max-w-6xl grid-cols-1 gap-8 mx-auto mt-8 sm:grid-cols-2 lg:grid-cols-2">
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
          </div>
        </div>
      </div>
    </section>
  );
};

export default InsPermissions;
