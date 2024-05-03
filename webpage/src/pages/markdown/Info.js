import React, { memo } from "react";
import Navbar from "../../components/navigation/Navbar";
import AboutSection from "../../components/sections/AboutSection";
import { Footer } from "../../components/sections/Footer";

const Info = () => {
  return (
    <div className="dark:bg-dot-white/[0.2] bg-dot-black/[0.2]">
      <Navbar />
      <AboutSection />
      <Footer />
    </div>
  );
};

export default memo(Info);
