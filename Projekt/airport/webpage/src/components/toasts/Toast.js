import React from "react";
import { motion } from "framer-motion";

const Toast = ({ message, closeToast }) => {
  return (
    <motion.div
      initial={{ y: -50, opacity: 0 }}
      animate={{ y: 0, opacity: 1 }}
      exit={{ y: -50, opacity: 0 }}
      id="SuccessToast-success"
      className="absolute top-16 flex items-center justify-center w-full max-w-xs p-4 mb-4"
      role="alert"
    >
      <div role="alert" className="alert">
        <svg
          xmlns="http://www.w3.org/2000/svg"
          className="stroke-current shrink-0 h-6 w-6"
          fill="none"
          viewBox="0 0 24 24"
        >
          <path
            strokeLinecap="round"
            strokeLinejoin="round"
            strokeWidth="2"
            d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z"
          />
        </svg>
        <span className="text-base">{message}</span>
        <button
          type="button"
          className="ml-auto -mx-1.5 -my-1.5  rounded-lg focus:ring-2 p-1.5  inline-flex items-center justify-center h-8 w-8 hover:text-white ring-0"
          data-dismiss-target="#SuccessToast-success"
          aria-label="Close"
          onClick={closeToast}
        >
          <svg
            className="w-3 h-3"
            aria-hidden="true"
            xmlns="http://www.w3.org/2000/svg"
            fill="none"
            viewBox="0 0 14 14"
          >
            <path
              stroke="currentColor"
              strokeLinecap="round"
              strokeLinejoin="round"
              strokeWidth="2"
              d="m1 1 6 6m0 0 6 6M7 7l6-6M7 7l-6 6"
            />
          </svg>
        </button>
      </div>
    </motion.div>
  );
};

export default Toast;
