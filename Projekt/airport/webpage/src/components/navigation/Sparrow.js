import { useNavigate } from "react-router-dom";
import Container from "../components/Container";

export const Sparrow = () => {
  const navigate = useNavigate();
  return (
    <section>
      <Container>
        <div className="divide-y divide-gray-200 dark:divide-gray-700">
          <div className="space-y-2 pt-6 pb-4 md:space-y-5 mt-5">
            <h2 className="justify-center text-center mb-4 text-4xl tracking-tight font-extrabold text-white firefox:font-bold firefox:font-inter">
              Odnaleziono kompas Jacka Sparrowa!
            </h2>
            <p className="justify-center text-center font-inter font-semibold sm:text-xl md:px-12 text-gray-400">
              Zaprowadzi Cię on gdzie tylko zechcesz, ale pamiętaj, że nie
              wkroczy on na nieznane wody (strony dostępne tylko dla
              administracji).
            </p>
          </div>
          <img
            className="flex items-center justify-center mx-auto max-xl:w-2/3 rounded-xl mb-3"
            src={"https://i.imgur.com/FnDwlMY.gif"}
            alt="Sparrow"
            draggable="false"
          ></img>
          <div className="flex flex-col my-2 bg-gray-800 rounded-lg p-2 max-w-lg items-center justify-center mx-auto">
            <h2 className="justify-center text-center mt-2 text-2xl tracking-tight font-bold text-white firefox:font-bold firefox:font-inter">
              🧭 Wszystkie możliwe kierunki kompasu
            </h2>
            <div className="pt-8 pb-8 font-inter text-gray-200 text-lg items-center justify-center mx-auto">
              <ul className="max-lg:flex max-lg:flex-col list-disc items-center justify-center mx-auto">
                <li
                  className="hover:text-main transition-colors duration-200 font-inter font-semibold cursor-pointer"
                  onClick={() => navigate("/")}
                >
                  🏠 Strona główna
                </li>
                <li
                  className="hover:text-main transition-colors duration-200 font-inter font-semibold cursor-pointer"
                  onClick={() => navigate("/kursy")}
                >
                  ✈️ Odprawy
                </li>
                <li
                  className="hover:text-main transition-colors duration-200 font-inter font-semibold cursor-pointer"
                  onClick={() => navigate("/generator-zadan")}
                >
                  👤 O autorze
                </li>
              </ul>
            </div>
          </div>
        </div>
      </Container>
    </section>
  );
};
