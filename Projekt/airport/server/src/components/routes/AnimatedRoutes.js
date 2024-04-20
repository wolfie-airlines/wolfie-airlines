import React from "react";
import { Route, Routes, useLocation } from "react-router-dom";
import Home from "../../pages/Home";
import Info from "../../pages/markdown/Info";
import { FAQ } from "../../pages/markdown/FAQ";
import NotFound from "../../pages/errors/404";
import { Maintainance } from "../../pages/errors/Maintainance";
import { Error } from "../../pages/errors/Error";
import { Sparrow } from "../navigation/Sparrow";
function AnimatedRoutes() {
  const location = useLocation();

  return (
    <div className="font-inter">
      <Routes location={location} key={location.pathname}>
        <Route path="*" element={<NotFound />} />
        <Route path="/" element={<Home />} />
        <Route path="/home" element={<Home />} />
        <Route path="/faq" element={<FAQ />} />
        <Route path="/not-yet" element={<Maintainance />} />
        <Route path="/info" element={<Info />} />
        <Route path="/sparrow" element={<Sparrow />} />
        <Route path="/error/:errorMessage/:errorType" element={<Error />} />
      </Routes>
    </div>
  );
}

export default AnimatedRoutes;
