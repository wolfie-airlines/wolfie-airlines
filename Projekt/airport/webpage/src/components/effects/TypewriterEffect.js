import { motion } from "framer-motion";
import React from "react";

const TypewriterEffectSmooth = ({ words }) => {
  const wordsArray = words.map((word) => {
    return {
      ...word,
      text: word.text.split(" "),
    };
  });

  const renderWords = () => {
    try {
      return wordsArray.map((word, idx) => {
        let renderedChars = word.text.map((char, index) => (
          <span key={`char-${index}`} className={`dark:text-white text-black `}>
            {char}
          </span>
        ));

        // Usuń białe znaki na końcu słowa
        while (renderedChars[renderedChars.length - 1].props.children === " ") {
          renderedChars.pop();
        }

        return (
          <div key={`word-${idx}`} className="inline-block">
            {renderedChars}
            <span>&nbsp;</span>
          </div>
        );
      });
    } catch (error) {
      console.error(error);
      return null;
    }
  };

  try {
    return (
      <div className={"flex space-x-1 my-6"}>
        <motion.div
          className="overflow-hidden pb-2"
          initial={{ width: "0%" }}
          animate={{ width: "fit-content" }}
          transition={{ duration: 2, ease: "linear", delay: 1 }}
        >
          <div
            className="text-xs sm:text-base md:text-xl lg:text:3xl xl:text-5xl font-bold"
            style={{ whiteSpace: "nowrap" }}
          >
            {renderWords()}
          </div>
        </motion.div>
        <motion.span
          initial={{ opacity: 0 }}
          animate={{ opacity: 1 }}
          transition={{
            duration: 0.8,
            repeat: Infinity,
            repeatType: "reverse",
          }}
          className={"block rounded-sm w-[4px] h-4 sm:h-6 xl:h-12 bg-blue-500"}
        ></motion.span>
      </div>
    );
  } catch (error) {
    console.error(error);
    return null;
  }
};

export default TypewriterEffectSmooth;
