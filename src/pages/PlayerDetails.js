import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { db } from 'js/firebaseConfig.js'
import { collection, getDoc, doc } from 'firebase/firestore'

import './PlayerDetails.css';

function PlayerDetails() {

    // === Hooks === //
    
    const getPlayer = async (groupId, playerName) => {
        const playerRef = doc(db, `/Groups/${groupId}/Players`, playerName);
        const playerSnap = await getDoc(playerRef);

        if(playerSnap.exists()) {
            return {
                name: playerSnap.id,
                rank: playerSnap.data().Rank,
                gameCount: playerSnap.data().GameCount
            };
        } else {
            throw new Error('Player not found')
        }
    }

    const usePlayer = (groupId, playerName) => {
        const [player, setPlayer] = useState([]);

        useEffect(() => {
            const fetchPlayer = async () => {
                const player = await getPlayer(groupId, playerName);
                setPlayer(player);
            }
            fetchPlayer();
        }, []);
        return { player };
    } 

    const { groupId, playerName } = useParams();
    const { player } = usePlayer(groupId, playerName)

    // === HTML === //

    return (
        <div className="PlayerDetails">
            <h1> Page in development </h1>
            <p>Player: {player.name}</p>
            <p>Player Rank: {player.rank}</p>
            <p>Player Games: {player.gameCount}</p>
        </div>
    );
}

export default PlayerDetails;
