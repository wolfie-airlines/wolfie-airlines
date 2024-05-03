import React from "react";
import AnimatedRoutes from "./components/routes/AnimatedRoutes";
import { useEffect } from "react";

function App() {
  useEffect(() => {
    const body = document.querySelector("body");
    body.style.overflowY = "auto";
  }, []);

  return <AnimatedRoutes />;
}

export default App;
