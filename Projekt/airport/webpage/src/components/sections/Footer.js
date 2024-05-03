export const Footer = ({ bgColor }) => {
  return (
    <footer className={`font-inter ${bgColor ? `${bgColor}` : ""}`}>
      <div className="max-w-screen-xl p-4 py-6 mx-auto lg:py-14 md:p-8 lg:p-10">
        <div className="grid grid-cols-1 gap-4 md:grid-cols-3 lg:grid-cols-3 justify-center">
          <div className="flex flex-col mx-auto max-md:text-center">
            <h3 className="mb-6 text-sm font-semibold text-gray-900 uppercase dark:text-white">
              Strona
            </h3>
            <ul className="text-gray-500 dark:text-gray-400">
              <li className="mb-4">
                <a href="/" className=" hover:underline">
                  Strona główna
                </a>
              </li>
              <li className="mb-4">
                <a href="/odprawy" className="hover:underline">
                  Odprawy
                </a>
              </li>
            </ul>
          </div>
          <div className="flex flex-col mx-auto max-md:text-center">
            <h3 className="mb-6 text-sm font-semibold text-gray-900 uppercase dark:text-white">
              Centrum pomocy
            </h3>
            <ul className="text-gray-500 dark:text-gray-400">
              <li className="mb-4">
                <a
                  href="https://github.com/szymonwilczek"
                  className="hover:underline"
                  target="_blank"
                  rel="noopener noreferrer"
                >
                  GitHub
                </a>
              </li>
              <li className="mb-4">
                <a
                  href="mailto:szymonwilczek@outlook.com"
                  className="hover:underline"
                >
                  Kontakt mailowy
                </a>
              </li>
            </ul>
          </div>
          <div className="flex flex-col mx-auto max-md:text-center">
            <h3 className="mb-6 text-sm font-semibold text-gray-900 uppercase dark:text-white">
              O twórcy
            </h3>
            <ul className="text-gray-500 dark:text-gray-400">
              <li className="mb-4">
                <a href="/info" className=" hover:underline">
                  Informacje
                </a>
              </li>
              <li className="mb-4">
                <a
                  href="https://szymon-wilczek.pl"
                  target="_blank"
                  rel="noopener noreferrer"
                  className="hover:underline"
                >
                  Portfolio
                </a>
              </li>
            </ul>
          </div>
        </div>
        <hr className="my-6 border-gray-200 sm:mx-auto dark:border-gray-700 lg:my-8" />
        <div className="text-center">
          <div className="font-inter flex items-center justify-center mb-5 text-2xl font-semibold text-gray-900 dark:text-white font-ubuntu">
            <img
              src="https://i.imgur.com/MLlNSm4.png"
              className="h-14 mr-3 sm:h-16"
              alt="Logo"
            />
            WOLFIE AIRLINES
          </div>
          <span className="block text-sm text-center text-gray-500 dark:text-gray-400">
            © 2024 WOLFIE Szymon Wilczek™. Wszystkie prawa zastrzeżone.
          </span>
          <ul className="flex justify-center mt-5 space-x-5">
            <li>
              <a
                href="https://github.com/szymonwilczek"
                target="_blank"
                rel="noopener noreferrer"
                className="hover:text-white text-gray-400 transition-colors duration-200"
              >
                <svg
                  className="w-5 h-5"
                  fill="currentColor"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                >
                  <path
                    fillRule="evenodd"
                    d="M12 2C6.477 2 2 6.484 2 12.017c0 4.425 2.865 8.18 6.839 9.504.5.092.682-.217.682-.483 0-.237-.008-.868-.013-1.703-2.782.605-3.369-1.343-3.369-1.343-.454-1.158-1.11-1.466-1.11-1.466-.908-.62.069-.608.069-.608 1.003.07 1.531 1.032 1.531 1.032.892 1.53 2.341 1.088 2.91.832.092-.647.35-1.088.636-1.338-2.22-.253-4.555-1.113-4.555-4.951 0-1.093.39-1.988 1.029-2.688-.103-.253-.446-1.272.098-2.65 0 0 .84-.27 2.75 1.026A9.564 9.564 0 0112 6.844c.85.004 1.705.115 2.504.337 1.909-1.296 2.747-1.027 2.747-1.027.546 1.379.202 2.398.1 2.651.64.7 1.028 1.595 1.028 2.688 0 3.848-2.339 4.695-4.566 4.943.359.309.678.92.678 1.855 0 1.338-.012 2.419-.012 2.747 0 .268.18.58.688.482A10.019 10.019 0 0022 12.017C22 6.484 17.522 2 12 2z"
                    clipRule="evenodd"
                  />
                </svg>
              </a>
            </li>
            <li>
              <a href="https://szymon-wilczek.pl">
                <svg
                  className="w-5 h-5 hover:text-white text-gray-400 transition-colors duration-200"
                  aria-hidden="true"
                  xmlns="http://www.w3.org/2000/svg"
                  fill="currentColor"
                  viewBox="0 0 20 20"
                >
                  <path d="m7.164 3.805-4.475.38L.327 6.546a1.114 1.114 0 0 0 .63 1.89l3.2.375 3.007-5.006ZM11.092 15.9l.472 3.14a1.114 1.114 0 0 0 1.89.63l2.36-2.362.38-4.475-5.102 3.067Zm8.617-14.283A1.613 1.613 0 0 0 18.383.291c-1.913-.33-5.811-.736-7.556 1.01-1.98 1.98-6.172 9.491-7.477 11.869a1.1 1.1 0 0 0 .193 1.316l.986.985.985.986a1.1 1.1 0 0 0 1.316.193c2.378-1.3 9.889-5.5 11.869-7.477 1.746-1.745 1.34-5.643 1.01-7.556Zm-3.873 6.268a2.63 2.63 0 1 1-3.72-3.72 2.63 2.63 0 0 1 3.72 3.72Z" />
                </svg>
              </a>
            </li>
          </ul>
        </div>
      </div>
    </footer>
  );
};
