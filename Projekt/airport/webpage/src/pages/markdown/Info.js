import React, { memo } from "react";
import Navbar from "../../components/navigation/Navbar";
import AboutSection from "../../components/sections/AboutSection";
import { Footer } from "../../components/sections/Footer";
import { BackgroundBeams } from "../../components/effects/BackgroundBeams";

const Info = () => {
  return (
    <div>
      <BackgroundBeams />
      <Navbar />
      <AboutSection />
      <Footer />
    </div>
  );
};

export default memo(Info);
