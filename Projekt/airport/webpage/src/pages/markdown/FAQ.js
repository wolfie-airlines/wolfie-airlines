import React from "react";
import Navbar from "../../components/navigation/Navbar";
import "../../css/FAQ.css";
// import QuestionsComponent from "../../components/components/QuestionsComponent";
import { Footer } from "../../components/components/Footer";

export const FAQ = () => {
  const handleContextMenu = (e) => {
    e.preventDefault();
  };

  return (
    <div onContextMenu={handleContextMenu}>
      <Navbar />
      {/* <QuestionsComponent /> */}
      <Footer />
    </div>
  );
};
