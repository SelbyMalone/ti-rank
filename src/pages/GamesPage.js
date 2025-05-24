import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { db } from 'js/firebaseConfig.js';
import { getRankColor } from 'js/getRankColor.js';
import { collection, getDocs } from 'firebase/firestore';

import './GamesPage.css';

import Sidebar from 'components/Sidebar';

function GamesPage() {
    
    // === Hooks === //

    // query Firestore and log the results
    const getPlayers = async (group) => {
        try {
            const querySnapshot = await getDocs(collection(db, `/Groups/${group}/Players`));
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

    const usePlayers = (group) => {
        const [rankedPlayers, setRankedPlayers] = useState([]);
        const [unrankedPlayers, setUnrankedPlayers] = useState([]);

        useEffect(() => {
            const fetchPlayers = async () => {
                const { ranked, unranked } = await getPlayers(group);

                //sort out players by rank
                ranked.sort((a, b) => b.rank - a.rank);
                unranked.sort((a, b) => {
                    if (b.gameCount !== a.gameCount) {
                        return b.gameCount - a.gameCount;
                    }
                    return b.rank - a.rank;
                });
                setRankedPlayers(ranked);
                setUnrankedPlayers(unranked);
            }

            fetchPlayers();
        }, []);

        return { rankedPlayers, unrankedPlayers };
    }

    const { groupId } = useParams()
    const { rankedPlayers, unrankedPlayers } = usePlayers(groupId);

    // === HTML === //

    return (
        <div className="app row-flex">
            <div className="main-content">
                <div className="header">
                    Game History
                </div>
                main content
            </div>
            <Sidebar className="Sidebar" rankedPlayers={rankedPlayers} unrankedPlayers={unrankedPlayers}/>
      </div>
    );
}

export default GamesPage;
