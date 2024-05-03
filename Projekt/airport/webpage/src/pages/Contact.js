import React from "react";
import "katex/dist/katex.min.css";
import Navbar from "../components/navigation/Navbar";
import "../css/FAQ.css";
import ContactForm from "../components/components/ContactForm";
import { Footer } from "../components/sections/Footer";

export const Contact = () => {
  const handleContextMenu = (e) => {
    e.preventDefault();
  };

  return (
    <div onContextMenu={handleContextMenu}>
      <Navbar />
      <ContactForm />
      <Footer />
    </div>
  );
};
