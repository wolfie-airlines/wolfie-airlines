import React from "react";
import { Route, Routes, useLocation } from "react-router-dom";
import Home from "../../pages/Home";
import Info from "../../pages/markdown/Info";
import NotFound from "../../pages/errors/404";
import { Sparrow } from "../navigation/Sparrow";
import { Checkin } from "../../pages/Checkin";
import { CheckinParams } from "../../pages/CheckinParams";
function AnimatedRoutes() {
  const location = useLocation();

  return (
    <div className="font-inter">
      <Routes location={location} key={location.pathname}>
        <Route path="*" element={<NotFound />} />
        <Route path="/" element={<Home />} />
        <Route path="/home" element={<Home />} />
        <Route path="/info" element={<Info />} />
        <Route path="/odprawy" element={<Checkin />} />
        <Route
          path="/odprawy/:username/:email/:flightId/:seats"
          element={<CheckinParams />}
        />
        <Route path="/sparrow" element={<Sparrow />} />
      </Routes>
    </div>
  );
}

export default AnimatedRoutes;
