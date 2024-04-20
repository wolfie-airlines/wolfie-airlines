// App.js
import React from "react";
import AnimatedRoutes from "./components/routes/AnimatedRoutes";
import { useEffect } from "react";
import { auth, db } from "./firebase";
import { useNavigate } from "react-router-dom";
import { collection, getDocs, query, where } from "@firebase/firestore";

function App() {
  const navigate = useNavigate();
  useEffect(() => {
    const body = document.querySelector("body");
    body.style.overflowY = "auto";

    const fetchData = async (user, userQuery, notifications) => {
      const userSnapshot = await getDocs(userQuery);

      if (!userSnapshot.empty) {
        const userDocs = userSnapshot.docs[0].data();

        let userCookie = localStorage.getItem("user");
        if (!userCookie) {
          if (!user) return navigate("/");
          userCookie = JSON.stringify(userDocs);
          localStorage.setItem("user", userCookie);
        }

        if (userDocs.notifications) {
          // Subtract notifications that have already been read
          let readNotif = notifications.filter(
            (notif) => !userDocs.notifications.read.includes(notif.id)
          );

          if (readNotif.length !== 0) {
            localStorage.setItem("messagesToRead", true);

            // Get user from cookies
            let userCookie = localStorage.getItem("user");
            userCookie = JSON.parse(userCookie);

            // Create an updated object with new notifications
            const updatedUser = {
              ...userCookie,
              notifications: [...readNotif],
            };

            // Save the updated user object in localStorage
            localStorage.setItem("user", JSON.stringify(updatedUser));
          }
        } else {
          // If no notifications, set messagesToRead to true
          localStorage.setItem("messagesToRead", true);

          // Get user from cookies
          let userCookie = localStorage.getItem("user");
          userCookie = JSON.parse(userCookie);

          // Create an updated object with new notifications
          const updatedUser = {
            ...userCookie,
            notifications: [...notifications],
          };

          // Save the updated user object in localStorage
          localStorage.setItem("user", JSON.stringify(updatedUser));
        }
      }
    };

    const unsubscribe = auth.onAuthStateChanged(async (user) => {
      if (!user) return;

      const q = query(collection(db, "notifications"));
      const querySnapshot = await getDocs(q);

      let notifications = [];
      querySnapshot.forEach((doc) => {
        notifications.push({ ...doc.data() });
      });

      notifications = notifications.filter((notif) => notif.active === true);

      const userQuery = query(
        collection(db, "users"),
        where("userId", "==", auth.currentUser.uid)
      );

      setTimeout(() => {
        fetchData(user, userQuery, notifications);
      }, 1000);
    });

    return () => {
      unsubscribe();
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return <AnimatedRoutes />;
}

export default App;
