import React, { memo } from "react";
import Navbar from "../../components/navigation/Navbar";
import "../../css/AboutMe.css";
import AboutSection from "../../components/sections/AboutSection";
import { Footer } from "../../components/components/Footer";
import { BackgroundBeams } from "../../components/components/BackgroundBeams";

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
