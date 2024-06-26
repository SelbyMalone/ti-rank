import { app, analytics } from './firebaseConfig';
import { collection, getDocs } from 'firebase/firestore';
import { getFirestore } from "firebase/firestore";
import { useEffect, useState } from 'react';

// Initialize Firestore
const db = getFirestore(app);

// query Firestore and log the results
const getPlayers = async () => {
    try {
        const querySnapshot = await getDocs(collection(db, "/Groups/uYmHldpJVY2K0uiEH99L/Players"));
        const ranked = []; //ranked meaning they have 3 or more games recorded
        const unranked = []; //unranked meaning they have less then 3 games recorded

        querySnapshot.forEach((doc) => {
            const playerData = { name: doc.id, rank: doc.data().Rank, gameCount: doc.data().GameCount };
            if (playerData.gameCount >= 3) {
                ranked.push(playerData);
            } else {
                unranked.push(playerData);
            }
        });
        return { ranked, unranked };
    } catch (error) {
        console.error("Error querying Firestore: ", error);
    }
};

export const usePlayers = () => {
    const [rankedPlayers, setRankedPlayers] = useState([]);
    const [unrankedPlayers, setUnrankedPlayers] = useState([]);

    useEffect(() => {
        const fetchPlayers = async () => {
            const { ranked, unranked } = await getPlayers();

            //sort out players by rank
            ranked.sort((a, b) => b.rank - a.rank);

            setRankedPlayers(ranked);
            setUnrankedPlayers(unranked);
        }

        fetchPlayers();
    }, []);

    return { rankedPlayers, unrankedPlayers };
}