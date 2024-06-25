import { app, analytics } from './firebaseConfig';
import { collection, getDocs } from 'firebase/firestore';
import { getFirestore } from "firebase/firestore";

// Initialize Firestore
const db = getFirestore(app);

// query Firestore and log the results
export const queryFirestore = async () => {
    try {
        const querySnapshot = await getDocs(collection(db, "/Groups/uYmHldpJVY2K0uiEH99L/Players"));
        querySnapshot.forEach((doc) => {
            console.log(`Name: ${doc.id}, Rank: ${doc.data().Rank}`);
        });
    } catch (error) {
        console.error("Error querying Firestore: ", error);
    }
};