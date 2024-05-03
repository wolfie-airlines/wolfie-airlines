export function generateGateNumber() {
  return Math.floor(Math.random() * 30) + 1;
}

export function generateCardBoardNumber() {
  let cardBoardNumber = "";
  for (let i = 0; i < 20; i++) {
    cardBoardNumber += Math.floor(Math.random() * 9) + 1;
  }
  cardBoardNumber += String.fromCharCode(Math.floor(Math.random() * 26) + 65);
  return cardBoardNumber;
}
