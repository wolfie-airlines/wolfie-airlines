import { useNavigate } from "react-router-dom";

export const NotYetSection = () => {
  const navigate = useNavigate();
  return (
    <section className="bg-gray-900 ">
      <div className="container flex items-center justify-center min-h-screen px-6 py-12 mx-auto">
        <div className="w-full ">
          <div className="flex flex-col items-center max-w-lg mx-auto text-center">
            <svg
              className="mx-auto mb-4 w-10 h-10 text-gray-400"
              xmlns="http://www.w3.org/2000/svg"
              viewBox="0 0 512 512"
            >
              <path
                fill="currentColor"
                d="M331.8 224.1c28.29 0 54.88 10.99 74.86 30.97l19.59 19.59c40.01-17.74 71.25-53.3 81.62-96.65c5.725-23.92 5.34-47.08 .2148-68.4c-2.613-10.88-16.43-14.51-24.34-6.604l-68.9 68.9h-75.6V97.2l68.9-68.9c7.912-7.912 4.275-21.73-6.604-24.34c-21.32-5.125-44.48-5.51-68.4 .2148c-55.3 13.23-98.39 60.22-107.2 116.4C224.5 128.9 224.2 137 224.3 145l82.78 82.86C315.2 225.1 323.5 224.1 331.8 224.1zM384 278.6c-23.16-23.16-57.57-27.57-85.39-13.9L191.1 158L191.1 95.99l-127.1-95.99L0 63.1l96 127.1l62.04 .0077l106.7 106.6c-13.67 27.82-9.251 62.23 13.91 85.39l117 117.1c14.62 14.5 38.21 14.5 52.71-.0016l52.75-52.75c14.5-14.5 14.5-38.08-.0016-52.71L384 278.6zM227.9 307L168.7 247.9l-148.9 148.9c-26.37 26.37-26.37 69.08 0 95.45C32.96 505.4 50.21 512 67.5 512s34.54-6.592 47.72-19.78l119.1-119.1C225.5 352.3 222.6 329.4 227.9 307zM64 472c-13.25 0-24-10.75-24-24c0-13.26 10.75-24 24-24S88 434.7 88 448C88 461.3 77.25 472 64 472z"
              />
            </svg>
            <h1 className="md:whitespace-nowrap mb-4 text-4xl font-bold tracking-tight leading-none text-gray-900 lg:mb-6 xl:text-5xl dark:text-white">
              Trwa proces tworzenia tej części strony
            </h1>
            <p className="font-light text-gray-500 md:text-lg xl:text-xl dark:text-gray-400">
              Przepraszamy za utrudnienia. <br /> Mamy nadzieję, że wkrótce się
              tutaj zobaczymy!
            </p>
            <p className="mt-4 text-gray-400 firefox:font-inter">
              Nasz zespół (ja sam - jednoosobowa maszyna techniczna) dokłada
              wszelkich starań, żeby skończyć ten kurs najszybciej jak się da
              zachowując przy tym tym najwyższą jakość i spójność logiczną
              przekazywanej wiedzy. Wszystko po to, żebyś mógł się uczyć
              matematyki w jak najbardziej efektywny sposób. Dziękujemy za
              wyrozumiałość i cierpliwość.
            </p>

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
                Zanurkuj w fontannie wiedzy z której przybyłeś. Wybierz kurs,
                który obecnie jest dostępny i zacznij swoją przygodę z
                matematyką już od teraz!
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
                Nawet mapa Huncwotów nie jest w stanie odnaleźć tego czego
                szukasz? Skontaktuj się z nami, a wyczarujemy odpowiedź której
                szukasz.
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
