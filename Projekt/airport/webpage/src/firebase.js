// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAuth, signOut } from "firebase/auth";
import { getFirestore } from "firebase/firestore";
import { getStorage } from "firebase/storage";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyCnBUT8Sdnkdv0OOdGZlVFzIAQKE-7UhSI",
  authDomain: "math-course-3d6ba.firebaseapp.com",
  projectId: "math-course-3d6ba",
  storageBucket: "math-course-3d6ba.appspot.com",
  messagingSenderId: "556063721",
  appId: "1:556063721:web:c485ac7682fbf205b78978",
  measurementId: "G-Q2YYSQ2CCH",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const auth = getAuth(app);
const db = getFirestore(app);
const storage = getStorage(app);
export { app, auth, db, storage };

export const handleLogout = () => {
  localStorage.removeItem("user");
  signOut(auth).catch((error) => {
    console.error(error);
  });
};
