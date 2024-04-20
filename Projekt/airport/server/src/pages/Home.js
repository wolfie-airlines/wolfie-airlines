import React, { memo } from "react";
import "../css/Home.css";
import { motion } from "framer-motion";
import World from "../components/components/Globe";
import { sampleArcs } from "../components/imports/sampleArcs";
import { globeConfig } from "../components/imports/globeConfig";
import Nav from "../components/navigation/Navbar";
import { Footer } from "../components/components/Footer";
const Home = () => {
  return (
    <div>
      <Nav />

      <div className="flex flex-row items-center justify-center py-20 h-screen md:h-auto dark:bg-black bg-white relative w-full">
        <div className="max-w-7xl mx-auto w-full relative overflow-hidden h-full md:h-[40rem] px-4">
          <motion.div
            initial={{
              opacity: 0,
              y: 20,
            }}
            animate={{
              opacity: 1,
              y: 0,
            }}
            transition={{
              duration: 1,
            }}
            className="div"
          >
            <h2 className="text-center text-xl md:text-4xl font-bold text-black dark:text-white">
              Poleć gdzie chcesz. Kiedy chcesz.
            </h2>
            <p className="text-center font-inter font-semibold text-base md:text-lg text-neutral-700 dark:text-neutral-200 max-w-md mt-2 mx-auto">
              Wybierz <span className="text-blue-500">Wolfie Airlines</span> z
              niepowtarzalnym lotniskiem{" "}
              <span className="text-blue-500">Wolfie Airport</span> i ciesz się
              niesamowitymi podróżami.
            </p>
          </motion.div>
          <div className="absolute w-full bottom-0 inset-x-0 h-40 bg-gradient-to-b pointer-events-none select-none from-transparent dark:to-black to-white z-40" />
          <div className="absolute w-full -bottom-20 h-72 md:h-full z-10">
            <World data={sampleArcs} globeConfig={globeConfig} />;
          </div>
        </div>
      </div>
      <Footer />
    </div>
  );
};

export default memo(Home);
