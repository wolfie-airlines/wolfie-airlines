import { useNavigate } from "react-router-dom";

const FAQLoader = () => {
  const navigate = useNavigate();
  return (
    <section className="-mt-16 relative z-20 overflow-hidden pt-20 pb-12 lg:pt-[120px] lg:pb-[90px]">
      <div className="container mx-auto">
        <div className="-mx-4 flex flex-wrap">
          <div className="w-full px-4">
            <div className="mx-auto mb-[60px] max-w-[520px] text-center lg:mb-10">
              <span className="mb-2 block text-4xl font-semibold text-main">
                FAQ
              </span>
              <h2 className="mb-4 text-3xl font-bold text-unWhite sm:text-4xl md:text-[40px]">
                Masz jakieś pytania? <br /> Zajrzyj tutaj
              </h2>
              <p className="font-betterDisplay text-unWhite">
                Na większość pytań, które użytkownik jest w stanie zadać -
                odpowiedź już się znajduje. Jeśli jednak odpowiedź na Twoje
                pytanie nie została znaleziona, zapraszam do kontaktu{" "}
                <span
                  onClick={() => navigate("/contact")}
                  className="text-main font-bold cursor-pointer"
                >
                  tutaj
                </span>
                .
              </p>
            </div>
          </div>
        </div>

        <div className="-mx-4 max-md:-mx-1">
          <div className="w-full px-4 max-lg:items-center max-lg:justify-center max-lg:flex">
            <div className=" mb-[20px] max-w-[520px] text-start max-lg:text-center lg:mb-4">
              <h2 className="mb-8 text-4xl tracking-tight font-extrabold text-white">
                <div
                  role="status"
                  className="space-y-8 animate-pulse md:space-y-0 md:space-x-8 md:flex md:items-center"
                >
                  <div className="w-full">
                    <div className="h-4  rounded-full bg-gray-400 w-48 -mb-2"></div>
                  </div>
                  <span className="sr-only">Loading...</span>
                </div>
              </h2>
              <div className="grid pt-8 border-t  md:gap-16 border-gray-700 md:grid-cols-1" />
            </div>
          </div>
        </div>

        <div className="-mx-4 flex flex-wrap">
          {[1, 2, 3, 4].map((index) => (
            <div
              className={`w-full px-4 lg:w-1/2 ${
                index % 2 === 0 ? "" : "lg:order-last"
              }`}
              key={index}
            >
              <AccordionItem />
            </div>
          ))}
        </div>
      </div>
    </section>
  );
};

const AccordionItem = () => {
  return (
    <div className="single-faq mb-8 w-full rounded-lg border border-gray-600 bg-gray-800 p-4 sm:p-8 lg:px-6 xl:px-8">
      <button className={`faq-btn flex w-full text-left`}>
        <div
          initial={{ rotate: 0 }}
          animate={{ rotate: 0 }}
          transition={{ duration: 0.2 }}
          className="mr-5 flex h-10 w-full max-w-[40px] items-center justify-center rounded-lg bg-main bg-opacity-10 text-info"
        >
          <svg
            className={`duration-200 ease-in-out fill-main stroke-main`}
            width="17"
            height="10"
            viewBox="0 0 17 10"
            xmlns="http://www.w3.org/2000/svg"
          >
            <path
              d="M7.28687 8.43257L7.28679 8.43265L7.29496 8.43985C7.62576 8.73124 8.02464 8.86001 8.41472 8.86001C8.83092 8.86001 9.22376 8.69083 9.53447 8.41713L9.53454 8.41721L9.54184 8.41052L15.7631 2.70784L15.7691 2.70231L15.7749 2.69659C16.0981 2.38028 16.1985 1.80579 15.7981 1.41393C15.4803 1.1028 14.9167 1.00854 14.5249 1.38489L8.41472 7.00806L2.29995 1.38063L2.29151 1.37286L2.28271 1.36548C1.93092 1.07036 1.38469 1.06804 1.03129 1.41393L1.01755 1.42738L1.00488 1.44184C0.69687 1.79355 0.695778 2.34549 1.0545 2.69659L1.05999 2.70196L1.06565 2.70717L7.28687 8.43257Z"
              fill=""
              stroke=""
            />
          </svg>
        </div>

        <div className="w-full">
          <h4 className="text-lg font-semibold text-gray-200">
            <div
              role="status"
              className="space-y-8 animate-pulse md:space-y-0 md:space-x-8 md:flex md:items-center"
            >
              <div className="w-full">
                <div className="h-4  rounded-full bg-gray-400 w-48 mt-3"></div>
              </div>
              <span className="sr-only">Ładowanie pytań...</span>
            </div>
          </h4>
        </div>
      </button>
    </div>
  );
};

export default FAQLoader;
