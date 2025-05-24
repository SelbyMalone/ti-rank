import { app, analytics } from './firebaseConfig';
import { collection, getDocs } from 'firebase/firestore';
import { getFirestore } from "firebase/firestore";

// Initialize Firestore
const db = getFirestore(app);
