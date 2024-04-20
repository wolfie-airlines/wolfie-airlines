import { FaEnvelope, FaGithub } from "react-icons/fa";
import { BsGlobe2 } from "react-icons/bs";
import Container from "../components/Container";
import { useState } from "react";
const AboutSection = () => {
  const [isHovered, setIsHovered] = useState(false);
  const handleMouseEnter = () => {
    setIsHovered(true);
  };

  const handleMouseLeave = () => {
    setIsHovered(false);
  };

  const gifSrc = isHovered
    ? "https://i.imgur.com/ZOmDQD2.gif"
    : "https://i.imgur.com/7cCLWEY.gif";

  return (
    <section>
      <Container>
        <div className="divide-y divide-slate-700">
          <div className="space-y-2 pt-6 pb-8 md:space-y-5 mt-5">
            <h2 className="justify-center text-center mb-4 text-4xl tracking-tight font-bold text-white firefox:font-bold firefox:font-inter">
              Informacje o autorze
            </h2>
            <p className="justify-center text-center font-inter font-semibold sm:text-xl text-gray-400">
              Trochę informacji o mnie, skromnym twórcy tej strony i materiałów
            </p>
          </div>
          <div className="items-start space-y-2 xl:grid xl:grid-cols-3 xl:gap-x-8 xl:space-y-0">
            <div className="flex flex-col items-center pt-8">
              <div className="relative bg-cover bg-[50%] bg-no-repeat">
                <img
                  className="mask mask-squircle h-48 w-48 "
                  src="https://i.imgur.com/mPGyoJ0.png"
                  alt="avatar"
                  draggable="false"
                />
                <div class="mask mask-squircle absolute bottom-0 left-0 right-0 top-0 h-full w-full overflow-hidden bg-slate-900 bg-fixed opacity-20"></div>
              </div>
              <h3 className="pt-4 pb-2 text-2xl font-bold leading-8 tracking-tight">
                Szymon Wilczek
              </h3>
              <div className="text-gray-500 dark:text-gray-400 text-center">
                Programista, student informatyki, iżynier oprogramowania i
                miłośnik matematyki
              </div>
              <div className="flex space-x-3 pt-4">
                <ul className="flex justify-center space-x-4 max-md:mb-4">
                  <li>
                    <a
                      href="mailto:szymonwilczek@outlook.com"
                      className="text-gray-300 hover:text-white transition-colors duration-200"
                    >
                      <FaEnvelope className="w-6 h-6" />
                    </a>
                  </li>
                  <li className="max-md:mb-3">
                    <a
                      href="https://github.com/szymonwilczek"
                      target="_blank"
                      rel="noreferrer"
                      className=" hover:text-white text-gray-300 transition-colors duration-200"
                    >
                      <FaGithub className="w-6 h-6" />
                    </a>
                  </li>
                  <li className="max-md:mb-3">
                    <a
                      href="https://szymon-wilczek.pl"
                      target="_blank"
                      rel="noreferrer"
                      className=" hover:text-white text-gray-300 transition-colors duration-200"
                    >
                      <BsGlobe2 className="w-6 h-6" />
                    </a>
                  </li>
                </ul>
              </div>
            </div>
            <div className="font-inter font-normal max-w-2xl pt-8 pb-8 text-gray-200 text-lg xl:col-span-2 max-xl:mx-auto max-xl:justify-center max-xl:text-center">
              Hobbyista, filantrop, dżentelmen, a to tylko niektóre z moich
              przydomków. Tak naprawdę jestem tylko studentem informatyki.
              Zajmuję się głównie tworzeniem własnych projektów, które pomagają
              mi się rozwijać. W wolnym czasie tworzę strony internetowe.
              Programuję głównie w JavaScripcie/TypeScripcie, C++, Go oraz
              Javie, ale nie boję się poszerzania horyzontów. Mam nadzieję, że
              moja praca zostanie doceniona i czas spędzony w tym przytulnym
              zaułku internetu będzie dobrze zapamiętany i wykorzystany. Ta
              strona powstała jako pomocnicza stronka, która rozszerzy
              działalność mojego projektu na studia. To ja jestem tym przyjaznym
              Spider-Manem z sąsiedztwa. <br /> Pozdrawiam i podpisuję się pod
              tymi słowami:
              <img
                className="max-xl:mx-auto w-1/ rounded-xl mt-2 "
                src={gifSrc}
                alt="Spiderman"
                draggable="false"
                onMouseEnter={handleMouseEnter}
                onMouseLeave={handleMouseLeave}
              ></img>
              <img
                className="max-xl:mx-auto w-4/5 rounded-full "
                src="https://i.imgur.com/K3n9FPy.png"
                alt="Signature"
                draggable="false"
              ></img>
            </div>
          </div>
        </div>
      </Container>
    </section>
  );
};

export default AboutSection;
