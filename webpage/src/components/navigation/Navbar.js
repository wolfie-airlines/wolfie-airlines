import { useState } from "react";
import Container from "../components/Container";
import { useLocation, useNavigate } from "react-router-dom";

const Navbar = () => {
  const [isMobileMenuOpen, setMobileMenuOpen] = useState(false);
  const navigate = useNavigate();
  const location = useLocation();
  const toggleMobileMenu = () => {
    setMobileMenuOpen(!isMobileMenuOpen);
  };
  const isActive = (path) => {
    return location.pathname === path ? "text-white" : "";
  };

  return (
    <nav className="z-[9997] w-full mt-5 firefox:font-inter">
      <Container>
        <div className="flex flex-wrap items-center justify-between py-2 gap-6 md:py-4 md:gap-0 relative xl:bg-slate-900 xl:rounded-2xl xl:border xl:border-slate-700">
          <input
            aria-hidden="true"
            type="checkbox"
            name="toggle_nav"
            id="toggle_nav"
            className="hidden peer"
            checked={isMobileMenuOpen}
            onChange={toggleMobileMenu}
          />
          <div className="relative z-[9996] w-full flex justify-between xl:w-max md:px-0">
            <button
              onClick={() => navigate("/")}
              aria-label="logo"
              className="flex space-x-2 items-center"
            >
              <div aria-hidden="true" className="flex space-x-1">
                <img
                  draggable="false"
                  className="w-14 h-14 rounded-full ml-5"
                  src="https://i.imgur.com/MLlNSm4.png"
                  alt="logo"
                />
              </div>
              <span className="text-2xl max-md:text-xl font-bold text-white">
                Wolfie Airlines
              </span>
            </button>

            <div className="z-[9995] relative flex items-center xl:hidden max-h-10">
              <label
                role="button"
                htmlFor="toggle_nav"
                aria-label="hamburger"
                id="hamburger"
                className="relative  p-6 -mr-6"
              >
                <div
                  aria-hidden="true"
                  id="line"
                  className={`m-auto h-0.5 w-5 rounded bg-gray-300 transition duration-300 ${
                    isMobileMenuOpen
                      ? "rotate-[45deg] transform translate-y-[5px]"
                      : ""
                  }`}
                ></div>

                <div
                  aria-hidden="true"
                  id="line2"
                  className={`m-auto mt-2 h-0.5 w-5 rounded bg-gray-300 transition duration-300 ${
                    isMobileMenuOpen
                      ? "-rotate-[45deg] transform -translate-y-[5px]"
                      : ""
                  }
                  `}
                ></div>
              </label>
            </div>
          </div>
          <div
            aria-hidden="true"
            className={`fixed z-[99] opacity-80 inset-0 h-screen w-screen  backdrop-blur-2xl origin-bottom scale-y-0 transition duration-500 peer-checked:origin-top peer-checked:scale-y-100 xl:hidden bg-gray-900/70 ${
              isMobileMenuOpen ? "origin-top scale-y-100" : ""
            }`}
          ></div>
          <div
            className={`flex-col z-[9994] flex-wrap gap-6 p-8 rounded-3xl border  shadow-gray-600/10 justify-end w-full invisible opacity-0 translate-y-1 absolute top-full left-0 transition-all duration-300 scale-95 origin-top 
                        xl:relative xl:scale-100 xl:peer-checked:translate-y-0 xl:translate-y-0 xl:flex xl:flex-row xl:items-center xl:gap-0 xl:p-0 xl:bg-transparent xl:w-7/12 xl:visible xl:opacity-100 xl:border-none
                        peer-checked:scale-100 peer-checked:opacity-100 peer-checked:visible xl:shadow-none 
                        shadow-none bg-slate-900 border-slate-700 ${
                          isMobileMenuOpen
                            ? "visible opacity-100 scale-100 z-[9994]"
                            : ""
                        }`}
          >
            <div className="text-gray-300 xl:pr-4 xl:w-auto w-full xl:pt-0">
              <ul
                className="tracking-wide font-semibold flex-col flex xl:flex-row gap-6 xl:gap-0 xl:justify-center xl:text-center
                                xl:items-center
                                xl:space-x-4 xl:space-y-0 space-y-4 xl:whitespace-nowrap xl:text-xl"
              >
                <li>
                  <button
                    onClick={() => navigate("/home")}
                    className={`block md:px-4 transition hover:text-unWhite ${isActive(
                      "/home"
                    )}`}
                  >
                    <span>Strona główna</span>
                  </button>
                </li>
                <li>
                  <button
                    onClick={() => navigate("/odprawy")}
                    className={`block md:px-4 transition hover:text-unWhite ${isActive(
                      "/odprawy"
                    )}`}
                  >
                    <span>Odprawy</span>
                  </button>
                </li>
                <li>
                  <button
                    onClick={() => navigate("/info")}
                    className={`block md:px-4 transition hover:text-unWhite ${isActive(
                      "/info"
                    )}`}
                  >
                    <span>O autorze</span>
                  </button>
                </li>
              </ul>
            </div>
          </div>
        </div>
      </Container>
    </nav>
  );
};

export default Navbar;
