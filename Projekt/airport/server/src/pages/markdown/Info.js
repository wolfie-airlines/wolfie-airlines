import React, { memo } from "react";
import Navbar from "../../components/navigation/Navbar";
import "../../css/AboutMe.css";
import AboutSection from "../../components/sections/AboutSection";
import { Footer } from "../../components/components/Footer";

const Info = () => {
  return (
    <div>
      <Navbar />
      <AboutSection />
      <Footer />
    </div>
  );
};

export default memo(Info);
